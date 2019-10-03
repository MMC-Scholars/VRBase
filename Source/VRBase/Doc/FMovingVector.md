# `FMovingVector` Class

`extends` `FVector`

An `FMovingVector` is a general purpose moving vector. This works closely with [`IMovingVectorManager`](IMovingVectorManager.md).

## Constructors
```cpp
FMovingVector(const FVector& v);
FMovingVector(const FVector& v, const FVector& vel);
FMovingVector(vec x, vec y, vec z);
FMovingVector(vec x, vec y, vec z, vec dx, vec dy, vec dz);
```

## Variables

|  | Name | Description |
| --- | --- | --- |
| `FVector` | velocity | The velocity of the vector |

## Functions

|  | Name | Description |
| --- | --- | --- |
| [`vec`](./typedefs.md) | speed() | Returns the speed of the moving vector |
