// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AICombatComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOST_API UAICombatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UAICombatComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Attack")
	float DamageValue = 25.0f;

	UFUNCTION(BlueprintCallable, Category = "Animations")
	UAnimMontage* GetAttackMontage() const { return AttackMontage; }

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Attack")
	UAnimMontage* AttackMontage;
	
public:	
private:
	void PlayAnimMontage(UAnimMontage* Animation);
	
};
