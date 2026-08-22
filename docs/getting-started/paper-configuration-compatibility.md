---
comments: true
---

# Paper configuration compatibility

The two Paper configuration files are generated with Paper's current version `31` layout. The status below describes
the Bedrock implementation boundary, not whether Endstone already has a wrapper for the setting.

| Status | Meaning |
| --- | --- |
| Implemented | Wired to a verified BDS path in this change. |
| Investigate | BDS has a related mechanism, but a version-specific ABI or call path must be resolved before wiring it. |
| Partial | A BDS mechanism exists, but it cannot provide Paper's Java semantics exactly. |
| Unsupported | No safe Bedrock equivalent was established. |

## `paper-global.yml`

| Path | Status | Bedrock basis |
| --- | --- | --- |
| `chunk-loading-basic.player-max-chunk-send-rate`, `player-max-chunk-load-rate`, `player-max-chunk-generate-rate` | Investigate | BDS `NetworkChunkSubscriber`, `ChunkViewSource`, and chunk generation queues exist; per-player rate limits need ABI work. |
| `chunk-loading-advanced.auto-config-send-distance`, `player-max-concurrent-chunk-loads`, `player-max-concurrent-chunk-generates` | Investigate | BDS has client chunk radius and per-player chunk generation state; the Java limits are not direct fields. |
| `messages.kick.authentication-servers-down`, `connection-throttle`, `flying-player`, `flying-vehicle` | Partial | Bedrock has typed disconnect packets and authentication/flying paths, but its reasons and text pipeline differ. |
| `messages.no-permission` | Partial | Endstone command senders can customize command errors; this is not a BDS global disconnect message. |
| `messages.use-display-name-in-quit-message` | Investigate | BDS has player disconnect text events and Endstone has the player text hook. |
| `spark.enabled`, `spark.enable-immediately` | Partial | BDS exposes profiler controls, but not Paper's Spark lifecycle. |
| `proxies.bungee-cord.online-mode`, `proxies.velocity.enabled`, `velocity.online-mode`, `velocity.secret`, `proxy-protocol` | Unsupported | Java proxy forwarding and PROXY protocol semantics are not Bedrock authentication/transport semantics. |
| `console.enable-brigadier-highlighting`, `enable-brigadier-completions` | Partial | Bedrock has command registration and completion, but no Java Brigadier console pipeline. |
| `console.has-all-permissions` | Implemented | Maps to Endstone's console `PermissionLevel::Console` evaluation. |
| `watchdog.early-warning-every`, `early-warning-delay` | Investigate | BDS has a watchdog and tick loop; its timing/reporting policy needs a dedicated hook. |
| `spam-limiter.tab-spam-increment`, `tab-spam-limit` | Unsupported | Bedrock has no Java tab-completion request model. |
| `spam-limiter.recipe-spam-increment`, `recipe-spam-limit` | Partial | Bedrock has recipe and item-stack request packets, but the Java counter/kick semantics differ. |
| `spam-limiter.incoming-packet-threshold` | Investigate | BDS `PacketSecurityController` and `PacketLimitHandler` implement native packet violation handling. |
| `unsupported-settings.allow-unsafe-end-portal-teleportation`, `skip-tripwire-hook-placement-validation`, `allow-permanent-block-break-exploits`, `allow-piston-duplication`, `perform-username-validation`, `allow-headless-pistons`, `skip-vanilla-damage-tick-when-shield-blocked`, `update-equipment-on-player-actions` | Investigate | BDS has corresponding portal, block, login, damage, and equipment paths; each needs a separate proof and is not a shared Java toggle. |
| `unsupported-settings.oversized-item-component-sanitizer.dont-sanitize` | Partial | Bedrock item stacks and network serialization can be filtered, but Java data-component names are not a compatible schema. |
| `commands.suggest-player-names-when-null-tab-completions`, `ride-command-allow-player-as-vehicle` | Investigate | Bedrock command completion and `/ride` handlers exist and need targeted call-path checks. |
| `time.affects-all-worlds` | Partial | BDS stores time per level/dimension; Paper's Java dimension-type sharing model is different. |
| `scoreboards.track-plugin-scoreboards` | Partial | Bedrock scoreboards exist, but do not have Java plugin scoreboard ownership semantics. |
| `scoreboards.save-empty-scoreboard-teams` | Unsupported | Bedrock has no direct Java scoreboard-team persistence equivalent. |
| `chunk-system.io-threads`, `worker-threads` | Partial | BDS has asynchronous chunk tasks and thread limits, but not Paper's two executor contract. |
| `item-validation.display-name`, `lore-line`, `book.title`, `book.author`, `book.page`, `book-size.page-max`, `book-size.total-multiplier` | Partial | Bedrock book packets and item text can be validated, but their wire/data limits differ from Java. |
| `item-validation.resolve-selectors-in-books` | Unsupported | No Java selector expansion behavior exists for Bedrock book text. |
| `packet-limiter.kick-message`, `all-packets.interval`, `max-packet-rate`, `action`, `overrides` | Investigate | BDS has `packetlimitconfig.json`, `PacketGroupDefinition`, `BucketPacketLimitAlgorithm`, `PacketLimitHandler`, and reload support. Paper packet names/actions still need Bedrock packet-ID mapping and 1.26.44 symbols. |
| `collisions.enable-player-collisions` | Implemented | Suppresses the verified BDS player-to-player `PushableByEntityUtility::push` path. |
| `collisions.send-full-pos-for-hard-colliding-entities` | Investigate | BDS has entity movement/position packets; the Java hard-collision correction path needs an ABI proof. |
| `player-auto-save.rate`, `max-per-tick` | Investigate | BDS saves player/actor state, but its batching scheduler is different. |
| `misc.chat-threads.chat-executor-core-size`, `chat-executor-max-size` | Investigate | BDS has asynchronous text/network workers; a chat-specific pool must be located. |
| `misc.max-joins-per-tick`, `catchup-ticks` | Investigate | BDS has connection admission and a server tick loop; both need targeted hooks. |
| `misc.send-full-pos-for-item-entities` | Investigate | BDS has item actor movement packets; Java's position precision option needs packet-path confirmation. |
| `misc.load-permissions-yml-before-plugins` | Unsupported | BDS/Endstone has no Bukkit `permissions.yml` loading phase. |
| `misc.region-file-cache-size` | Unsupported | BDS uses Bedrock chunk storage rather than Java Anvil region files. |
| `misc.use-alternative-luck-formula`, `strict-advancement-dimension-check`, `max-tracking-combat-entries` | Unsupported | These are Java fishing/advancement/combat-tracker mechanisms. |
| `misc.use-dimension-type-for-custom-spawners`, `compression-level`, `client-interaction-leniency-distance`, `xp-orb-groups-per-area`, `prevent-negative-villager-demand` | Partial | Related BDS spawner, network, interaction, XP, and trade paths exist, but the Java settings are not isomorphic. |
| `misc.enable-nether` | Investigate | BDS has active dimension checks and a dimension manager; disabling Nether requires a safe startup/transfer policy. |
| `misc.fix-far-end-terrain-generation` | Unsupported | Paper's Java End generator bug/fix has no established Bedrock equivalent. |
| `block-updates.disable-noteblock-updates`, `disable-tripwire-updates`, `disable-chorus-plant-updates`, `disable-mushroom-block-updates` | Investigate | BDS block update/random-tick paths exist and need per-block hooks. |
| `anticheat.obfuscation.items.*` | Partial | Bedrock item and inventory packets can be transformed, but Java item components/models are not the Bedrock schema. |
| `update-checker.enabled` | Unsupported | This is a Paper update service, not a BDS gameplay mechanism. |

