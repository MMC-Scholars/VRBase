# `IBaseEntity` Interface

The `IBaseEntity` abstract class is the most important part of the library. It defines a common interface shared by all Actor-derived classes in the libraries. Its features include: a more detailed initialization system, null-safe referencing, dynamically timed thinking, respawning, optional health system, bitfield flags, and a generic VR-controller-compatible “Use” system.

## Variables

|  | Name | Description |
| --- | --- | --- |
| [`ftime`](./typedefs.md) | m_tConstructionTime | The amount of elapsed time (in seconds) from the start of the game to the construction of the entity |
| [`ftime`](./typedefs.md) | m_tLastTimeUsed | The time (in seconds) since the start of the game that the entity was Used. If never used, returns the minimum value of a float |

## Functions

|  | Name | Description |
| -- | --- | --- |
| `void` | AddFlags([`ulong`](./typedefs.md) flags) | Adds the specified flags |
| `virtual void` | DefaultThink() | Called every frame following all PreInit() calls |
| `bool` | DestroyEntity() | Destroys this actor. Returns true if already destroyed or already marked for destruction, false if indestructible |
| [`eindex`](./typedefs.md) | EntIndex() | Returns the entity index |
| `static IBaseEntity*` | FromActor(`AActor*` pActor) | Converts a given `AActor` to a [`BaseEntity`](./ABaseEntity.md) |
| `AActor*` | GetActor() | Returns a pointer to the actor. _Note that this is not protected by an [`EHandle`](./EHandle.md)_ |
| [`EHANDLE`](EHandle.md) | GetEHandle() | Returns an [EHandle](EHandle.md) to the entity |
| [`ulong`](./typedefs.md) | GetFlags() | Returns the entity's set flags |
| `int` | GetHealth() | Returns the health of the entity |
| `FVector` | GetInitialLocation() | Returns the starting world location of the entity |
| `FRotator` | GetInitialRotation() | Returns the starting world rotation of the entity |
| `FVector` | GetInitialScale() | Returns the starting world scale of the entity |
| `FTransform` | getInitialTransform() | Returns the starting transform of the entity |
| `UInputComponent*` | GetInput() | Returns input as a `UInputComponent` pointer |
| `virtual` [`FEntityInputRegistrationParams*`](./typedefs.md) | GetLeftControllerInputRegistrationParams() | __ |
| `ftime` | GetNextThink() | __ |
| `virtual` [`FEntityInputRegistrationParams*`](./typedefs.md) | GetRightControllerInputRegistrationParams() | __ |
| `IBaseEntity&` | GetRef() | Returns a reference to `this` |
| `int` | GetSpawnHealth() | Returns the spawn health of the entity |
| `bool` | HasFlags([`ulong`](./typedefs.md) flags) | Returns true if the specified flags are set |
| `bool` | HasFlagsAll([`ulong`](./typedefs.md) flags) | Returns true if all flags are set |
| `bool` | IsBaseCharacter() | Returns true if the entity is a [BaseCharacter](./ABaseCharacter.md) |
| `bool` | IsBaseEntity() | Returns true if the entity is a [BaseEntity](./ABaseEntity.md) |
| `bool` | IsBasePawn() | Returns true if the entity is a [BasePawn](./ABasePawn.md)
| `bool` | IsInputEnabled() | Returns true if input is not ignored |
| `bool` | IsInvincible() | Returns true if the entity is invincible |
| `bool` | IsNotDamageable() | Returns true if the entity is not damageable | 
| `bool` | IsUseable() | Returns true if Use is not ignored and input is not ignored |
| `bool` | IsUseableBy(`const` [`ABaseController*`](./ABaseController.md)) | Returns true |
| `virtual void` | OnUsed([`ABaseEntity*`](./ABaseEntity.md) pActivator) | __ |
| `virtual void` | PostInit() | Called after all static initializers |
| `virtual void` | PreInit() | Called before all static intializers |
| `void` | RegisterInputsToControllers() | __ |
| `void` | RemoveFlags([`ulong`](./typedefs.md) flags) | Removes the specified flags |
| `void` | RemoveSelfFromLists() | Removes entity from entity lists, invalidating [`EHANDLES`](./EHandle.md) (but not modifying static counts) |
| `void` | ReportReady() | Increments the ready entities count (should never be called by a user) |
| `void` | ResetFlags() | Resets flags to the initial flags at spawn |
| `virtual void` | Respawn() | __ |
| `void` | SetHealth(`int` health) | Sets the health of the entity |
| `void` | SetNextThink(`ftime` time) | __ |
| `void` | StopThink() | __ |
| `void` | Think() | Called every frame after DefaultThink(), if enabled via __ |
| `void` | ThinkSet(BASEPTR pProcedure, `void*` pThinkParam) | __ |
| `void` | ToggleFlags([`ulong`](./typedefs.md) flags) | Toggles or inverts the specified flags |
| `bool` | Use([`ABaseEntity*`](./ABaseEntity.md) pActivator) | Uses a given entity. Returns true on success, false if blocked |


## Implementations
- [`ABaseCharacter`](./ABaseCharacter.md)
- [`ABaseEntity`](./ABaseEntity.md)
- [`ABasePawn`](./ABasePawn.md)
