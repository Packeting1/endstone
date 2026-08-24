# Paper-Compatible Configuration Audit

## Scope and accounting

This audit covers the packaged templates `endstone/config/endstone-global.yml` and `endstone/config/endstone-world-defaults.yml` in this checkout. A **leaf** is a scalar, list, or mapping-valued configuration entry that is not further expanded by the template's configuration shape; placeholder entries such as `<entity-type>` and `<item-type>` are retained as literal template leaves. The two metadata leaves `unsupported-settings.inline-docs-warning.color` and `unsupported-settings.inline-docs-warning.message`, plus the documentation-only `packet-limiter.overrides.header.message`, are deliberately excluded. Counts are therefore **93 global leaves + 195 world-default schema leaves = 288 audited leaves**. The world inventory contains 181 fixed leaves and 14 placeholder schema leaves.

`IMPLEMENTED` means the current source reads the exact synchronized `paper.global.*` or `paper.world_defaults.*` path and uses it at a verified runtime decision point. `BRIDGE_ONLY` means the value is synchronized by `endstone/cli/paper_config.py` into `endstone.toml`, but this checkout has no safe verified Bedrock runtime decision point for the Paper behavior. The world-default table is Level-wide; Bedrock does not provide Paper's independent per-world YAML model.

## Global defaults — 93 leaves

