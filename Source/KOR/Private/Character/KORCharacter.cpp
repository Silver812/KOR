// Copyright Epic Games, Inc. All Rights Reserved.

#include "Character/KORCharacter.h"
#include "Character/AC_DrunkPhysics.h" //drunk component
#include "Engine/LocalPlayer.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputActionValue.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "Character/AC_Grabbing.h" //GRABBING COMP INCLUDE
#include "PhysicsEngine/PhysicalAnimationComponent.h"
#include "TimerManager.h"
#include "VectorTypes.h"
#include "Character/AC_GrabbableBase.h"
#include "Character/AC_GrabbableChild.h"
#include "Core/KORBaseHUD.h"
#include "Core/KorBasePC.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

DEFINE_LOG_CATEGORY(LogTemplateCharacter);

AKORCharacter::AKORCharacter()
{
	// Set size for collision capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate when the controller rotates. Let that just affect the camera.
	bUseControllerRotationPitch = true;
	bUseControllerRotationYaw = true;
	bUseControllerRotationRoll = true;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Character moves in the direction of input... 
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.0f, 0.0f); // ...at this rotation rate

	// Create a camera boom (pulls in towards the player if there is a collision)
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetMesh());
	CameraBoom->TargetArmLength = 400.0f; // The camera follows at this distance behind the character 
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	// Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm

	// Create components
	PhysicalAnimationComponent = CreateDefaultSubobject<UPhysicalAnimationComponent>(TEXT("PhysicalAnimation"));
	DrunkPhysicsComponent = CreateDefaultSubobject<UAC_DrunkPhysics>(TEXT("AC_DrunkPhysics"));
	PhysicalConstraintSoft = CreateDefaultSubobject<UPhysicsConstraintComponent>(TEXT("PhysicsConstraint1"));
	GrabbingComponent = CreateDefaultSubobject<UAC_Grabbing>(TEXT("AC_Grabbing"));
	GrabbableChildComponent = CreateDefaultSubobject<UAC_GrabbableChild>(TEXT("AC_GrabbableChild"));

	Hand_l = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hand_l"));
	Hand_r = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Hand_r"));

	// Scale mesh of hands if necessary ( should NOT be necesary if hands come in good scale
	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("/Engine/BasicShapes/Sphere.Sphere"));
	//Sphere route in explorer //Change route when hand mesh implemented

	if (SphereMesh.Succeeded())
	{
		Hand_l->SetStaticMesh(SphereMesh.Object);
		Hand_r->SetStaticMesh(SphereMesh.Object);
	}

	// Assume getMesh is an SkeletalComponent and snap to sockets in skeletal mesh
	// Call SetupAttachment (not AttachToComponent)
	Hand_l->SetupAttachment(GetMesh(), "Hand_l_Socket");
	Hand_r->SetupAttachment(GetMesh(), "Hand_r_Socket");

}
void AKORCharacter::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AKORCharacter, PlayerNameCustom);
}

void AKORCharacter::BeginPlay()
{
	// Call the base class 
	Super::BeginPlay();
	
	DrunkPhysicsComponent->DrunkMesh(GetMesh(), PhysicalAnimationComponent, "spine_01");

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<
			UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(KOR_InputMappingContext, 0);
		}
	}

	GrabbingComponent->SetHands(Hand_l, Hand_r);
}

AKorBasePC* AKORCharacter::GetKorPCRef()
{
	if (!KorPCRef)
	{
		KorPCRef = Cast<AKorBasePC>(Controller);

		if (!KorPCRef)
		{
			KorPCRef = nullptr;
			UE_LOG(LogTemp, Error, TEXT("Can't get KorPCRef if Controller is not KorBasePC"));
		}
	}

	return KorPCRef;
}
AKORBaseHUD* AKORCharacter::GetKorHUD()
{
	if (!KorHUDRef)
	{
		KorHUDRef = Cast<AKORBaseHUD>(GetKorPCRef()->GetHUD());

		if (!KorHUDRef)
		{
			KorHUDRef = nullptr;
			UE_LOG(LogTemp, Error, TEXT("Can't get KorHUDRef if HUD is not KorBaseHUD"));
		}
	}

	return KorHUDRef;
}

// Input
void AKORCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		// Jumping
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ACharacter::Jump);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ACharacter::StopJumping);

		// Moving
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AKORCharacter::Move);

		// Looking
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &AKORCharacter::Look);

		// Grab -> NORMAL
		EnhancedInputComponent->BindAction(GrabAction, ETriggerEvent::Triggered, this, &AKORCharacter::Grab);

		// EndGrab - NORMAL
		EnhancedInputComponent->BindAction(EndGrabAction, ETriggerEvent::Triggered, this, &AKORCharacter::EndGrab);

		// Fart
		EnhancedInputComponent->BindAction(FartAction, ETriggerEvent::Started, this, &AKORCharacter::Fart);

		// Pause
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &AKORCharacter::ShowPauseMenu);
	}
	else
	{
		UE_LOG(LogTemplateCharacter, Error,
		       TEXT(
			       "'%s' Failed to find an Enhanced Input component! This template is built to use the Enhanced Input system. If you intend to use the legacy system, then you will need to update this C++ file."
		       ), *GetNameSafe(this));
	}
}

