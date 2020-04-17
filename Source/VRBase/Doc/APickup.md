# `APickup` Class

`extends` [`ABaseEntity`](./ABaseEntity.md)

`APickup` is a concrete `ABaseEntity`-derived class containing a static mesh. It and any classes derived from it can be picked up by any `ABaseController`.

## Variables

|  | Name | Description |
| --- | --- | --- |
| `UMaterialInterface*` | material0 | The material of the pickup mesh. Accessible via UProperty |
| `TArray`<`AActor*`> | m_aParentActors | Array of parent actors which the pickup is attached to |
| `UStaticMeshComponent*` | m_pPickupMeshComponent | The mesh component of the pickup |
| `UStaticMesh*` | staticMesh | The static mesh of the pickup. Accessible via UProperty |

## Functions

|  | Name | Description |
| --- | --- | --- |
| `virtual void` | Drop([`ABaseController*`](./ABaseController.md) controller) | Drops the pickup from the controller |
| `void` | OnDrop([`ABaseController*`](./ABaseController.md) controller) | Called on drop of pickup. Accessible via UFunction |
| `void` | OnPickup([`ABaseController*`](./ABaseController.md) controller) | Called on attachment of pickup. Accessible via UFunction |
| `virtual void` | Pickup([`ABaseController*`](./ABaseController.md) controller) | Attaches the pickup to the controller |

## Overridden
|  | Name | Description |
| --- | --- | --- |
| [`ABaseEntity`](./ABaseEntity.md) | | |
| `virtual void` | PreInit() | Called before initializing the actor |
