# `AWorldButton` Class

`extends` [`ABaseEntity`](./ABaseEntity.md)

`AWorldButton` is used to define a button or activator which executes some functions when pressed.

## Variables

|  | Name | Description |
| --- | --- | --- |
| `UStaticMeshComponent*` | m_pMeshComponent | The static mesh component representing the mesh |
| `USoundCue*` | m_pOnPressCue | Sound to play on press. Accessible via UProperty |
| `UMaterialInterface*` | m_pOnPressMaterial | Switch to this material for the duration of the press. Accessible via UProperty |
| `UStaticMesh*` | m_pStaticMesh | Defines the static mesh of the button. Accessible via UProperty |

## Functions

|  | Name | Description |
| --- | --- | --- |
| `void` | OffPressed([`ABaseController*`](./ABaseController.md) pController) | Called on end button press. Accessible via UFunction |
| `virtual void` | OffPressed_Implementation([`ABaseController*`](./ABaseController.md) pController) | Called on end button press |
| `void` | OnOverlapBegin(`UPrimitiveComponent*` OverlappedComp, `AActor*` OtherActor, `UPrimitiveComponent*` OtherComp, `int32` OtherBodyIndex, `bool` bFromSweep, `const` `FHitResult&` SweepResult) | Called on overlapping another actor. Accessible via UFunction |
| `void` | OnOverlapEnd(`UPrimitiveComponent*` OverlappedComp, `AActor*` OtherActor, `UPrimitiveComponent*` OtherComp, `int32` OtherBodyIndex) | Called on not overlapping another actor. Accessible via UFunction |
| `void` | OnPressed([`ABaseController*`](./ABaseController.md) pController) | Called on button press. Accessible via UFunction |
| `virtual void` | OnPressed_Implementation([`ABaseController*`](./ABaseController.md) pController) | Called on button press |

## Overridden
|  | Name | Description |
| --- | --- | --- |
| [`ABaseEntity`](./ABaseEntity.md) | | |
| `virtual void` | OnUsed([`ABaseEntity*`](./ABaseEntity.md) override) | __ |
