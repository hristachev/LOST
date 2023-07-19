// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "CheckPlayerRangeService.generated.h"

/**
 * 
 */
UCLASS()
class LOST_API UCheckPlayerRangeService : public UBTService
{
	GENERATED_BODY()

public:
	UCheckPlayerRangeService();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	FBlackboardKeySelector IsPlayerInRangeKeySelector;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	float AttackRange = 200.0f;

	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;

private:
	bool IsEnemyInRange = false;

};
