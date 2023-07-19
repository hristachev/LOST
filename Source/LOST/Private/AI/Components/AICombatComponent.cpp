// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "AI/Components/AICombatComponent.h"

#include "GameFramework/Character.h"

UAICombatComponent::UAICombatComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}


void UAICombatComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UAICombatComponent::PlayAnimMontage(UAnimMontage* Animation)
{
	if(!Animation) return;
	
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;
	
	Character->PlayAnimMontage(Animation);

	
}

