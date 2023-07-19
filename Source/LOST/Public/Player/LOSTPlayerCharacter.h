// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "BaseClasses/LOSTBaseCharacter.h"
#include "LOST/Public/CoreTypes.h"
#include "LOSTPlayerCharacter.generated.h"

class ULOSTStaminaComponent;
class ULOSTWeaponComponent;
class USpringArmComponent;
class UCameraComponent;
class USphereComponent;

UCLASS()
class LOST_API ALOSTPlayerCharacter : public ALOSTBaseCharacter
{
	GENERATED_BODY()

public:
	ALOSTPlayerCharacter(const FObjectInitializer& ObjInit);

	
protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArmComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	UCameraComponent* CameraComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	ULOSTStaminaComponent* StaminaComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	ULOSTPlayerInteractionComponent* InteractionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	ULOSTWeaponComponent* WeaponComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	FName WeaponEquipSocketName = "RightHandWeaponSocket";
	
	UPROPERTY(EditDefaultsOnly, Category = "Player Condition")
	EPlayerCondition PlayerCondition;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Stamina")
	float DecreaseStaminaValue = 1.0f;

	/*UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	USphereComponent* CameraCollisionComponent;*/

	virtual void OnDeath() override;
	virtual void Jump() override;

	virtual void StartAttack() override;
public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	virtual bool IsRunning() const override;
	virtual float GetMovementDirection() const override;

	void SetPlayerCondition(EPlayerCondition Condition) { CurrentPlayerCondition = Condition; };
	UFUNCTION(BlueprintCallable, Category = "Player Condition")
	EPlayerCondition GetPlayerCondition() const { return CurrentPlayerCondition; }

	ULOSTWeaponComponent* GetWeaponComponent() const { return WeaponComponent; }
	FName GetWeaponEquipSocketName() const { return WeaponEquipSocketName; }
private:
	EPlayerCondition CurrentPlayerCondition;
	bool WantsToRun = false;

	FTimerHandle DecreaseStaminaTimerHandle;

	//Movement
	void MoveForward(float AxisAmount);
	void MoveRight(float AxisAmount);
	void LookUp(float AxisAmount);
	void Turn(float AxisAmount);
	void SetMovementSpeed();

	void OnStartRunning();
	void OnStopRunning();

	void Interact();

	void DecreaseStamina();
};
