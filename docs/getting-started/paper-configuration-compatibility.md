---
comments: true
---

# Paper configuration compatibility

The two Paper configuration files are generated with Paper's current version `31` layout. The status below describes
what this PR wires into Endstone; the detailed 1.26.40 audits separately record whether a BDS adapter is feasible.

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
| `collisions.only-players-collide`, `allow-vehicle-collisions`, `fix-climbing-bypassing-cramming-rule`, `max-entity-collisions`, `allow-player-cramming-damage` | Investigate | BDS collision/push/cramming paths exist; this PR wires only the non-player push subset for `only-players-collide`. |
| `chunks.auto-save-interval`, `max-auto-save-chunks-per-tick`, `fixed-chunk-inhabited-time`, `prevent-moving-into-unloaded-chunks`, `delay-chunk-unloads-by`, `entity-per-chunk-save-limit`, `flush-regions-on-save` | Partial/Investigate | BDS chunk storage, save, unload, and entity persistence exist; Java region/inhabited-time concepts do not map directly. |
| `fishing-time-range.minimum`, `maximum` | Investigate | BDS fishing actor timing exists. |
| `tick-rates.*` | Investigate | BDS random ticks, block actors, sensors, and behavior components exist; Java names are not direct BDS scheduler keys. |
| `feature-seeds.*` | Unsupported | Java configured-feature population seeds are not Bedrock world-generation seeds. |
| `command-blocks.permissions-level`, `force-follow-perm-level` | Partial | BDS command blocks and permission levels exist, but the Java/Bukkit permission interaction is different. |
| `misc.update-pathfinding-on-block-update`, `show-sign-click-command-failure-msgs-to-player`, `disable-end-credits`, `max-leash-distance`, `disable-sprint-interruption-on-attack`, `disable-relative-projectile-velocity`, `legacy-ender-pearl-behavior`, `allow-remote-ender-dragon-respawning` | Investigate | BDS has pathfinding, sign, credits, leash, attack, projectile, pearl, and dragon paths; each needs an independent proof. |
| `misc.redstone-implementation`, `alternate-current-update-order` | Unsupported | Paper selects Java redstone algorithms; Bedrock's redstone implementation is a different engine. |

The `Investigate` entries are intentionally retained in the files because Bedrock has a related subsystem. The detailed
audits below use the supplied 1.26.40 databases; an implementation still needs the 1.26.44 ABI declarations and live
server behavior when it introduces a new hook or layout-dependent field.

## Detailed 1.26.40 global audit

The first global batch below is based on the Windows 1.26.40 IDA database. `E` means the BDS path is confirmed and an
Endstone adapter is feasible; `I` means a related path exists but the exact caller, field, or runtime contract is still
missing. The addresses are 1.26.40 research evidence, not 1.26.44 offsets.

The detailed tables cover all 94 scalar leaves in `paper-global.default.yml`; map-valued settings are represented with
their concrete defaults and an explicit `<...>` entry for extensible keys.

