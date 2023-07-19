// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "LOSTStaminaComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOST_API ULOSTStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	ULOSTStaminaComponent();


	UFUNCTION(BlueprintCallable, Category = "Health")
	bool IsTired() const { return FMath::IsNearlyZero(Stamina); }

	UFUNCTION(BlueprintCallable, Category = "Health")
	float GetStaminaPercent() const { return Stamina / MaxStamina; }

	float GetStamina() const { return Stamina; }

	bool IsStaminaFull() const;
protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina", meta = (ClampMin = "0.0", ClampMax = "100.0"))
	float MaxStamina = 100.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
	bool AutoRecover = true;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina", meta = (EditCondition = "AutoRecover"))
	float RecoverUpdateTime = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina", meta = (EditCondition = "AutoRecover"))
	float RecoverModifier = 1.0f;

public:	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION()
	void StaminaChange(float ChangeValue);

private:
	float Stamina = 0.0f;
	FTimerHandle RecoverTimerHandle;


	void RecoverUpdate();
	void SetStamina(float NewStamina);
};
