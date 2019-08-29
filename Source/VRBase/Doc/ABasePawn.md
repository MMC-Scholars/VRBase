# `ABasePawn` Class

`inherits APawn`, [`IBaseEntity`](IBaseEntity.md)

`ABasePawn` works as a basic possessable virtual reality pawn. This class automatically comes with an HMD and two [`ABaseController`](ABaseController.md) motion controllers. 

<!-- `ABasePawn` is a concrete class which inherits from `IBaseEntity` and `APawn` and links the two interfaces together. It works as a virtual reality camera and also spawns a pair of `ABaseController` virtual reality controllers. `ABasePawn` is the class embodiment of the user. -->



## UProperties

## Variables

|  | Name | Description |
| --- | --- | --- |

## Functions

|  | Name | Description |
| -- | --- | --- |
| `void` | SetControllerClass(`UClass`* leftControllerClass, `UClass`* rightControllerClass) | Sets classes to be used by motion controllers. Both must be classes which inherit from `ABaseController`. These can also be changed via `UProperty`. |
| `bool` | IsWithinTeleportBounds(const `FVector`& location, const `FVector`& bOrigin, const `FVector`& bExtent) | |
|	`bool` | CanTeleportToLocation(const `FVector`& loc) | |
|	`bool` | TeleportPlayer(const `FVector`& loc, const `FRotator`& rot) | |

<!-- void SetInstruction(FPawnInstruction instr);
void NextInstruction(); -->

