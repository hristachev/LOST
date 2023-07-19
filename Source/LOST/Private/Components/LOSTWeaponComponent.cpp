// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "Components/LOSTWeaponComponent.h"
#include "Actors/WeaponBaseActor.h"
#include "Animations/EndAttackAnimNotify.h"
#include "GameFramework/Character.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All)

ULOSTWeaponComponent::ULOSTWeaponComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void ULOSTWeaponComponent::BeginPlay()
{
	Super::BeginPlay();

	InitAnimations();
	
}

void ULOSTWeaponComponent::StartAttack()
{
	UE_LOG(LogWeaponComponent, Display, TEXT("Attack!"));
	PlayAnimMontage(AttackMontage);
	bInAttack = true;
}


void ULOSTWeaponComponent::InitAnimations()
{
	if(!AttackMontage) return;
	
	const auto NotifyEvents = AttackMontage->Notifies;
	for (auto NotifyEvent : NotifyEvents)
	{
		auto AttackFinishedNotify = Cast<UEndAttackAnimNotify>(NotifyEvent.Notify);
		if (AttackFinishedNotify)
		{
			AttackFinishedNotify->OnNotified.AddUObject(this, &ULOSTWeaponComponent::EndAttack);
			break;
		}
	}
}

void ULOSTWeaponComponent::EndAttack(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;

	if (Character->GetMesh() == MeshComponent)
	{
		bInAttack = false;
	}
}

