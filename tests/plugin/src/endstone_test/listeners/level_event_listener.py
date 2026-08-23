from endstone.event import ChunkLoadEvent, ChunkUnloadEvent, LevelLoadEvent, event_handler

from .event_listener import EventListener


class LevelEventListener(EventListener):
    @event_handler
    def on_level_load(self, event: LevelLoadEvent):
        self.record(
            event,
            f"{event.level.name} is loaded",
            level=event.level.name,
        )

    @event_handler
    def on_chunk_load(self, event: ChunkLoadEvent):
        self.record(
            event,
            f"{event.chunk} is loaded",
            always_log=True,
            chunk_xz=(event.chunk.x, event.chunk.z),
            dimension=str(event.dimension.id),
        )

    @event_handler
    def on_chunk_unload(self, event: ChunkUnloadEvent):
        self.record(
            event,
            f"{event.chunk} is unloaded",
            always_log=True,
            chunk_xz=(event.chunk.x, event.chunk.z),
            dimension=str(event.dimension.id),
        )