| Paper path | Default | 1.26.40 evidence and implementation boundary | Result |
| --- | ---: | --- | --- |
| `chunk-loading-basic.player-max-chunk-send-rate` | `75.0` | BDS `BatchedNetworkPeer::sendPacket` (`0x140FDFFF0`) only batches bytes; no per-player chunk scheduler was established. A chunk-packet dispatch budget is still required. | I |
| `chunk-loading-basic.player-max-chunk-load-rate` | `100.0` | The packet path is distinct from chunk loading; `ChunkSource`/generation scheduling remains to be located. | I |
| `chunk-loading-basic.player-max-chunk-generate-rate` | `-1.0` | The supplied batch did not establish a per-player generation queue or rate field. | I |
| `chunk-loading-advanced.auto-config-send-distance` | `true` | `RequestChunkRadiusPacket` (id `69`) and Linux `ServerPlayer_updateChunkViewRadius` (`0x98D8AC0`) confirm the client radius path; the policy still needs a targeted hook. | I |
| `chunk-loading-advanced.player-max-concurrent-chunk-loads` | `0` | BDS has asynchronous chunk work, but no per-player concurrent-load field was confirmed in this batch. | I |
| `chunk-loading-advanced.player-max-concurrent-chunk-generates` | `0` | BDS has asynchronous generation work, but no per-player concurrent-generate field was confirmed in this batch. | I |
| `chunk-system.io-threads` | `-1` | BDS has asynchronous chunk/storage tasks, but no safe Paper-compatible I/O thread-count field was confirmed. | I |
| `chunk-system.worker-threads` | `-1` | BDS has worker/task scheduling, but no safe Paper-compatible generation worker-count field was confirmed. | I |
| `packet-limiter.kick-message` | `'<red><lang:disconnect.exceeded_packet_rate>'` | Windows `NetworkSystem::_sortAndPacketizeEvents` (`0x140BF9F40`) and Linux `PacketSecurityController_makeLimitError` (`0x85B3D80`) confirm a native violation/disconnect path; Endstone can supply the configured Bedrock disconnect text. | E |
| `packet-limiter.all-packets.interval` | `7.0` | Windows `NetworkSystem::runEvents` (`0x140BF9700`) and Linux `PacketViolationHandler_updateBucket` (`0x85B49C0`) confirm monotonic/token-bucket windows. A new Endstone adapter still needs the 1.26.44 ABI. | E |
| `packet-limiter.all-packets.max-packet-rate` | `500.0` | Linux `PacketLimitHandler_checkPacketId` (`0x85B39B0`) and the Windows packet-id table both enforce native limits; an adapter can feed Paper's rate after ABI regeneration. | E |
| `packet-limiter.all-packets.action` | `KICK` | The BDS violation path marks the connection; Linux's receive path can drop and the existing disconnect hook can kick, but the action adapter is not wired in this change. | E |
| `spam-limiter.tab-spam-increment` | `1` | Bedrock has no Java command-suggestion request counter. | X |
| `spam-limiter.tab-spam-limit` | `500` | Bedrock has no Java command-suggestion request counter. | X |
| `spam-limiter.recipe-spam-increment` | `1` | Bedrock recipe/item-stack request packets can be counted, but their scope is wider than Java recipe-book requests. | N |
| `spam-limiter.recipe-spam-limit` | `20` | Bedrock recipe/item-stack request packets can be limited, but the Java counter/kick semantics are not equivalent. | N |
| `spam-limiter.incoming-packet-threshold` | `300` | Linux packet security/violation paths (`0x85B39B0`, `0x85B49C0`) can count per-connection packets, but Bedrock batch/input semantics differ. | N |
| `packet-limiter.overrides.minecraft:place_recipe.interval` | `4.0` | BDS has packet-id buckets, but no Java `PlaceRecipe` packet; mapping this key to Bedrock recipe/item-stack requests would cover a wider protocol operation. | N |
| `packet-limiter.overrides.minecraft:place_recipe.max-packet-rate` | `5.0` | The native table is real, but the named Java packet has no Bedrock equivalent and a broad substitute could reject valid requests. | N |
| `packet-limiter.overrides.minecraft:place_recipe.action` | `DROP` | BDS can drop or disconnect at its packet-security path, but applying it to `ItemStackRequest` is not Java-equivalent. | N |
| `messages.kick.authentication-servers-down` | `<lang:multiplayer.disconnect.authservers_down>` | Linux login (`0x84D72D0`) and unified disconnect (`0x84C4000`) paths accept a message; a reason-specific adapter is feasible. | E |
| `messages.kick.connection-throttle` | `Connection throttled! Please wait before reconnecting.` | BDS has a connection admission/disconnect path; the throttle branch still needs a targeted caller hook. | E |
| `messages.kick.flying-player` | `<lang:multiplayer.disconnect.flying>` | BDS flying validation ultimately uses the unified disconnect path; the player-specific caller needs a targeted hook. | E |
| `messages.kick.flying-vehicle` | `<lang:multiplayer.disconnect.flying>` | BDS vehicle flying validation ultimately uses the unified disconnect path; the vehicle-specific caller needs a targeted hook. | E |
| `messages.no-permission` | `<red>I'm sorry, but you do not have permission to perform this command. Please contact the server administrators if you believe this is an error.` | Endstone's command permission layer can supply the configured text at the command compiler/dispatch boundary (`0x98A52B0`). | E |
| `messages.use-display-name-in-quit-message` | `false` | Endstone already has player disconnect/quit broadcast handling; choose the display-name source at that event boundary. | E |
| `console.enable-brigadier-highlighting` | `true` | BDS command compiler (`0x98A52B0`) is not Java Brigadier console UI. | X |
| `console.enable-brigadier-completions` | `true` | BDS command compiler (`0x98A52B0`) is not Java Brigadier console UI. | X |
| `console.has-all-permissions` | `false` | Endstone `PermissionLevel::Console` evaluation already provides the equivalent switch. | E |
| `watchdog.early-warning-every` | `5000` | BDS `Level::tick` (`0xC069730`) is the heartbeat boundary, but Paper's early warning cadence needs a separate monitor. | I |
| `watchdog.early-warning-delay` | `10000` | BDS has a heartbeat/tick boundary but no established Paper early-warning delay field. | I |
| `commands.suggest-player-names-when-null-tab-completions` | `true` | No Java null tab-completion semantic was found in Bedrock command handling. | X |
| `commands.ride-command-allow-player-as-vehicle` | `false` | BDS command compilation exists, but the Ride executor and player-as-vehicle check need a targeted hook. | I |
| `time.affects-all-worlds` | `false` | BDS exposes `Level_getTime` (`0xC070CB0`) and `Level_setTime` (`0xC070A60`), but not Paper's shared dimension-type policy. | I |
| `player-auto-save.rate` | `-1` | BDS save paths (`0xC075740`, `0xC0720E0`, `0xC072860`) exist; per-player interval scheduling needs a hook. | I |
| `player-auto-save.max-per-tick` | `-1` | BDS save queues exist, but a Paper-style per-tick player budget is not an exposed field. | I |
| `misc.chat-threads.chat-executor-core-size` | `-1` | No Bedrock chat-specific executor with Java's core-size contract was established. | X |
| `misc.chat-threads.chat-executor-max-size` | `-1` | No Bedrock chat-specific executor with Java's max-size contract was established. | X |
| `misc.max-joins-per-tick` | `5` | Linux player-load path (`0x84EB200`) exists; admission batching has no Paper cap field. | I |
| `misc.catchup-ticks` | `default` | BDS `Level::tick` (`0xC069730`) is a single tick boundary; catch-up policy needs a server-loop hook. | I |
| `misc.send-full-pos-for-item-entities` | `false` | BDS packet send (`0x6E4B9C0`) exists; item-entity precision fields need a packet-specific hook. | I |
| `misc.load-permissions-yml-before-plugins` | `true` | BDS/Endstone has no Bukkit `permissions.yml` loading phase. | X |
| `misc.region-file-cache-size` | `256` | BDS chunk/storage loading (`0xC191870`) exists, but Java Anvil region-cache semantics do not. | I |
| `misc.use-alternative-luck-formula` | `false` | Java loot luck formula has no safe Bedrock equivalent. | X |
| `misc.use-dimension-type-for-custom-spawners` | `false` | BDS dimension/spawner initialization exists, but Paper custom-spawner dimension selection is only partially mappable. | N |
| `misc.strict-advancement-dimension-check` | `false` | Bedrock has no Java advancement dimension-check mechanism. | X |
| `misc.compression-level` | `default` | Bedrock compression/threshold handling exists, but Java zlib-level semantics are not shared. | N |
| `misc.client-interaction-leniency-distance` | `default` | BDS interaction validation (`0xBC85B20`) is a real hook candidate; the distance field/caller needs ABI confirmation. | I |
| `misc.xp-orb-groups-per-area` | `default` | Bedrock XP-orb merging exists, but its area grouping path needs a targeted hook. | I |
| `misc.prevent-negative-villager-demand` | `false` | Bedrock trading exists, but Java demand values and update rules are not proven equivalent. | N |
| `misc.enable-nether` | `true` | BDS dimension initialization (`0x9A15F00`) is a real startup/transfer hook candidate. | I |
| `misc.fix-far-end-terrain-generation` | `true` | Paper's Java End terrain fix has no established Bedrock equivalent. | X |
| `misc.max-tracking-combat-entries` | `10240` | No Java CombatTracker-equivalent Bedrock storage path was established. | X |
| `block-updates.disable-noteblock-updates` | `false` | Linux NoteBlock vtable (`0xE75F2D8`) and event paths (`0xC7145E0`, `0xC7147D0`) provide targeted update hooks. | I |
| `block-updates.disable-tripwire-updates` | `false` | Linux TripWire vtable (`0xE74B5E8`) and update paths (`0xC6C3710`, `0xBE14DC0`) provide targeted hooks. | I |
| `block-updates.disable-chorus-plant-updates` | `false` | Linux Chorus vtable (`0xE6E1010`) and survival/update paths (`0xBDF4EA0`, `0xBDF4F50`) provide targeted hooks. | I |
| `block-updates.disable-mushroom-block-updates` | `false` | Bedrock has a HugeMushroom vtable (`0xE6C6488`), but no isolated update override was confirmed; a generic neighbour-update hook risks unrelated blocks. | I |
| `unsupported-settings.allow-unsafe-end-portal-teleportation` | `false` | BDS dimension initialization exists, but Java End-portal duplication/unsafe teleport semantics have no safe equivalent. | X |
| `unsupported-settings.skip-tripwire-hook-placement-validation` | `false` | Linux TripWireHookBlock vtable (`0xE73B470`) and update chain exist; placement validation needs a targeted hook. | I |
| `unsupported-settings.allow-permanent-block-break-exploits` | `false` | BDS piston actor tick (`0xC581B00`) and block update paths exist, but Java exploit behavior is not identical. | I |
| `unsupported-settings.allow-piston-duplication` | `false` | BDS piston state paths (`0xC581B00`, `0xE726C38`) exist; duplication requires an ABI-level state/sync policy. | I |
| `unsupported-settings.perform-username-validation` | `true` | BDS login validation (`0x84D72D0`) is a real entry, but the native validation runs before the existing Endstone hook. | I |
| `unsupported-settings.allow-headless-pistons` | `false` | BDS PistonBlock/PistonBlockActor paths (`0xE7614F8`, `0xC581B00`) exist; headless behavior needs a targeted state hook. | I |
| `unsupported-settings.skip-vanilla-damage-tick-when-shield-blocked` | `false` | BDS player action/shield path (`0xB35E070`) exists, but Java damage-tick semantics are not a shared field. | I |
| `unsupported-settings.update-equipment-on-player-actions` | `true` | BDS player action and equipment packet paths (`0xB35E070`) provide a concrete adapter boundary. | E |
| `unsupported-settings.oversized-item-component-sanitizer.dont-sanitize` | `[]` | BDS ItemStack serialization (`0x85993B0`, `0x6E4B9C0`) exists, but Java item components are not the Bedrock schema. | N |
| `item-validation.display-name` | `8192` | Linux BookEditPacket/validation paths (`0x8335E20`, `0x85B2A30`, `0x85B2C40`) provide a length-check boundary. | I |
| `item-validation.lore-line` | `8192` | Bedrock ItemStack/packet serialization (`0x85993B0`) exists, but line/text units need a Bedrock-specific limit. | I |
| `item-validation.book.title` | `8192` | Linux BookEditPacket deserialization (`0x85B2C40`) provides a targeted title check. | I |
| `item-validation.book.author` | `8192` | Linux BookEditPacket deserialization (`0x85B2C40`) provides a targeted author check. | I |
| `item-validation.book.page` | `16384` | Linux BookEditPacket deserialization (`0x85B2C40`) provides a targeted page payload check; formats differ. | I |
| `item-validation.book-size.page-max` | `2560` | BDS book packet validation can enforce a page maximum, but Paper's book-size semantics are not identical. | N |
| `item-validation.book-size.total-multiplier` | `0.98` | BDS has packet max-size gates (`0x8335E20`), not Paper's Java total-size multiplier. | N |
| `item-validation.resolve-selectors-in-books` | `false` | Java book selector expansion has no safe Bedrock equivalent. | X |
| `proxies.bungee-cord.online-mode` | `true` | RakNet startup (`0x85B91C0`) is not the Java Bungee forwarding protocol. | X |
| `proxies.velocity.enabled` | `false` | Bedrock has no Velocity modern-forwarding handshake. | X |
| `proxies.velocity.online-mode` | `true` | Bedrock has no Velocity online-mode handshake. | X |
| `proxies.velocity.secret` | `''` | Bedrock has no Velocity secret exchange. | X |
| `proxies.proxy-protocol` | `false` | RakNet startup exists, but HAProxy PROXY protocol is not a Bedrock transport equivalent. | N |
| `spark.enabled` | `true` | Paper Spark lifecycle has no BDS equivalent. | X |
| `spark.enable-immediately` | `false` | Paper Spark startup lifecycle has no BDS equivalent. | X |
| `scoreboards.track-plugin-scoreboards` | `false` | BDS ServerScoreboard (`0xE763B78`) and Endstone player-board tracking exist; ownership semantics need an adapter. | E |
| `scoreboards.save-empty-scoreboard-teams` | `true` | BDS scoreboard storage (`0xE763B78`) exists; empty-team serialization still needs a save hook. | I |
| `anticheat.obfuscation.items.enable-item-obfuscation` | `false` | BDS outbound ItemStack serialization (`0x85993B0`, `0x6E4B9C0`) provides a transformer boundary. | I |
| `anticheat.obfuscation.items.all-models.also-obfuscate` | `[]` | Bedrock item identity exists, but Java DataComponent/model identifiers are not one-to-one. | N |
| `anticheat.obfuscation.items.all-models.dont-obfuscate` | `[minecraft:lodestone_tracker]` | Bedrock item identity exists, but Java model identifiers are not one-to-one. | N |
| `anticheat.obfuscation.items.all-models.sanitize-count` | `true` | Bedrock outbound item count serialization can be rewritten after a Bedrock-specific identity map is defined. | I |
| `anticheat.obfuscation.items.model-overrides.minecraft:elytra.also-obfuscate` | `[]` | Bedrock item model identifiers differ from Java Elytra DataComponents. | N |
| `anticheat.obfuscation.items.model-overrides.minecraft:elytra.dont-obfuscate` | `[minecraft:damage]` | Bedrock has no one-to-one Java Elytra damage component mapping. | N |
| `anticheat.obfuscation.items.model-overrides.minecraft:elytra.sanitize-count` | `true` | Bedrock outbound item count serialization can be rewritten after a Bedrock-specific identity map is defined. | I |
| `update-checker.enabled` | `true` | Paper update service has no BDS gameplay/runtime equivalent. | X |
| `collisions.enable-player-collisions` | `true` | Existing Endstone `PushableByEntityUtility::push` hook identifies player/player pairs and is wired in this PR. | E |
| `collisions.send-full-pos-for-hard-colliding-entities` | `true` | BDS outbound movement packets (`0x6E4B9C0`) exist, but hard-collision entity selection and full-position encoding need a new hook. | I |

