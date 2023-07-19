// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "Enemies/LOSTZombieBaseCharacter.h"
#include "ZombieWorkerCharacter.generated.h"

class UTextRenderComponent;
/**
 * 
 */
UCLASS()
class LOST_API AZombieWorkerCharacter : public ALOSTZombieBaseCharacter
{
	GENERATED_BODY()

public:
	AZombieWorkerCharacter(const FObjectInitializer& ObjInit);

protected:
	UPROPERTY(BlueprintReadWrite, EditDefaultsOnly)
	UTextRenderComponent* HealthTextComponent;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;

	virtual bool IsRunning() const override;

private:
	bool bReadyToRun = false;
};
