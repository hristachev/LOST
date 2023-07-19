// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "Actors/InteractionActor.h"
#include "WeaponBaseActor.generated.h"

class UCapsuleComponent;
class USphereComponent;
/**
 * 
 */
UCLASS()
class LOST_API AWeaponBaseActor : public AInteractionActor
{
	GENERATED_BODY()

public:
	AWeaponBaseActor();

	void EnableDamageCollision();
	void DisableDamageCollision();
	
	virtual void OnInteract_Implementation(AActor* InteractBy) override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* DamageCollision;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
	float DamageAmount = 15.0f;

	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnDamageCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	AController* GetController() const;

	void AttachWeaponToSocket(AWeaponBaseActor* Weapon, USceneComponent* SceneComponent, const FName& SocketName);
};
