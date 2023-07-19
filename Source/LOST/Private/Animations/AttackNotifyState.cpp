// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "Animations/AttackNotifyState.h"

#include "Actors/WeaponBaseActor.h"
#include "AI/LOSTBaseAICharacter.h"
#include "Components/LOSTWeaponComponent.h"
#include "Enemies/LOSTZombieBaseCharacter.h"
#include "Player/LOSTPlayerCharacter.h"

void UAttackNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                     float TotalDuration)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration);

	const auto Player = Cast<ALOSTPlayerCharacter>(MeshComp->GetOwner());
	const auto AIPawn = Cast<ALOSTZombieBaseCharacter>(MeshComp->GetOwner());
	if(Player)
	{
		TArray<AActor*> Attached;
		Player->GetAttachedActors(Attached);

		for (auto Actor : Attached)
		{
			const auto Weapon = Cast<AWeaponBaseActor>(Actor);
			if (Weapon)
			{
				Weapon->EnableDamageCollision();
			}
		}
	}

	if (AIPawn)
	{
		AIPawn->EnableDamageCollision();
	}
	
}

void UAttackNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::NotifyEnd(MeshComp, Animation);

	const auto Player = Cast<ALOSTPlayerCharacter>(MeshComp->GetOwner());
	const auto AIPawn = Cast<ALOSTZombieBaseCharacter>(MeshComp->GetOwner());

	if(Player)
	{
		TArray<AActor*> Attached;
		Player->GetAttachedActors(Attached);

		for (auto Actor : Attached)
		{
			const auto Weapon = Cast<AWeaponBaseActor>(Actor);
			if (Weapon)
			{
				Weapon->DisableDamageCollision();
			}
		}
	}

	if (AIPawn)
	{
		AIPawn->DisableDamageCollision();
	}
}
