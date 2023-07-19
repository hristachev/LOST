// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "Actors/FireDamagerActor.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraComponent.h"

AFireDamagerActor::AFireDamagerActor()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFireDamagerActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	InitialNiagara();
}

void AFireDamagerActor::InitialNiagara()
{
	if(!GetWorld() || !NiagaraEffect) return;
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), NiagaraEffect, GetActorLocation(), GetActorRotation(), FVector(1.0f), false, true);
}