## Detailed 1.26.40 world audit

The following entries are the first leaf-level audit based on the supplied 1.26.40 Bedrock headers and the corresponding
LeviLamina reconstructions. `I` means the BDS path is real but still needs a version-specific hook/ABI and runtime test;
`N` means a Bedrock implementation can only be a documented subset; `X` means the Java behaviour has no safe Bedrock
equivalent.

The detailed tables cover all 208 scalar leaves in `paper-world-defaults.default.yml`; map-valued settings are shown
with their concrete defaults and an explicit `<...>` entry for extensible keys.

| Paper path | Default | 1.26.40 evidence and implementation boundary | Result |
| --- | ---: | --- | --- |
| `anticheat.anti-xray.enabled` | `false` | Bedrock has `LevelChunkPacket`, `SubChunkPacket`, and subchunk palettes; enabling this needs per-player packet rewriting. | I |
| `anticheat.anti-xray.engine-mode` | `1` | Paper serializes `1=HIDE`, `2=OBFUSCATE`, `3=OBFUSCATE_LAYER`; Bedrock palette rewriting is the required implementation boundary. | I |
| `anticheat.anti-xray.max-block-height` | `64` | Bedrock subchunks expose height/palette data; a height-limited rewrite needs packet and Y-range handling. | I |
| `anticheat.anti-xray.update-radius` | `2` | Bedrock chunk/block update packets exist, but the post-change neighbour rewrite radius is not an existing field. | I |
| `anticheat.anti-xray.lava-obscures` | `false` | Block state/palette data can identify lava, but the obscuring policy must be added to the packet rewrite. | I |
| `anticheat.anti-xray.use-permission` | `false` | Bedrock player permissions and packet subscriptions exist; the Paper bypass permission must be checked before rewriting. | I |
| `anticheat.anti-xray.hidden-blocks` | `copper_ore`, `deepslate_copper_ore`, `raw_copper_block`, `gold_ore`, `deepslate_gold_ore`, `iron_ore`, `deepslate_iron_ore`, `raw_iron_block`, `coal_ore`, `deepslate_coal_ore`, `lapis_ore`, `deepslate_lapis_ore`, `mossy_cobblestone`, `obsidian`, `chest`, `diamond_ore`, `deepslate_diamond_ore`, `redstone_ore`, `deepslate_redstone_ore`, `clay`, `emerald_ore`, `deepslate_emerald_ore`, `ender_chest` | The Paper registry list can be represented by Bedrock block states, but the per-player SubChunk transformation is new code. | I |
| `anticheat.anti-xray.replacement-blocks` | `[stone, oak_planks, deepslate]` | Bedrock palettes can encode replacement states; choosing them requires a new per-player packet transformer. | I |
| `entities.mob-effects.spiders-immune-to-poison-effect` | `true` | Bedrock exposes actor effect application and spider actor types; a targeted `canBeAffected`-equivalent hook is required. | I |
| `entities.mob-effects.immune-to-wither-effect.wither` | `true` | Bedrock Wither actor/effect paths exist; immunity must be checked at effect application, not by changing the effect registry. | I |
| `entities.mob-effects.immune-to-wither-effect.wither-skeleton` | `true` | Bedrock skeleton subtype and effect paths exist; subtype-specific immunity needs a targeted hook. | I |
| `entities.armor-stands.do-collision-entity-lookups` | `true` | Bedrock armor stands have actor collision/push paths; the collision lookup branch needs a targeted hook. | I |
| `entities.armor-stands.tick` | `true` | Bedrock armor stands have a normal tick path; disabling only ticking must preserve equipment updates. | I |
| `entities.markers.tick` | `true` | No Bedrock/Levi Java Marker actor or actor type was found. | X |
| `entities.sniffer.hatch-time` | `default` | Levi has Sniffer actors and Bedrock has the egg/block tick subsystem; the SnifferEgg timer caller remains to be located. | I |
| `entities.sniffer.boosted-hatch-time` | `default` | Same SnifferEgg path, with the boosted timer as a separate branch. | I |
| `entities.spawning.non-player-arrow-despawn-rate` | `default` | Bedrock `AbstractArrow` actors have tick/lifetime state; the Paper fallback rate needs a targeted despawn hook. | I |
| `entities.spawning.creative-arrow-despawn-rate` | `default` | The same arrow lifecycle has creative-state branches; the Paper category-specific fallback is not a BDS field. | I |
| `entities.spawning.max-arrow-despawn-invulnerability` | `200` | Bedrock arrow tick state can carry an invulnerability window; the 200-tick cap needs an ABI-verified hook. | I |
| `entities.spawning.filter-bad-tile-entity-nbt-from-falling-blocks` | `true` | Bedrock `FallingBlockActor` and block-actor NBT load paths exist; filter before actor creation. | I |
| `entities.spawning.filtered-entity-tag-nbt-paths` | `[Pos, Motion, sleeping_pos]` | Bedrock actor load/spawn-egg factories have NBT paths, but the Paper permission-gated filter must be added. | I |
| `entities.spawning.disable-mob-spawner-spawn-egg-transformation` | `false` | Bedrock `MobSpawnerBlock`/`BaseMobSpawner` and SpawnEgg use paths exist; block-actor transformation needs a targeted hook. | I |
| `entities.spawning.per-player-mob-spawns` | `true` | Levi `NaturalSpawner`/`BedrockSpawner` expose per-player candidate and cap logic; the BDS scheduler needs a per-player adapter. | I |
| `entities.spawning.scan-for-legacy-ender-dragon` | `true` | Bedrock `EndDragonFight` and dragon state loading exist; the legacy scan/kill-state branch needs a hook. | I |
| `entities.spawning.spawn-limits.monster` | `-1` | Bedrock natural spawners expose monster category counts; negative Paper values fall back to the world default. | I |
| `entities.spawning.spawn-limits.creature` | `-1` | Bedrock natural spawners expose creature category counts; negative Paper values fall back to the world default. | I |
| `entities.spawning.spawn-limits.ambient` | `-1` | Bedrock natural spawners expose ambient category counts; negative Paper values fall back to the world default. | I |
| `entities.spawning.spawn-limits.axolotls` | `-1` | Bedrock natural spawners expose axolotl category counts; negative Paper values fall back to the world default. | I |
| `entities.spawning.spawn-limits.underground-water-creature` | `-1` | Bedrock natural spawners expose underground-water category counts; negative Paper values fall back to the world default. | I |
| `entities.spawning.spawn-limits.water-creature` | `-1` | Bedrock natural spawners expose water-creature category counts; negative Paper values fall back to the world default. | I |
| `entities.spawning.spawn-limits.water-ambient` | `-1` | Bedrock natural spawners expose water-ambient category counts; negative Paper values fall back to the world default. | I |
| `entities.spawning.despawn-ranges.monster.hard` | `default` | Bedrock actor despawn checks have category/range inputs; Paper hard-distance semantics need a hook. | I |
| `entities.spawning.despawn-ranges.monster.soft` | `default` | Bedrock actor despawn checks have category/range inputs; Paper soft-distance/random semantics need a hook. | I |
| `entities.spawning.despawn-ranges.creature.hard` | `default` | Bedrock actor despawn checks have category/range inputs; Paper hard-distance semantics need a hook. | I |
| `entities.spawning.despawn-ranges.creature.soft` | `default` | Bedrock actor despawn checks have category/range inputs; Paper soft-distance/random semantics need a hook. | I |
| `entities.spawning.despawn-ranges.ambient.hard` | `default` | Bedrock actor despawn checks have category/range inputs; Paper hard-distance semantics need a hook. | I |
| `entities.spawning.despawn-ranges.ambient.soft` | `default` | Bedrock actor despawn checks have category/range inputs; Paper soft-distance/random semantics need a hook. | I |
| `entities.spawning.despawn-ranges.axolotls.hard` | `default` | Bedrock actor despawn checks have category/range inputs; Paper hard-distance semantics need a hook. | I |
| `entities.spawning.despawn-ranges.axolotls.soft` | `default` | Bedrock actor despawn checks have category/range inputs; Paper soft-distance/random semantics need a hook. | I |
| `entities.spawning.despawn-ranges.underground-water-creature.hard` | `default` | Bedrock actor despawn checks have category/range inputs; Paper hard-distance semantics need a hook. | I |
| `entities.spawning.despawn-ranges.underground-water-creature.soft` | `default` | Bedrock actor despawn checks have category/range inputs; Paper soft-distance/random semantics need a hook. | I |
| `entities.spawning.despawn-ranges.water-creature.hard` | `default` | Bedrock actor despawn checks have category/range inputs; Paper hard-distance semantics need a hook. | I |
| `entities.spawning.despawn-ranges.water-creature.soft` | `default` | Bedrock actor despawn checks have category/range inputs; Paper soft-distance/random semantics need a hook. | I |
| `entities.spawning.despawn-ranges.water-ambient.hard` | `default` | Bedrock actor despawn checks have category/range inputs; Paper hard-distance semantics need a hook. | I |
| `entities.spawning.despawn-ranges.water-ambient.soft` | `default` | Bedrock actor despawn checks have category/range inputs; Paper soft-distance/random semantics need a hook. | I |
| `entities.spawning.despawn-ranges.misc.hard` | `default` | Bedrock actor despawn checks have category/range inputs; Paper hard-distance semantics need a hook. | I |
| `entities.spawning.despawn-ranges.misc.soft` | `default` | Bedrock actor despawn checks have category/range inputs; Paper soft-distance/random semantics need a hook. | I |
| `entities.spawning.despawn-range-shape` | `ELLIPSOID` | Bedrock actor position queries exist; selecting ellipsoid versus cylinder requires changing the distance predicate. | I |
| `entities.spawning.despawn-time.minecraft:snowball` | `disabled` | Bedrock `Snowball` actor lifetime exists; the Paper total-age override needs an actor-tick hook. | I |
| `entities.spawning.despawn-time.minecraft:llama_spit` | `disabled` | Bedrock `LlamaSpit` actor lifetime exists; the Paper total-age override needs an actor-tick hook. | I |
| `entities.spawning.ticks-per-spawn.monster` | `-1` | Bedrock natural-spawner tick scheduling has monster categories; negative values fall back to the world scheduler. | I |
| `entities.spawning.ticks-per-spawn.creature` | `-1` | Bedrock natural-spawner tick scheduling has creature categories; negative values fall back to the world scheduler. | I |
| `entities.spawning.ticks-per-spawn.ambient` | `-1` | Bedrock natural-spawner tick scheduling has ambient categories; negative values fall back to the world scheduler. | I |
| `entities.spawning.ticks-per-spawn.axolotls` | `-1` | Bedrock natural-spawner tick scheduling has axolotl categories; negative values fall back to the world scheduler. | I |
| `entities.spawning.ticks-per-spawn.underground-water-creature` | `-1` | Bedrock natural-spawner tick scheduling has underground-water categories; negative values fall back to the world scheduler. | I |
| `entities.spawning.ticks-per-spawn.water-creature` | `-1` | Bedrock natural-spawner tick scheduling has water-creature categories; negative values fall back to the world scheduler. | I |
| `entities.spawning.ticks-per-spawn.water-ambient` | `-1` | Bedrock natural-spawner tick scheduling has water-ambient categories; negative values fall back to the world scheduler. | I |
| `entities.spawning.despawn-time.<entity-type>` | `disabled` when absent | Bedrock actor/item lifetime fields exist; arbitrary Paper entity-type age limits require a type-aware actor-tick hook. | I |
| `entities.spawning.wateranimal-spawn-height.maximum` | `default` | Bedrock water-animal spawn rules expose Y checks and sea-level fallbacks; add a configured boundary. | I |
| `entities.spawning.wateranimal-spawn-height.minimum` | `default` | Bedrock water-animal spawn rules expose Y checks; add a configured lower boundary. | I |
| `entities.spawning.slime-spawn-height.surface-biome.minimum` | `50` | Bedrock slime spawn rules expose surface-biome Y checks; add a configured lower boundary. | I |
| `entities.spawning.slime-spawn-height.surface-biome.maximum` | `70` | Bedrock slime spawn rules expose surface-biome Y checks; add a configured upper boundary. | I |
| `entities.spawning.slime-spawn-height.slime-chunk.maximum` | `40` | Bedrock slime-chunk spawn rules expose Y checks; add a configured upper boundary. | I |
| `entities.spawning.wandering-trader.spawn-minute-length` | `1200` | Bedrock wandering-trader scheduler has attempt timers; Paper's minute interval needs a scheduler hook. | I |
| `entities.spawning.wandering-trader.spawn-day-length` | `24000` | Bedrock wandering-trader scheduler has daily delay state; Paper's day length needs a scheduler hook. | I |
| `entities.spawning.wandering-trader.spawn-chance-failure-increment` | `25` | Bedrock wandering-trader scheduler tracks failed attempts/chance; the increment needs a configured branch. | I |
| `entities.spawning.wandering-trader.spawn-chance-min` | `25` | Bedrock wandering-trader scheduler tracks chance; the lower bound needs a configured branch. | I |
| `entities.spawning.wandering-trader.spawn-chance-max` | `75` | Bedrock wandering-trader scheduler tracks chance; the upper bound needs a configured branch. | I |
| `entities.spawning.all-chunks-are-slime-chunks` | `false` | Bedrock chunk seed/slime checks exist; a forced result can be inserted in the slime predicate. | I |
| `entities.spawning.skeleton-horse-thunder-spawn-chance` | `default` | Bedrock lightning/skeleton-horse trap and spawn paths exist; Paper's fallback chance needs a hook. | I |
| `entities.spawning.iron-golems-can-spawn-in-air` | `false` | Bedrock iron-golem spawn checks include support/block predicates; remove only the support requirement in a targeted hook. | I |
| `entities.spawning.count-all-mobs-for-spawning` | `false` | Bedrock natural-spawner entity counts exist; include or exclude non-natural sources in the cap calculation. | I |
| `entities.spawning.monster-spawn-max-light-level` | `default` | Bedrock monster spawn checks expose dimension/block-light limits; configurable maximum needs a hook. | I |
| `entities.spawning.duplicate-uuid.mode` | `SAFE_REGEN` | Bedrock `ActorUniqueID` and chunk entity loading exist; duplicate handling needs a load-time policy hook. | I |
| `entities.spawning.duplicate-uuid.safe-regen-delete-range` | `32` | Bedrock chunk entity lists and actor positions exist; safe-regen deletion range needs a load-time filter. | I |
| `entities.spawning.alt-item-despawn-rate.enabled` | `false` | Bedrock `ItemActor` age/lifetime fields exist; enable a type-aware lifetime table only when configured. | I |
| `entities.spawning.alt-item-despawn-rate.items.minecraft:cobblestone` | `300` | Bedrock `ItemActor` exposes item stack and age/lifetime; cobblestone needs a configured per-item lifetime branch. | I |
| `entities.behavior.disable-chest-cat-detection` | `false` | Bedrock chest/block-actor obstruction and cat lookup paths exist; skip only the cat check. | I |
| `entities.behavior.spawner-nerfed-mobs-should-jump` | `false` | Bedrock mob-spawner and jump/float goals exist; preserve or remove the jump goal in the spawner spawn branch. | I |
| `entities.behavior.experience-merge-max-value` | `-1` | Bedrock `ExperienceOrb` merge/tick paths exist; cap or split merged values before replacing the orb. | I |
| `entities.behavior.should-remove-dragon` | `false` | Bedrock `EndDragonFight` and `EnderDragon` state exist; remove only the legacy active dragon branch. | I |
| `entities.behavior.zombies-target-turtle-eggs` | `true` | Bedrock Zombie, TurtleEggBlock, and stomp-goal paths exist; add/remove that target goal. | I |
| `entities.behavior.piglins-guard-chests` | `true` | Bedrock Piglin and chest interaction/anger paths exist; gate the guard reaction. | I |
| `entities.behavior.baby-zombie-movement-modifier` | `0.5` | Bedrock Zombie/Mob attributes expose baby movement modifiers; adjust only the baby modifier. | I |
| `entities.behavior.allow-spider-world-border-climbing` | `true` | Bedrock Spider climbing and collision paths exist; the border-specific collision branch needs a hook. | I |
| `entities.behavior.door-breaking-difficulty.minecraft:zombie` | `[HARD]` | Bedrock BreakDoorGoal/DoorBlock and Zombie difficulty checks exist; replace the allowed difficulty list. | I |
| `entities.behavior.door-breaking-difficulty.minecraft:husk` | `[HARD]` | Bedrock Husk/Zombie subtype and BreakDoorGoal paths exist; replace the allowed difficulty list. | I |
| `entities.behavior.door-breaking-difficulty.minecraft:zombie_villager` | `[HARD]` | Bedrock ZombieVillager and BreakDoorGoal paths exist; replace the allowed difficulty list. | I |
| `entities.behavior.door-breaking-difficulty.minecraft:zombified_piglin` | `[HARD]` | Bedrock zombified-piglin actor and BreakDoorGoal paths exist; replace the allowed difficulty list. | I |
| `entities.behavior.door-breaking-difficulty.minecraft:vindicator` | `[NORMAL, HARD]` | Bedrock Vindicator/HumanoidMonster and BreakDoorGoal paths exist; replace the allowed difficulty list. | I |
| `entities.behavior.door-breaking-difficulty.<entity-type>` | per-entity default | Bedrock BreakDoorGoal supports a type-aware difficulty predicate; arbitrary map entries need validation. | I |
| `entities.behavior.disable-creeper-lingering-effect` | `false` | Bedrock Creeper explosion/effect-spawn paths exist; skip only the AreaEffectCloud/effect branch. | I |
| `entities.behavior.ender-dragons-death-always-places-dragon-egg` | `false` | Bedrock EndDragonFight/DragonEggBlock state exists; gate repeated dragon-egg placement. | I |
| `entities.behavior.phantoms-do-not-spawn-on-creative-players` | `true` | Bedrock Phantom spawn rules and player game mode exist; exclude creative players in the spawn predicate. | I |
| `entities.behavior.phantoms-only-attack-insomniacs` | `true` | Bedrock Phantom and InsomniaComponent/InsomniaSystem paths exist; gate target selection. | I |
| `entities.behavior.player-insomnia-start-ticks` | `72000` | Bedrock insomnia timer state exists; change the threshold used by Phantom logic. | I |
| `entities.behavior.phantoms-spawn-attempt-min-seconds` | `60` | Bedrock Phantom/natural-spawn tick scheduling exists; change the lower random interval bound. | I |
| `entities.behavior.phantoms-spawn-attempt-max-seconds` | `119` | Bedrock Phantom/natural-spawn tick scheduling exists; change the upper random interval bound. | I |
| `entities.behavior.parrots-are-unaffected-by-player-movement` | `false` | Bedrock Player shoulder/passenger state and Parrot actor paths exist; preserve or clear the movement-drop branch. | I |
| `entities.behavior.zombie-villager-infection-chance` | `default` | Bedrock Zombie/Villager conversion paths exist; difficulty-dependent infection probability needs a hook. | I |
| `entities.behavior.mobs-can-always-pick-up-loot.zombies` | `false` | Bedrock Zombie/Mob pickup state exists; bypass the random/difficulty gate when enabled. | I |
| `entities.behavior.mobs-can-always-pick-up-loot.skeletons` | `false` | Bedrock Skeleton/Mob pickup state exists; bypass the random/difficulty gate when enabled. | I |
| `entities.behavior.disable-player-crits` | `false` | Bedrock Player attack parameters include a critical-hit decision; gate it before damage calculation. | I |
| `entities.behavior.nerf-pigmen-from-nether-portals` | `false` | Bedrock PortalBlock pig-zombie/piglin spawn and awareness paths exist; change only portal-spawned actors. | I |
| `entities.behavior.only-merge-items-horizontally` | `false` | Bedrock ItemActor neighbour merge paths exist; set the merge query's vertical extent to zero. | I |
| `entities.behavior.pillager-patrols.disable` | `false` | Bedrock Pillager patrol spawn/reason paths exist; skip patrol attempts when enabled. | I |
| `entities.behavior.pillager-patrols.spawn-chance` | `0.2` | Bedrock patrol scheduler tracks spawn attempts/chance; replace the probability. | I |
| `entities.behavior.pillager-patrols.spawn-delay.per-player` | `false` | Bedrock player/level tick and patrol state exist; choose shared or per-player delay storage. | I |
| `entities.behavior.pillager-patrols.spawn-delay.ticks` | `12000` | Bedrock patrol scheduler has delay state; replace the retry delay. | I |
| `entities.behavior.pillager-patrols.start.per-player` | `false` | Bedrock player/level day and patrol state exist; choose shared or per-player start tracking. | I |
| `entities.behavior.pillager-patrols.start.day` | `5` | Bedrock patrol scheduler has world-day state; replace the initial day threshold. | I |
| `entities.behavior.cooldown-failed-beehive-releases` | `true` | Bedrock BeehiveBlockActor/Bee release and retry paths exist; gate the failure cooldown. | I |
| `entities.behavior.stuck-entity-poi-retry-delay` | `200` | Bedrock POI/navigation and stuck-goal paths exist; replace the retry delay or disable it. | I |
| `entities.tracking-range-y.enabled` | `false` | Bedrock `ActorReplication`/`Dimension` relevance and add/remove actor packets provide a vertical tracking filter boundary. | I |
| `entities.tracking-range-y.player` | `default` | Bedrock player replication/location sender paths exist; use the normal tracking range when unset and add a Y filter when configured. | I |
| `entities.tracking-range-y.animal` | `default` | Bedrock actor replication and mob categories provide an animal/water/villager filter boundary. | I |
| `entities.tracking-range-y.monster` | `default` | Bedrock actor replication and monster/raider categories provide a monster filter boundary. | I |
| `entities.tracking-range-y.misc` | `default` | Bedrock item/XP/hanging actor replication provides a misc filter boundary. | I |
| `entities.tracking-range-y.display` | `default` | Levi/BDS display actor manager and display entity lists provide a display filter boundary. | I |
| `entities.tracking-range-y.other` | `default` | Bedrock actor replication provides a fallback other-entity filter boundary. | I |
| `lootables.auto-replenish` | `false` | Bedrock randomizable block actors have loot tables/fill paths; add timed refill state without changing ordinary containers. | I |
| `lootables.restrict-player-reloot` | `true` | Bedrock randomizable containers have player identity/open/loot state; add the Paper per-player reloot check. | I |
| `lootables.restrict-player-reloot-time` | `disabled` | Paper's `disabled` value with the default restriction means a player cannot reloot once recorded; Bedrock container/player time state can represent this. | I |
| `lootables.reset-seed-on-fill` | `true` | Bedrock randomizable container loot seed and fill paths exist; reset the seed at the configured refill boundary. | I |
| `lootables.max-refills` | `-1` | Bedrock randomizable container persistent state can track refill count; negative means unlimited. | I |
| `lootables.refresh-min` | `12h` | Bedrock container tick/level clock can schedule a random refill lower bound. | I |
| `lootables.refresh-max` | `2d` | Bedrock container tick/level clock can schedule a random refill upper bound. | I |
| `lootables.retain-unlooted-shulker-box-loot-table-on-non-player-break` | `true` | Bedrock ShulkerBox block/actor and randomizable container removal paths exist; preserve an unfilled loot table on non-player break. | I |
| `scoreboards.allow-non-player-entities-on-scoreboards` | `true` | Endstone scoreboard identity creation already handles `Actor` entries; BDS `Scoreboard`/`IdentityDictionary` has entity identities. | E |
| `scoreboards.use-vanilla-world-scoreboard-name-coloring` | `false` | Bedrock scoreboards have objectives/identities but no Java Bukkit `Team`/`teamDisplayName` color abstraction. | X |
| `spawn.allow-using-signs-inside-spawn-protection` | `false` | Bedrock sign interaction and spawn-protection permission checks exist; bypass only the sign interaction branch. | I |
| `maps.item-frame-cursor-limit` | `128` | Endstone/BDS map decoration and item-frame tracking paths exist; cap tracked cursors before adding decorations. | I |
| `maps.item-frame-cursor-update-interval` | `10` | Endstone/BDS map tick and item-frame cursor packet paths exist; schedule updates at the configured interval. | I |
| `fixes.fix-items-merging-through-walls` | `false` | Bedrock ItemActor merge paths and `BlockSource::clip` exist; reject a merge when a block ray blocks the two item positions. | I |
| `fixes.disable-unloaded-chunk-enderpearl-exploit` | `false` | Bedrock ThrownEnderpearl owner/tick and chunk lifecycle paths exist; this only has Paper meaning together with `misc.legacy-ender-pearl-behavior`. | I |
| `fixes.prevent-tnt-from-moving-in-water` | `false` | Bedrock PrimedTnt tick and fluid movement paths exist; suppress fluid impulse while preserving TNT ticking. | I |
| `fixes.split-overstacked-loot` | `true` | Bedrock LootTable/LootPool and ItemStack output paths exist; split results at the item maximum. | I |
| `fixes.falling-block-height-nerf` | `disabled` | Bedrock FallingBlockActor tick/position exists; remove or drop the actor above a configured Y threshold. | I |
| `fixes.tnt-entity-height-nerf` | `disabled` | Bedrock PrimedTnt and MinecartTNT tick/position paths exist; remove entities above a configured Y threshold. | I |
| `unsupported-settings.fix-invulnerable-end-crystal-exploit` | `true` | Bedrock EnderCrystal/EndDragonFight/SpikeFeature state exists; clear stale invulnerability/beam state at the fight boundary. | I |
| `unsupported-settings.disable-world-ticking-when-empty` | `false` | Bedrock Level/Dimension, ticking areas, and chunk tick-range managers exist; skip only when no players/tickets require ticking. | I |
| `unsupported-settings.ticking.chunks` | `true` | Bedrock LevelChunk/TickingLevelChunk and chunk tick-range managers exist; gate chunk ticking independently. | I |
| `unsupported-settings.ticking.block-entities` | `true` | Bedrock BlockActor/LevelChunk ticker registration and updates exist; gate block-entity ticking independently. | I |
| `fishing-time-range.minimum` | `100` | Bedrock FishingHook has bite/lure timers and server update paths; replace the lower wait bound. | I |
| `fishing-time-range.maximum` | `600` | Bedrock FishingHook has bite/lure timers and server update paths; replace the upper wait bound. | I |
| `tick-rates.grass-spread` | `1` | Bedrock GrassBlock random-tick and block-ticking queues exist; throttle grass spread without changing other random ticks. | I |
| `tick-rates.container-update` | `1` | Bedrock PlayerTickProxy/container broadcast paths exist; change inventory synchronization cadence. | I |
| `tick-rates.mob-spawner` | `1` | Bedrock BaseMobSpawner/MobSpawnerBlockActor tick paths exist; gate or retime spawner updates. | I |
| `tick-rates.wet-farmland` | `1` | Bedrock FarmBlock random-tick path exposes moisture state; throttle only wet farmland. | I |
| `tick-rates.dry-farmland` | `1` | Bedrock FarmBlock random-tick path exposes moisture state; throttle only dry farmland. | I |
| `tick-rates.sensor.minecraft:villager.secondarypoisensor` | `40` | Bedrock EntitySensorSystem/BehaviorSystem and villager POI paths exist; retime this sensor key. | I |
| `tick-rates.behavior.minecraft:villager.validatenearbypoi` | `-1` | Bedrock BehaviorSystem/villager POI paths exist; use the behavior default for negative values. | I |
| `tick-rates.sensor.<entity-type>.<sensor-key>` | `-1` | Bedrock sensor definitions and EntitySensorSystem provide a type/key scheduling boundary. | I |
| `tick-rates.behavior.<entity-type>.<behavior-key>` | `-1` | Bedrock behavior definitions and BehaviorSystem provide a type/key scheduling boundary. | I |
| `feature-seeds.generate-random-seeds-for-all` | `false` | Bedrock levelgen feature registries, WorldGenRandom, and chunk generation exist; generating/persisting configured-feature seeds needs a worldgen hook. | I |
| `feature-seeds.features.<configured-feature>` | `{}` (missing values use `-1`) | Bedrock feature/chunk generation has seed inputs; mapping a configured feature to Paper's decoration seed chain needs a generator hook. | I |
| `command-blocks.permissions-level` | `2` | Bedrock BaseCommandBlock/CommandBlockActor and BlockCommandOrigin expose command permission levels; replace the command-block source level. | I |
| `command-blocks.force-follow-perm-level` | `true` | Bedrock BlockCommandOrigin/command execution paths expose source permissions; enforce or relax the configured level requirement. | I |
| `misc.update-pathfinding-on-block-update` | `true` | Bedrock Level block updates and PathNavigation/PathFinder paths exist; gate navigation refreshes after shape changes. | I |
| `misc.show-sign-click-command-failure-msgs-to-player` | `false` | Bedrock SignBlockActor has text/open/edit paths but no Java sign ClickEvent.RunCommand failure message mechanism. | X |
| `misc.redstone-implementation` | `VANILLA` | Bedrock CircuitSystem/redstone update paths exist, but Java Vanilla/Eigencraft/Alternate Current algorithms are not shared. | I |
| `misc.alternate-current-update-order` | `HORIZONTAL_FIRST_OUTWARD` | Bedrock redstone update queues exist; porting Java Alternate Current order would be a new algorithm, not a field switch. | I |
| `misc.disable-end-credits` | `false` | Bedrock EndPortal/player credits and seen-state paths exist; skip the credits transition when configured. | I |
| `misc.max-leash-distance` | `default` | Bedrock Actor leash tick/holder paths exist; replace the snap-distance predicate. | I |
| `misc.disable-sprint-interruption-on-attack` | `false` | Bedrock Player attack/AttackParameters and sprint state exist; preserve sprint after a successful attack. | I |
| `misc.disable-relative-projectile-velocity` | `false` | Bedrock ProjectileFactory/Throwable shoot paths use actor velocity; omit source velocity when configured. | I |
| `misc.legacy-ender-pearl-behavior` | `false` | Bedrock ThrownEnderpearl/EnderpearlItem and chunk/portal lifecycle paths exist; select legacy ticket behavior. | I |
| `misc.allow-remote-ender-dragon-respawning` | `false` | Bedrock EndDragonFight/EnderCrystal/portal-frame paths exist; gate the portal-proximity requirement. | I |
| `max-growth-height.cactus` | `3` | Levi `CactusBlock::randomTick`/`tick` are dedicated growth paths; add a targeted hook and check column height before growth. | I |
| `max-growth-height.reeds` | `3` | Levi `SugarCaneBlock::randomTick`/`tick` are dedicated growth paths; add a targeted hook and check column height. | I |
| `max-growth-height.bamboo.max` | `16` | Levi `BambooStalkBlock::randomTick`, `tick`, and `getMaxHeight` expose the exact growth subsystem; hook the state decision. | I |
| `max-growth-height.bamboo.min` | `11` | Same Bamboo state machine; Java's minimum-height semantics require runtime comparison. | N/I |
| `environment.disable-thunder` | `false` | BDS `WeatherManager::updateWeather` has independent lightning level/time inputs; Endstone clears both and keeps rain. | E |
| `environment.disable-ice-and-snow` | `false` | Windows 1.26.40 IDA has SnowBlock/IceBlock random-tick registration/executor anchors; the separate accumulation/freeze leaves still need targeted hooks. | I |
| `environment.optimize-explosions` | `false` | BDS has explosion parameters but no equivalent optimization mode; changing radius/resistance would change gameplay. | X |
| `environment.disable-explosion-knockback` | `false` | `Explosion::explode` directly applies impulse; `knockback_scaling_` is a candidate but its offset and all variants require ABI proof. | I |
| `environment.generate-flat-bedrock` | `false` | Bedrock generators exist, but no current flat-bedrock feature switch or safe shared generator hook is established. | X |
| `environment.frosted-ice.enabled` | `true` | Windows 1.26.40 IDA has FrostedIce/FrostWalker behavior anchors; the ice generation/melt leaf still needs a targeted hook. | I |
| `environment.frosted-ice.delay.min` | `20` | Frosted-ice queued tick behavior exists, but no native delay field was confirmed; adjust scheduling only after ABI proof. | N/I |
| `environment.frosted-ice.delay.max` | `40` | Same queued tick behavior and no confirmed native delay field as the minimum. | N/I |
| `environment.void-damage-amount` | `4` | BDS has `ActorDamageCause::Void` and Endstone's before-hurt event can modify damage; threshold/timing still require ABI/runtime proof. | N/I |
| `environment.void-damage-min-build-height-offset` | `-64` | BDS exposes dimension minimum height and block-source minimum height; the original void-damage cadence must be matched. | N/I |
| `environment.treasure-maps.enabled` | `true` | No BDS equivalent of Paper's Java treasure-map trade/search/reloot configuration was found. | X |
| `environment.treasure-maps.find-already-discovered.villager-trade` | `false` | No matching Bedrock villager trade discovery state. | X |
| `environment.treasure-maps.find-already-discovered.loot-tables` | `default` | Bedrock loot tables exist, but not the Java discovered-map decision. | X |
| `environment.fire-tick-delay` | `30` | Windows 1.26.40 IDA confirms FireBlock logic, but the exact random-tick/checkBurn leaf and delay field remain to be located. | I |
| `environment.water-over-lava-flow-speed` | `5` | Windows 1.26.40 IDA confirms `LiquidBlock::_trySpreadTo` (`0x142E116C0`) and water/lava scheduling; no Paper-style speed field exists. | I |
| `environment.portal-search-radius` | `128` | BDS exposes `ILevel::getPortalForcer`; PortalForcer search must be located before changing the radius. | I |
| `environment.portal-create-radius` | `16` | Same PortalForcer ABI requirement for creation. | I |
| `environment.portal-search-vanilla-dimension-scaling` | `true` | BDS dimension conversion exists, but Java's scaling toggle is not a shared field and changing it can corrupt transfers. | X/N |
| `environment.nether-ceiling-void-damage-height` | `disabled` | BDS has dimension heights and void damage, but no Java Nether-ceiling threshold equivalent. | X |
| `environment.max-fluid-ticks` | `65536` | BDS has LevelChunk tick/random-tick queues; a fluid budget requires locating the queue scheduler. | I |
| `environment.max-block-ticks` | `65536` | Same scheduler requirement, separated from fluid processing. | I |
| `environment.locate-structures-outside-world-border` | `false` | No BDS WorldBorder/structure-locator equivalent was established. | X |
| `chunks.auto-save-interval` | `default` | Windows 1.26.40 confirms the ChunkSource save system, but the exact save scheduler field is not yet isolated. | I |
| `chunks.max-auto-save-chunks-per-tick` | `24` | BDS chunk save is available, but no native per-tick save budget was confirmed. | I |
| `chunks.fixed-chunk-inhabited-time` | `-1` | No Java inhabited-time equivalent was confirmed in BDS; do not map `LevelChunk::last_tick_` by name. | X/I |
| `chunks.prevent-moving-into-unloaded-chunks` | `false` | BDS chunk publisher/movement lifecycle exists; the exact movement correction ABI remains to be isolated. | I |
| `chunks.delay-chunk-unloads-by` | `10s` | BDS ChunkSource/NetworkChunkPublisher region lifecycle exists, but no delay field was confirmed. | I |
| `chunks.entity-per-chunk-save-limit.*` | `-1` | BDS actor/chunk persistence exists, but no per-type save-limit field was confirmed; filtering risks data loss. | I |
| `chunks.flush-regions-on-save` | `false` | BDS chunk save/unload exists, but Java region flush has no confirmed equivalent. | I |
| `hopper.cooldown-when-full` | `true` | Windows 1.26.40 confirms the HopperSystem registration chain (`0x1417C27C0`, `0x1417C980F`); Levi exposes cooldown fields, but the tick/full branch remains to be located. | I |
| `hopper.disable-move-event` | `false` | Bedrock has hopper transfer functions but no Java `InventoryMoveItemEvent`; disabling all transfer is not equivalent. | X |
| `hopper.ignore-occluding-blocks` | `false` | Hopper container lookup and collision-shape paths exist; Windows IDA has not yet isolated the occlusion predicate. | I |
| `collisions.only-players-collide` | `false` | Existing BDS `PushableByEntityUtility::push` filtering suppresses pairs where neither actor is a player; vehicle/special collision paths remain outside this subset. | E/N |
| `collisions.allow-vehicle-collisions` | `true` | `PushableByEntityUtility::push` (`0x142CF1F50`) accepts actor context, but vehicle boarding/special paths need separate validation. | E/I |
| `collisions.fix-climbing-bypassing-cramming-rule` | `false` | No Java cramming rule or matching BDS counter was established. | X |
| `collisions.max-entity-collisions` | `8` | Windows 1.26.40 confirms `Mob::pushActors` (`0x14240A4A0`) as the per-owner candidate loop; a counter can be added there, but no native max field exists. | E/I |
| `collisions.allow-player-cramming-damage` | `false` | Windows 1.26.40 found no explicit cramming/playersqueeze damage path; do not claim a native equivalent until one is located. | I |
