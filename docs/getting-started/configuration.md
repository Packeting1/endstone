---
comments: true
---

# Configuration

Endstone keeps its server configuration in two layers. The YAML files are the administrator-facing files; `endstone.toml` is the runtime bridge used by the native server.

## Configuration files

The files created in a server directory are:

- `config/endstone-global.yml` contains server-wide defaults.
- `config/endstone-world-defaults.yml` contains world-default values.
- `endstone.toml` contains the existing Endstone settings and synchronized `[paper.global]` and `[paper.world_defaults]` tables.

The installed package also contains `endstone/config/endstone-global.yml` and `endstone/config/endstone-world-defaults.yml`. Those are templates used by the launcher; edit the copies under the server's `config/` directory instead.

The names and most keys intentionally follow Paper's configuration shape. They provide a familiar place for settings that can be implemented on Bedrock, settings that may be implemented later, and settings for which the closest Java behavior has no safe Bedrock equivalent. A Paper key being present does not by itself promise Paper behavior.

## Startup synchronization

The launcher prepares the files before starting BDS:

1. It loads the packaged YAML defaults.
2. It creates or updates the server-local YAML files under `config/`.
3. Existing values are preserved, and missing default keys are added.
4. If an older installation has a file under `server/config/`, it is moved to `config/` only when the new destination does not already exist.
5. The merged YAML values are written to the `paper.global` and `paper.world_defaults` tables in `endstone.toml`.

Unknown keys already present in a YAML file are preserved. Invalid YAML, a non-mapping YAML root, or a value with a type incompatible with its default (apart from the documented `disabled` sentinels) stops synchronization with a configuration error instead of silently changing that value. Other top-level Endstone TOML settings are kept while the two Paper-compatible tables are refreshed.

Configuration is loaded by the native server at startup. Changes to either YAML file require running the launcher again and restarting the server; `/reload` does not reload these values. The synchronized Paper tables in `endstone.toml` are generated from YAML during startup preparation, so editing the YAML files is the durable way to change them.

## Scope on Bedrock

`endstone-global.yml` is server-wide.

`endstone-world-defaults.yml` is a single set of defaults for the BDS `Level`. Bedrock Dedicated Server does not expose Paper's Java per-world configuration model: the dimensions in a BDS Level do not get separate YAML files or independent Paper-style overrides. A world-default value can only affect the Level-wide behavior of a setting once Endstone has a verified Bedrock implementation for that setting.

## Behavior currently wired to the runtime

The following behavior is verified in the current source tree rather than inferred from the YAML names:

| TOML path | YAML key | Current behavior |
| --- | --- | --- |
| `paper.global.collisions.enable-player-collisions` | `collisions.enable-player-collisions` | When `false`, the push hook skips the vanilla player-to-player push. The actor collision event is still dispatched before this check. Other collision pairs are not disabled by this setting. |
| `paper.global.console.has-all-permissions` | `console.has-all-permissions` | When `true`, the console sender reports every permission as granted, matching Paper. When `false`, the existing permission defaults and attachments are used. |
| `paper.global.item-validation.book.page` | `item-validation.book.page` | A positive value limits the UTF-8 character count of an edited page. The native BDS byte cap remains in force, and larger values do not expand it. An invalid page action is ignored before the native packet handler runs. |
| `paper.global.item-validation.book-size.page-max` | `item-validation.book-size.page-max` | A positive value limits the encoded byte length of an edited page. `disabled` removes this additional Paper-side cap, but the native BDS byte cap remains. An invalid page action is ignored before the native packet handler runs. |
| `paper.world_defaults.environment.disable-thunder` | `environment.disable-thunder` | When `true`, the weather hook passes zero lightning level and duration to BDS and skips the normal thunder-change event path. |
| `paper.world_defaults.environment.disable-explosion-knockback` | `environment.disable-explosion-knockback` | When `true`, the mob knockback hook suppresses knockback invoked synchronously from an explosion. Other knockback is unchanged. |

Book author/title limits and `item-validation.book-size.total-multiplier` remain retained-only. `paper.global.item-validation.resolve-selectors-in-books` is read for future compatibility but selector resolution is not implemented. `environment.void-damage-amount` accepts the Paper `disabled` sentinel in the bridge but is retained-only at runtime.

World-default values are only consumed where a runtime hook explicitly reads the corresponding `paper.world_defaults.*` path. The current source tree wires the two environment settings listed above; the remaining world-default keys stay synchronized and retained but do not change BDS behavior in this checkout.

## Retained configuration and ignored behavior

The templates retain the following families for Paper compatibility, but they are not active Endstone behavior unless listed in the table above:

- Global anticheat, block-update, chunk-loading, chunk-system, command, message, packet-limiter, player-auto-save, proxy, scoreboard, spam-limiter, Spark, time, update-checker, and watchdog settings.
- Global item-validation settings other than `book.page` and `book-size.page-max`. Author/title limits, the total multiplier, and selector resolution remain retained-only.
- World anticheat/anti-xray, chunk save and unload, world collision, command-block, entity behavior, entity spawning and tracking, environment, feature-seed, fishing, fix, hopper, lootable, map, growth, world-misc, scoreboard, spawn, tick-rate, and unsupported-settings families.

These keys are intentionally retained rather than deleted. Their values are copied into `endstone.toml` so the configuration shape remains stable and future implementations can use the existing values. They must be treated as ignored by the current runtime.

Additional reviewed but inactive world keys include:

- `environment.disable-ice-and-snow`
- `environment.fire-tick-delay`
- `environment.max-block-ticks`
- `environment.max-fluid-ticks`
- `environment.optimize-explosions`
- `environment.water-over-lava-flow-speed`
- `environment.portal-create-radius`
- `environment.portal-search-radius`
- `misc.disable-relative-projectile-velocity`
- `misc.disable-sprint-interruption-on-attack`
- `unsupported-settings.allow-headless-pistons`
- `unsupported-settings.allow-piston-duplication`
- `unsupported-settings.skip-tripwire-hook-placement-validation`

The source-level check for this checkout additionally keeps the other environment keys in the retained-only set until their configuration reads and runtime behavior are present. The two environment keys listed in the active table above are the exceptions. The list above is not a substitute for a runtime implementation check.

## Why some settings are not implemented

A setting remains retained-only when one or more of the following applies:

- The behavior depends on Java-only systems such as Paper's region scheduler, Java proxy integrations, Brigadier implementation, Spark integration, or Java plugin infrastructure.
- Bedrock has different packet, transport, dimension, entity-AI, loot, or world-ticking semantics, so there is no behavior-preserving equivalent.
- A current 1.26.44 ABI-confirmed function or data path is not available. Older IDA findings are not used as a substitute for a target-version verification, and no guessed hook is installed for a gameplay or tick path.
- The setting changes an experimental or exploit-related implementation path whose Bedrock decision point has not been identified safely.

This is deliberate: an ignored key is preferable to a hook that silently targets the wrong BDS function or changes vanilla behavior outside the requested setting. When a setting gains a verified Bedrock implementation, its runtime behavior and this page should be updated together.