void AKORCharacter::GetUp_Implementation()
{
	AActor* ParentActor = GetAttachParentActor();
	AKORCharacter* ParentCharacter = Cast<AKORCharacter>(ParentActor);
	if (ParentCharacter != nullptr)
	{
		ParentCharacter->EndGrab_Replicated_Implementation(FInputActionValue{});
	}

	GrabbableChildComponent->bCanBeGrabbed = false;
	EnableInput(Cast<APlayerController>(GetController()));
}

void AKORCharacter::Knockout()
{
	DisableInputs(FInputActionValue{});
	GetWorld()->GetTimerManager().SetTimer(CooldownTimerHandle, this, &AKORCharacter::GetUp, 1.0f, false, 6.0f);
}

void AKORCharacter::Move(const FInputActionValue& Value)
{
	// input is a Vector2D
	const FVector2D MovementVector = Value.Get<FVector2D>().GetSafeNormal();

	if (Controller != nullptr)
	{
		// Find Movement Axis by using 2 cross products from the camera forward 
		const FVector RightDirection = UE::Geometry::Cross(FollowCamera->GetForwardVector(), FVector::UpVector);
		const FVector ForwardDirection = UE::Geometry::Cross(RightDirection, FVector::UpVector);

		// add movement
		AddMovementInput(ForwardDirection, MovementVector.Y);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AKORCharacter::Look(const FInputActionValue& Value)
{
	// input is a Vector2D
	FVector2D LookAxisVector = Value.Get<FVector2D>();

	if (Controller != nullptr)
	{
		// add yaw and pitch input to controller
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AKORCharacter::ShowPauseMenu(const FInputActionValue& Value)
{
	// Get HUD
	GetKorHUD()->ShowPauseMenu();
}

void AKORCharacter::Fart(const FInputActionValue& Value)
{
	Fart_Server(GetKorPCRef(), this);
}

void AKORCharacter::Fart_Server_Implementation(AKorBasePC* PC, ACharacter* Character)
{
	//Make noise
	Character->PawnMakeNoise(1.0f, Character->GetActorLocation(), false, PC);
	Fart_Multicast();
}

void AKORCharacter::Fart_Multicast_Implementation(/*AKorBasePC* PC, ACharacter* Character*/)
{
	if (FartVFX)
	{
		// Rotate 90 degrees
		const FRotator SpawnRotation = GetActorRotation() + FRotator(90, 0, 0);

		UNiagaraFunctionLibrary::SpawnSystemAttached(FartVFX, GetMesh(),TEXT("Butt_Socket"), FVector::Zero(),
		                                             SpawnRotation, EAttachLocation::Type::SnapToTarget, true);

		if (!FartSounds.IsEmpty())
		{
			// Play random sound from the array
			UGameplayStatics::PlaySoundAtLocation(GetWorld(), FartSounds[FMath::RandRange(0, FartSounds.Num() - 1)],
			                                      GetActorLocation());
		}
	}
}

void AKORCharacter::DisableInputs_Implementation(const FInputActionValue& Value)
{
	UNiagaraFunctionLibrary::SpawnSystemAttached(StarsVFX, GetMesh(),TEXT("Stars_Socket"), FVector(0, 0, 0),
	                                             GetMesh()->GetComponentRotation(), EAttachLocation::Type::SnapToTarget,
	                                             true, true);
	GrabbableChildComponent->bCanBeGrabbed = true;
	DisableInput(Cast<APlayerController>(GetController()));
}

void AKORCharacter::EnableInputs_Implementation(const FInputActionValue& Value)
{
	EnableInput(Cast<APlayerController>(GetController()));
}

// GRAB -> GOES TO COMPONENT GRABBING TO CREATE THE SPHERE AND DETECT IF THE OBJECT IS A PHYSIC ACTOR
void AKORCharacter::Grab(const FInputActionValue& Value)
{
	//REPLICATED ON SERVER
	Grab_Replicated(Value);
}

// CATCH THE GRABBINGBASE COMPONENT VARIABLE REF (SAVED IN COMPONENT GRABBING) AND ON OBJECT, CALLS THE FUNCTION END GRAB
void AKORCharacter::EndGrab(const FInputActionValue& Value)
{
	//REPLICATED ON SERVER
	EndGrab_Replicated(Value);
}


void AKORCharacter::EndGrab_Replicated_Implementation(const FInputActionValue& Value)
{
	if (GrabbingComponent->GrabbedComponent != nullptr)
	{
		GrabbingComponent->EndGrab();
		GrabbingComponent->IsGrabbingFalse();
	}
}

void AKORCharacter::Grab_Replicated_Implementation(const FInputActionValue& Value)
{
	GrabbingComponent->IsGrabbingTrue();
	GrabbingComponent->AttempGrab();
}
