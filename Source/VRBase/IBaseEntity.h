// Fill out your copyright notice in the Description page of Project Settings.
#ifndef MMC_IBASEENTITY_H
#define MMC_IBASEENTITY_H
#include "CoreMinimal.h"
#include "Engine.h"

#define abstract_class class

/**
 * 
 */
abstract_class VRBASE_API IBaseEntity {



public:
	int m_iHealth;
	int m_iFlags;

	IBaseEntity();
	~IBaseEntity();

public:
	
	


};

#endif //MMC_IBASEENTITY_H
