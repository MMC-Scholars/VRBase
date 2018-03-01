// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs

//-------------------------------------------------------------------------------------
// The purpose of this file is to define and alias things which are useful all-around
//-------------------------------------------------------------------------------------
#ifndef MMC_PREDEFS_H
#define MMC_PREDEFS_H

#include "CoreMinimal.h"

//Typedefs
typedef unsigned char	byte;
typedef unsigned short	ushort;
typedef unsigned int	uint;
typedef unsigned long	ulong;

typedef float			ftime; //denotes time variable
typedef unsigned long	hcode; //denotes a ulong which is a unique hashcode
typedef float			vec; //denotes a float used by vectors; represents world space
typedef unsigned short	eindex;

//Syntax aliases
#define until(condition) while (!(condition)) //simplifies thinking in some contexts
#define abstract_class class //denotes a class as one which should not be directly constructed
#define DECLARE_CLASS_SIMPLE(ChildClass, ParentClass) \
	typedef ChildClass ThisClass; \
	typedef ParentClass BaseClass;

//forward declarations of classes so that other classes can contain pointers to them in their header files
class IBaseEntity;
class CBaseEntity;
class CBasePawn;
class CBaseCharacter;
class CTakeDamageInfo;
struct EHANDLE;

//tags denoting our Unreal-to-entity classes
#define TAG_BASEENTITY		"MMC_BaseEntity"
#define TAG_BASEPAWN		"MMC_BasePawn"
#define TAG_BASECHARACTER	"MMC_BaseCharacter"



//Forward declaration of global entity lists
#define MAX_ENTITY_COUNT 2048
extern IBaseEntity* g_ppEntityList[];	//const-index list, don't iterate over this, don't modify
extern TArray<IBaseEntity*>* g_ppEntityListSmall; //entity list, iterate through this instead



#endif //MMC_PREDEFS_H