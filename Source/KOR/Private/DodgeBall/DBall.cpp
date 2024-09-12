#include "DodgeBall/DBall.h"
#include "Character/AC_GrabbableHard.h"
#include "Character/KorCharacterDodgeBall.h"

ADBall::ADBall()
{
	PrimaryActorTick.bCanEverTick = true;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);
	Mesh->SetSimulatePhysics(true);

	GrabbableHardComponent = CreateDefaultSubobject<UAC_GrabbableHard>(TEXT("GrabbableHardComponent"));

	//this->SetReplicates(true);
	bReplicates = true;
	Mesh->BeginReplication();
	GrabbableHardComponent->BeginReplication();
}

void ADBall::BeginPlay()
{
	Super::BeginPlay();

	Mesh->SetCollisionProfileName(TEXT("PhysicsActor"));
}

void ADBall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADBall::Grabbed()
{
	UE_LOG(LogTemp, Display, TEXT("LLego hasta aqui"));
}

void ADBall::EndGrabbed()
{
	characterRef->OnBallGrabbed.Unbind();
}
