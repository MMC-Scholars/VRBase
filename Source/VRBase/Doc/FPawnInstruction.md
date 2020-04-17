# `FPawnInstruction` Struct

An `FPawnInstruction` represents a text instruction to display to a player. These are connected to an [`ABasePawn`](./ABasePawn.md) instance and should not need to be instantiated otherwise.

## Constructors

```cpp
FPawnInstruction();
FPawnInstruction(FString string);
```

## Variables

| Order | | Member | Description |
| --- | --- | --- | --- |
| 4 | `bool` | changeOnButtonPress | If true, will switch instruction on button press. Otherwise, will switch based on time. Accessible via UProperty |
| 2 | `FColor` | color | The instruction color. Default is white. Accessible via UProperty |
| 3 | `EControllerHand` | hand | The hand the instruction should be displayed near. Default is `Right`. Accessible via UProperty |
| 1 | `FText` | text | The instruction text to display. Accessible via UProperty |
| 5 | `float` | timedChange | The time needed to switch instructions. Default is 5. Accessible via UProperty |
