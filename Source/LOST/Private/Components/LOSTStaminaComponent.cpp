// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "Components/LOSTStaminaComponent.h"

ULOSTStaminaComponent::ULOSTStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

bool ULOSTStaminaComponent::IsStaminaFull() const
{
	return FMath::IsNearlyEqual(Stamina, MaxStamina);
}

void ULOSTStaminaComponent::BeginPlay()
{
	Super::BeginPlay();

	check(MaxStamina >= 0);

	SetStamina(MaxStamina);
}

void ULOSTStaminaComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void ULOSTStaminaComponent::StaminaChange(float ChangeValue)
{
	if (ChangeValue <= 0.0f || IsTired() || !GetWorld()) return;
	
	SetStamina(Stamina - ChangeValue);
	GetWorld()->GetTimerManager().ClearTimer(RecoverTimerHandle);

	
	if (AutoRecover && GetWorld())
	{
		GetWorld()->GetTimerManager().SetTimer(RecoverTimerHandle, this, &ULOSTStaminaComponent::RecoverUpdate, RecoverUpdateTime, true);
	}
}

void ULOSTStaminaComponent::RecoverUpdate()
{
	SetStamina(Stamina + RecoverModifier);

	if (IsStaminaFull() && GetWorld())
	{
		GetWorld()->GetTimerManager().ClearTimer(RecoverTimerHandle);
	}
}

void ULOSTStaminaComponent::SetStamina(float NewStamina)
{
	const auto NextStamina = FMath::Clamp(NewStamina, 0.0f, MaxStamina);
	Stamina = NextStamina;
}


