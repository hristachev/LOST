// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "LOSTGameModeBase.h"

#include "Player/LOSTPlayerCharacter.h"
#include "Player/LOSTPlayerController.h"

ALOSTGameModeBase::ALOSTGameModeBase()
{
	DefaultPawnClass = ALOSTPlayerCharacter::StaticClass();
	PlayerControllerClass = ALOSTPlayerController::StaticClass();
}
