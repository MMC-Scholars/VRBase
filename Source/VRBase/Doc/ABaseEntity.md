# `ABaseEntity` Class

`extends` `AActor`, [`IBaseEntity`](./IBaseEntity.md)

`ABaseEntity` is a concrete class which inherits directly from [`IBaseEntity`](./IBaseEntity.md) and `AActor`. This links the two interfaces together. This is a common entry point for defining new classes; you should derive new classes from this and not from `AActor`.

## Variables

|  | Name | Description |
| --- | --- | --- |
| `float` | m_flUseMaxRadius | __. Accessible via UProperty |
| [`FEntityInputRegistrationParams`](./typedefs.md) | m_leftControllerInput | __. Accessible via UProperty |
| [`FEntityInputRegistrationParams`](./typedefs.md) | m_rightControllerInput | __. Accessible via UProperty |

## Overridden

|  | Name | Description |
| --- | --- | --- |
| [`IBaseEntity`](./IBaseEntity.md) | | |
| `virtual void` | DefaultThink() | __ |
| `virtual` [`FEntityInputRegistrationParams`](./typedefs.md) | GetLeftControllerInputRegistrationParams() | __ |
| `virtual` [`FEntityInputRegistrationParams`](./typedefs.md) | GetRightControllerInputRegistrationParams() | __ |
| `virtual void` | OnUsed(`ABaseEntity*` pActivator) | __ |
| `virtual bool` | IsUseableBy(`const` `ABaseController*`) | __ |

# Implementations
- [`ABaseController`](./ABaseController.md)
- [`ABaseMoving`](./ABaseMoving.md)
- [`AGameRules`](./AGameRules.md)
- [`AHMDTeleportTarget`](./AHMDTeleportTarget.md)