import copy
import logging
from datetime import date, datetime, time
from pathlib import Path
from typing import Any

import yaml


class ConfigError(ValueError):
    pass


_MISSING = object()
_CONFIG_NAMES = ("endstone-global.yml", "endstone-world-defaults.yml")
_LEGACY_NAMES = {
    "endstone-global.yml": ("paper-global.yml", "paper-global.default.yml"),
    "endstone-world-defaults.yml": ("paper-world-defaults.yml", "paper-world-defaults.default.yml"),
}
_DISABLED_SENTINEL_PATHS = frozenset(
    {
        "item-validation.book-size.page-max",
        "environment.void-damage-amount",
        "spam-limiter.incoming-packet-threshold",
    }
)
_NUMERIC_OR_DEFAULT_PATHS = frozenset({"entities.spawning.monster-spawn-max-light-level"})
_NUMERIC_OR_DISABLED_PATHS = frozenset({"environment.nether-ceiling-void-damage-height"})


def _normalize_default(value: Any) -> Any:
    if isinstance(value, dict):
        if "default" in value:
            return _normalize_default(value["default"])
        return {key: normalized for key, item in value.items() if (normalized := _normalize_default(item)) is not None}
    if isinstance(value, list):
        return [_normalize_default(item) for item in value]
    if isinstance(value, str):
        try:
            parsed = yaml.safe_load(value)
        except yaml.YAMLError:
            return value
        if isinstance(parsed, (bool, int, float, list)) and not isinstance(parsed, dict):
            return parsed
    return value


def defaults_only(node: Any) -> Any:
    return copy.deepcopy(_normalize_default(node))


def _type_name(value: Any) -> str:
    if value is _MISSING:
        return "missing"
    if value is None:
        return "null"
    if isinstance(value, dict):
        return "mapping"
    if isinstance(value, list):
        return "list"
    if isinstance(value, bool):
        return "bool"
    if isinstance(value, int):
        return "int"
    if isinstance(value, float):
        return "float"
    if isinstance(value, str):
        return "string"
    return type(value).__name__


def merge_defaults(defaults: Any, current: Any = _MISSING, path: str = "") -> Any:
    if isinstance(defaults, dict):
        if current is _MISSING:
            result = {}
        elif not isinstance(current, dict):
            raise ConfigError(f"Invalid type at {path or '<root>'}: expected mapping, got {_type_name(current)}")
        else:
            result = copy.deepcopy(current)
        for key, value in defaults.items():
            child_path = f"{path}.{key}" if path else key
            result[key] = merge_defaults(value, result.get(key, _MISSING), child_path)
        return result

    if current is _MISSING:
        return copy.deepcopy(defaults)
    if current == "disabled" and path in _DISABLED_SENTINEL_PATHS:
        return current
    if (
        path in _NUMERIC_OR_DEFAULT_PATHS
        and defaults == "default"
        and isinstance(current, (int, float))
        and not isinstance(current, bool)
    ):
        return current
    if (
        path in _NUMERIC_OR_DISABLED_PATHS
        and defaults == "disabled"
        and isinstance(current, (int, float))
        and not isinstance(current, bool)
    ):
        return current
    if defaults is None:
        if current is None:
            return None
        raise ConfigError(f"Invalid type at {path}: expected null, got {_type_name(current)}")
    if current is None:
        raise ConfigError(f"Invalid type at {path}: expected {_type_name(defaults)}, got null")
    if isinstance(defaults, bool):
        if not isinstance(current, bool):
            raise ConfigError(f"Invalid type at {path}: expected bool, got {_type_name(current)}")
    elif isinstance(defaults, int) and (not isinstance(current, int) or isinstance(current, bool)):
        raise ConfigError(f"Invalid type at {path}: expected int, got {_type_name(current)}")
    elif isinstance(defaults, float) and (not isinstance(current, (int, float)) or isinstance(current, bool)):
        raise ConfigError(f"Invalid type at {path}: expected float, got {_type_name(current)}")
    elif isinstance(defaults, str) and not isinstance(current, str):
        raise ConfigError(f"Invalid type at {path}: expected string, got {_type_name(current)}")
    if isinstance(defaults, list):
        if not isinstance(current, list):
            raise ConfigError(f"Invalid type at {path}: expected list, got {_type_name(current)}")
        return _merge_list(defaults, current, path)
    return current


