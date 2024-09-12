// Fill out your copyright notice in the Description page of Project Settings.

#include "Character/AC_GrabbableChild.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UAC_GrabbableChild::UAC_GrabbableChild()
{
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}

void UAC_GrabbableChild::Grab_Server_Implementation(UStaticMeshComponent* Hand)
//Actually this must be multicasted (it is so error is fixed)
{
	Super::Grab_Server(Hand);
	GetOwner()->FindComponentByClass<UCharacterMovementComponent>()->Deactivate();

	static const FAttachmentTransformRules AttachmentRules(
		EAttachmentRule::SnapToTarget, // Location
		EAttachmentRule::SnapToTarget, // Rotation
		EAttachmentRule::KeepWorld, // Scale
		true // Weld simulated bodies
	);

	CapsuleComponent = GetOwner()->FindComponentByClass<UCapsuleComponent>();
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	USkeletalMeshComponent* SkeletalMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	SkeletalMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	CapsuleComponent->AttachToComponent(Hand, AttachmentRules);
}

void UAC_GrabbableChild::EndGrab_Server_Implementation(UStaticMeshComponent* Hand)
{
	Super::EndGrab_Server(Hand);

	static const FDetachmentTransformRules DetachmentRules(
		EDetachmentRule::KeepWorld, // Location
		EDetachmentRule::KeepWorld, // Rotation
		EDetachmentRule::KeepWorld, // Scale
		true // Weld simulated bodies
	);

	GetOwner()->DetachFromActor(DetachmentRules);
	CapsuleComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	USkeletalMeshComponent* SkeletalMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	SkeletalMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	SkeletalMesh->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Block);
	SkeletalMesh->SetWorldScale3D(FVector::One());
	GetOwner()->FindComponentByClass<UCharacterMovementComponent>()->Activate();
	bGrabChild = false;
}

void UAC_GrabbableChild::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAC_GrabbableChild::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(UAC_GrabbableChild, CapsuleComponent)
}

void UAC_GrabbableChild::OnRep_Capsule_Updated()
{
	CapsuleComponent = GetOwner()->FindComponentByClass<UCapsuleComponent>();
	CapsuleComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	USkeletalMeshComponent* SkeletalMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	SkeletalMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	SkeletalMesh->SetWorldScale3D(FVector::One());
}

void UAC_GrabbableChild::Grab_Multicast_Implementation(UStaticMeshComponent* Hand)
{
	//UE_LOG(LogTemp, Warning, TEXT("Object GRABBED -> %s"), *GetOwner()->GetName())
	CapsuleComponent = GetOwner()->FindComponentByClass<UCapsuleComponent>();
	CapsuleComponent->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	CapsuleComponent->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Block);
	CapsuleComponent->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);

	USkeletalMeshComponent* SkeletalMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	SkeletalMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	SkeletalMesh->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Ignore);
}

void UAC_GrabbableChild::EndGrab_Multicast_Implementation(UStaticMeshComponent* Hand)
{
	USkeletalMeshComponent* SkeletalMesh = GetOwner()->FindComponentByClass<USkeletalMeshComponent>();
	SkeletalMesh->SetCollisionResponseToChannel(ECC_Pawn, ECR_Block);
	SkeletalMesh->SetCollisionResponseToChannel(ECC_PhysicsBody, ECR_Block);
}