| Path | Status | Evidence |
| --- | --- | --- |
| `anticheat.obfuscation.items.all-models.also-obfuscate` | BRIDGE_ONLY | No safe Bedrock item-obfuscation decision point is identified. |
| `anticheat.obfuscation.items.all-models.dont-obfuscate` | BRIDGE_ONLY | No safe Bedrock item-obfuscation decision point is identified. |
| `anticheat.obfuscation.items.all-models.sanitize-count` | BRIDGE_ONLY | No safe Bedrock item-obfuscation decision point is identified. |
| `anticheat.obfuscation.items.enable-item-obfuscation` | BRIDGE_ONLY | No safe Bedrock item-obfuscation decision point is identified. |
| `anticheat.obfuscation.items.model-overrides.minecraft:elytra.also-obfuscate` | BRIDGE_ONLY | No safe Bedrock item-obfuscation decision point is identified. |
| `anticheat.obfuscation.items.model-overrides.minecraft:elytra.dont-obfuscate` | BRIDGE_ONLY | No safe Bedrock item-obfuscation decision point is identified. |
| `anticheat.obfuscation.items.model-overrides.minecraft:elytra.sanitize-count` | BRIDGE_ONLY | No safe Bedrock item-obfuscation decision point is identified. |
| `block-updates.disable-chorus-plant-updates` | BRIDGE_ONLY | No safe Bedrock block-update decision point is identified. |
| `block-updates.disable-mushroom-block-updates` | BRIDGE_ONLY | No safe Bedrock block-update decision point is identified. |
| `block-updates.disable-noteblock-updates` | BRIDGE_ONLY | No safe Bedrock block-update decision point is identified. |
| `block-updates.disable-tripwire-updates` | BRIDGE_ONLY | No safe Bedrock block-update decision point is identified. |
| `chunk-loading-advanced.auto-config-send-distance` | BRIDGE_ONLY | No safe Bedrock chunk-send policy decision point is identified. |
| `chunk-loading-advanced.player-max-concurrent-chunk-generates` | BRIDGE_ONLY | No safe Bedrock chunk-generation decision point is identified. |
| `chunk-loading-advanced.player-max-concurrent-chunk-loads` | BRIDGE_ONLY | No safe Bedrock chunk-load decision point is identified. |
| `chunk-loading-basic.player-max-chunk-generate-rate` | BRIDGE_ONLY | No safe Bedrock chunk-generation rate decision point is identified. |
| `chunk-loading-basic.player-max-chunk-load-rate` | BRIDGE_ONLY | No safe Bedrock chunk-load rate decision point is identified. |
| `chunk-loading-basic.player-max-chunk-send-rate` | BRIDGE_ONLY | No safe Bedrock chunk-send rate decision point is identified. |
| `chunk-system.io-threads` | BRIDGE_ONLY | No safe Bedrock chunk-system thread decision point is identified. |
| `chunk-system.worker-threads` | BRIDGE_ONLY | No safe Bedrock chunk-system thread decision point is identified. |
| `collisions.enable-player-collisions` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/pushable_by_entity_utility.cpp`: reads `paper.global.collisions.enable-player-collisions` and skips vanilla player-to-player push when false. |
| `collisions.send-full-pos-for-hard-colliding-entities` | BRIDGE_ONLY | No safe Bedrock hard-collision position serialization decision point is identified. |
| `commands.ride-command-allow-player-as-vehicle` | BRIDGE_ONLY | No safe Bedrock ride-command decision point is identified. |
| `commands.suggest-player-names-when-null-tab-completions` | BRIDGE_ONLY | No safe Bedrock command-completion decision point is identified. |
| `console.enable-brigadier-completions` | BRIDGE_ONLY | Paper Brigadier completion behavior has no safe Bedrock equivalent identified. |
| `console.enable-brigadier-highlighting` | BRIDGE_ONLY | Paper Brigadier highlighting behavior has no safe Bedrock equivalent identified. |
| `console.has-all-permissions` | IMPLEMENTED | `src/endstone/core/command/console_command_sender.cpp`: reads `paper.global.console.has-all-permissions` for permission checks. |
| `item-validation.book.author` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/packet.cpp`: reads `paper.global.item-validation.book.author` before native book finalization. |
| `item-validation.book.page` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/packet.cpp`: reads `paper.global.item-validation.book.page` before native page handling. |
| `item-validation.book.title` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/packet.cpp`: reads `paper.global.item-validation.book.title` before native book finalization. |
| `item-validation.book-size.page-max` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/packet.cpp`: reads `paper.global.item-validation.book-size.page-max` and applies the additional byte cap. |
| `item-validation.book-size.total-multiplier` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/packet.cpp`: reads and clamps `paper.global.item-validation.book-size.total-multiplier`. |
| `item-validation.display-name` | BRIDGE_ONLY | No safe Bedrock item display-name validation decision point is identified. |
| `item-validation.lore-line` | BRIDGE_ONLY | No safe Bedrock item lore validation decision point is identified. |
| `item-validation.resolve-selectors-in-books` | BRIDGE_ONLY | Source explicitly leaves book selector resolution inactive; no safe decision point is identified. |
| `messages.kick.authentication-servers-down` | BRIDGE_ONLY | `src/endstone/runtime/bedrock_hooks/server_network_handler.cpp::_validateLoginPacket` receives only the aggregate optional authentication result after the native validator; `disconnectClientWithMessage` has no verified authentication-server provenance at this hook, so rewriting every failed authentication message would mislabel invalid certificates and other failures. |
| `messages.kick.connection-throttle` | BRIDGE_ONLY | `src/endstone/runtime/bedrock_hooks/rak_peer_helper.cpp::RakPeerHelper::peerStartup` exposes startup configuration only; the underlying RakNet IP-frequency limiter is not a verified message-producing rejection hook, so the Paper message cannot be safely substituted. |
| `messages.kick.flying-player` | BRIDGE_ONLY | `src/endstone/runtime/bedrock_hooks/packet.cpp::EndstonePacketHandler::handle(PlayerAuthInputPacket&)` observes client flight input and movement events, but not BDS's downstream flying validator or its player/vehicle classification. |
| `messages.kick.flying-vehicle` | BRIDGE_ONLY | `src/endstone/runtime/bedrock_hooks/packet.cpp::EndstonePacketHandler::handle(PlayerAuthInputPacket&)` has no verified vehicle-flying validator or vehicle-specific kick reason; changing all movement corrections to this message would affect legitimate teleports. |
| `messages.no-permission` | IMPLEMENTED | `src/endstone/core/message.cpp`: reads `paper.global.messages.no-permission` for command sender error messages. |
| `messages.use-display-name-in-quit-message` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/script_player_gameplay_handler.cpp`: reads the setting in the existing PlayerDisconnectEvent path and uses a non-empty player name tag as the quit-message name. |
| `misc.catchup-ticks` | BRIDGE_ONLY | `src/endstone/runtime/bedrock_hooks/level.cpp::Level::tick` is called once per BDS tick and can skip the native tick, but no missed-wall-clock-tick accumulator or bounded catch-up loop is exposed. |
| `misc.chat-threads.chat-executor-core-size` | BRIDGE_ONLY | No safe Bedrock chat executor sizing decision point is identified. |
| `misc.chat-threads.chat-executor-max-size` | BRIDGE_ONLY | No safe Bedrock chat executor sizing decision point is identified. |
| `misc.client-interaction-leniency-distance` | BRIDGE_ONLY | `src/endstone/runtime/bedrock_hooks/packet.cpp` receives block actions and player-auth input after the packet has been decoded, but no Bedrock interaction-range validation function or distance parameter is exposed by the current hook/header set. |
| `misc.compression-level` | BRIDGE_ONLY | `src/endstone/runtime/bedrock_hooks/batched_network_peer.cpp::sendPacket` receives an already serialized packet and a `Compressibility` flag; it is downstream of the codec-level selection and cannot safely change the configured compression level. |
| `misc.enable-nether` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/server_player.cpp`: reads `paper.global.misc.enable-nether` and rejects Nether transitions when false. |
| `misc.fix-far-end-terrain-generation` | BRIDGE_ONLY | No safe Bedrock End terrain-generation decision point is identified. |
| `misc.load-permissions-yml-before-plugins` | BRIDGE_ONLY | No safe Bedrock plugin/permissions ordering decision point is identified. |
| `misc.max-joins-per-tick` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/server_network_handler.cpp`: reads `paper.global.misc.max-joins-per-tick` in authenticated join validation. |
| `misc.max-tracking-combat-entries` | BRIDGE_ONLY | No safe Bedrock combat-tracking retention decision point is identified. |
| `misc.prevent-negative-villager-demand` | BRIDGE_ONLY | No safe Bedrock villager-demand decision point is identified. |
| `misc.region-file-cache-size` | BRIDGE_ONLY | No safe Bedrock region-file cache decision point is identified. |
| `misc.send-full-pos-for-item-entities` | BRIDGE_ONLY | No safe Bedrock item-entity position serialization decision point is identified. |
| `misc.strict-advancement-dimension-check` | BRIDGE_ONLY | No safe Bedrock advancement decision point is identified. |
| `misc.use-alternative-luck-formula` | BRIDGE_ONLY | No safe Bedrock entity-luck decision point is identified. |
| `misc.use-dimension-type-for-custom-spawners` | BRIDGE_ONLY | No safe Bedrock custom-spawner decision point is identified. |
| `misc.xp-orb-groups-per-area` | BRIDGE_ONLY | No safe Bedrock XP-orb grouping decision point is identified. |
| `packet-limiter.all-packets.action` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/packet.cpp`: reads the all-packets action for over-limit handling. |
| `packet-limiter.all-packets.interval` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/packet.cpp`: reads the all-packets interval for address-based packet accounting. |
| `packet-limiter.all-packets.max-packet-rate` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/packet.cpp`: reads the all-packets rate for address-based packet accounting. |
| `packet-limiter.kick-message` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/packet.cpp`: reads `paper.global.packet-limiter.kick-message` for `KICK` disconnects. |
| `packet-limiter.overrides.minecraft:place_recipe.action` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/packet.cpp`: matching packet-name override replaces the all-packets action. |
| `packet-limiter.overrides.minecraft:place_recipe.interval` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/packet.cpp`: matching packet-name override replaces the all-packets interval. |
| `packet-limiter.overrides.minecraft:place_recipe.max-packet-rate` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/packet.cpp`: matching packet-name override replaces the all-packets rate. |
| `player-auto-save.max-per-tick` | BRIDGE_ONLY | No safe Bedrock player auto-save scheduling decision point is identified. |
| `player-auto-save.rate` | BRIDGE_ONLY | No safe Bedrock player auto-save scheduling decision point is identified. |
| `proxies.bungee-cord.online-mode` | BRIDGE_ONLY | Java Bungee proxy integration has no safe Bedrock equivalent identified. |
| `proxies.proxy-protocol` | BRIDGE_ONLY | No safe Bedrock proxy-protocol decision point is identified. |
| `proxies.velocity.enabled` | BRIDGE_ONLY | Java Velocity integration has no safe Bedrock equivalent identified. |
| `proxies.velocity.online-mode` | BRIDGE_ONLY | Java Velocity integration has no safe Bedrock equivalent identified. |
| `proxies.velocity.secret` | BRIDGE_ONLY | Java Velocity integration has no safe Bedrock equivalent identified. |
| `scoreboards.save-empty-scoreboard-teams` | BRIDGE_ONLY | No safe Bedrock scoreboard persistence decision point is identified. |
| `scoreboards.track-plugin-scoreboards` | BRIDGE_ONLY | No safe Bedrock plugin-scoreboard tracking decision point is identified. |
| `spam-limiter.incoming-packet-threshold` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/packet.cpp`: reads the threshold and drops packets after the initial window allowance. |
| `spam-limiter.recipe-spam-increment` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/craft_handler_crafting.cpp`: increments the per-player tick-decaying recipe-action counter. |
| `spam-limiter.recipe-spam-limit` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/craft_handler_crafting.cpp`: kicks recipe-book spammers when the configured positive threshold is reached. |
| `spam-limiter.tab-spam-increment` | BRIDGE_ONLY | No safe Bedrock tab-spam decision point is identified. |
| `spam-limiter.tab-spam-limit` | BRIDGE_ONLY | No safe Bedrock tab-spam decision point is identified. |
| `spark.enable-immediately` | BRIDGE_ONLY | Spark is Java-specific; no safe Bedrock Spark decision point is identified. |
| `spark.enabled` | BRIDGE_ONLY | Spark is Java-specific; no safe Bedrock Spark decision point is identified. |
| `time.affects-all-worlds` | BRIDGE_ONLY | Bedrock's current `Level` time APIs are Level-wide and the existing hooks expose no per-dimension clock manager or routing decision; treating the global clock as Paper's switch would make `false` ineffective. |
| `unsupported-settings.allow-headless-pistons` | BRIDGE_ONLY | No safe Bedrock piston-execution decision point is identified. |
| `unsupported-settings.allow-permanent-block-break-exploits` | BRIDGE_ONLY | No safe Bedrock exploit-path decision point is identified. |
| `unsupported-settings.allow-piston-duplication` | BRIDGE_ONLY | No safe Bedrock piston-duplication decision point is identified. |
| `unsupported-settings.allow-unsafe-end-portal-teleportation` | BRIDGE_ONLY | No safe Bedrock portal-teleport decision point is identified. |
| `unsupported-settings.oversized-item-component-sanitizer.dont-sanitize` | BRIDGE_ONLY | No safe Bedrock oversized-component sanitizer decision point is identified. |
| `unsupported-settings.perform-username-validation` | BRIDGE_ONLY | No safe Bedrock username-validation decision point is identified. |
| `unsupported-settings.skip-tripwire-hook-placement-validation` | BRIDGE_ONLY | No safe Bedrock tripwire-placement decision point is identified. |
| `unsupported-settings.skip-vanilla-damage-tick-when-shield-blocked` | BRIDGE_ONLY | No safe Bedrock shield-damage decision point is identified. |
| `unsupported-settings.update-equipment-on-player-actions` | BRIDGE_ONLY | No safe Bedrock equipment-update decision point is identified. |
| `update-checker.enabled` | BRIDGE_ONLY | No safe Bedrock update-checker decision point is identified. |
| `watchdog.early-warning-delay` | BRIDGE_ONLY | No safe Bedrock watchdog warning decision point is identified. |
| `watchdog.early-warning-every` | BRIDGE_ONLY | No safe Bedrock watchdog warning decision point is identified. |

## World defaults — 195 schema leaves

| Path | Status | Evidence |
| --- | --- | --- |
| `anticheat.anti-xray.enabled` | BRIDGE_ONLY | No safe Bedrock anti-xray decision point is identified. |
| `anticheat.anti-xray.engine-mode` | BRIDGE_ONLY | No safe Bedrock anti-xray decision point is identified. |
| `anticheat.anti-xray.hidden-blocks` | BRIDGE_ONLY | No safe Bedrock anti-xray decision point is identified. |
| `anticheat.anti-xray.lava-obscures` | BRIDGE_ONLY | No safe Bedrock anti-xray decision point is identified. |
| `anticheat.anti-xray.max-block-height` | BRIDGE_ONLY | No safe Bedrock anti-xray decision point is identified. |
| `anticheat.anti-xray.replacement-blocks` | BRIDGE_ONLY | No safe Bedrock anti-xray decision point is identified. |
| `anticheat.anti-xray.update-radius` | BRIDGE_ONLY | No safe Bedrock anti-xray decision point is identified. |
| `anticheat.anti-xray.use-permission` | BRIDGE_ONLY | No safe Bedrock anti-xray decision point is identified. |
| `chunks.auto-save-interval` | BRIDGE_ONLY | No safe Bedrock chunk auto-save decision point is identified. |
| `chunks.delay-chunk-unloads-by` | BRIDGE_ONLY | No safe Bedrock chunk-unload delay decision point is identified. |
| `chunks.entity-per-chunk-save-limit.experience_orb` | BRIDGE_ONLY | No safe Bedrock per-entity chunk-save decision point is identified. |
| `chunks.entity-per-chunk-save-limit.<entity-type>` | BRIDGE_ONLY | No safe Bedrock per-entity chunk-save decision point is identified. |
| `chunks.fixed-chunk-inhabited-time` | BRIDGE_ONLY | No safe Bedrock inhabited-time decision point is identified. |
| `chunks.flush-regions-on-save` | BRIDGE_ONLY | No safe Bedrock region flush decision point is identified. |
| `chunks.max-auto-save-chunks-per-tick` | BRIDGE_ONLY | No safe Bedrock chunk-save budget decision point is identified. |
| `chunks.prevent-moving-into-unloaded-chunks` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/packet.cpp`: reads the path in PlayerAuthInput/block-action validation and rejects unloaded targets. |
| `collisions.allow-player-cramming-damage` | BRIDGE_ONLY | No safe Bedrock cramming-damage decision point is identified. |
| `collisions.allow-vehicle-collisions` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/pushable_by_entity_utility.cpp`: reads the path when only-player collision mode is active. |
| `collisions.fix-climbing-bypassing-cramming-rule` | BRIDGE_ONLY | No safe Bedrock climbing/cramming decision point is identified. |
| `collisions.max-entity-collisions` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/pushable_by_entity_utility.cpp`: reads the path and caps per-tick push resolutions. |
| `collisions.only-players-collide` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/pushable_by_entity_utility.cpp`: reads the path and filters non-player pairs. |
| `command-blocks.force-follow-perm-level` | BRIDGE_ONLY | No safe Bedrock command-block permission decision point is identified. |
| `command-blocks.permissions-level` | BRIDGE_ONLY | No safe Bedrock command-block permission decision point is identified. |
| `entities.armor-stands.do-collision-entity-lookups` | BRIDGE_ONLY | No safe Bedrock armor-stand collision lookup decision point is identified. |
| `entities.armor-stands.tick` | BRIDGE_ONLY | No safe Bedrock armor-stand ticking decision point is identified. |
| `entities.behavior.allow-spider-world-border-climbing` | BRIDGE_ONLY | No safe Bedrock spider border-climbing decision point is identified. |
| `entities.behavior.baby-zombie-movement-modifier` | BRIDGE_ONLY | No safe Bedrock baby-zombie movement decision point is identified. |
| `entities.behavior.cooldown-failed-beehive-releases` | BRIDGE_ONLY | No safe Bedrock beehive-release decision point is identified. |
| `entities.behavior.disable-chest-cat-detection` | BRIDGE_ONLY | No safe Bedrock chest-cat decision point is identified. |
| `entities.behavior.disable-creeper-lingering-effect` | BRIDGE_ONLY | No safe Bedrock creeper-effect decision point is identified. |
| `entities.behavior.disable-player-crits` | BRIDGE_ONLY | No safe Bedrock critical-hit decision point is identified. |
| `entities.behavior.door-breaking-difficulty.vindicator` | BRIDGE_ONLY | No safe Bedrock door-breaking difficulty decision point is identified. |
| `entities.behavior.door-breaking-difficulty.<entity-type>` | BRIDGE_ONLY | No safe Bedrock door-breaking difficulty decision point is identified. |
| `entities.behavior.ender-dragons-death-always-places-dragon-egg` | BRIDGE_ONLY | No safe Bedrock dragon-egg decision point is identified. |
| `entities.behavior.experience-merge-max-value` | BRIDGE_ONLY | No safe Bedrock XP merge decision point is identified. |
| `entities.behavior.mobs-can-always-pick-up-loot.skeletons` | BRIDGE_ONLY | No safe Bedrock mob-loot pickup decision point is identified. |
| `entities.behavior.mobs-can-always-pick-up-loot.zombies` | BRIDGE_ONLY | No safe Bedrock mob-loot pickup decision point is identified. |
| `entities.behavior.nerf-pigmen-from-nether-portals` | BRIDGE_ONLY | No safe Bedrock portal pigman decision point is identified. |
| `entities.behavior.only-merge-items-horizontally` | BRIDGE_ONLY | No safe Bedrock item-merge decision point is identified. |
| `entities.behavior.parrots-are-unaffected-by-player-movement` | BRIDGE_ONLY | No safe Bedrock parrot movement decision point is identified. |
| `entities.behavior.phantoms-do-not-spawn-on-creative-players` | BRIDGE_ONLY | No safe Bedrock phantom spawn decision point is identified. |
| `entities.behavior.phantoms-only-attack-insomniacs` | BRIDGE_ONLY | No safe Bedrock phantom targeting decision point is identified. |
| `entities.behavior.phantoms-spawn-attempt-max-seconds` | BRIDGE_ONLY | No safe Bedrock phantom spawn timing decision point is identified. |
| `entities.behavior.phantoms-spawn-attempt-min-seconds` | BRIDGE_ONLY | No safe Bedrock phantom spawn timing decision point is identified. |
| `entities.behavior.piglins-guard-chests` | BRIDGE_ONLY | No safe Bedrock piglin chest decision point is identified. |
| `entities.behavior.pillager-patrols.disable` | BRIDGE_ONLY | No safe Bedrock patrol decision point is identified. |
| `entities.behavior.pillager-patrols.spawn-chance` | BRIDGE_ONLY | No safe Bedrock patrol decision point is identified. |
| `entities.behavior.pillager-patrols.spawn-delay.ticks` | BRIDGE_ONLY | No safe Bedrock patrol decision point is identified. |
| `entities.behavior.pillager-patrols.spawn-delay.per-player` | BRIDGE_ONLY | No safe Bedrock patrol decision point is identified. |
| `entities.behavior.pillager-patrols.start.day` | BRIDGE_ONLY | No safe Bedrock patrol decision point is identified. |
| `entities.behavior.pillager-patrols.start.per-player` | BRIDGE_ONLY | No safe Bedrock patrol decision point is identified. |
| `entities.behavior.player-insomnia-start-ticks` | BRIDGE_ONLY | No safe Bedrock insomnia decision point is identified. |
| `entities.behavior.should-remove-dragon` | BRIDGE_ONLY | No safe Bedrock dragon removal decision point is identified. |
| `entities.behavior.spawner-nerfed-mobs-should-jump` | BRIDGE_ONLY | No safe Bedrock spawner-mob decision point is identified. |
| `entities.behavior.stuck-entity-poi-retry-delay` | BRIDGE_ONLY | No safe Bedrock POI retry decision point is identified. |
| `entities.behavior.zombie-villager-infection-chance` | BRIDGE_ONLY | No safe Bedrock infection decision point is identified. |
| `entities.behavior.zombies-target-turtle-eggs` | BRIDGE_ONLY | No safe Bedrock turtle-egg targeting decision point is identified. |
| `entities.entities-target-with-follow-range` | BRIDGE_ONLY | No safe Bedrock follow-range targeting decision point is identified. |
| `entities.markers.tick` | BRIDGE_ONLY | No safe Bedrock marker ticking decision point is identified. |
| `entities.mob-effects.immune-to-wither-effect` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/script_actor_gameplay_handler.cpp`: rejects Wither for Withers and Wither Skeletons when true. |
| `entities.mob-effects.spiders-immune-to-poison-effect` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/script_actor_gameplay_handler.cpp`: rejects Poison for spiders when true. |
| `entities.sniffer.boosted-hatch-time` | BRIDGE_ONLY | No safe Bedrock sniffer hatch decision point is identified. |
| `entities.sniffer.hatch-time` | BRIDGE_ONLY | No safe Bedrock sniffer hatch decision point is identified. |
| `entities.spawning.all-chunks-are-slime-chunks` | BRIDGE_ONLY | No safe Bedrock slime-chunk decision point is identified. |
| `entities.spawning.alt-item-despawn-rate.enabled` | BRIDGE_ONLY | No safe Bedrock alternate item despawn decision point is identified. |
| `entities.spawning.alt-item-despawn-rate.items.cobblestone` | BRIDGE_ONLY | No safe Bedrock alternate item despawn decision point is identified. |
| `entities.spawning.alt-item-despawn-rate.items.<item-type>` | BRIDGE_ONLY | No safe Bedrock alternate item despawn decision point is identified. |
| `entities.spawning.max-arrow-despawn-invulnerability` | BRIDGE_ONLY | No safe Bedrock arrow despawn decision point is identified. |
| `entities.spawning.count-all-mobs-for-spawning` | BRIDGE_ONLY | No safe Bedrock mob-count decision point is identified. |
| `entities.spawning.creative-arrow-despawn-rate` | BRIDGE_ONLY | No safe Bedrock arrow despawn decision point is identified. |
| `entities.spawning.despawn-range-shape` | BRIDGE_ONLY | No safe Bedrock despawn-shape decision point is identified. |
| `entities.spawning.despawn-ranges.<mob_category>.hard` | BRIDGE_ONLY | No safe Bedrock despawn-range decision point is identified. |
| `entities.spawning.despawn-ranges.<mob_category>.soft` | BRIDGE_ONLY | No safe Bedrock despawn-range decision point is identified. |
| `entities.spawning.despawn-ranges.<mob_category>_.hard.horizontal` | BRIDGE_ONLY | No safe Bedrock despawn-range decision point is identified. |
| `entities.spawning.despawn-ranges.<mob_category>_.hard.vertical` | BRIDGE_ONLY | No safe Bedrock despawn-range decision point is identified. |
| `entities.spawning.despawn-ranges.<mob_category>_.soft.horizontal` | BRIDGE_ONLY | No safe Bedrock despawn-range decision point is identified. |
| `entities.spawning.despawn-ranges.<mob_category>_.soft.vertical` | BRIDGE_ONLY | No safe Bedrock despawn-range decision point is identified. |
| `entities.spawning.despawn-time.<entity-type>` | BRIDGE_ONLY | No safe Bedrock despawn-time decision point is identified. |
| `entities.spawning.disable-mob-spawner-spawn-egg-transformation` | BRIDGE_ONLY | No safe Bedrock spawner spawn-egg decision point is identified. |
| `entities.spawning.duplicate-uuid.mode` | BRIDGE_ONLY | No safe Bedrock duplicate-UUID decision point is identified. |
| `entities.spawning.duplicate-uuid.safe-regen-delete-range` | BRIDGE_ONLY | No safe Bedrock duplicate-UUID decision point is identified. |
| `entities.spawning.filter-bad-tile-entity-nbt-from-falling-blocks` | BRIDGE_ONLY | No safe Bedrock falling-block NBT decision point is identified. |
| `entities.spawning.filtered-entity-tag-nbt-paths` | BRIDGE_ONLY | No safe Bedrock entity-NBT filtering decision point is identified. |
| `entities.spawning.iron-golems-can-spawn-in-air` | BRIDGE_ONLY | No safe Bedrock iron-golem spawn decision point is identified. |
| `entities.spawning.monster-spawn-max-light-level` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/level.cpp`: reads the numeric path and updates loaded Dimensions' monster block-light limit before ticking. |
| `entities.spawning.non-player-arrow-despawn-rate` | BRIDGE_ONLY | No safe Bedrock arrow despawn decision point is identified. |
| `entities.spawning.per-player-mob-spawns` | BRIDGE_ONLY | No safe Bedrock per-player spawn decision point is identified. |
| `entities.spawning.scan-for-legacy-ender-dragon` | BRIDGE_ONLY | No safe Bedrock dragon scan decision point is identified. |
| `entities.spawning.skeleton-horse-thunder-spawn-chance` | BRIDGE_ONLY | No safe Bedrock skeleton-horse spawn decision point is identified. |
| `entities.spawning.slime-spawn-height.slime-chunk.maximum` | BRIDGE_ONLY | No safe Bedrock slime-height decision point is identified. |
| `entities.spawning.slime-spawn-height.surface-biome.minimum` | BRIDGE_ONLY | No safe Bedrock slime-height decision point is identified. |
| `entities.spawning.slime-spawn-height.surface-biome.maximum` | BRIDGE_ONLY | No safe Bedrock slime-height decision point is identified. |
| `entities.spawning.spawn-limits.ambient` | BRIDGE_ONLY | No safe Bedrock spawn-limit decision point is identified. |
| `entities.spawning.spawn-limits.axolotls` | BRIDGE_ONLY | No safe Bedrock spawn-limit decision point is identified. |
| `entities.spawning.spawn-limits.creature` | BRIDGE_ONLY | No safe Bedrock spawn-limit decision point is identified. |
| `entities.spawning.spawn-limits.monster` | BRIDGE_ONLY | No safe Bedrock spawn-limit decision point is identified. |
| `entities.spawning.spawn-limits.underground_water_creature` | BRIDGE_ONLY | No safe Bedrock spawn-limit decision point is identified. |
| `entities.spawning.spawn-limits.water_ambient` | BRIDGE_ONLY | No safe Bedrock spawn-limit decision point is identified. |
| `entities.spawning.spawn-limits.water_creature` | BRIDGE_ONLY | No safe Bedrock spawn-limit decision point is identified. |
| `entities.spawning.ticks-per-spawn.ambient` | BRIDGE_ONLY | No safe Bedrock spawn-tick decision point is identified. |
| `entities.spawning.ticks-per-spawn.axolotls` | BRIDGE_ONLY | No safe Bedrock spawn-tick decision point is identified. |
| `entities.spawning.ticks-per-spawn.creature` | BRIDGE_ONLY | No safe Bedrock spawn-tick decision point is identified. |
| `entities.spawning.ticks-per-spawn.monster` | BRIDGE_ONLY | No safe Bedrock spawn-tick decision point is identified. |
| `entities.spawning.ticks-per-spawn.underground_water_creature` | BRIDGE_ONLY | No safe Bedrock spawn-tick decision point is identified. |
| `entities.spawning.ticks-per-spawn.water_ambient` | BRIDGE_ONLY | No safe Bedrock spawn-tick decision point is identified. |
| `entities.spawning.ticks-per-spawn.water_creature` | BRIDGE_ONLY | No safe Bedrock spawn-tick decision point is identified. |
| `entities.spawning.wandering-trader.spawn-chance-failure-increment` | BRIDGE_ONLY | No safe Bedrock wandering-trader decision point is identified. |
| `entities.spawning.wandering-trader.spawn-chance-max` | BRIDGE_ONLY | No safe Bedrock wandering-trader decision point is identified. |
| `entities.spawning.wandering-trader.spawn-chance-min` | BRIDGE_ONLY | No safe Bedrock wandering-trader decision point is identified. |
| `entities.spawning.wandering-trader.spawn-day-length` | BRIDGE_ONLY | No safe Bedrock wandering-trader decision point is identified. |
| `entities.spawning.wandering-trader.spawn-minute-length` | BRIDGE_ONLY | No safe Bedrock wandering-trader decision point is identified. |
| `entities.spawning.wateranimal-spawn-height.maximum` | BRIDGE_ONLY | No safe Bedrock water-animal spawn-height decision point is identified. |
| `entities.spawning.wateranimal-spawn-height.minimum` | BRIDGE_ONLY | No safe Bedrock water-animal spawn-height decision point is identified. |
| `entities.tracking-range-y.animal` | BRIDGE_ONLY | No safe Bedrock tracking-range decision point is identified. |
| `entities.tracking-range-y.display` | BRIDGE_ONLY | No safe Bedrock tracking-range decision point is identified. |
| `entities.tracking-range-y.enabled` | BRIDGE_ONLY | No safe Bedrock tracking-range decision point is identified. |
| `entities.tracking-range-y.misc` | BRIDGE_ONLY | No safe Bedrock tracking-range decision point is identified. |
| `entities.tracking-range-y.monster` | BRIDGE_ONLY | No safe Bedrock tracking-range decision point is identified. |
| `entities.tracking-range-y.other` | BRIDGE_ONLY | No safe Bedrock tracking-range decision point is identified. |
| `entities.tracking-range-y.player` | BRIDGE_ONLY | No safe Bedrock tracking-range decision point is identified. |
| `environment.disable-explosion-knockback` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/mob.cpp`: reads the path and suppresses explosion-synchronous knockback. |
| `environment.disable-ice-and-snow` | BRIDGE_ONLY | No safe Bedrock ice-and-snow decision point is identified. |
| `environment.disable-thunder` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/weather_manager.cpp`: reads the path and zeros lightning level/duration. |
| `environment.fire-tick-delay` | BRIDGE_ONLY | No safe Bedrock fire tick decision point is identified. |
| `environment.frosted-ice.delay.max` | BRIDGE_ONLY | No safe Bedrock frosted-ice delay decision point is identified. |
| `environment.frosted-ice.delay.min` | BRIDGE_ONLY | No safe Bedrock frosted-ice delay decision point is identified. |
| `environment.frosted-ice.enabled` | BRIDGE_ONLY | No safe Bedrock frosted-ice decision point is identified. |
| `environment.generate-flat-bedrock` | BRIDGE_ONLY | No safe Bedrock flat-bedrock generation decision point is identified. |
| `environment.locate-structures-outside-world-border` | BRIDGE_ONLY | No safe Bedrock structure-location decision point is identified. |
| `environment.max-block-ticks` | BRIDGE_ONLY | No safe Bedrock block-tick budget decision point is identified. |
| `environment.max-fluid-ticks` | BRIDGE_ONLY | No safe Bedrock fluid-tick budget decision point is identified. |
| `environment.nether-ceiling-void-damage-height` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/script_actor_gameplay_handler.cpp`: reads the path to opt Nether ceiling Void damage into the existing hurt path. |
| `environment.optimize-explosions` | BRIDGE_ONLY | No safe Bedrock explosion-optimization decision point is identified. |
| `environment.portal-create-radius` | BRIDGE_ONLY | No safe Bedrock portal-create decision point is identified. |
| `environment.portal-search-radius` | BRIDGE_ONLY | No safe Bedrock portal-search decision point is identified. |
| `environment.portal-search-vanilla-dimension-scaling` | BRIDGE_ONLY | No safe Bedrock portal-scaling decision point is identified. |
| `environment.treasure-maps.enabled` | BRIDGE_ONLY | No safe Bedrock treasure-map decision point is identified. |
| `environment.treasure-maps.find-already-discovered.loot-tables` | BRIDGE_ONLY | No safe Bedrock treasure-map decision point is identified. |
| `environment.treasure-maps.find-already-discovered.villager-trade` | BRIDGE_ONLY | No safe Bedrock treasure-map decision point is identified. |
| `environment.void-damage-amount` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/script_actor_gameplay_handler.cpp`: reads the path and supplies the configured Void damage to the existing hurt path. |
| `environment.void-damage-min-build-height-offset` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/script_actor_gameplay_handler.cpp`: reads the path to suppress native Void hurt at/above the configured offset. |
| `environment.water-over-lava-flow-speed` | BRIDGE_ONLY | No safe Bedrock fluid-flow decision point is identified. |
| `feature-seeds.generate-random-seeds-for-all` | BRIDGE_ONLY | No safe Bedrock feature-seed generation decision point is identified. |
| `feature-seeds.<feature-namespace>` | BRIDGE_ONLY | No safe Bedrock feature-seed decision point is identified. |
| `fishing-time-range.maximum` | BRIDGE_ONLY | No safe Bedrock fishing timing decision point is identified. |
| `fishing-time-range.minimum` | BRIDGE_ONLY | No safe Bedrock fishing timing decision point is identified. |
| `fixes.disable-unloaded-chunk-enderpearl-exploit` | BRIDGE_ONLY | No safe Bedrock Ender Pearl exploit decision point is identified. |
| `fixes.falling-block-height-nerf` | BRIDGE_ONLY | No safe Bedrock falling-block height decision point is identified. |
| `fixes.fix-items-merging-through-walls` | BRIDGE_ONLY | No safe Bedrock item-merge collision decision point is identified. |
| `fixes.prevent-tnt-from-moving-in-water` | BRIDGE_ONLY | No safe Bedrock TNT-water movement decision point is identified. |
| `fixes.split-overstacked-loot` | BRIDGE_ONLY | No safe Bedrock loot-stack decision point is identified. |
| `fixes.tnt-entity-height-nerf` | BRIDGE_ONLY | No safe Bedrock TNT height decision point is identified. |
| `hopper.cooldown-when-full` | BRIDGE_ONLY | No safe Bedrock hopper cooldown decision point is identified. |
| `hopper.disable-move-event` | BRIDGE_ONLY | No safe Bedrock hopper move-event decision point is identified. |
| `hopper.ignore-occluding-blocks` | BRIDGE_ONLY | No safe Bedrock hopper occlusion decision point is identified. |
| `lootables.auto-replenish` | BRIDGE_ONLY | No safe Bedrock lootable replenishment decision point is identified. |
| `lootables.max-refills` | BRIDGE_ONLY | No safe Bedrock lootable replenishment decision point is identified. |
| `lootables.refresh-max` | BRIDGE_ONLY | No safe Bedrock lootable replenishment decision point is identified. |
| `lootables.refresh-min` | BRIDGE_ONLY | No safe Bedrock lootable replenishment decision point is identified. |
| `lootables.reset-seed-on-fill` | BRIDGE_ONLY | No safe Bedrock lootable seed decision point is identified. |
| `lootables.restrict-player-reloot` | BRIDGE_ONLY | No safe Bedrock reloot decision point is identified. |
| `lootables.restrict-player-reloot-time` | BRIDGE_ONLY | No safe Bedrock reloot decision point is identified. |
| `lootables.retain-unlooted-shulker-box-loot-table-on-non-player-break` | BRIDGE_ONLY | No safe Bedrock shulker-loot decision point is identified. |
| `maps.item-frame-cursor-limit` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/batched_network_peer.cpp`: reads the path when serializing visible map cursors. |
| `maps.item-frame-cursor-update-interval` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/batched_network_peer.cpp`: reads the path for cached frame-cursor updates. |
| `max-growth-height.bamboo.max` | BRIDGE_ONLY | No safe Bedrock bamboo growth-height decision point is identified. |
| `max-growth-height.bamboo.min` | BRIDGE_ONLY | No safe Bedrock bamboo growth-height decision point is identified. |
| `max-growth-height.cactus` | BRIDGE_ONLY | No safe Bedrock cactus growth-height decision point is identified. |
| `max-growth-height.reeds` | BRIDGE_ONLY | No safe Bedrock reeds growth-height decision point is identified. |
| `misc.allow-remote-ender-dragon-respawning` | BRIDGE_ONLY | No safe Bedrock dragon-respawn decision point is identified. |
| `misc.alternate-current-update-order` | BRIDGE_ONLY | No safe Bedrock redstone decision point is identified. |
| `misc.disable-end-credits` | BRIDGE_ONLY | No safe Bedrock end-credits decision point is identified. |
| `misc.disable-relative-projectile-velocity` | BRIDGE_ONLY | No safe Bedrock projectile-velocity decision point is identified. |
| `misc.disable-sprint-interruption-on-attack` | BRIDGE_ONLY | No safe Bedrock sprint interruption decision point is identified. |
| `misc.legacy-ender-pearl-behavior` | BRIDGE_ONLY | No safe Bedrock Ender Pearl behavior decision point is identified. |
| `misc.max-leash-distance` | BRIDGE_ONLY | No safe Bedrock leash-distance decision point is identified. |
| `misc.redstone-implementation` | BRIDGE_ONLY | No safe Bedrock redstone implementation decision point is identified. |
| `misc.show-sign-click-command-failure-msgs-to-player` | BRIDGE_ONLY | No safe Bedrock sign-command failure decision point is identified. |
| `misc.update-pathfinding-on-block-update` | BRIDGE_ONLY | No safe Bedrock pathfinding-update decision point is identified. |
| `scoreboards.allow-non-player-entities-on-scoreboards` | BRIDGE_ONLY | No safe Bedrock scoreboard decision point is identified. |
| `scoreboards.use-vanilla-world-scoreboard-name-coloring` | BRIDGE_ONLY | No safe Bedrock scoreboard-color decision point is identified. |
| `spawn.allow-using-signs-inside-spawn-protection` | BRIDGE_ONLY | No safe Bedrock spawn-protection decision point is identified. |
| `tick-rates.behavior.villager.validatenearbypoi` | BRIDGE_ONLY | No safe Bedrock behavior tick-rate decision point is identified. |
| `tick-rates.behavior.<entity-type>.<behavior-name>` | BRIDGE_ONLY | No safe Bedrock behavior tick-rate decision point is identified. |
| `tick-rates.container-update` | BRIDGE_ONLY | No safe Bedrock container tick-rate decision point is identified. |
| `tick-rates.dry-farmland` | BRIDGE_ONLY | No safe Bedrock farmland tick-rate decision point is identified. |
| `tick-rates.grass-spread` | BRIDGE_ONLY | No safe Bedrock grass tick-rate decision point is identified. |
| `tick-rates.mob-spawner` | BRIDGE_ONLY | No safe Bedrock mob-spawner tick-rate decision point is identified. |
| `tick-rates.sensor.villager.secondarypoisensor` | BRIDGE_ONLY | No safe Bedrock sensor tick-rate decision point is identified. |
| `tick-rates.sensor.<entity-type>.<sensor-name>` | BRIDGE_ONLY | No safe Bedrock sensor tick-rate decision point is identified. |
| `tick-rates.wet-farmland` | BRIDGE_ONLY | No safe Bedrock farmland tick-rate decision point is identified. |
| `unsupported-settings.disable-world-ticking-when-empty` | IMPLEMENTED | `src/endstone/runtime/bedrock_hooks/level.cpp`: reads the path and skips native Level ticking when no players are online. |
| `unsupported-settings.fix-invulnerable-end-crystal-exploit` | BRIDGE_ONLY | No safe Bedrock end-crystal exploit decision point is identified. |
| `unsupported-settings.ticking.chunks` | BRIDGE_ONLY | No safe Bedrock chunk-ticking switch decision point is identified. |
| `unsupported-settings.ticking.block-entities` | BRIDGE_ONLY | No safe Bedrock block-entity ticking switch decision point is identified. |

## Synchronization and validation method

`endstone/cli/paper_config.py` is the bridge source: `prepare_paper_configs()` loads both packaged YAMLs, normalizes defaults, merges server-local values, preserves unknown keys, and writes the resulting mappings to `paper.global` and `paper.world_defaults` in `endstone.toml`. Its explicit sentinel/type rules were reviewed for `disabled`, numeric-or-`default`, and numeric-or-`disabled` leaves.

Validation performed for this audit:

1. Read `docs/getting-started/configuration.md`, both packaged YAML templates, the bridge implementation, and source references for every active runtime path.
2. Flattened each YAML mapping into dot paths, retaining placeholder leaves and excluding the two inline-doc metadata leaves plus the documentation-only packet-limiter header.
3. Reconciled the flattened inventory to the documented totals: **93 global**, **195 world-default schema leaves**, **288 total**.
4. Classified a leaf as `IMPLEMENTED` only when a source read of its exact TOML path reaches a concrete runtime decision point; all remaining leaves have an explicit concrete no-safe-decision-point statement.
5. Confirmed that no C++ or configuration source was modified; this audit is documentation-only.

Expected audit statistics: **288 leaves**, **36 IMPLEMENTED**, **252 BRIDGE_ONLY**, with **93 global + 195 world-default schema leaves** and **3 documentation/metadata leaves excluded**. The active implementation set is intentionally narrow and matches the runtime behavior table in `configuration.md`; synchronization alone is not treated as implementation.
