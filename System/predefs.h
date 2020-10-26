// Creates commonly-used code aliases and definitions to be used throughout any project.

#ifndef VRBASE_PREDEFS_H
#define VRBASE_PREDEFS_H

#ifndef VRBASE_API
#define VRBASE_API
#endif

// types

typedef unsigned char      byte;
typedef unsigned short     ushort;
typedef unsigned int       uint;
typedef unsigned long long ulong;
typedef float              ftime; // time
typedef float              vec;   // float representing world space (used by vectors)
typedef unsigned short     eindex; // entity index
typedef float              lerp;   // linear interpolation

// aliases

#define interface class // no native interfaces
#define until(condition) while (!(condition))

// common functions

#define sqr(a) ((a) * (a))
#define toString(x) #x

// misc

// forward declarations of classes so that other classes can use them in header
// files
class IBaseEntity;
class ABaseEntity;
class ABasePawn;
class CTakeDamageInfo;
struct EHANDLE;

// tags denoting Unreal-to-entity classes
#define TAG_BASEENTITY    "VRBASE_BaseEntity"
#define TAG_BASEPAWN      "VRBASE_BasePawn"
#define TAG_BASECHARACTER "VRBASE_BaseCharacter"

// forward declaration of global entity lists
#define MAX_ENTITY_COUNT 2048
extern IBaseEntity*
                            g_ppEntityList[]; // const-index list, don't iterate over this, don't modify
extern TArray<IBaseEntity*> g_entList; // entity list, iterate through this instead.
                                       // All entries guaranteed to be non-null

#endif // VRBASE_PREDEFS_H
