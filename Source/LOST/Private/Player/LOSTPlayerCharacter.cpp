// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "Player/LOSTPlayerCharacter.h"

ALOSTPlayerCharacter::ALOSTPlayerCharacter()
{
}

void ALOSTPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(GetCharacterMovement());
}

void ALOSTPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void ALOSTPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALOSTPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALOSTPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ALOSTPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ALOSTPlayerCharacter::Turn);

	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ALOSTPlayerCharacter::Interact);

	
}

void ALOSTPlayerCharacter::MoveForward(float AxisAmount)
{
	if(AxisAmount == 0.0f) return;

	AddMovementInput(GetActorForwardVector(), AxisAmount);
}

void ALOSTPlayerCharacter::MoveRight(float AxisAmount)
{
	if(AxisAmount == 0.0f) return;

	AddMovementInput(GetActorRightVector(), AxisAmount);
}

void ALOSTPlayerCharacter::LookUp(float AxisAmount)
{
	AddControllerPitchInput(AxisAmount);
}

void ALOSTPlayerCharacter::Turn(float AxisAmount)
{
	AddControllerYawInput(AxisAmount);
}

void ALOSTPlayerCharacter::Interact()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, TEXT("INTERACTION!"));
}
