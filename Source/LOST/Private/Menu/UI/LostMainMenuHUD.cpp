// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "Menu/UI/LostMainMenuHUD.h"
#include "Blueprint/UserWidget.h"

void ALostMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	if (MenuWidgetClass)
	{
		const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
		if (MenuWidget)
		{
			MenuWidget->AddToViewport();
		}
	}}
