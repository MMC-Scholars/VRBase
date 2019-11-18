# `NLogger` Namespace

`NLogger` is a namespace which defines useful on-screen logging functionality. The most helpful one is Msg(`const` `char*` pszFormat, …) which is a `printf`-like function to log messages to the screen.

## Usage
```cpp
#include "System/NLogger.h"
...
Msg("Created %d actors", 4);
```

## Functions

|  | Name | Description |
| --- | --- | --- |
| `void` | Blurp(`const` `char*` pszFormat, ...), <br /> Blurp(`const` `FString&` str) | Prints a temporary message to the screen. Messages display for a short amount of time. This is intended for messages that print out constantly |
| `void` | Fatal(`const` `char*` pszFormat, ...), <br /> Fatal(`const` `FString&` str) | Prints a fatal message to the screen |
| `void` | Msg(`const` `char*` pszFormat, ...), <br /> Msg(`const` `wchar_t*` pszFormat, ...), <br /> Msg(`const` `FString&` str), <br /> Msg(`const` `FVector&` v), <br /> Msg(`const` `FRotator&` r) <br /> Msg(`AActor*` actor) | Prints a given message to the screen |
| `void` | Warning(`const` `char*` pszFormat, ...), <br /> Warning(`const` `FString&` str) | Prints a warning message to the screen |
