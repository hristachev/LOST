// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "AI/LOSTBaseAIController.h"
#include "AI/LOSTBaseAICharacter.h"
#include "AI/Components/LOSTAIPerceptionComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemies/ZombieWorkerCharacter.h"

ALOSTBaseAIController::ALOSTBaseAIController()
{
	 LOSTAIPerceptionComponent = CreateDefaultSubobject<ULOSTAIPerceptionComponent>("LOSTPerceptionComponent");
	 SetPerceptionComponent(*LOSTAIPerceptionComponent);
}

void ALOSTBaseAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	const auto LOSTCharacter = Cast<AZombieWorkerCharacter>(InPawn);
	if (LOSTCharacter)
	{
		RunBehaviorTree(LOSTCharacter->BehaviorTreeAsset);
		UE_LOG(LogTemp, Display, TEXT("RUN TREE"));
	}
}

void ALOSTBaseAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	const auto AimActor = GetFocusOnActor();
	SetFocus(AimActor);
}

AActor* ALOSTBaseAIController::GetFocusOnActor() const
{
	if (!GetBlackboardComponent()) return nullptr;
	return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
