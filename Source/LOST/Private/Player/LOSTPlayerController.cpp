// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "Player/LOSTPlayerController.h"

void ALOSTPlayerController::BeginPlay()
{
	Super::BeginPlay();

	SetInputMode(FInputModeGameOnly());
	bShowMouseCursor = false;
}
