// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "PhysicsEngine/PhysicalAnimationComponent.h"
#include "LOSTPhysicalAnimationComponent.generated.h"

/**
 * 
 */
UCLASS()
class LOST_API ULOSTPhysicalAnimationComponent : public UPhysicalAnimationComponent
{
	GENERATED_BODY()

public:
	ULOSTPhysicalAnimationComponent();

	void HitReaction(FHitResult HitResult);

protected:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hit")
	float HitReactionTimeRemaining = 1.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hit")
	FName HipsName = "Spine";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hit")
	FName ProfileName = "HitReactionProfile";

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Hit")
	float ImpulseStrength = 10000.0f;

private:
	USkeletalMeshComponent* GetOwnerMesh(AActor* Actor);
};

