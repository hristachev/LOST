// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "AI/Tasks/NextLocationTask.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "AI/LOSTBaseAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"

UNextLocationTask::UNextLocationTask()
{
	NodeName = "Next Location";
}

EBTNodeResult::Type UNextLocationTask::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Blackboard = OwnerComp.GetBlackboardComponent();

	if(!Controller || !Blackboard) return EBTNodeResult::Failed;

	const auto Pawn = Controller->GetPawn();
	if(!Pawn) return EBTNodeResult::Failed;
	
	const auto NavSystem = UNavigationSystemV1::GetCurrent(Pawn);
	if(!NavSystem) return EBTNodeResult::Failed;

	FNavLocation NavLocation;
	auto Location = Pawn->GetActorLocation();
	
	const auto Found = NavSystem->GetRandomReachablePointInRadius(Location, Radius, NavLocation);
	if(!Found) return EBTNodeResult::Failed;

	Blackboard->SetValueAsVector(AimLocationKey.SelectedKeyName, NavLocation.Location);
	return EBTNodeResult::Succeeded;
}

