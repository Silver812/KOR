// Fill out your copyright notice in the Description page of Project Settings.

#include "ADestructibleObjects/ADestructibleObj.h"
#include "Character/IKnockable.h"

// Sets default values
AADestructibleObj::AADestructibleObj()
{
	PrimaryActorTick.bCanEverTick = true;

	//CREATE STATIC MESH
	Object_MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh_Object"));
	Object_MeshComp->SetupAttachment(RootComponent);
	Object_MeshComp->SetSimulatePhysics(true); //Physics
	Object_MeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Block);

	//CREATE SPAWN POINT
	SpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SpawnPoint_SceneComp"));
	SpawnPoint->AttachToComponent(Object_MeshComp, FAttachmentTransformRules::KeepRelativeTransform);

	//CREATE COMPONENT
	DestructibleObjectComp = CreateDefaultSubobject<UACDestructibleObjectComponent>(TEXT("DestructibleObjectComponent"));
	GrabbableHardComponent = CreateDefaultSubobject<UAC_GrabbableHard>(TEXT("GrabbableSoftComponent"));

	//CREATE BOX COLLIDER
	boxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxColliderComponent"));
	boxCollider->AttachToComponent(Object_MeshComp, FAttachmentTransformRules::KeepRelativeTransform);
	boxCollider->OnComponentBeginOverlap.AddDynamic(this,&AADestructibleObj::OnBoxBeginOverlap); //ON OVERLAP

	
	

	
	//REPLICATION BEHAVIOUR
	//this->SetReplicates(true);
	bReplicates = true;
	Object_MeshComp->SetIsReplicated(true);
	DestructibleObjectComp->BeginReplication();
	GrabbableHardComponent->BeginReplication();
	
	
}


void AADestructibleObj::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                          UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                          const FHitResult& SweepResult)
{
	
	FTransform spawmnedTrasnform = SpawnPoint->GetComponentTransform(); //SetTransform
	
	if(!destroyWithOnlyOneTouch)
	{
		//UE_LOG(LogTemp,Warning,TEXT("OnBeginOverlap"¨));
		if (DestructibleObjectComp->hasBeenTrhown)
		{
			if (OtherActor != this)
			{
				if (!bSpawned)
				{
					if (characterRef != nullptr && OtherActor != characterRef)
					{
						if(IKnockable* KnockableInterface = Cast<IKnockable>(OtherActor))
						{
							KnockableInterface->Knockout();
						}
						DestructibleObjectComp->SpawnPieces_Implementation(spawmnedTrasnform);
						bSpawned = true;
					}
				}
			}
		}
		else
		{
			//UE_LOG(LogTemp,Warning,TEXT("Overlapeando"));
			DestructibleObjectComp->MakingNoise_Implementation(spawmnedTrasnform, OtherActor );
		}
	}
	else
	{
		//FTransform spawmnedTrasnform = SpawnPoint->GetComponentTransform();
		DestructibleObjectComp->SpawnPieces_Implementation(spawmnedTrasnform);
		bSpawned = true;
	}
	
}

void AADestructibleObj::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor,
                              UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	
}


void AADestructibleObj::BeginPlay()
{
	Super::BeginPlay();

	PrimaryActorTick.bCanEverTick = true;

	
	//Set Mass
	//Object_MeshComp->SetMassScale("None", DestructibleObjectComp->ObjStruct.objectMass);

	//Set Collision Pressets
	Object_MeshComp->SetCollisionProfileName(TEXT("PhysicsActor"));
	boxCollider->SetCollisionProfileName(TEXT("Destructible"));

	//SET REPLICATION VARIABLES
	//this->SetReplicates(true);
	bReplicates = true;
	this->SetReplicateMovement(true);
	Object_MeshComp->SetIsReplicated(true);
}

// Called every frame
void AADestructibleObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
