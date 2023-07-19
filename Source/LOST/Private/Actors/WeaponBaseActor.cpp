// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "Actors/WeaponBaseActor.h"
#include "LOSTUtils.h"
#include "Components/CapsuleComponent.h"
#include "Components/LOSTPhysicalAnimationComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Player/LOSTPlayerCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponBaseActor, All, All)

AWeaponBaseActor::AWeaponBaseActor()
{
	PrimaryActorTick.bCanEverTick = false;

	DamageCollision = CreateDefaultSubobject<UCapsuleComponent>("DamageCollision");
	DamageCollision->SetupAttachment(InteractionMesh);
	DamageCollision->SetCollisionObjectType(ECC_GameTraceChannel1);

	DisableDamageCollision();
}

void AWeaponBaseActor::BeginPlay()
{
	Super::BeginPlay();

	check(DamageCollision);
	DamageCollision->OnComponentBeginOverlap.AddDynamic(this, &AWeaponBaseActor::OnDamageCollisionBeginOverlap);
}

void AWeaponBaseActor::OnDamageCollisionBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	const auto Player = Cast<ALOSTPlayerCharacter>(OtherActor);
	if (OtherActor == Player) return;
	
	if (OtherActor)
	{
		const auto HitReactionComponent = LOSTUtils::GetLOSTPlayerComponent<ULOSTPhysicalAnimationComponent>(OtherActor);
		if(!HitReactionComponent) return;

		HitReactionComponent->HitReaction(SweepResult);
		
		OtherActor->TakeDamage(DamageAmount, FDamageEvent{}, GetController(), this);
	}
}

void AWeaponBaseActor::EnableDamageCollision()
{
	DamageCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
}

void AWeaponBaseActor::DisableDamageCollision()
{
	DamageCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void AWeaponBaseActor::OnInteract_Implementation(AActor* InteractBy)
{
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	const auto PlayerPawn = Cast<ALOSTPlayerCharacter>(InteractBy);
	if (!PlayerPawn) return;
	
	const auto WeaponEquipSocketName = PlayerPawn->GetWeaponEquipSocketName();
	
	AttachWeaponToSocket(this, PlayerPawn->GetMesh(), WeaponEquipSocketName);
}

AController* AWeaponBaseActor::GetController() const
{
	const auto Pawn = Cast<APawn>(GetOwner());
	return Pawn ? Pawn->GetController() : nullptr;
}

void AWeaponBaseActor::AttachWeaponToSocket(AWeaponBaseActor* Weapon, USceneComponent* SceneComponent,
	const FName& SocketName)
{
	if(!Weapon || !SceneComponent) return;
	
	FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
	Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}
