// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "AI/Components/LOSTAIPerceptionComponent.h"

#include "LOSTUtils.h"
#include "AI/LOSTBaseAIController.h"
#include "Components/LOSTHealthComponent.h"
#include "Perception/AISense_Sight.h"

AActor* ULOSTAIPerceptionComponent::GetClosestEnemy() const
{
	TArray<AActor*> PercieveActors;
	GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
	if(PercieveActors.Num() == 0) return nullptr;

	const auto Controller = Cast<ALOSTBaseAIController>(GetOwner());
	if(!Controller) return nullptr;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return nullptr;

	float BestDistance = MAX_FLT;
	AActor* BestPawn = nullptr;

	for (const auto PercieveActor : PercieveActors)
	{
		const auto HealthComponent = LOSTUtils::GetLOSTPlayerComponent<ULOSTHealthComponent>(PercieveActor);
		if (HealthComponent && !HealthComponent->IsDead())
		{
			const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
			if (CurrentDistance < BestDistance)
			{
				BestDistance = CurrentDistance;
				BestPawn = PercieveActor;
			}
		}
	}

	return BestPawn;
}
