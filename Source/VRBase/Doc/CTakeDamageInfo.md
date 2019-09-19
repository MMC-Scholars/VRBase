# `CTakeDamageInfo` Class

`CTakeDamageInfo` is a class which stores health and damage information for a given BaseEntity.

## Constructors

```cpp
CTakeDamageInfo(ushort damage, EHANDLE receiver, EHANDLE attacker);
```

## Functions

|  | Name | Description |
| -- | --- | --- |
| [`ushort`](typedefs.md) | GetBaseDamage() | Returns the base damage |
| [`EHANDLE`](EHandle.md) | GetAttacker() | Returns a safe pointer to the attacker |
| [`EHANDLE`](EHandle.md) | GetReceived() | Returns a safe pointer to the damage receiver |