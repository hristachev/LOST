// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseClasses/LOSTBaseCharacter.h"

#include "Components/CapsuleComponent.h"
#include "Components/LOSTHealthComponent.h"
#include "Components/LOSTMovementComponent.h"
#include "Components/LOSTPhysicalAnimationComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogLOSTBaseCharacter, All, All);

ALOSTBaseCharacter::ALOSTBaseCharacter(const FObjectInitializer& ObjInit)
	: Super(ObjInit.SetDefaultSubobjectClass<ULOSTMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = true;

	HealthComponent = CreateDefaultSubobject<ULOSTHealthComponent>("HealthComponent");
	PhysicalAnimationComponent = CreateDefaultSubobject<ULOSTPhysicalAnimationComponent>("PhysicalAnimationComponent");
}

void ALOSTBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(HealthComponent);
	check(GetCharacterMovement());
	check(GetMesh());

	OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
	HealthComponent->OnDeath.AddUObject(this, &ALOSTBaseCharacter::OnDeath);
	HealthComponent->OnHealthChanged.AddUObject(this, &ALOSTBaseCharacter::OnHealthChanged);

	LandedDelegate.AddDynamic(this, &ALOSTBaseCharacter::OnGroundLanded);
}

bool ALOSTBaseCharacter::IsRunning() const
{
	return false;
}

float ALOSTBaseCharacter::GetMovementDirection() const
{
	if (GetVelocity().IsZero()) return 0.0f;
	
	const auto VelocityNormal = GetVelocity().GetSafeNormal();
	const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
	const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
	const auto Degrees = FMath::RadiansToDegrees(AngleBetween);
	return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void ALOSTBaseCharacter::OnHealthChanged(float Health, float HealthDelta)
{
}

void ALOSTBaseCharacter::OnGroundLanded(const FHitResult& Hit)
{
	const auto FallVelocityZ = -GetVelocity().Z;

	if (FallVelocityZ < LandedDamageVelocity.X) return;

	const auto FinalDamage = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
	TakeDamage(FinalDamage, FDamageEvent{}, nullptr, nullptr);
}

void ALOSTBaseCharacter::OnDeath()
{
	PhysicalAnimationComponent->ApplyPhysicalAnimationProfileBelow("Hips", "DeadBody", false, false);
	PhysicalAnimationComponent->DestroyComponent();
	UE_LOG(LogLOSTBaseCharacter, Display, TEXT("Player %s is dead"), *GetName());
	//PlayAnimMontage(DeathAnimMontage);
	GetCharacterMovement()->DisableMovement();
	SetLifeSpan(LifeSpanOnDeath);
	
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
	
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);

	GetMesh()->SetSimulatePhysics(true);

}

void ALOSTBaseCharacter::StartAttack()
{
}

void ALOSTBaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}


