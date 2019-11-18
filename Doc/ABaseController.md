# `ABaseController` Class

`extends` [`ABaseEntity`](./ABaseEntity.md)

`ABaseController` is a concrete class which defines how a virtual reality motion controller works in game. It defines the teleportation mechanics and keeps track of which buttons are pressed on the controller. You can access the left and right controllers from anywhere with the global variables `g_pLeftController` and `g_pRightController`.

## Variables

|  | Name | Description |
| --- | --- | --- |
| `TArray`<[`APickup*`](./APickup.md)> | m_aAttachActors | Array of actors attached to the controller |
| `TArray`<`AActor*`> | m_aOverlapActors | Array of actors overlapping with the controller's `m_pControllerCollision` |
| `bool` | m_bPerformedPositionFixup | True if controller position was corrected when setting hand |
| `bool` | m_bTeleportationActive | True if teleportation is currently active for this controller |
| `EControllerHand` | m_eWhichHand | Specify which hand the controller is owned by |
| `USphereComponent*` | m_pControllerCollision | Collision bounds for the controller. This is used to determine proximity to [`APickups`](./APickup.md) and other objects |
| `uint32` | m_iButtons | Specifies in a bitfield which buttons are currently being pressed |
| `uint32` | m_iButtonsPressed | Specifies in a bitfield which buttons were just pressed |
| `uint32` | m_iButtonsReleased | Specifies in a bitfield which buttons were just released |
| `UStaticMeshComponent*` | m_pHandMeshComponent | The static mesh representing the controller |
| `UStaticMeshComponent*` | m_pHandScene | Defines the root of the entity |
| [`ABasePawn*`](./ABasePawn.md) | m_pOwnerPawn | The BasePawn which owns the controller |

## Functions

|  | Name | Description |
| --- | --- | --- |
| `uint32` | ButtonsPressed() | Returns a bitfield of buttons currently pressed on this controller |
| `void` | GetTraceIgnoredActors(`TArray`<`AActor*`>&) | Adds a null-terminated list of actors to ignore when raytracing for teleportation |
| `virtual void` | OnButtonsChanged() | Called when button bitfields have been changed |
| `void` | OnOverlapBegin(`UPrimitiveComponent*` OverlappedComp, `AActor*` OtherActor, `UPrimitiveComponent*` OtherComp, `int32` OtherBodyIndex, `bool` bFromSweep, `const` `FHitResult&` SweepResult) | Called on overlapping another actor. Accessible via UFunction |
| `void` | OnOverlapEnd(`UPrimitiveComponent*` OverlappedComp, `AActor*` OtherActor, `UPrimitiveComponent*` OtherComp, `int32` OtherBodyIndex) | Called on not overlapping another actor. Accessible via UFunction |
| `ABaseController*` | OtherController() | Returns the other motion controller held by the player |
| `void` | RegisterEntityInput([`IBaseEntity*`](./IBaseEntity.md), `uint32` iButton, `bool` bOnReleased) | __ |
| `void` | SetStaticMesh(`UStaticMesh*` mesh) | Sets the static mesh of the controller |
| `void` | SetWhichHand(`EControllerHand` hand) | Sets the hand of the motion controller |

## Overridden
|  | Name | Description |
| --- | --- | --- |
| [`IBaseEntity`](./IBaseEntity.md) | | |
| `void` | DefaultThink() | Casts a spline and circle while `m_bTeleportationActive` is true |
| `void` | OnUsed([`ABaseEntity*`](./ABaseEntity.md) pActivator) | __ |
