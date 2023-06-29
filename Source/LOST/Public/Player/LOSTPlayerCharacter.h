// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "BaseClasses/LOSTBaseCharacter.h"
#include "LOSTPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class LOST_API ALOSTPlayerCharacter : public ALOSTBaseCharacter
{
	GENERATED_BODY()

public:
	ALOSTPlayerCharacter();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	//Movement
	void MoveForward(float AxisAmount);
	void MoveRight(float AxisAmount);
	void LookUp(float AxisAmount);
	void Turn(float AxisAmount);

	void Interact();
};
