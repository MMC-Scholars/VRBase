# Globals

Globals are variables or methods accessible from any method of any class without `includes`. Globals in VRBase are 
generally accessed via the `g_pGlobals*` specifier (with exceptions below). `g_pGlobals` does not inherit from any 
other class.

## Variables

|  | Name | Description |
| --- | --- | --- |
| [`ftime`](./typedefs.md) | g_pGlobals->curtime | The current game time of the world, in seconds, and will be reset by any calls to `g_pGlobals->reset()` |
| [`ftime`](./typedefs.md) | g_pGlobals->frametime | Keeps track of how much time has passed since the last frame |
| `TArray`<[`IBaseEntity*`](IBaseEntity.md)> | g_entList | a complete iterable entity list. All entries guaranteed to be non-null |
| [`ABasePawn*`](ABasePawn.md) | g_pBasePawn | a reference to the main virtual reality pawn |
| [`AGameRules*`](AGameRules.md) | g_pGameRules | a reference to the world [`AGameRules`](AGameRules.md) |
| [`ABaseController*`](ABaseController.md) | g_pLeftController | a reference to the [`ABasePawn`](ABasePawn.md) left motion controller |
| [`ABaseController*`](ABaseController.md) | g_pRightController | a reference to the [`ABasePawn`](ABasePawn.md) right motion controller |
| `bool` | g_pGlobals->ineditor | true if in Unreal editor or Play In Editor |
| `bool` | g_pGlobals->worldcreated | True if the world has been created and BeginPlays have started |

## Functions

|  | Name | Description |
| -- | --- | --- |
| `void` | g_pGlobals->checkReset() | Calls `g_pGlobals->reset()` only if reset has been marked. In most projects you will never need to call this |
| `UStaticMesh*` | FindMesh(`const` `char*` path) | a function which returns a static mesh, given a path reference to the mesh |
| `UStaticMesh*` | FindMesh(`const` `wchar_t*` path) | |
| `void` | g_pGlobals->markReset() | Marks the game ready for a reset. In most projects you will never need to call this |
| `void` | g_pGlobals->reset() | Resets the game entity counts, time, and initializations. In most projects you will never need to call this  |
| `void` | g_pGlobals->update() | Manually updates the global variables. This is periodically called automatically regardless of subsequent calls. In most projects you will never need to call this |

The functions below are useful vanilla Unreal globals.

|  | Name | Description |
| -- | --- | --- |
| `UWorld*` | GetWorld() | a reference to the game world |
