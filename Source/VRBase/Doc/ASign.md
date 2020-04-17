# `ASign` Class

`extends` [`ABaseEntity`](./ABaseEntity.md)

`ASign` removes the need for multiple TextRender components and manual text wrapping. `ASign` represents a textbox with customizeable properties.

## Variables

|  | Name | Description |
| --- | --- | --- |
| `bool` | m_bAlwaysFacePlayer | Boolean whether the text should always face the player. Accessible via UProperty |
| `bool` | m_bMeshHiddenInGame | Boolean whether the mesh should be hidden in game. Default is true. Accessible via UProperty |
| `EHorizTextAligment` | m_eAlignX | The text horizontal alignment. Accessible via UProperty |
| `EVerticalTextAligment` | m_eAlignY | The text vertical alignment. Accessible via UProperty |
| `float` | m_fFontSize | The text font size. Accessible via UProperty |
| `UMaterialInterface*` | m_pMeshMaterial | The material of the mesh. Accessible via UProperty |
| `FColor` | m_sColor | The text color. Accessible via UProperty |
| `FString` | m_string | The text to display. Accessible via UProperty |

## Overridden
|  | Name | Description |
| --- | --- | --- |
| [`ABaseEntity`](./ABaseEntity.md) | | |
| `virtual void` | PreInit() | Called before initializing the actor |
| `virtual void` | DefaultThink() | Called each frame |
