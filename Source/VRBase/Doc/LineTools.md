# LineTools Namespace

`LineTools` declares a set of utility functions for tracing and drawing various shapes. For example, `LineTools` is used by [`ABaseController`](ABaseController.md) for teleportation.

## Usage

```cpp
#include "LineTools/linetools.h"
...
SLineDrawParams lineProps;
lineProps.Color = FColor::FromHex("CCC");
lineProps.Thickness = 0.4f;
lineProps.Duration = 0.1f;

UTIL_DrawLine(myActor->GetComponentLocation(), FVector(0, 0, 0), &lineProps);
```

## `SLineDrawParams` Struct

| Order |  | Member | Description |
| --- | --- | --- | --- |
| 1 | `FColor` | Color | The color of the line |
| 3 | [`ftime`](typedefs.md) | Duration | The duration or lifetime of the line once rendered  |
| 2 | `float` | Thickness | The thickness of the line |

## Functions

|  | Name | Description |
| --- | --- | --- |
| `void` | UTIL_TraceLine(`FHitResult&` t, `const` `FVector&` start, `FVector` direction, `AActor**` ppIgnoredActors, `float` maxDistance) | Performs a ray cast and stores the result in the `FHitResult` |
| `void` | UTIL_TraceSpline(`FHitResult&` t, `const` `FVector&` start, `FVector` direction, `FVector` force, `uint16` maxIterations, `SLineDrawParams*` rendered, `AActor**` ppIgnoredActors) | Performs a spline cast and stores the result in the `FHitResult`. The magnitude of the direction does not affect the trace; however, the direction and magnitude of the force determines the curvature of the spline |
| `void` | UTIL_DrawLine(`FVector` start, `FVector` end, `SLineDrawParams*` rendered) | Draws a line in the world |
| `void` | UTIL_DrawSpline(`FVector` start, `FVector` end, `FVector` force, `FColor` c, `float` thickness, [`ftime`](typedefs.md) life) | Draws a spline curve in the world. The direction and magnitude of force determines the curvature of the spline |
| `void` | UTIL_DrawCircle(`FVector` loc, [`vec`](typedefs.md) radius, `SLineDrawParams*` lineParams) | Renders a circle in the world |
| [`vec`](typedefs.md) | UTIL_DistanceToLine(`FVector` vDirection, `FVector` vOrigin, `FVector` point) | Finds the distance between that worldline and the given point. The magnitude of vDirection does not affect the returned value |

[Main](../README.md)