// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "LOSTBaseAnimNotify.h"
#include "EndAttackAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class LOST_API UEndAttackAnimNotify : public ULOSTBaseAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
