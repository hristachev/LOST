// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LOSTBaseCharacter.generated.h"

class ULOSTPhysicalAnimationComponent;
class ULOSTHealthComponent;
class ULOSTPlayerInteractionComponent;
UCLASS()
class LOST_API ALOSTBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALOSTBaseCharacter(const FObjectInitializer& ObjInit);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	ULOSTHealthComponent* HealthComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
	ULOSTPhysicalAnimationComponent* PhysicalAnimationComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	float LifeSpanOnDeath = 5.0f;

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D LandedDamageVelocity = FVector2D(900.0f,1200.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Damage")
	FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

	virtual void OnDeath();

	virtual void StartAttack();
public:
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual bool IsRunning() const;

	UFUNCTION(BlueprintCallable, Category = "Movement")
	virtual float GetMovementDirection() const;

private:
	void OnHealthChanged(float Health, float HealthDelta);

	UFUNCTION()
	void OnGroundLanded(const FHitResult& Hit);
};
