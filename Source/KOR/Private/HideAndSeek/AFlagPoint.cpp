// Fill out your copyright notice in the Description page of Project Settings.

#include "HideAndSeek/AFlagPoint.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/SphereComponent.h" //Collider

// Sets default values
AAFlagPoint::AAFlagPoint()
{
	PrimaryActorTick.bCanEverTick = true;

	//-----------------------------CREATING OBJ COMPONENTS-------------------------------//

	FlagPointMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh_Object"));
	FlagPointMeshComp->SetupAttachment(RootComponent);

	//CREATE Sphere COLLIDER
	sphereColliderComp = CreateDefaultSubobject<USphereComponent>("SphereColliderComponent");
	sphereColliderComp->AttachToComponent(FlagPointMeshComp, FAttachmentTransformRules::KeepRelativeTransform);
	sphereColliderComp->OnComponentBeginOverlap.AddDynamic(this, &AAFlagPoint::OnBoxBeginOverlap); //ON OVERLAP
}

void AAFlagPoint::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                    const FHitResult& SweepResult)
{
	if (OtherActor != this)
	{
		if (activeFlagPoint)
		{
			if (!bSleeping)
			{
				FlagCatched_Implementation();
			}
		}
	}
}

void AAFlagPoint::SetRandomSleepingDelay_Implementation()
{
	delaySleepingTime = rand() % (25 + 1);
	
	if (delaySleepingTime < 10)
	{
		SetRandomSleepingDelay_Implementation();
	}
}

void AAFlagPoint::SetFlagStaticMesh_Implementation(bool active)
{
	FlagPointMeshComp->SetVisibility(active);
}

void AAFlagPoint::FlagCatched_Implementation()
{
	currentSleepingTime = 0.0f;
	FlagPointMeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	bSleeping = true;
	ActiveVFX_Implementation();
	SetFlagStaticMesh_Implementation(false);
	SleepingTime_Implementation();
}


void AAFlagPoint::SleepingTime_Implementation()
{
	GetWorldTimerManager().SetTimer(flagPointTimer, this, &AAFlagPoint::Countdown_Implementation, 1.f, true, 0.0);
}

void AAFlagPoint::Countdown_Implementation()
{
	currentSleepingTime += 1.f;
	if (currentSleepingTime >= delaySleepingTime)
	{
		GetWorldTimerManager().PauseTimer(flagPointTimer);
		ActiveVFX_Implementation();
		SetFlagStaticMesh_Implementation(true);
		FlagPointMeshComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		bSleeping = false;
	}
}

void AAFlagPoint::ActiveFlagPoint_Implementation()
{
	SleepingTime_Implementation();
}

void AAFlagPoint::ActiveVFX_Implementation()
{
	if (appearVFX != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, appearVFX, FlagPointMeshComp->GetComponentLocation(),
		                                               FRotator::ZeroRotator, FlagPointMeshComp->GetComponentScale(),
		                                               true, true, ENCPoolMethod::None, true);
	}
}

// Called when the game starts or when spawned
void AAFlagPoint::BeginPlay()
{
	Super::BeginPlay();

	//REPLICATION
	this->SetReplicates(true);
	FlagPointMeshComp->BeginReplication();

	//SET ACTIVATION
	SetFlagStaticMesh_Implementation(false);
	SleepingTime_Implementation();
}

// Called every frame
void AAFlagPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
