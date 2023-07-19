// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "LostGameHUD.generated.h"


class UUserWidget;

UCLASS()
class LOST_API ALostGameHUD : public AHUD
{
	GENERATED_BODY()

public:

	virtual void DrawHUD() override;
protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

	virtual void BeginPlay() override;

private:
	UPROPERTY()
	UUserWidget* CurrentWidget = nullptr;
};
