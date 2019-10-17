# Globals

Globals are variables or methods accessible from any method of any class. Globals are generally accessed via the `g_pGlobals*` specifier (with some exceptions below). It does not inherit from any other class and acts as a wrapper.

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

## Variables (accessible **without** the `g_pGlobals*` specifier)

|  | Name | Description |
| --- | --- | --- |
| `UWorld*` | GetWorld() | a reference to the game world |
| `TArray`<[`IBaseEntity*`](IBaseEntity.md)> | g_entList | a complete iterable entity list. All entries guaranteed to be non-null |
| [`ABasePawn*`](ABasePawn.md) | g_pBasePawn | a reference to the main virtual reality pawn |
| [`AGameRules*`](AGameRules.md) | g_pGameRules | a reference to the world [`AGameRules`](AGameRules.md) |
| [`ABaseController*`](ABaseController.md) | g_pLeftController | a reference to the [`ABasePawn`](ABasePawn.md) left motion controller |
| [`ABaseController*`](ABaseController.md) | g_pRightController | a reference to the [`ABasePawn`](ABasePawn.md) right motion controller |