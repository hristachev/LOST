// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "AI/LOSTBaseAICharacter.h"
#include "BrainComponent.h"
#include "NavigationSystem.h"
#include "AI/LOSTBaseAIController.h"
#include "AI/Components/AICombatComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

ALOSTBaseAICharacter::ALOSTBaseAICharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ALOSTBaseAIController::StaticClass();

	CombatComponent = CreateDefaultSubobject<UAICombatComponent>("CombatComponent");

	bUseControllerRotationYaw = false;
	if (GetCharacterMovement())
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
	}
}

void ALOSTBaseAICharacter::SetMaxSpeed(float SpeedValue)
{
	GetCharacterMovement()->MaxWalkSpeed = SpeedValue;
}

void ALOSTBaseAICharacter::BeginPlay()
{
	Super::BeginPlay();

	check(CombatComponent);
}

void ALOSTBaseAICharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	DropItem();
}

void ALOSTBaseAICharacter::OnDeath()
{
	Super::OnDeath();
	
	const auto LOSTController = Cast<ALOSTBaseAIController>(Controller);
	if (LOSTController && LOSTController->BrainComponent)
	{
		LOSTController->BrainComponent->Cleanup();
	}
}

void ALOSTBaseAICharacter::DropItem()
{
	if(!GetWorld()) return;

	FActorSpawnParameters SpawnParameters;
	
	FVector SpawnLocation;
	FRotator SpawnRotation;

	SpawnActorTrace(SpawnLocation, SpawnRotation);
	
	GetWorld()->SpawnActor<AActor>(DropItemActor, SpawnLocation, SpawnRotation, SpawnParameters);
}

void ALOSTBaseAICharacter::SpawnActorTrace(FVector& Location, FRotator& Rotation)
{
	FVector ActorLoc = GetActorLocation();
	const auto TraceEnd = ActorLoc - FVector(0.0f, 0.0f, 200.0f);

	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(GetOwner());
	
	FHitResult HitResult;
	GetWorld()->LineTraceSingleByChannel(HitResult, ActorLoc, TraceEnd, ECollisionChannel::ECC_Visibility, TraceParams);

	FNavLocation NavLocation;
	
	const auto SpawnRadius = 50.0f;

	const auto NavSystem = UNavigationSystemV1::GetCurrent(this);
	NavSystem->GetRandomReachablePointInRadius(HitResult.Location, SpawnRadius, NavLocation);

	
	const auto Rotator = HitResult.ImpactNormal;

	Location = NavLocation.Location;
	Rotation = FRotator(Rotator.X, Rotator.Y, Rotator.Z);
	
}
