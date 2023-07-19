// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LostMainMenuHUD.generated.h"

/**
 * 
 */
UCLASS()
class LOST_API ALostMainMenuHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> MenuWidgetClass;
	
	virtual void BeginPlay() override;
};
