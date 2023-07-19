// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "LOSTBaseAIController.generated.h"

class ULOSTAIPerceptionComponent;
/**
 * 
 */
UCLASS()
class LOST_API ALOSTBaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	ALOSTBaseAIController();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	ULOSTAIPerceptionComponent* LOSTAIPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	FName FocusOnKeyName = "EnemyActor";

	virtual void OnPossess(APawn* InPawn) override;
	virtual void Tick(float DeltaSeconds) override;

private:
	AActor* GetFocusOnActor() const;
};
