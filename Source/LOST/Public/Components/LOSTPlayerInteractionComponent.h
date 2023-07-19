// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Interfaces/InteractableObjectInterface.h"
#include "LOSTPlayerInteractionComponent.generated.h"


class UInteractWidget;
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class LOST_API ULOSTPlayerInteractionComponent : public UActorComponent, public IInteractableObjectInterface
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	ULOSTPlayerInteractionComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
	TSubclassOf<UUserWidget> InteractMessageWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "Animation")
	UAnimMontage* PickupMontage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Interaction")
	float MaxInteractionDistance = 300.0f;

	
public:
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void Interact();
	AActor* GetPickUpActor() { return FocusedActor; }
	bool GetIsInInteracted() { return bIsInteracted; }
	AActor* GetActorInTraceView();
	bool GetPlayerView(FVector& ViewLocation, FRotator& ViewRotation) const;
	bool GetTraceData(FVector& TraceStart, FVector& TraceEnd) const;

	void HitData(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd);

	bool GetPickupAnimInProgress() const { return bPickupAnimInProgress; }
	void StopInteraction();

	void PlayAnimMontage(UAnimMontage* AnimMontage);

private:

	bool bPickupAnimInProgress = false;
	bool bCanInteract = true;
	bool bIsInteracted = false;
	UPROPERTY()
	UInteractWidget* InteractMessageWidget = nullptr;

	UPROPERTY()
	AActor* FocusedActor;
	

	virtual void InitAnimations();
	void ShowInteractionMessage(bool IsShow);
	void OnActorFocus();

	virtual void OnPickupFinished(USkeletalMeshComponent* SkeletalMeshComponent);

	void OnPickingUp(USkeletalMeshComponent* MeshComponent);
};




