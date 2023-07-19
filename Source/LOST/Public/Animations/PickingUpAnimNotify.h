// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "LOSTBaseAnimNotify.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "PickingUpAnimNotify.generated.h"

/**
 * 
 */
UCLASS()
class LOST_API UPickingUpAnimNotify : public ULOSTBaseAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
