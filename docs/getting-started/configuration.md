---
comments: true
---

# Configuration

Endstone creates Paper-style configuration files in the server's `config` directory before BDS starts:

- `config/paper-global.yml` applies to the server.
- `config/paper-world-defaults.yml` applies to the BDS level.

The YAML files are the source of truth. They are read on every server start, and Endstone derives the values it needs at
runtime. Restart the server after changing either file.

## Supported settings

```yaml title="config/paper-global.yml"
_version: 31
collisions:
  enable-player-collisions: true
console:
  has-all-permissions: false
packet-limiter:
  kick-message: '<red><lang:disconnect.exceeded_packet_rate>'
  all-packets:
    interval: 7.0
    max-packet-rate: 500.0
    action: KICK
```

`collisions.enable-player-collisions` controls BDS player-to-player pushing. It does not change collisions involving
mobs, vehicles, or blocks.

`console.has-all-permissions` grants the Endstone console sender every plugin permission when enabled.

`packet-limiter.all-packets` applies a per-connection packet window in the BDS receive hook. `DROP` discards packets
over the limit; `KICK` disconnects with `packet-limiter.kick-message`. The Paper `place_recipe` override is preserved
but is not mapped to Bedrock's broader item-stack request protocol.

```yaml title="config/paper-world-defaults.yml"
_version: 31
collisions:
  only-players-collide: false
environment:
  disable-thunder: false
```

`collisions.only-players-collide` suppresses BDS push calls where neither actor is a player. It does not change vehicle
boarding or other collision systems.

`environment.disable-thunder` clears BDS lightning strength and timer while leaving rain enabled.

## Paper compatibility

The file names, keys, and defaults above match Paper. BDS has one level rather than Java Edition's independent worlds,
so `paper-world-defaults.yml` applies to that entire level. The default files contain the complete current Paper
configuration tree. Endstone only applies settings whose Bedrock behaviour has been established; unsupported keys are
preserved for compatibility and intentionally ignored rather than emulated with incompatible semantics.

See the [Paper compatibility matrix](paper-configuration-compatibility.md) for the Bedrock evidence and status of every
configuration group.
