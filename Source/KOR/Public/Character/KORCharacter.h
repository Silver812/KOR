// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AC_GrabbableChild.h"
#include "Character/IKnockable.h"
#include "GameFramework/Character.h"
#include "Logging/LogMacros.h"
#include "PhysicsEngine/PhysicsConstraintComponent.h"
#include "KORCharacter.generated.h"

class AKORBaseHUD;
class AKorBasePC;
class UTextRenderComponent;
class UPhysicalAnimationComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AKORCharacter : public ACharacter, public IKnockable
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Grab Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* GrabAction;

	/** Grab Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* FartAction;

	/** Grab Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* PauseAction;

	/** Grab Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EndGrabAction;

	/** DisableInputs Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* RagdollAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* EndRagdollAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* KOR_InputMappingContext;

	UPROPERTY(EditAnywhere, Category="Component")
	UPhysicsConstraintComponent* PhysicalConstraintSoft;

	// Niagara fart VFX
	UPROPERTY(EditDefaultsOnly, Category="VFX", meta=(AllowPrivateAccess="true"))
	class UNiagaraSystem* FartVFX;

	UPROPERTY(EditDefaultsOnly, Category="VFX", meta=(AllowPrivateAccess="true"))
	UNiagaraSystem* StarsVFX;

	// Fart sounds
	UPROPERTY(EditDefaultsOnly, Category="Sound", meta=(AllowPrivateAccess="true"))
	TArray<USoundWave*> FartSounds;

	UPROPERTY()
	AKorBasePC* KorPCRef;

	UPROPERTY()
	AKORBaseHUD* KorHUDRef;

	// AC GRABBABLE BASE COMP
	FTimerHandle CooldownTimerHandle;
	UPROPERTY(EditAnywhere)
	float KnockedTime = 3.0f;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Replicated, meta=(ExposeOnSpawn="true"))
	FName PlayerNameCustom;
	
	AKORCharacter();
	
	UFUNCTION(BlueprintCallable, NetMulticast, Reliable)
	virtual void GetUp();

	UFUNCTION()
	virtual void Knockout() override;

protected:
	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	/** Called for farting input */
	void Fart(const FInputActionValue& Value);

	/** Called for showing the pause menu input */
	void ShowPauseMenu(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void Fart_Server(AKorBasePC* PC, ACharacter* Character);

	UFUNCTION(NetMulticast, Reliable)
	void Fart_Multicast(/*AKorBasePC* PC, ACharacter* Character*/);

	/** Called for DisableInputs input */
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	virtual void DisableInputs(const FInputActionValue& Value);
	
	/** Called for EnableInputs input */
	UFUNCTION(Client, Reliable, BlueprintCallable)
	void EnableInputs(const FInputActionValue& Value);

	/** Called for grabbing input */
	void Grab(const FInputActionValue& Value);

	void EndGrab(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void Grab_Replicated(const FInputActionValue& Value);

	UFUNCTION(Server, Reliable)
	void EndGrab_Replicated(const FInputActionValue& Value);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerComponent")
	UPhysicalAnimationComponent* PhysicalAnimationComponent;

	// DRUNK PHYSICS COMP
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerComponent")
	class UAC_DrunkPhysics* DrunkPhysicsComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Attachment")
	AActor* ActorToAttach;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Hand_l;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UStaticMeshComponent* Hand_r;

	// GRABBING COMPONENT
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerComponent")
	class UAC_Grabbing* GrabbingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "PlayerComponent")
	UAC_GrabbableChild* GrabbableChildComponent;

	// APawn interface
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// To add mapping context
	virtual void BeginPlay() override;

public:
	/** Returns CameraBoom subobject **/
	FORCEINLINE USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE UCameraComponent* GetFollowCamera() const { return FollowCamera; }

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AKorBasePC* GetKorPCRef();

	UFUNCTION(BlueprintCallable, BlueprintPure)
	AKORBaseHUD* GetKorHUD();

private:
	UPROPERTY()
	AActor* AttachedActor;

	UPROPERTY()
	FName SocketName = FName("Bone");

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"))
	FRotator CapsuleEndRotation = FRotator(90.0f, 0.0f, 90.0f);

	UPROPERTY(EditDefaultsOnly, Category = "Config")
	UUserWidget* PlayerNameWidget;
};