## `paper-world-defaults.yml`

| Path | Status | Bedrock basis |
| --- | --- | --- |
| `anticheat.anti-xray.*` | Investigate | Bedrock chunk packets can theoretically be transformed per player; the required chunk palette/protocol rewrite needs a separate implementation and runtime proof. Paper serializes `engine-mode` as numeric ids (`1` = HIDE, `2` = OBFUSCATE, `3` = OBFUSCATE_LAYER). |
| `entities.mob-effects.*` | Investigate | BDS has entity effect application and actor types; effect immunity needs a targeted effect hook. |
| `entities.armor-stands.*` | Investigate | BDS has armor-stand actors and actor ticking/collision paths. |
| `entities.markers.tick` | Unsupported | Java marker entities have no Bedrock actor equivalent. |
| `entities.sniffer.hatch-time`, `boosted-hatch-time` | Investigate | A Bedrock sniffer/egg lifecycle must be confirmed before mapping timers. |
| `entities.spawning.non-player-arrow-despawn-rate`, `creative-arrow-despawn-rate`, `max-arrow-despawn-invulnerability` | Investigate | BDS projectile actors have despawn/tick state; Java category semantics differ. |
| `entities.spawning.filter-bad-tile-entity-nbt-from-falling-blocks`, `filtered-entity-tag-nbt-paths` | Partial | BDS falling-block actor NBT exists, but Java NBT paths are not a shared serialization contract. |
| `entities.spawning.disable-mob-spawner-spawn-egg-transformation`, `per-player-mob-spawns`, `scan-for-legacy-ender-dragon` | Investigate | BDS spawner and actor spawn systems exist; each requires a separate call-path proof. |
| `entities.spawning.spawn-limits.*`, `ticks-per-spawn.*`, `despawn-ranges.*`, `despawn-range-shape`, `despawn-time.*` | Investigate | BDS `Spawner`, actor categories, and despawn logic exist, but Paper's Java categories and distance rules must be mapped explicitly. |
| `entities.spawning.wateranimal-spawn-height.*`, `slime-spawn-height.*`, `wandering-trader.*`, `all-chunks-are-slime-chunks`, `skeleton-horse-thunder-spawn-chance`, `iron-golems-can-spawn-in-air`, `count-all-mobs-for-spawning`, `monster-spawn-max-light-level` | Investigate | BDS biome/spawn rules and actor-specific spawners exist; no safe global approximation is assumed. |
| `entities.spawning.duplicate-uuid.*`, `alt-item-despawn-rate.*` | Investigate | BDS actor UUID and item actor lifecycle exist and require targeted hooks. |
| `entities.behavior.*` | Investigate | Most actors/behaviors exist in BDS, but Java AI goals and Bedrock behavior components are different. |
| `entities.tracking-range-y.*` | Partial | BDS has player chunk/entity subscription state; Java vertical tracking categories are not direct fields. |
| `lootables.*` | Partial | BDS containers and loot tables exist, but Paper's per-player replenishment/relot timer is Java-specific. |
| `max-growth-height.cactus`, `reeds`, `bamboo.*` | Investigate | BDS random-tick growth paths exist and can be targeted per block. |
| `scoreboards.allow-non-player-entities-on-scoreboards`, `use-vanilla-world-scoreboard-name-coloring` | Partial | Bedrock scoreboards exist, but Java team/color semantics do not map directly. |
| `environment.disable-thunder` | Implemented | 1.26.40 BDS `WeatherManager::updateWeather` has independent lightning level/time inputs and client weather events. Endstone clears both lightning values while preserving rain. |
| `environment.disable-ice-and-snow` | Investigate | BDS weather/block random-tick logic can be targeted. |
| `environment.optimize-explosions` | Partial | BDS has a native explosion algorithm; Paper's optimization is an implementation strategy, not a common result contract. |
| `environment.disable-explosion-knockback` | Investigate | BDS `Explosion::explode` applies its own impulse directly; the 1.26.40 Windows IDA path confirms this is not safely covered by the generic `Mob::knockback` hook. The precise `knockback_scaling_` offset and all explosion variants still need confirmation. |
| `environment.generate-flat-bedrock` | Investigate | BDS terrain generation and bedrock feature paths exist. |
| `environment.frosted-ice.*`, `void-damage-*`, `treasure-maps.*`, `fire-tick-delay`, `water-over-lava-flow-speed`, `portal-*`, `nether-ceiling-void-damage-height`, `max-fluid-ticks`, `max-block-ticks`, `locate-structures-outside-world-border` | Investigate | BDS has corresponding weather, damage, map, block, portal, fluid, tick, and structure systems; each needs a version-specific hook and cannot be inferred from names. |
| `spawn.allow-using-signs-inside-spawn-protection` | Partial | BDS spawn protection and sign interaction exist, but Java's spawn-protection permission behavior differs. |
| `maps.item-frame-cursor-limit`, `item-frame-cursor-update-interval` | Partial | BDS maps/item frames exist, but map cursor synchronization is not Java's packet model. |
| `fixes.fix-items-merging-through-walls`, `disable-unloaded-chunk-enderpearl-exploit`, `prevent-tnt-from-moving-in-water`, `split-overstacked-loot`, `falling-block-height-nerf`, `tnt-entity-height-nerf` | Investigate | BDS item, projectile, TNT, falling-block, and loot actors provide real hook candidates. |
| `unsupported-settings.fix-invulnerable-end-crystal-exploit`, `disable-world-ticking-when-empty`, `ticking.chunks`, `ticking.block-entities` | Investigate | BDS has Level tick, chunk tick, block-entity tick, and end-crystal paths; skipping any requires preserving players, ticking areas, and saves. |
| `hopper.cooldown-when-full`, `disable-move-event`, `ignore-occluding-blocks` | Investigate | BDS hopper block actors and inventory movement paths exist. |
| `collisions.only-players-collide`, `allow-vehicle-collisions`, `fix-climbing-bypassing-cramming-rule`, `max-entity-collisions`, `allow-player-cramming-damage` | Investigate | BDS collision/push/cramming paths exist; the current global player-push hook is not enough to claim these semantics. |
| `chunks.auto-save-interval`, `max-auto-save-chunks-per-tick`, `fixed-chunk-inhabited-time`, `prevent-moving-into-unloaded-chunks`, `delay-chunk-unloads-by`, `entity-per-chunk-save-limit`, `flush-regions-on-save` | Partial/Investigate | BDS chunk storage, save, unload, and entity persistence exist; Java region/inhabited-time concepts do not map directly. |
| `fishing-time-range.minimum`, `maximum` | Investigate | BDS fishing actor timing exists. |
| `tick-rates.*` | Investigate | BDS random ticks, block actors, sensors, and behavior components exist; Java names are not direct BDS scheduler keys. |
| `feature-seeds.*` | Unsupported | Java configured-feature population seeds are not Bedrock world-generation seeds. |
| `command-blocks.permissions-level`, `force-follow-perm-level` | Partial | BDS command blocks and permission levels exist, but the Java/Bukkit permission interaction is different. |
| `misc.update-pathfinding-on-block-update`, `show-sign-click-command-failure-msgs-to-player`, `disable-end-credits`, `max-leash-distance`, `disable-sprint-interruption-on-attack`, `disable-relative-projectile-velocity`, `legacy-ender-pearl-behavior`, `allow-remote-ender-dragon-respawning` | Investigate | BDS has pathfinding, sign, credits, leash, attack, projectile, pearl, and dragon paths; each needs an independent proof. |
| `misc.redstone-implementation`, `alternate-current-update-order` | Unsupported | Paper selects Java redstone algorithms; Bedrock's redstone implementation is a different engine. |

The `Investigate` entries are intentionally retained in the files because Bedrock has a related subsystem. They are not
reported as implemented until the 1.26.44 ABI, caller flow, and live-server behavior are verified.
