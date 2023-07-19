// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "AI/LOSTBaseAICharacter.h"
#include "LOSTZombieBaseCharacter.generated.h"


UCLASS()
class LOST_API ALOSTZombieBaseCharacter : public ALOSTBaseAICharacter
{
	GENERATED_BODY()

public:
	ALOSTZombieBaseCharacter(const FObjectInitializer& ObjInit);

	void EnableDamageCollision();
	void DisableDamageCollision();
	
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Components")
	UCapsuleComponent* DamageCollision;

	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnDamageCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
