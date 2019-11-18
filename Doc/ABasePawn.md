# `ABasePawn` Class

`extends` `APawn`, [`IBaseEntity`](IBaseEntity.md)

`ABasePawn` works as a basic possessable virtual reality pawn. It is most commonly used to represent the virtual reality player character in world space. This class automatically comes with an HMD and two [`ABaseController`](ABaseController.md) motion controllers.

## Variables

|  | Name | Description |
| --- | --- | --- |
| `TArray`<`AActor*`> | m_aTeleportBounds | Bounds of the actor(s) specify the bounds in which the player can teleport. `AVolumes` work best. Accessible via UProperty |
| `bool` | m_bTeleportationEnabled | True if teleportation is enabled. Accessible via UProperty |
| [`FEntityInputRegistrationParams`](./typedefs.md) | m_leftControllerInput | __. Accessible via UProperty |
| `UCameraComponent*` | m_pCamera | The virtual reality camera |
| `UStaticMesh*` | m_pLeftControllerMesh | The static mesh of the left controller. Accessible via UProperty |
| `UChildActorComponent*` | m_pLChildActor | The actor representing the left hand of the player |
| `UClass*` | m_pLControllerClass | The left controller class. Accessible via UProperty |
| `UMotionControllerComponent*` | m_pLMotionController | The left motion controller |
| `UTextRenderComponent*` | m_pLTextInstr | The text component to render the left instruction |
| `USceneComponent*` | m_pPlayerRoot | Origin of the player |
| `UStaticMesh*` | m_pRightControllerMesh | The static mesh of the right controller. Accessible via UProperty |
| `UChildActorComponent*` | m_pRChildActor | The actor representing the right hand of the player |
| `UClass*` | m_pRControllerClass | The right controller class. Accessible via UProperty |
| `UMotionControllerComponent*` | m_pRMotionController | The right motion controller |
| `UCapsuleComponent*` | m_pRootCapsule | The capsule the player resides within |
| `UTextRenderComponent*` | m_pRTextInstr | The text component to render the right instruction |
| [`FEntityInputRegistrationParams`](./typedefs.md) | m_rightControllerInput | __. Accessible via UProperty |
| [`ftime`](./typedefs.md) | m_tInstrChangeTime | Time it takes to switch between instructions if instruction time switching is enabled |
| `TArray`<[`FPawnInstruction`](./typedefs.md)> | m_aInstr | Array of instructions to display in order. Accessible via UProperty |

## Functions

|  | Name | Description |
| -- | --- | --- |
|	`bool` | CanTeleportToLocation(`const` `FVector&` loc) | Returns true if player is able to teleport to location |
| `bool` | IsWithinTeleportBounds(`const` `FVector&` location, `const` `FVector&` bOrigin, `const` `FVector&` bExtent) | Returns true if the player is within the specified teleportation bounds |
| `void` | NextInstruction() | Switches the current instruction to the next instruction in the `m_aInstr` array |
| `virtual void` | SetControllerClass(`UClass*` LControllerClass, `UClass*` RControllerClass) | Sets classes to be used by motion controllers. Both must be classes which inherit from [`ABaseController`](./ABaseController.md) |
| `void` | SetInstruction([`FPawnInstruction`](./typedefs.md) instr) | Sets the currently displayed instruction |
|	`bool` | TeleportPlayer(`const` `FVector&` loc, `const` `FRotator&` rot) | Teleports the player to the given location. Returns true if successful |

## Overridden

|  | Name | Description |
| --- | --- | --- |
| [`IBaseEntity`](./IBaseEntity.md) | | |
| `virtual void` | DefaultThink() | __ |
| `FVector` | GetInitialLocation() | Returns the starting world location of the pawn where the Z axis value represents the location of the player feet, or the bottom of the capsule |
| `virtual` [`FEntityInputRegistrationParams`](./typedefs.md) | GetLeftControllerInputRegistrationParams() | __ |
| `virtual` [`FEntityInputRegistrationParams`](./typedefs.md) | GetRightControllerInputRegistrationParams() | __ |
| `virtual void` | PreInit() | __ |