def _matches_list_item(default: Any, current: Any) -> bool:
    if default is None:
        return current is None
    if current is None:
        return False
    if isinstance(default, dict):
        if not isinstance(current, dict):
            return False
        return all(key not in current or _matches_list_item(value, current[key]) for key, value in default.items())
    if isinstance(default, list):
        if not isinstance(current, list):
            return False
        if not default:
            return True
        return all(_matches_list_item(default[0], item) for item in current)
    if isinstance(default, bool):
        return isinstance(current, bool)
    if isinstance(default, int):
        return isinstance(current, int) and not isinstance(current, bool)
    if isinstance(default, float):
        return isinstance(current, (int, float)) and not isinstance(current, bool)
    if isinstance(default, str):
        return isinstance(current, str)
    return isinstance(current, type(default))


def _merge_list(defaults: list[Any], current: list[Any], path: str) -> list[Any]:
    if not defaults:
        return copy.deepcopy(current)
    merged = []
    for index, item in enumerate(current):
        default = next((candidate for candidate in defaults if _matches_list_item(candidate, item)), defaults[0])
        merged.append(merge_defaults(default, item, f"{path}[{index}]"))
    return merged


def load_yaml(path: Path) -> dict[str, Any]:
    try:
        with path.open(encoding="utf-8") as file:
            text = file.read()
        value = yaml.safe_load(text)
        if value is None and not text.strip():
            value = {}
    except (OSError, yaml.YAMLError) as error:
        raise ConfigError(f"Invalid YAML in {path}: {error}") from error
    if not isinstance(value, dict):
        raise ConfigError(f"Invalid YAML root in {path}: expected mapping")
    return value


def sync_yaml(path: Path, defaults: dict[str, Any]) -> dict[str, Any]:
    current = load_yaml(path) if path.exists() else {}
    merged = merge_defaults(defaults, current)
    path.parent.mkdir(parents=True, exist_ok=True)
    with path.open("w", encoding="utf-8", newline="\n") as file:
        yaml.safe_dump(merged, file, sort_keys=False, allow_unicode=True, default_flow_style=False)
    return merged


def _toml_value(value: Any, path: str, tomlkit: Any) -> Any:
    if value is None:
        raise ConfigError(f"Invalid TOML value at {path or '<root>'}: null is not supported")
    if isinstance(value, tomlkit.items.Item):
        return value
    if isinstance(value, dict):
        table = tomlkit.table()
        for key, item in value.items():
            child_path = f"{path}.{key}" if path else str(key)
            table[key] = _toml_value(item, child_path, tomlkit)
        return table
    if isinstance(value, list):
        if value and all(isinstance(item, dict) for item in value):
            array_of_tables = tomlkit.aot()
            for index, item in enumerate(value):
                table = tomlkit.table()
                for key, child in item.items():
                    child_path = f"{path}[{index}].{key}" if path else f"[{index}].{key}"
                    table[key] = _toml_value(child, child_path, tomlkit)
                array_of_tables.append(table)
            return array_of_tables
        array = tomlkit.array()
        for index, item in enumerate(value):
            child_path = f"{path}[{index}]" if path else f"[{index}]"
            converted = _toml_value(item, child_path, tomlkit)
            if isinstance(converted, (tomlkit.items.Table, tomlkit.items.InlineTable, tomlkit.items.AoT)):
                raise ConfigError(f"Invalid TOML value at {child_path}: mapping lists must contain mappings only")
            array.append(converted)
        return array
    if isinstance(value, (str, bool, int, float, date, datetime, time)):
        return tomlkit.item(value)
    try:
        return tomlkit.item(value)
    except (TypeError, ValueError, tomlkit.exceptions.ConvertError) as error:
        raise ConfigError(f"Invalid TOML value at {path or '<root>'}: {_type_name(value)}") from error


