// LOST GAME. ALL RIGHTS RESERVED! MADE BY IAMHRISTACHEV


#include "Actors/InteractionActor.h"

DEFINE_LOG_CATEGORY_STATIC(LogLOSTInteractionActor, All, All);

// Sets default values
AInteractionActor::AInteractionActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>("SceneComponent");
	SetRootComponent(RootComponent);


	InteractionMesh = CreateDefaultSubobject<UStaticMeshComponent>("MeshComponent");
	InteractionMesh->SetCollisionResponseToChannel(ECollisionChannel::ECC_Visibility, ECR_Block);
	InteractionMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AInteractionActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AInteractionActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractionActor::OnInteract_Implementation(AActor* InteractBy)
{
	Destroy();
}

void AInteractionActor::StartFocus_Implementation()
{
	UE_LOG(LogLOSTInteractionActor, Display, TEXT("Start Focus!!"))
	InteractionMesh->SetRenderCustomDepth(true);
	InteractionMesh->SetCustomDepthStencilValue(254);
}

void AInteractionActor::EndFocus_Implementation()
{
	UE_LOG(LogLOSTInteractionActor, Display, TEXT("End Focus!!"))
	InteractionMesh->SetRenderCustomDepth(false);
}

