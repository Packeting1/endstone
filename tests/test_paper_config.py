import sys
from pathlib import Path

import pytest
import yaml

sys.path.insert(0, str(Path(__file__).parents[1]))

from endstone.cli.paper_config import (
    ConfigError,
    merge_defaults,
    prepare_paper_configs,
    sync_toml,
)

PACKAGE = Path(__file__).parents[1] / "endstone" / "config"


def leaf_count(value):
    if isinstance(value, dict):
        return sum(leaf_count(item) for item in value.values())
    if isinstance(value, list):
        return sum(leaf_count(item) for item in value)
    return 1


def test_resources_are_mappings_and_paths_are_stable():
    expected_leaves = {"endstone-global.yml": 93, "endstone-world-defaults.yml": 224}
    for name, expected_leaf_count in expected_leaves.items():
        path = PACKAGE / name
        text = path.read_text(encoding="utf-8")
        value = yaml.safe_load(text)
        assert "<!doctype html>" not in text.lower()
        assert isinstance(value, dict)
        assert leaf_count(value) == expected_leaf_count
        assert len(value) >= 18


def test_prepare_creates_targets_and_syncs_paper_values(tmp_path):
    value = yaml.safe_load((PACKAGE / "endstone-global.yml").read_text(encoding="utf-8"))
    assert value["collisions"]["enable-player-collisions"] is True

    global_config, world_config = prepare_paper_configs(tmp_path, PACKAGE)
    global_path = tmp_path / "config/endstone-global.yml"
    world_path = tmp_path / "config/endstone-world-defaults.yml"
    assert global_path.exists() and world_path.exists()
    assert not (tmp_path / "server/config").exists()
    assert isinstance(global_config["block-updates"]["disable-chorus-plant-updates"], bool)
    assert isinstance(world_config["environment"]["void-damage-amount"], float)
    value = yaml.safe_load(global_path.read_text(encoding="utf-8"))
    value["misc"]["max-joins-per-tick"] = 99
    global_path.write_text(yaml.safe_dump(value, sort_keys=False), encoding="utf-8")
    first = prepare_paper_configs(tmp_path, PACKAGE)
    second = prepare_paper_configs(tmp_path, PACKAGE)
    assert first == second
    assert first[0]["misc"]["max-joins-per-tick"] == 99
    bridge = __import__("tomllib").load((tmp_path / "endstone.toml").open("rb"))
    assert "global" in bridge["paper"] and "world_defaults" in bridge["paper"]
    assert bridge["paper"]["global"]["misc"]["max-joins-per-tick"] == 99
    assert bridge["paper"]["global"]["packet-limiter"]["all-packets"]["max-packet-rate"] == 500.0


def test_console_has_all_permissions_setting_is_synced(tmp_path):
    prepare_paper_configs(tmp_path, PACKAGE)
    global_path = tmp_path / "config/endstone-global.yml"
    value = yaml.safe_load(global_path.read_text(encoding="utf-8"))
    assert value["console"]["has-all-permissions"] is False
    value["console"]["has-all-permissions"] = True
    global_path.write_text(yaml.safe_dump(value, sort_keys=False), encoding="utf-8")

    global_config, _ = prepare_paper_configs(tmp_path, PACKAGE)
    bridge = __import__("tomllib").load((tmp_path / "endstone.toml").open("rb"))
    assert global_config["console"]["has-all-permissions"] is True
    assert bridge["paper"]["global"]["console"]["has-all-permissions"] is True


def test_global_runtime_settings_are_synced(tmp_path):
    prepare_paper_configs(tmp_path, PACKAGE)
    global_path = tmp_path / "config/endstone-global.yml"
    value = yaml.safe_load(global_path.read_text(encoding="utf-8"))
    value["misc"]["max-joins-per-tick"] = 11
    value["misc"]["enable-nether"] = False
    value["item-validation"]["book"]["author"] = 1024
    value["item-validation"]["book"]["title"] = 2048
    value["item-validation"]["book-size"]["total-multiplier"] = 0.75
    value["packet-limiter"]["all-packets"]["max-packet-rate"] = 321.5
    global_path.write_text(yaml.safe_dump(value, sort_keys=False), encoding="utf-8")

    global_config = prepare_paper_configs(tmp_path, PACKAGE)[0]
    bridge = __import__("tomllib").load((tmp_path / "endstone.toml").open("rb"))
    assert global_config["misc"]["max-joins-per-tick"] == 11
    assert global_config["misc"]["enable-nether"] is False
    assert global_config["item-validation"]["book"]["author"] == 1024
    assert global_config["item-validation"]["book"]["title"] == 2048
    assert global_config["item-validation"]["book-size"]["total-multiplier"] == 0.75
    assert global_config["packet-limiter"]["all-packets"]["max-packet-rate"] == 321.5
    assert bridge["paper"]["global"]["misc"]["max-joins-per-tick"] == 11
    assert bridge["paper"]["global"]["misc"]["enable-nether"] is False
    assert bridge["paper"]["global"]["item-validation"]["book"]["author"] == 1024
    assert bridge["paper"]["global"]["item-validation"]["book"]["title"] == 2048
    assert bridge["paper"]["global"]["item-validation"]["book-size"]["total-multiplier"] == 0.75
    assert bridge["paper"]["global"]["packet-limiter"]["all-packets"]["max-packet-rate"] == 321.5


