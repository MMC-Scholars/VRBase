#pragma once

#include "APickup/APickup.h"

#include "ABaseMoving.generated.h"

// fractional lerp value for measuring the open/closed status of a still door
#define OPENCLOSE_MEASURE_TOLERANCE        0.05f
#define OPENCLOSE_MOVING_MEASURE_TOLERANCE 0.001f

/**
 *-------------------------------------------------------------------------------------
 * ABaseMoving
 * An interface for anything that moves on 0.0 - 1.0 scale (e.g. a sliding door,
 * a pivoting door).
 * Does not explicitly have to move between two settings but can also model
 * a strength of a single setting (e.g. a velocity-scaled follower)
 *-------------------------------------------------------------------------------------
 */
UCLASS()
class VRBASE_API ABaseMoving : public APickup {
public:
    GENERATED_BODY()

    ABaseMoving();
    virtual void OnConstruction(
        const FTransform& Transform) override; // sets all in-editor properties

    virtual void PreInit() override;
    virtual bool IsUseableBy(const ABaseController*) const override;

    virtual void Pickup(ABaseController* pController) override;
    virtual void Drop(ABaseController* pController) override;

    virtual void SetPositionFromController(ABaseController*);

    bool m_bAttachToController;

    UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "BaseMoving")
    float m_lInitialLerp;

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

protected:
    bool             m_bInAttachThink;
    float            m_lCurrentLerp;
    ABaseController* m_pHoldingController; // what controller is holding on to us?

    FVector m_vTempAttachLoc; // the position of the object if it were not
                              // constrained (e.g. the position of the
                              // controller during movement)

    static void OpenThink(void* vpBaseMoving);
    static void CloseThink(void* vpBaseMoving);
    static void AttachThink(void* vpBaseMoving);
};
