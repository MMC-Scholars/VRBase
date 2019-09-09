/**
 * This software is under partial ownership by The Ohio State University, 
 * for it is a product of student employees. For official policy, see
 * https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf 
 * or contact The Ohio State University's Office of Legal Affairs.
 */

// IBaseEntity_shared.h declares UPROPERTY and UFUNCTION accessible variables 
// and functions shared between all classes which derive from IBaseEntity (as 
// IBaseEntity itself cannot have UPROPERTY or UFUNCTION). These includes do 
// not serve any purpose at compile time; rather, they only help with parsing 
// during editing.

#ifndef IBASEENTITY_H
#include "CoreMinimal.h"
#include "UnrealEngine.h"
#include "GameFramework/Actor.h"
#include "System/predefs.h"
#include "System/Globals.h"
#include "System/static_initialize.h"
#include "System/EHandle.h"
#include "IBaseEntity_flags.h"
#endif

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
SEntityInputRegistrationParams m_leftControllerInput;

UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Input)
SEntityInputRegistrationParams m_leftControllerInput;