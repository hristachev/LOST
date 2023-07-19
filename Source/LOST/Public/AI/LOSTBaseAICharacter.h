// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "BaseClasses/LOSTBaseCharacter.h"
#include "LOSTBaseAICharacter.generated.h"

class UAICombatComponent;
class UBehaviorTree;
UCLASS()
class LOST_API ALOSTBaseAICharacter : public ALOSTBaseCharacter
{
	GENERATED_BODY()

public:
	ALOSTBaseAICharacter(const FObjectInitializer& ObjInit);
	
	virtual void SetMaxSpeed(float SpeedValue);

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
	UBehaviorTree* BehaviorTreeAsset;
	
	UFUNCTION(BlueprintCallable, Category = "AI")
	UAICombatComponent* GetAICombat() const { return CombatComponent; }

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UAICombatComponent* CombatComponent;


	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Drop")
	TSubclassOf<AActor> DropItemActor;
	
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void OnDeath() override;
	virtual void DropItem();

private:
	UFUNCTION()
	void SpawnActorTrace(FVector& Location, FRotator& Rotation);
};
