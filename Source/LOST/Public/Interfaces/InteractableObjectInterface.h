// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "InteractableObjectInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UInteractableObjectInterface : public UInterface
{
	GENERATED_BODY()
};

class LOST_API IInteractableObjectInterface
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void OnInteract(AActor* InteractBy);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void StartFocus();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "Interaction")
	void EndFocus();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "UI")
	FText GetInteractionText();

	UFUNCTION()
	virtual FText GetInteractionText_Implementation() { return FText::FromString(TEXT("Interact")); }
};
