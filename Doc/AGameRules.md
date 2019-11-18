# `AGameRules` Class

`extends` [`ABaseEntity`](./ABaseEntity.md)

`AGameRules` is invisible in game. It controls the initialization of all entities. You should extend this class to define the global rules of how your specific virtual reality game works; use it like a level blueprint. You will need to manually place it into your level; afterwards, the global variable `g_pGameRules` can be used from anywhere in your C++ code to access it.

## Functions

|  | Name | Description |
| --- | --- | --- |
| `bool` | GameReady() | Returns true when all entities have been initialized |
| [`ftime`](./typedefs.md) | GetNextResetRount() | __ |
| `virtual void` | RestartRound() | __ |
| `void` | SetNextRoundRestart([`ftime`](./typedefs.md) next) | __ |
