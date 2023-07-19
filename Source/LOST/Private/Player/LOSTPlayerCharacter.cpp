// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "Player/LOSTPlayerCharacter.h"

#include "Actors/WeaponBaseActor.h"
#include "Camera/CameraComponent.h"
#include "Components/LOSTMovementComponent.h"
#include "Components/LOSTPlayerInteractionComponent.h"
#include "Components/LOSTStaminaComponent.h"
#include "Components/LOSTWeaponComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogLOSTPlayer, All, All);

ALOSTPlayerCharacter::ALOSTPlayerCharacter(const FObjectInitializer& ObjInit) : Super(ObjInit)
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
	SpringArmComponent->SetupAttachment(GetRootComponent());
	SpringArmComponent->bUsePawnControlRotation = false;
	SpringArmComponent->SocketOffset = FVector(0.0f, 40.0f, 60.0f);
	SpringArmComponent->TargetArmLength = 180.0f;

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
	CameraComponent->SetupAttachment(SpringArmComponent);
	
	InteractionComponent = CreateDefaultSubobject<ULOSTPlayerInteractionComponent>("InteractionComponent");
	WeaponComponent = CreateDefaultSubobject<ULOSTWeaponComponent>("WeaponComponent");

	StaminaComponent = CreateDefaultSubobject<ULOSTStaminaComponent>("StaminaComponent");

	/*CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
	CameraCollisionComponent->SetupAttachment(CameraComponent);
	CameraCollisionComponent->SetSphereRadius(10.0f);
	CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);*/
}

void ALOSTPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	check(InteractionComponent);
	check(WeaponComponent);
	check(StaminaComponent);

	SetPlayerCondition(CurrentPlayerCondition); // set default condition for player
}

void ALOSTPlayerCharacter::OnDeath()
{
	UE_LOG(LogLOSTPlayer, Display, TEXT("Player is Dead!"));
	InteractionComponent->StopInteraction();
	Super::OnDeath();
}

void ALOSTPlayerCharacter::Jump()
{
	float JumpStaminaDecrease = 15.0f;
	if(StaminaComponent->GetStamina() < JumpStaminaDecrease || GetMovementComponent()->IsFalling()) return;

	StaminaComponent->StaminaChange(JumpStaminaDecrease);
	
	Super::Jump();
}


void ALOSTPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	SetMovementSpeed();
}

void ALOSTPlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ALOSTPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &ALOSTPlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &ALOSTPlayerCharacter::LookUp);
	PlayerInputComponent->BindAxis("Turn", this, &ALOSTPlayerCharacter::Turn);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ALOSTPlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Run", IE_Pressed, this, &ALOSTPlayerCharacter::OnStartRunning);
	PlayerInputComponent->BindAction("Run", IE_Released, this, &ALOSTPlayerCharacter::OnStopRunning);
	PlayerInputComponent->BindAction("Interact", IE_Pressed, this, &ALOSTPlayerCharacter::Interact);
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this, &ALOSTPlayerCharacter::StartAttack);
}

void ALOSTPlayerCharacter::StartAttack()
{
	if(CurrentPlayerCondition != EPlayerCondition::EPC_InCombat || WeaponComponent->GetInAttack() || InteractionComponent->GetPickupAnimInProgress()) return;

	float AttackStaminaDecrease = 10.0f;

	if(StaminaComponent->GetStamina() < AttackStaminaDecrease) return;
	
	WeaponComponent->StartAttack();
	StaminaComponent->StaminaChange(AttackStaminaDecrease);

}

bool ALOSTPlayerCharacter::IsRunning() const
{
	return WantsToRun && !GetVelocity().IsZero() && !StaminaComponent->IsTired();
}

float ALOSTPlayerCharacter::GetMovementDirection() const
{
	return Super::GetMovementDirection();
}

void ALOSTPlayerCharacter::MoveForward(float AxisAmount)
{
	if(AxisAmount == 0.0f || InteractionComponent->GetPickupAnimInProgress()) return;
	
	AddMovementInput(GetActorForwardVector(), AxisAmount);
}

void ALOSTPlayerCharacter::MoveRight(float AxisAmount)
{
	if(AxisAmount == 0.0f || InteractionComponent->GetPickupAnimInProgress()) return;
	
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

void ALOSTPlayerCharacter::SetMovementSpeed()
{
	const auto MovementComponent = Cast<ULOSTMovementComponent>(GetMovementComponent());
	if (MovementComponent)
	{
		if(CurrentPlayerCondition == EPlayerCondition::EPC_InCombat)
		{
			MovementComponent->MaxWalkSpeed = 150.0f;
			MovementComponent->RunModifier = 3.0f;
		}
		if (CurrentPlayerCondition == EPlayerCondition::EPC_Survive)
		{
			MovementComponent->MaxWalkSpeed = 240.0f;
			MovementComponent->RunModifier = 3.0f;

		}
	}
}

void ALOSTPlayerCharacter::OnStartRunning()
{
	WantsToRun = true;

	if (!GetWorld()) return;
	
	GetWorld()->GetTimerManager().SetTimer(DecreaseStaminaTimerHandle, this, &ALOSTPlayerCharacter::DecreaseStamina, 0.1f,true);
	
	UE_LOG(LogLOSTPlayer, Display, TEXT("Stamina now is: %f"), StaminaComponent->GetStamina());
}

void ALOSTPlayerCharacter::OnStopRunning()
{
	WantsToRun = false;

	if (!GetWorld()) return;

	GetWorld()->GetTimerManager().ClearTimer(DecreaseStaminaTimerHandle);
}

void ALOSTPlayerCharacter::Interact()
{
	InteractionComponent->Interact();

	const auto WeaponActor = Cast<AWeaponBaseActor>(InteractionComponent->GetPickUpActor());
	
	if (InteractionComponent->GetIsInInteracted() && WeaponActor)
	{
		SetPlayerCondition(EPlayerCondition::EPC_InCombat);
	}
}

void ALOSTPlayerCharacter::DecreaseStamina()
{
	StaminaComponent->StaminaChange(DecreaseStaminaValue);
}




