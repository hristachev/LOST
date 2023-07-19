// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "AI/Services/CheckPlayerRangeService.h"
#include "AIController.h"
#include "LOSTUtils.h"
#include "AI/Components/LOSTAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

class ULOSTAIPerceptionComponent;

UCheckPlayerRangeService::UCheckPlayerRangeService()
{
	NodeName = "CheckPlayerInRange";
}

void UCheckPlayerRangeService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Blackboard = OwnerComp.GetBlackboardComponent();
	const auto Controller = OwnerComp.GetAIOwner();
	if(!Blackboard || !Controller) return;
	
	const auto PerceptionComponent = LOSTUtils::GetLOSTPlayerComponent<ULOSTAIPerceptionComponent>(Controller);
	if (PerceptionComponent)
	{
		const auto Enemy = PerceptionComponent->GetClosestEnemy();
		if(!Enemy) return;
		
		float EnemyRangeValue = Controller->GetPawn()->GetDistanceTo(Enemy);
		
		if (EnemyRangeValue > AttackRange)
		{
			IsEnemyInRange = false;
			Blackboard->SetValueAsBool(IsPlayerInRangeKeySelector.SelectedKeyName, IsEnemyInRange);
		}
		else
		{
			IsEnemyInRange = true;
			Blackboard->SetValueAsBool(IsPlayerInRangeKeySelector.SelectedKeyName, IsEnemyInRange);

		}
	}
	

	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
