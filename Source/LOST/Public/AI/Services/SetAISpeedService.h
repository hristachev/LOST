// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "SetAISpeedService.generated.h"

/**
 * 
 */
UCLASS()
class LOST_API USetAISpeedService : public UBTService
{
	GENERATED_BODY()

public:
	USetAISpeedService();
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Speed")
	float SpeedValue = 35.0f;
	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
private:
	void SetAISpeed(APawn* Pawn);
};
