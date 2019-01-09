// This software is under partial ownership by The Ohio State University, 
//for it is a product of student employees. For official policy, see
//https://tco.osu.edu/wp-content/uploads/2013/09/PatentCopyrightPolicy.pdf 
//or contact The Ohio State University's Office of Legal Affairs

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IBaseEntity/IBaseEntity.h"
#include "ABaseEntity.generated.h"

//Each entity will have four of these total - two for each controller, pressed and released.
//In IBaseEntity::PostInit(), every entity will register themselves with their controllers based off of these values.
USTRUCT(BlueprintType)
struct FEntityInputRegistrationButtons {
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		bool m_AX;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		bool m_BY;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		bool m_TRIGGER;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		bool m_GRIP;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		bool m_MENU;
};

//This has two sets of booleans - one for released, one for pressed.
//Each entity will have two of these, one for each controller.
USTRUCT(BlueprintType)
struct FEntityInputRegistrationParams {
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		FEntityInputRegistrationButtons m_onPressed;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		FEntityInputRegistrationButtons m_onReleased;
};

//-------------------------------------------------------------------------------------
// This is our master base class for anything that is not controlled by the player.
// I.e. anything that is not an APawn or an ACharacter
//-------------------------------------------------------------------------------------
UCLASS()
class VRBASE_API ABaseEntity : public AActor, public IBaseEntity
{
public:
	DECLARE_CLASS_SIMPLE(ABaseEntity, IBaseEntity)
	GENERATED_BODY()

	//not much to do here because most of the functionality is built into
	//the IBaseEntity interface
	ABaseEntity();

	virtual void OnUsed(ABaseEntity* pActivator) {}
	virtual void DefaultThink() {}

	//you can override these if you want, but there's no guarantees
	//about how these interact with the new custom game flow
	//for example, BeginPlay() might be called before 
	// g_pGlobals->curtime is correctly set
	virtual void BeginPlay() override;
	virtual void Tick(float deltaTime) override {  }
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override {}
	virtual void PostDuplicate(EDuplicateMode::Type mode) override {
		Super::PostDuplicate(mode);
		IBaseEntity::PostDuplicate(mode);
	}

	//Controller input for "use"
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		FEntityInputRegistrationParams m_leftControllerInput;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		FEntityInputRegistrationParams m_rightControllerInput;

	//These overrides expose our UPROPERTY variables to IBaseEntity
	virtual FEntityInputRegistrationParams*			GetLeftControllerInputRegistrationParams() { return &m_leftControllerInput; }
	virtual FEntityInputRegistrationParams*			GetRightControllerInputRegistrationParams() { return &m_rightControllerInput; }

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		float m_flUseMaxRadius;

	virtual bool IsUseableBy(const ABaseController*) const override;
};
