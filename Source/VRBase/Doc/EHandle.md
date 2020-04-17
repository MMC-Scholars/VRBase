# `EHandle` Utility

An `EHandle` is a safe pointer to an [`IBaseEntity`](IBaseEntity.md). What this means is that it provides the same functionality as a normal pointer to an [`IBaseEntity`](IBaseEntity.md), in addition to providing a fail-safe check in case the original entity is deleted and the pointer is no longer valid.

An `EHandle` provides a handler to an [`IBaseEntity`](IBaseEntity.md) acting as a pointer. 
An `EHandle` is safe against entities which are removed after the initial `EHandle` is created. 
What this means is that a BaseEntity that is overwritten after game start will not return an 
arbitrary garbage value or entity, but instead, `NULL`. `EHandles` act as wrappers for `BaseEntities`, e.g.
```cpp
APickup* pPickup = (APickup*) GetWorld()->SpawnActor(APickup::StaticClass(), &loc);
EHANDLE m_pMyPickup = EHANDLE(pPickup);
```

## Constructors
```cpp
EHANDLE(const IBaseEntity* pEnt);
EHANDLE(eindex iEnt);
```

## Functions

|  | Name | Description |
| -- | --- | --- |
| [`IBaseEntity*`](IBaseEntity.md) | Get() | Returns the entity |

_An EHandle acts as a pointer to an entity to ensure safety. This means that any operations performed on a pointer can also be performed with an EHandle._