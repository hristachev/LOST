// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV

#include "Components/LOSTPlayerInteractionComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/Character.h"
#include "Actors/InteractionActor.h"
#include "Animations/AnimUtils.h"
#include "Animations/PickingUpAnimNotify.h"
#include "Animations/PickupFinishedAnimNotify.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Interfaces/InteractableObjectInterface.h"
#include "UI/InteractWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogLOSTInteractionComponent, All, All);

ULOSTPlayerInteractionComponent::ULOSTPlayerInteractionComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	
	bCanInteract = true;
}

void ULOSTPlayerInteractionComponent::BeginPlay()
{
	Super::BeginPlay();

	InitAnimations();
}

void ULOSTPlayerInteractionComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	OnActorFocus();
}

void ULOSTPlayerInteractionComponent::Interact()
{
	if(!FocusedActor || !Cast<AInteractionActor>(FocusedActor)) return;
	
	bPickupAnimInProgress = true;
	PlayAnimMontage(PickupMontage);
	bIsInteracted = true;
}

AActor* ULOSTPlayerInteractionComponent::GetActorInTraceView()
{
	if(!GetWorld()) return nullptr;

	FVector TraceStart, TraceEnd;
	if(!GetTraceData(TraceStart, TraceEnd)) return nullptr;
	
	const auto Player = Cast<APawn>(GetOwner());
	if(!Player) return nullptr;

	const auto Controller = Player->GetController<APlayerController>();
	if(!Controller) return nullptr;
	
	FHitResult HitResult;
	HitData(HitResult, TraceStart, TraceEnd);

	return HitResult.GetActor();
}

bool ULOSTPlayerInteractionComponent::GetPlayerView(FVector& ViewLocation, FRotator& ViewRotation) const
{
	const auto LOSTCharacter = Cast<ACharacter>(GetOwner());
	if(!LOSTCharacter) return false;

	if (LOSTCharacter->IsPlayerControlled())
	{
		const auto Controller = LOSTCharacter->GetController<APlayerController>();;
		if(!Controller) return false;
	
		Controller->GetPlayerViewPoint(ViewLocation, ViewRotation);
	}

	return true;
}

bool ULOSTPlayerInteractionComponent::GetTraceData(FVector& TraceStart, FVector& TraceEnd) const
{
	if(!bCanInteract) return false;
	
	FVector ViewLocation;
	FRotator ViewRotation;

	if(!GetPlayerView(ViewLocation,ViewRotation)) return false;
	
	TraceStart = ViewLocation;
	const auto Direction = ViewRotation.Vector();
	TraceEnd = TraceStart + Direction * MaxInteractionDistance;
	return true;
}

void ULOSTPlayerInteractionComponent::HitData(FHitResult& HitResult, const FVector& TraceStart, const FVector& TraceEnd)
{
	if(!GetWorld()) return;
	
	FCollisionQueryParams TraceParams;
	TraceParams.AddIgnoredActor(GetOwner());

	GetWorld()->LineTraceSingleByChannel(HitResult, TraceStart, TraceEnd, ECollisionChannel::ECC_Visibility, TraceParams);
}

void ULOSTPlayerInteractionComponent::StopInteraction()
{
	//TODO
	bCanInteract = false;
	if (FocusedActor)
	{
		const auto* Interface = Cast<IInteractableObjectInterface>(FocusedActor);
		if (Interface)
		{
			ShowInteractionMessage(false);
			Interface->Execute_EndFocus(FocusedActor);
			bIsInteracted = false;
		}
	}
	
	UE_LOG(LogLOSTInteractionComponent, Display, TEXT("Stop Interact!!"));
}

void ULOSTPlayerInteractionComponent::InitAnimations()
{
	auto PickupFinishedNotify = AnimUtils::FindNotifyByClass<UPickupFinishedAnimNotify>(PickupMontage);
	auto PickingUpNotify = AnimUtils::FindNotifyByClass<UPickingUpAnimNotify>(PickupMontage);
	if (PickupFinishedNotify)
	{
		PickupFinishedNotify->OnNotified.AddUObject(this, &ULOSTPlayerInteractionComponent::OnPickupFinished);
	}
	else
	{
		UE_LOG(LogLOSTInteractionComponent, Error, TEXT("Equip Anim notify is forgotten to set"));
		checkNoEntry();
	}

	if (PickingUpNotify)
	{
		PickingUpNotify->OnNotified.AddUObject(this, &ULOSTPlayerInteractionComponent::OnPickingUp);
	}
}

void ULOSTPlayerInteractionComponent::ShowInteractionMessage(bool IsShow)
{
	if (!InteractMessageWidgetClass) return;

	if (InteractMessageWidgetClass && InteractMessageWidget == nullptr)
	{
		InteractMessageWidget = CreateWidget<UInteractWidget>(GetWorld(), InteractMessageWidgetClass);
		if (InteractMessageWidget)
		{
			const auto InteractText = FText::Format(FText::FromString(TEXT("{0}	[E]")),
				IInteractableObjectInterface::Execute_GetInteractionText(GetActorInTraceView()));
			InteractMessageWidget->InteractionText->SetText(InteractText);
		}
	}
	
	if (InteractMessageWidget && !InteractMessageWidget->IsInViewport() && IsShow)
	{
		InteractMessageWidget->AddToViewport();
	}

	if (!IsShow)
	{
		InteractMessageWidget->RemoveFromViewport();
	}
	
}

void ULOSTPlayerInteractionComponent::OnActorFocus()
{
	const auto InteractActor = GetActorInTraceView();

	if (InteractActor)
	{
		if (InteractActor != FocusedActor)
		{
			if (FocusedActor)
			{
				const auto* Interface = Cast<IInteractableObjectInterface>(FocusedActor);
				if (Interface)
				{
					ShowInteractionMessage(false);
					Interface->Execute_EndFocus(FocusedActor);
				}
			}
			const auto* Interface = Cast<IInteractableObjectInterface>(InteractActor);
			if (Interface)
			{
				ShowInteractionMessage(true);
				Interface->Execute_StartFocus(InteractActor);
			}
			FocusedActor = InteractActor;
		}
	}
	else
	{
		if (FocusedActor)
		{
			const auto* Interface = Cast<IInteractableObjectInterface>(FocusedActor);
			if (Interface)
			{
				ShowInteractionMessage(false);
				Interface->Execute_EndFocus(FocusedActor);
			}
		}
		FocusedActor = nullptr;
	}
}

void ULOSTPlayerInteractionComponent::OnPickupFinished(USkeletalMeshComponent* SkeletalMeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character || SkeletalMeshComponent != Character->GetMesh()) return;

	bPickupAnimInProgress = false;
}

void ULOSTPlayerInteractionComponent::PlayAnimMontage(UAnimMontage* AnimMontage)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;

	Character->PlayAnimMontage(AnimMontage);
}

void ULOSTPlayerInteractionComponent::OnPickingUp(USkeletalMeshComponent* MeshComponent)
{
	ACharacter* Character = Cast<ACharacter>(GetOwner());
	if(!Character) return;
	
	if (Character->GetMesh() == MeshComponent)
	{
		if (FocusedActor)
		{
			const auto* Interface = Cast<IInteractableObjectInterface>(FocusedActor);
			if (Interface)
			{
				Interface->Execute_OnInteract(FocusedActor, GetOwner());
			}
		}
	}
}

