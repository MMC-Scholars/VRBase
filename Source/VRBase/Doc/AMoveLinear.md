# `AMoveLinear` Class

`extends` [`ABaseMoving`](./ABaseMoving.md)

`AMoveLinear` is an extension of [`ABaseMoving`](./ABaseMoving.md) which moves in a linear fashion.

## Variables

|  | Name | Description |
| --- | --- | --- |
| `FPlane` | m_endPlane | __ |
| `bool` | m_hasParent | True if actor has parent attached |
| `FVector` | m_parentToThis | __ |
| `FVector` | m_startLoc | The starting location of the vector |
| `FPlane` | m_startPlane | __ |
| `UStaticMeshComponent*` | m_staticMesh | The static mesh of this actor. Accessible via UProperty |
| `FVector` | m_vDirection | The direction of the vector. Accessible via UProperty |
| `FVector` | m_vOriginalDirection | The starting or original direction of the vector |

## Functions

|  | Name | Description |
| --- | --- | --- |
| `virtual void` | SetLerpPosition(`float` fLerp) | Sets the current lerp position. Accessible via UFunction |
| `virtual void` | SetPositionFromController([`ABaseController`](./ABaseController.md) controller) | Sets the position based on the position of an [`ABaseController`](./ABaseController.md) |

## Overridden
|  | Name | Description |
| --- | --- | --- |
| [`IBaseEntity`](./IBaseEntity.md) | | |
| `void` | DefaultThink() | Called every frame following all PreInit() calls |
| `void` | PreInit() | Called at initialization |