def sync_toml(path: Path, global_values: dict[str, Any], world_values: dict[str, Any]) -> None:
    import tomlkit

    try:
        if path.exists():
            with path.open("r", encoding="utf-8") as file:
                document = tomlkit.load(file)
        else:
            document = tomlkit.document()
    except (OSError, tomlkit.exceptions.ParseError) as error:
        raise ConfigError(f"Invalid TOML in {path}: {error}") from error

    paper = document.get("paper")
    if paper is None:
        paper = tomlkit.table()
        document["paper"] = paper
    elif isinstance(paper, tomlkit.items.InlineTable):
        table = tomlkit.table()
        for key, value in paper.items():
            table[key] = value
        paper = table
        document["paper"] = paper
    elif not isinstance(paper, tomlkit.items.Table):
        raise ConfigError("Invalid TOML value at paper: expected mapping")

    paper["global"] = _toml_value(global_values, "paper.global", tomlkit)
    paper["world_defaults"] = _toml_value(world_values, "paper.world_defaults", tomlkit)
    path.parent.mkdir(parents=True, exist_ok=True)
    try:
        with path.open("w", encoding="utf-8", newline="\n") as file:
            tomlkit.dump(document, file)
    except (OSError, tomlkit.exceptions.ConvertError) as error:
        raise ConfigError(f"Unable to write TOML in {path}: {error}") from error


def _resource_path(package_path: Path, name: str) -> Path:
    candidates = (package_path / name, *(package_path / legacy for legacy in _LEGACY_NAMES[name]))
    for candidate in candidates:
        if candidate.is_file():
            return candidate
    raise ConfigError(f"Missing packaged configuration resource: {name}")


def _migrate_legacy_config(config_path: Path, legacy_path: Path, name: str) -> None:
    destination = config_path / name
    if destination.exists():
        return
    candidates = [legacy_path / name, *(legacy_path / old_name for old_name in _LEGACY_NAMES[name])]
    candidates.append(config_path / _LEGACY_NAMES[name][0])
    for source in candidates:
        if not source.exists():
            continue
        if not source.is_file():
            raise ConfigError(f"Invalid legacy configuration path: {source}")
        destination.parent.mkdir(parents=True, exist_ok=True)
        source.replace(destination)
        return


def prepare_paper_configs(
    server_path: Path, package_path: Path | None = None, logger: logging.Logger | None = None
) -> tuple[dict[str, Any], dict[str, Any]]:
    package_path = Path(package_path) if package_path is not None else Path(__file__).resolve().parents[1] / "config"
    if not any((package_path / name).is_file() for name in _CONFIG_NAMES) and (package_path / "config").is_dir():
        package_path = package_path / "config"
    global_defaults = defaults_only(load_yaml(_resource_path(package_path, "endstone-global.yml")))
    world_defaults = defaults_only(load_yaml(_resource_path(package_path, "endstone-world-defaults.yml")))
    server_path = Path(server_path)
    config_path = server_path / "config"
    global_path = config_path / "endstone-global.yml"
    world_path = config_path / "endstone-world-defaults.yml"
    legacy_path = server_path / "server" / "config"
    for name in _CONFIG_NAMES:
        _migrate_legacy_config(config_path, legacy_path, name)
    try:
        legacy_path.rmdir()
    except OSError:
        pass
    result = (sync_yaml(global_path, global_defaults), sync_yaml(world_path, world_defaults))
    sync_toml(server_path / "endstone.toml", result[0], result[1])
    if logger:
        logger.info("Synchronized Endstone Paper configuration defaults")
    return result
