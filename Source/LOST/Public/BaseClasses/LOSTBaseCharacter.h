// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "LOSTBaseCharacter.generated.h"

UCLASS()
class LOST_API ALOSTBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ALOSTBaseCharacter();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

};
