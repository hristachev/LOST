// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "Components/LOSTMovementComponent.h"

#include "BaseClasses/LOSTBaseCharacter.h"

float ULOSTMovementComponent::GetMaxSpeed() const
{
	const float MaxSpeed = Super::GetMaxSpeed();
	const ALOSTBaseCharacter* Player = Cast<ALOSTBaseCharacter>(GetPawnOwner());
	return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}
