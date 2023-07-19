// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LOSTMainMenuPlayerController.generated.h"

UCLASS()
class LOST_API ALOSTMainMenuPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	
};
