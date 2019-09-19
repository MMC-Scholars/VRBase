# `EHandle` Utility

An `EHandle` is a safe pointer to an [`IBaseEntity`](IBaseEntity.md). What this means is that it provides the same functionality as a normal pointer to an [`IBaseEntity`](IBaseEntity.md), in addition to providing a fail-safe check in case the original entity is deleted and the pointer is no longer valid.

## Constructors
```cpp
EHANDLE(const IBaseEntity* pEnt);
EHANDLE(eindex iEnt);
```

## Functions

|  | Name | Description |
| -- | --- | --- |
| [`IBaseEntity*`](IBaseEntity.md) | Get() | Returns the entity |

_An EHandle acts the exact same as a pointer to an entity, provided that it is safe. This means that any operations performed on an entity can also be performed with an EHandle._