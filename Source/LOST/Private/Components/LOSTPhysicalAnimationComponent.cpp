// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "Components/LOSTPhysicalAnimationComponent.h"

#include "BaseClasses/LOSTBaseCharacter.h"
#include "Enemies/LOSTZombieBaseCharacter.h"

ULOSTPhysicalAnimationComponent::ULOSTPhysicalAnimationComponent()
{
	PrimaryComponentTick.bStartWithTickEnabled = false;

}

void ULOSTPhysicalAnimationComponent::TickComponent(float DeltaTime, ELevelTick TickType,
	FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	

	const auto InterpHitTime= FMath::FInterpTo(HitReactionTimeRemaining, 0.0f, 0.0f, 10.0f);

	HitReactionTimeRemaining = InterpHitTime - DeltaTime;


	if (HitReactionTimeRemaining <= 0.0f)
	{
		HitReactionTimeRemaining = 0.0f;
		GetOwnerMesh(GetOwner())->SetAllBodiesBelowSimulatePhysics(HipsName, false, true);
		
		SetComponentTickEnabled(false);	
	}
	else
	{
		const auto BlendWeight = FMath::Min(HitReactionTimeRemaining, 1.0f);
		GetOwnerMesh(GetOwner())->SetAllBodiesBelowPhysicsBlendWeight(HipsName, BlendWeight, false, true);
	}
	UE_LOG(LogTemp, Display, TEXT("HitTimeRem: %f"),HitReactionTimeRemaining);
}

void ULOSTPhysicalAnimationComponent::HitReaction(FHitResult HitResult)
{
	SetComponentTickEnabled(true);
	
	const auto Mesh = GetOwnerMesh(HitResult.GetActor());
	if(!Mesh) return;

	SetSkeletalMeshComponent(Mesh);
	ApplyPhysicalAnimationProfileBelow(HipsName, ProfileName, false, false);
	Mesh->SetAllBodiesBelowSimulatePhysics(HipsName, true, false);

	const auto HitIncrease = 1.0f;
	HitReactionTimeRemaining += HitIncrease;
	
	const auto TraceStart = HitResult.TraceStart;
	const auto TraceEnd = HitResult.TraceEnd;
	auto Impulse = TraceEnd - TraceStart;
	Impulse.Normalize(0.01f);
	const auto ImpulseVector = Impulse * ImpulseStrength;
	auto HitBone = HitResult.BoneName;
	
	HitBone == "Hips" ? HitBone = HipsName : HitBone = HitResult.BoneName;
	
	//Mesh->AddImpulse(ImpulseVector, HitBone, true);
	Mesh->AddImpulseToAllBodiesBelow(ImpulseVector, HitBone, true, false);
}

USkeletalMeshComponent* ULOSTPhysicalAnimationComponent::GetOwnerMesh(AActor* Actor)
{
	const auto ComponentOwner = Cast<ALOSTZombieBaseCharacter>(Actor);
	if(!ComponentOwner) return nullptr;
	
	return ComponentOwner->GetMesh();
}