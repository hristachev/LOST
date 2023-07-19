// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "AI/Services/SetAISpeedService.h"

#include "AIController.h"
#include "AI/LOSTBaseAICharacter.h"

USetAISpeedService::USetAISpeedService()
{
	NodeName = "SetAISpeed";
}

void USetAISpeedService::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	const auto Controller = OwnerComp.GetAIOwner();
	const auto Pawn = Controller->GetPawn();
	if (!Controller || !Pawn) return;

	SetAISpeed(Pawn);
	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}

void USetAISpeedService::SetAISpeed(APawn* Pawn)
{
	if(!Pawn) return;

	const auto AIPlayer = Cast<ALOSTBaseAICharacter>(Pawn);

	AIPlayer->SetMaxSpeed(SpeedValue);
}

