import importlib
from pathlib import Path

import tomlkit


class Bootstrap(importlib.import_module("endstone.cli.base").Bootstrap):
    @property
    def name(self) -> str:
        return "Bootstrap"

    @property
    def target_system(self) -> str:
        return "test"

    @property
    def executable_filename(self) -> str:
        return "bedrock_server"


def test_prepares_paper_configs_and_applies_values(tmp_path: Path):
    bootstrap = Bootstrap(str(tmp_path), True, "", False)
    bootstrap._prepare()

    global_config = tmp_path / "config" / "paper-global.yml"
    world_defaults = tmp_path / "config" / "paper-world-defaults.yml"
    assert global_config.exists()
    assert world_defaults.exists()

    global_config.write_text(
        "_version: 31\ncollisions:\n  enable-player-collisions: false\nconsole:\n  has-all-permissions: true\npacket-limiter:\n  kick-message: custom\n  all-packets:\n    interval: 2\n    max-packet-rate: 3\n    action: DROP\n",
        encoding="utf-8",
    )
    world_defaults.write_text(
        "_version: 31\nenvironment:\n  disable-thunder: true\ncollisions:\n  only-players-collide: true\n",
        encoding="utf-8",
    )
    bootstrap._prepare()

    with (tmp_path / "endstone.toml").open(encoding="utf-8") as f:
        config = tomlkit.load(f)

    assert config["paper"]["global"]["collisions"]["enable-player-collisions"] is False
    assert config["paper"]["global"]["console"]["has-all-permissions"] is True
    assert config["paper"]["global"]["packet-limiter"]["kick-message"] == "custom"
    assert config["paper"]["global"]["packet-limiter"]["all-packets"]["interval"] == 2.0
    assert config["paper"]["global"]["packet-limiter"]["all-packets"]["max-packet-rate"] == 3.0
    assert config["paper"]["global"]["packet-limiter"]["all-packets"]["action"] == "DROP"
    assert config["paper"]["world-defaults"]["environment"]["disable-thunder"] is True
    assert config["paper"]["world-defaults"]["collisions"]["only-players-collide"] is True
