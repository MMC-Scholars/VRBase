

#pragma once

#include "CoreMinimal.h"
#include "ABaseEntity/ABaseEntity.h"
#include "ABaseMoving.generated.h"

//Fractional lerp value for measuring the open/closed status of a still door
#define OPENCLOSE_MEASURE_TOLERANCE 0.05f
#define OPENCLOSE_MOVING_MEASURE_TOLERANCE 0.001f

/****************************************************************************
 * This class is an interface for anything that moves on 0.0-1.0 scale.
 *		Ex. Sliding door, pivoting door.
 *	Does not explicitly have to move between two settings but can also model
 *		a strength of a single setting
 *		Ex. Velocity-scaled follower
 ***************************************************************************/
//TODO @Michael Implement all of this and add more functionality
UCLASS()
class VRBASE_API ABaseMoving : public ABaseEntity
{
public:
	GENERATED_BODY()
	
	ABaseMoving();
	

	virtual void PreInit() override;

	virtual void PostInit() override;

	virtual void OnUsed(ABaseEntity*) override;

	virtual void SetPositionFromController(ABaseController*);

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseMoving")
		bool m_bAttachToController;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseMoving")
	float m_lInitialLerp; //Start lerp value for when 

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseMoving")
	float m_flLerpSpeed;

	UFUNCTION(BlueprintCallable, Category = "BaseMoving")
	virtual void SetLerpPosition(float _lLerp) { m_lCurrentLerp = _lLerp; }

	UFUNCTION(BlueprintCallable, Category = "BaseMoving")
	float GetLerpPosition() const { return m_lCurrentLerp; }

	UFUNCTION(BlueprintCallable, Category = "BaseMoving")
	void Open();

	UFUNCTION(BlueprintCallable, Category = "BaseMoving")
	void Close();

	UFUNCTION(BlueprintCallable, Category = "BaseMoving")
	bool IsOpen() const;

	UFUNCTION(BlueprintCallable, Category = "BaseMoving")
	bool IsClosed() const;

	UFUNCTION(BlueprintCallable, Category = "BaseMoving")
	bool IsOpening() const;

	UFUNCTION(BlueprintCallable, Category = "BaseMoving")
	bool IsClosing() const;

	UFUNCTION(BlueprintCallable, Category = "BaseMoving")
	bool IsMoving() const { return IsOpening() || IsClosing(); }

	UFUNCTION(BlueprintImplementableEvent, Category = "BaseMoving")
	void OnFinishOpen();

	UFUNCTION(BlueprintImplementableEvent, Category = "BaseMoving")
	void OnFinishClose();

private:
	lerp m_lCurrentLerp;
	ABaseController* m_pHoldingController; //What controller is holding on to us?

	static void OpenThink(void* vpBaseMoving);
	static void CloseThink(void* vpBaseMoving);
	static void AttachThink(void* vpBaseMoving);
};
