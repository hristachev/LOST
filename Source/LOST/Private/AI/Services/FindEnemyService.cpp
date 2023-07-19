// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "AI/Services/FindEnemyService.h"

#include "AIController.h"
#include "LOSTUtils.h"
#include "AI/LOSTBaseAICharacter.h"
#include "AI/Components/LOSTAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

UFindEnemyService::UFindEnemyService()
{
	NodeName = "Find Enemy";
}

void UFindEnemyService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	if (Blackboard)
	{
		const auto Controller = OwnerComp.GetAIOwner();
		
		const auto PerceptionComponent = LOSTUtils::GetLOSTPlayerComponent<ULOSTAIPerceptionComponent>(Controller);
		if (PerceptionComponent)
		{
			Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosestEnemy());
		}
	}
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
