// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "Animations/LOSTBaseNotifyState.h"
#include "AttackNotifyState.generated.h"

class LOSTUtils;
/**
 * 
 */
UCLASS()
class LOST_API UAttackNotifyState : public ULOSTBaseNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	
};
