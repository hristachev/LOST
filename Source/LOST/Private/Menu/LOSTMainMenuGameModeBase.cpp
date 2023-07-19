// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "Menu/LOSTMainMenuGameModeBase.h"
#include "Menu/LOSTMainMenuPlayerController.h"
#include "Menu/UI/LostMainMenuHUD.h"

ALOSTMainMenuGameModeBase::ALOSTMainMenuGameModeBase()
{
	PlayerControllerClass = ALOSTMainMenuPlayerController::StaticClass();
	HUDClass = ALostMainMenuHUD::StaticClass();
}
