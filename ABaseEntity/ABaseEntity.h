/**
 * This software is under partial ownership by The Ohio State University, 
 * for it is a product of student employees. For official policy, see
 * https://tco.osu.edu/sites/default/files/pdfs/IP-Policy.pdf 
 * or contact The Ohio State University's Office of Legal Affairs.
 */

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IBaseEntity/IBaseEntity.h"
#include "ABaseEntity.generated.h"

// each entity will have four of these total - two for each controller, pressed and released
// in IBaseEntity::PostInit() every entity will register themselves with their controllers based off of these values
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
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		bool m_STICK;
};

USTRUCT(BlueprintType)
struct FEntityInputRegistrationParams {
	GENERATED_USTRUCT_BODY()
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		FEntityInputRegistrationButtons m_onPressed;
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
		FEntityInputRegistrationButtons m_onReleased;
};

/**
 *-------------------------------------------------------------------------------------
 * ABaseEntity
 * Master base class for anything that is not controlled by the player
 * (i.e. anything that is not an APawn or an ACharacter)
 *-------------------------------------------------------------------------------------
 */
UCLASS()
class VRBASE_API ABaseEntity : public AActor, public IBaseEntity {
	public:
		DECLARE_CLASS_SIMPLE(ABaseEntity, IBaseEntity)
		GENERATED_BODY()

		ABaseEntity();

		virtual void OnUsed(ABaseEntity* pActivator) {}

		// unrecommended to override AActor functions
		virtual void BeginPlay() override;
		virtual void Tick(float deltaTime) override {  }
		virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override {}
		virtual void PostDuplicate(EDuplicateMode::Type mode) override {
		Super::PostDuplicate(mode);
		IBaseEntity::PostDuplicate(mode);
	}

	// "Use" controller input
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
