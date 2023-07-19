// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "Actors/DamagerActor.h"
#include "FireDamagerActor.generated.h"

class UNiagaraSystem;

UCLASS()
class LOST_API AFireDamagerActor : public ADamagerActor
{
	GENERATED_BODY()

public:
	AFireDamagerActor();

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
	UNiagaraSystem* NiagaraEffect;

public:	
	virtual void Tick(float DeltaTime) override;

private:
	void InitialNiagara();
};
