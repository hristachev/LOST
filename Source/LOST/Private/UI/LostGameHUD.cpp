// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "UI/LostGameHUD.h"

#include "Blueprint/UserWidget.h"

void ALostGameHUD::DrawHUD()
{
	Super::DrawHUD();
}

void ALostGameHUD::BeginPlay()
{
	Super::BeginPlay();

	if(CurrentWidget == nullptr && PlayerHUDWidgetClass)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), PlayerHUDWidgetClass);
		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
