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
| `paper.global.item-validation.book.author` | `item-validation.book.author` | A positive value limits the UTF-8 character count of the author during book finalization. Invalid finalization actions are ignored before the native handler runs. |
| `paper.global.item-validation.book.title` | `item-validation.book.title` | A positive value limits the UTF-8 character count of the title during book finalization. Invalid finalization actions are ignored before the native handler runs. |
| `paper.global.item-validation.book-size.total-multiplier` | `item-validation.book-size.total-multiplier` | When `book-size.page-max` is enabled, applies Paper's clamped 0.3–1.0 weighted total-byte multiplier to the edited book's pages. |
| `paper.global.misc.max-joins-per-tick` | `misc.max-joins-per-tick` | The login validation hook permits at most this many authenticated join attempts in a 50 ms server-tick window. Values below 1 disable this limit. Excess attempts are disconnected before player creation. |
| `paper.global.misc.enable-nether` | `misc.enable-nether` | When `false`, the existing ServerPlayer dimension-change hook rejects transitions to the Nether before constructing the dimension transfer. |
| `paper.global.packet-limiter.all-packets.interval` / `max-packet-rate` / `action` | `packet-limiter.all-packets.*` | The packet dispatcher counts incoming packets per network address over the configured interval. Over-limit packets are dropped for `DROP`; `KICK` disconnects the sender with `packet-limiter.kick-message`. |
| `paper.world_defaults.collisions.max-entity-collisions` | `collisions.max-entity-collisions` | Caps the number of push resolutions accepted for each actor during one BDS server tick. Values below 1 leave collision processing uncapped. |
| `paper.world_defaults.chunks.prevent-moving-into-unloaded-chunks` | `chunks.prevent-moving-into-unloaded-chunks` | When `true`, the PlayerAuthInput hook rejects movement whose translated player AABB is not fully covered by loaded chunks and filters block actions targeting unloaded chunks. |
| `paper.world_defaults.collisions.only-players-collide` | `collisions.only-players-collide` | When `true`, the push hook permits only player-player collision pushes; all other actor pairs are skipped. |
| `paper.world_defaults.collisions.allow-vehicle-collisions` | `collisions.allow-vehicle-collisions` | When `only-players-collide` is enabled, `false` also skips non-player collisions involving vehicles; when `true`, vehicle pairs remain eligible. |
| `paper.world_defaults.unsupported-settings.disable-world-ticking-when-empty` | `unsupported-settings.disable-world-ticking-when-empty` | When `true`, the existing `Level::tick` hook skips the native Level tick while the BDS Level has no online players. Endstone's scheduler heartbeat still runs. |
| `paper.world_defaults.environment.disable-thunder` | `environment.disable-thunder` | When `true`, the weather hook passes zero lightning level and duration to BDS and skips the normal thunder-change event path. |
| `paper.world_defaults.entities.spawning.monster-spawn-max-light-level` | `entities.spawning.monster-spawn-max-light-level` | A numeric value from 0 through 15 updates each loaded Dimension's Bedrock monster block-light limit before the Level tick. `default` or values outside that range preserve BDS behavior. |
| `paper.world_defaults.entities.mob-effects.immune-to-wither-effect` | `entities.mob-effects.immune-to-wither-effect` | When `true`, the existing actor effect event path rejects the Wither effect for Withers and Wither Skeletons. |
| `paper.world_defaults.entities.mob-effects.spiders-immune-to-poison-effect` | `entities.mob-effects.spiders-immune-to-poison-effect` | When `true`, the existing actor effect event path rejects the Poison effect for spiders. |
| `paper.world_defaults.environment.disable-explosion-knockback` | `environment.disable-explosion-knockback` | When `true`, the mob knockback hook suppresses knockback invoked synchronously from an explosion. Other knockback is unchanged. |
| `paper.world_defaults.environment.void-damage-amount` | `environment.void-damage-amount` | Sets the damage passed into the existing ActorDamageEvent/BDS hurt path for `Void` damage. `disabled` leaves the native BDS amount unchanged. |

Book selector resolution remains inactive. The packet hook validates book page, author, title, and total-size limits before invoking the native packet handler.

The current source tree wires the empty-world Level tick setting, packet limiter, join throttling, Nether toggle, unloaded-chunk movement guards, book validation, void damage, monster spawn light, mob-effect immunity, and the three collision entries. Other template values remain synchronized but are not runtime consumers in this checkout.

## Retained configuration and ignored behavior

The templates retain the following families for Paper compatibility, but they are not active Endstone behavior unless listed in the table above:

- Global anticheat, block-update, chunk-loading, chunk-system, command, message, player-auto-save, proxy, scoreboard, spam-limiter, Spark, time, update-checker, watchdog, and other `misc` settings except the active `max-joins-per-tick` and `enable-nether` entries.
- Global item-validation settings other than the active book page, author, title, page-max, and total-multiplier entries. Selector resolution remains inactive.
- World anticheat/anti-xray, chunk save and unload settings other than the active unloaded-chunk movement guard, world collision settings other than the three active collision entries above, command-block, entity behavior other than the active mob-effect settings, entity spawning and tracking other than the active monster-light setting, environment settings other than `disable-thunder`, `disable-explosion-knockback`, and `void-damage-amount`, feature-seed, fishing, fix, hopper, lootable, map, growth, world-misc, scoreboard, spawn, tick-rate, and unsupported-settings other than the active world-ticking entry.

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

The source-level check for this checkout additionally keeps the other environment keys in the retained-only set until their configuration reads and runtime behavior are present. The three environment keys listed in the active table above are the exceptions. The list above is not a substitute for a runtime implementation check.

## Why some settings are not implemented

A setting remains retained-only as an implementation status when one or more of the following applies:

- The behavior depends on Java-only systems such as Paper's region scheduler, Java proxy integrations, Brigadier implementation, Spark integration, or Java plugin infrastructure.
- Bedrock has different packet, transport, dimension, entity-AI, loot, or world-ticking semantics, so there is no behavior-preserving equivalent.
- A current 1.26.40 ABI-confirmed function or data path has not yet been identified for the setting. No guessed hook is installed for a gameplay or tick path.
- The setting changes an experimental or exploit-related implementation path whose Bedrock decision point has not been identified safely.

This is an implementation-status record, not a claim that retained keys are impossible on Bedrock. When a setting gains a verified Bedrock implementation, its runtime behavior and this page should be updated together.
