# `ABaseMoving` Class

`extends` [`ABaseEntity`](./ABaseEntity.md)

An [`ABaseEntity`](./ABaseEntity.md)-derived interface for other concrete classes which may generally move on a 0-1 scale; for example, a sliding door, a rotating door, or a pushable button. This should never be instantiated; rather, it should be extended.

## Variables

|  | Name | Description |
| --- | --- | --- |
| `bool` | m_bAttachToController | True if attached to a controller. Accessible via UProperty |
| `float` | m_flLerpSpeed | The speed of the lerp. Accessible via UProperty |
| `float` | m_lInitialLerp | Specifies the starting lerp value. Accessible via UProperty |

## Functions

|  | Name | Description |
| --- | --- | --- |
| `void` | Close() | __. Accessible via UProperty |
| `float` | GetLerpPosition() | Returns the current lerp value. Accessible via UFunction |
| `bool` | IsClosed() | Returns true if the actor is closed. Accessible via UFunction |
| `bool` | IsClosing() | Returns true if the actor is closing. Accessible via UFunction |
| `bool` | IsOpen() | Returns true if the actor is open. Accessible via UFunction |
| `bool` | IsOpening() | Returns true if the actor is opening. Accessible via UFunction |
| `bool` | IsMoving() | Returns true if the actor is moving. Accessible via UFunction |
| `void` | OnFinishClose() | Called once the actor has stopped closing. Accessible via UFunction |
| `void` | OnFinishOpen() | Called once the actor has stopped opening. Accessible via UFunction |
| `void` | Open() | Opens the actor. Accessible via UFunction |
| `virtual void` | SetLerpPosition(`float` fLerp) | Sets the current lerp position. Accessible via UFunction |
| `virtual void` | SetPositionFromController([`ABaseController`](./ABaseController.md) controller) | Sets the position based on the position of an [`ABaseController`](./ABaseController.md) |

## Overridden
|  | Name | Description |
| --- | --- | --- |
| [`IBaseEntity`](./IBaseEntity.md) | | |
| `virtual bool` | IsUseableBy(`const` [`ABaseController*`](./ABaseController.md)) | __ | 
| `void` | OnUsed([`ABaseEntity*`](./ABaseEntity.md) pActivator) | __ |
| `virtual void` | PreInit() | __ |
