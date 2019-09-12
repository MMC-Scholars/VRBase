# `EHandle` Utility

An `EHandle` is a safe pointer to an IBaseEntity. What this means is that it provides the same functionality as a normal pointer to an IBaseEntity, in addition to providing a fail-safe check in case the original entity is deleted and the pointer is no longer valid.

## Constructors
```cpp
EHANDLE(const IBaseEntity* pEnt);
EHANDLE(eindex iEnt);
```

<!-- ## Operations

## Functions

|  | Name | Description |
| -- | --- | --- |
| `IBaseEntity*` | Get() | Returns the entity. | -->