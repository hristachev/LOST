// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "LOSTPlayerInteractionComponent.h"
#include "Components/ActorComponent.h"
#include "LOSTWeaponComponent.generated.h"


class AWeaponBaseActor;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOST_API ULOSTWeaponComponent : public ULOSTPlayerInteractionComponent
{
	GENERATED_BODY()

public:	
	ULOSTWeaponComponent();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<AWeaponBaseActor> WeaponClass;

	UPROPERTY(EditDefaultsOnly, Category = "Animations")
	UAnimMontage* AttackMontage;

	UPROPERTY()
	AWeaponBaseActor* CurrentWeapon;

public:
	void StartAttack();

	AWeaponBaseActor* GetWeaponActor() { return CurrentWeapon; }
	bool GetInAttack() const { return bInAttack; }

private:
	bool bInAttack = false;

	virtual void InitAnimations() override;
	void EndAttack(USkeletalMeshComponent* MeshComponent);
};