def test_world_collision_settings_are_synced(tmp_path):
    prepare_paper_configs(tmp_path, PACKAGE)
    world_path = tmp_path / "config/endstone-world-defaults.yml"
    value = yaml.safe_load(world_path.read_text(encoding="utf-8"))
    assert value["collisions"]["only-players-collide"] is False
    assert value["collisions"]["allow-vehicle-collisions"] is True
    value["collisions"]["only-players-collide"] = True
    value["collisions"]["allow-vehicle-collisions"] = False
    world_path.write_text(yaml.safe_dump(value, sort_keys=False), encoding="utf-8")

    world_config = prepare_paper_configs(tmp_path, PACKAGE)[1]
    bridge = __import__("tomllib").load((tmp_path / "endstone.toml").open("rb"))
    assert world_config["collisions"]["only-players-collide"] is True
    assert world_config["collisions"]["allow-vehicle-collisions"] is False
    assert bridge["paper"]["world_defaults"]["collisions"]["only-players-collide"] is True
    assert bridge["paper"]["world_defaults"]["collisions"]["allow-vehicle-collisions"] is False


def test_prepare_rejects_type_errors(tmp_path):
    path = tmp_path / "config/endstone-global.yml"
    path.parent.mkdir(parents=True)
    path.write_text("block-updates: false\n", encoding="utf-8")
    try:
        prepare_paper_configs(tmp_path, PACKAGE)
    except ConfigError as error:
        assert "block-updates" in str(error)
    else:
        raise AssertionError("type error accepted")


def test_prepare_rejects_explicit_null_for_scalar(tmp_path):
    path = tmp_path / "config/endstone-global.yml"
    path.parent.mkdir(parents=True)
    path.write_text("misc:\n  max-joins-per-tick: null\n", encoding="utf-8")
    with pytest.raises(ConfigError, match=r"misc\.max-joins-per-tick.*null"):
        prepare_paper_configs(tmp_path, PACKAGE)


def test_prepare_accepts_paper_disabled_sentinels(tmp_path):
    global_path = tmp_path / "config/endstone-global.yml"
    world_path = tmp_path / "config/endstone-world-defaults.yml"
    global_path.parent.mkdir(parents=True)
    global_path.write_text("item-validation:\n  book-size:\n    page-max: disabled\n", encoding="utf-8")
    world_path.write_text("environment:\n  void-damage-amount: disabled\n", encoding="utf-8")

    global_config, world_config = prepare_paper_configs(tmp_path, PACKAGE)
    assert global_config["item-validation"]["book-size"]["page-max"] == "disabled"
    assert world_config["environment"]["void-damage-amount"] == "disabled"
    bridge = __import__("tomllib").load((tmp_path / "endstone.toml").open("rb"))
    assert bridge["paper"]["global"]["item-validation"]["book-size"]["page-max"] == "disabled"
    assert bridge["paper"]["world_defaults"]["environment"]["void-damage-amount"] == "disabled"


def test_merge_accepts_arbitrary_recursive_lists():
    defaults = {"outer": {"values": [{"enabled": True}, {"enabled": False}]}}
    current = {"outer": {"values": [{"enabled": False}, {"enabled": True}, {"enabled": False}]}}
    assert merge_defaults(defaults, current) == current


def test_sync_toml_preserves_user_values_and_converts_collections(tmp_path):
    path = tmp_path / "nested/endstone.toml"
    path.parent.mkdir(parents=True)
    path.write_text('[custom]\nkeep = "yes"\n[paper]\nkeep = "yes"\n', encoding="utf-8")
    sync_toml(
        path,
        {"mapping": {"value": 1}, "mapping-list": [{"enabled": True}, {"name": "second"}]},
        {"nested-list": [[1, 2], []]},
    )
    bridge = __import__("tomllib").loads(path.read_text(encoding="utf-8"))
    assert bridge["custom"]["keep"] == "yes"
    assert bridge["paper"]["keep"] == "yes"
    assert bridge["paper"]["global"]["mapping"]["value"] == 1
    assert bridge["paper"]["global"]["mapping-list"][1]["name"] == "second"
    assert bridge["paper"]["world_defaults"]["nested-list"] == [[1, 2], []]


def test_prepare_migrates_legacy_names_and_removes_empty_directory(tmp_path):
    legacy = tmp_path / "server/config"
    legacy.mkdir(parents=True)
    old = legacy / "paper-global.yml"
    old.write_text("misc:\n  max-joins-per-tick: 77\n", encoding="utf-8")
    prepare_paper_configs(tmp_path, PACKAGE)
    assert not old.exists()
    assert not legacy.exists()
    value = yaml.safe_load((tmp_path / "config/endstone-global.yml").read_text(encoding="utf-8"))
    assert value["misc"]["max-joins-per-tick"] == 77
