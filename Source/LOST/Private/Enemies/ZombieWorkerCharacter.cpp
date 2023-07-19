// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "Enemies/ZombieWorkerCharacter.h"
#include "Components/LOSTHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AZombieWorkerCharacter::AZombieWorkerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	HealthTextComponent = CreateDefaultSubobject<UTextRenderComponent>("HealthText");
	HealthTextComponent->SetupAttachment(GetRootComponent());
}

void AZombieWorkerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//Best speed:
	//Walk - 35
	//Run 150

	//SetMaxSpeed(150.0f);

}

void AZombieWorkerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const auto Health = HealthComponent->GetHealth();
	HealthTextComponent->SetText(FText::FromString(FString::Printf(TEXT("%.0f"), Health)));
}

bool AZombieWorkerCharacter::IsRunning() const
{
	return GetCharacterMovement()->MaxWalkSpeed > 145.0f;
}

