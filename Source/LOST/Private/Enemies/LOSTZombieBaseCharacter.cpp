// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "Enemies/LOSTZombieBaseCharacter.h"

#include "LOSTUtils.h"
#include "AI/Components/AICombatComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/LOSTPhysicalAnimationComponent.h"
#include "Player/LOSTPlayerCharacter.h"

ALOSTZombieBaseCharacter::ALOSTZombieBaseCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	
	DamageCollision = CreateDefaultSubobject<UCapsuleComponent>("DamageCollision");
	DamageCollision->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, "RightHandWeaponSocket");
	DamageCollision->SetCollisionObjectType(ECC_GameTraceChannel1);


	DisableDamageCollision();
}

void ALOSTZombieBaseCharacter::EnableDamageCollision()
{
	DamageCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void ALOSTZombieBaseCharacter::DisableDamageCollision()
{
	DamageCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ALOSTZombieBaseCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(DamageCollision);
	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &ALOSTZombieBaseCharacter::OnDamageCollisionBeginOverlap);
}

void ALOSTZombieBaseCharacter::OnDamageCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent,
                                                             AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                                             const FHitResult& SweepResult)
{
	//const auto Player = Cast<ALOSTPlayerCharacter>(OtherActor);
	if (OtherActor == this) return;
	
	if (OtherActor)
	{
		const auto HitReactionComponent = LOSTUtils::GetLOSTPlayerComponent<ULOSTPhysicalAnimationComponent>(OtherActor);
		if(!HitReactionComponent) return;

		HitReactionComponent->HitReaction(SweepResult);
		OtherActor->TakeDamage(CombatComponent->DamageValue, FDamageEvent{}, GetController(), this);
	}
}
