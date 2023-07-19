// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "UI/PlayerHUDWidget.h"

#include "Components/LOSTHealthComponent.h"
#include "Components/LOSTStaminaComponent.h"

float UPlayerHUDWidget::GetHealthPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if(!Player) return 0.0f;
	
	const auto Component = Player->GetComponentByClass(ULOSTHealthComponent::StaticClass());
	const auto HealthComponent = Cast<ULOSTHealthComponent>(Component);
	if(!HealthComponent) return 0.0f;

	return HealthComponent->GetHealthPercent();
}

float UPlayerHUDWidget::GetStaminaPercent() const
{
	const auto Player = GetOwningPlayerPawn();
	if(!Player) return 0.0f;
	
	const auto Component = Player->GetComponentByClass(ULOSTStaminaComponent::StaticClass());
	const auto StaminaComponent = Cast<ULOSTStaminaComponent>(Component);
	if(!StaminaComponent) return 0.0f;

	return StaminaComponent->GetStaminaPercent();
}

void UPlayerHUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if(GetOwningPlayer())
	{
		GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UPlayerHUDWidget::OnNewPawn);
		OnNewPawn(GetOwningPlayerPawn());
	}
}

void UPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
	if(HealthDelta < 0)
	{
		OnTakeDamage();
	}
}

void UPlayerHUDWidget::OnNewPawn(APawn* NewPawn)
{
	if(!NewPawn) return;
	
	const auto Component = NewPawn->GetComponentByClass(ULOSTHealthComponent::StaticClass());
	const auto HealthComponent = Cast<ULOSTHealthComponent>(Component);
	if (HealthComponent && !HealthComponent->OnHealthChanged.IsBoundToObject(this))
	{
		HealthComponent->OnHealthChanged.AddUObject(this, &UPlayerHUDWidget::OnHealthChanged);
	}
}
