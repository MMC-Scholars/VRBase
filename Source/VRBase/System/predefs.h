/**
 * This software is under partial ownership by The Ohio State University, 
 * for it is a product of student employees. For official policy, see
 * https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf 
 * or contact The Ohio State University's Office of Legal Affairs.
 */

// predefs.h creates commonly-used aliases and definitions throughout the project.

#ifndef VRBASE_PREDEFS_H
#define VRBASE_PREDEFS_H

#include "CoreMinimal.h"

#ifndef VRBASE_API
#define VRBASE_API
#endif

typedef unsigned char							byte;
typedef unsigned short						ushort;
typedef unsigned int							uint;
typedef unsigned long long				ulong;

typedef float											ftime; // time
typedef float											vec; // float representing world space (used by vectors)
typedef unsigned short						eindex; // entity index

// TODO remove later?
#define STRINGIZE(tokens) #tokens // stringifies a token

#define until(condition) while (!(condition)) // simplifies thinking in many contexts
#define abstract_class class // abstract class never directly constructed

#define DECLARE_CLASS_SIMPLE(ChildClass, ParentClass) \
	typedef ChildClass ThisClass; \
	typedef ParentClass BaseClass;

// forward declarations of classes so that other classes can use them in header files
class IBaseEntity;
class ABaseEntity;
class ABasePawn;
class ABaseCharacter;
class CTakeDamageInfo;
struct EHANDLE;

// tags denoting Unreal-to-entity classes
#define TAG_BASEENTITY						"VRBASE_BaseEntity"
#define TAG_BASEPAWN							"VRBASE_BasePawn"
#define TAG_BASECHARACTER					"VRBASE_BaseCharacter"

// forward declaration of global entity lists
#define MAX_ENTITY_COUNT 2048
extern IBaseEntity* g_ppEntityList[];	// const-index list, don't iterate over this, don't modify
extern TArray<IBaseEntity*> g_entList; // entity list, iterate through this instead. All entries guaranteed to be non-null

#endif // VRBASE_PREDEFS_H