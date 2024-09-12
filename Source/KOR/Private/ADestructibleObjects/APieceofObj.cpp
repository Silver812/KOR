// Fill out your copyright notice in the Description page of Project Settings.

#include "ADestructibleObjects/APieceofObj.h"

// Sets default values
AAPieceofObj::AAPieceofObj()
{
	PrimaryActorTick.bCanEverTick = true;
	
	//CREATE STATIC MESH
	PieceObj_MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh_PieceObj"));
	PieceObj_MeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Block);
	PieceObj_MeshComp->SetSimulatePhysics(true); //Physics
	SetRootComponent(PieceObj_MeshComp); // SET STATICMESHCOMP as RootComponent
	
	//CREATE COMPONENT
	GrabbableHardComponent = CreateDefaultSubobject<UAC_GrabbableHard>(TEXT("GrabbableHardComponent"));
	
	//REPLICATION BEHAVIOUR
	bReplicates = true;
	
	SetPhysicsReplicationMode(EPhysicsReplicationMode::Default);

	// Disable effect on nav mesh
	PieceObj_MeshComp->SetCanEverAffectNavigation(false);
}

void AAPieceofObj::SetStaticMesh()
{
	if (PieceObj_StaticMesh != nullptr)
	{
		PieceObj_MeshComp->SetStaticMesh(PieceObj_StaticMesh);
		PieceObj_MeshComp->SetCollisionProfileName(TEXT("PhysicsActor")); //Collision Channel!
	}
}

void AAPieceofObj::BeginPlay()
{
	Super::BeginPlay();

	SetStaticMesh(); //SETTING STATIC MESH COMPONENT!

	//REPLICATION BEHAVIOUR
	this->SetReplicateMovement(true);
	PieceObj_MeshComp->SetIsReplicated(true);
	
	//Collision Channel
	PieceObj_MeshComp->SetCollisionResponseToChannel(ECollisionChannel::ECC_PhysicsBody, ECollisionResponse::ECR_Block);
}

void AAPieceofObj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

