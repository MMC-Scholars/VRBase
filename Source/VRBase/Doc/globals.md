# Globals

Globals are variables or methods accessible from any method of any class. Globals are accessed via the `g_pGlobals*` specifier. It does not inherit from any other class and acts as a wrapper.

## Variables

|  | Name | Description |
| --- | --- | --- |
| [`ftime`](./typedefs.md) | curtime | The current game time of the world. This is returned in seconds and is useful for timers |
| [`ftime`](./typedefs.md) | frametime | Keeps track of how much time has passed since the last frame |
| `bool` | ineditor | true if in Unreal editor or Play In Editor |
| `bool` | worldcreated | True if the world has been created and BeginPlays have started |

## Functions

|  | Name | Description |
| -- | --- | --- |
| `void` | checkReset() | __ |
| `void` | markReset() | __ |
| `void` | reset() | __ |
| `void` | update() | __ |
