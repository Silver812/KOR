// Fill out your copyright notice in the Description page of Project Settings.

#include "ADestructibleObjects/ACDestructibleObjectComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "ADestructibleObjects/ADestructibleObj.h"
#include "ADestructibleObjects/APieceofObj.h"
#include "Kismet/GameplayStatics.h"

bool UACDestructibleObjectComponent::DestroyProbability()
{
	float rfloat = static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 100.0f));

	UE_LOG(LogTemp, Warning, TEXT("Probability-> %f // Actual rFloat -> %f"), ObjStruct.destroyProbability, rfloat);

	if (rfloat >= ObjStruct.destroyProbability)
	{
		return false;
	}

	return true;
}

//Spawn one simple piece of a APieceOfObject
void UACDestructibleObjectComponent::SpawnOnePiece_Implementation(FTransform spawnPointTrans, int i)
{
	//SPAWN DEFERRED
	const FTransform transform = spawnPointTrans;
	AAPieceofObj* objPiece = GetWorld()->SpawnActorDeferred<AAPieceofObj>(AAPieceofObj::StaticClass(), transform);
	objPiece->PieceObj_StaticMesh = ObjStruct.staticMeshST[i].PieceObjectStaticMesh;
	objPiece->FinishSpawning(transform, false);

	pieceOfObjRef = objPiece; // SET Spawn piece of object ref.
	pieceOfObjRef->SetReplicates(true); //Set pieceOfObject replication to TRUE
	pieceOfObjRef->SetReplicateMovement(true);
	pieceOfObjRef->PieceObj_MeshComp->SetIsReplicated(true); //Replicate MeshComp
	pieceOfObjRef->GrabbableHardComponent->SetIsReplicated(true);
}

void UACDestructibleObjectComponent::DestructibleEffect_Implementation(FTransform spawnPointTrans)
{
	if (ObjStruct.explosionVFX != nullptr)
	{
		UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ObjStruct.explosionVFX, spawnPointTrans.GetLocation(),
		                                               FRotator::ZeroRotator, spawnPointTrans.GetScale3D(), true, true,
		                                               ENCPoolMethod::None, true);
	}

	if (ObjStruct.destructionSound != nullptr)
	{
		// Random pitch for sound
		float pitch = FMath::RandRange(0.5f, 1.5f);
		
		// Play sound
		UGameplayStatics::PlaySoundAtLocation(this, ObjStruct.destructionSound, spawnPointTrans.GetLocation(), 1.0f, pitch);
	}
}

//This Spawn All the Pieces that are saved in the array 
void UACDestructibleObjectComponent::SpawnPieces_Implementation(FTransform spawnPointTrans)
{
	if (!ObjStruct.bJustOneObject)
	{
		const int arrayLenght = sizeof(ObjStruct.staticMeshST) / sizeof(ObjStruct.staticMeshST[0]);
		for (int i = 0; i <= arrayLenght; ++i)
		{
			for (int j = 1; j <= ObjStruct.staticMeshST[i].numberOfPieces; j++)
			{
				SpawnOnePiece_Implementation(spawnPointTrans, i);
			}
		}

		DestructibleEffect_Implementation(spawnPointTrans); //VFX AND SOUNDS

		if (Cast<AADestructibleObj>(GetOwner())->characterRef)
		{
			Cast<AADestructibleObj>(GetOwner())->characterRef->PawnMakeNoise(
				1.0f, spawnPointTrans.GetLocation(), true, Cast<AADestructibleObj>(GetOwner())->characterRef);
		}

		DestroyDestructibleObj_Implementation(spawnPointTrans); //Destroy Object
	}
	else
	{
		for (int k = 1; k <= ObjStruct.staticMeshST[0].numberOfPieces; k++)
		{
			SpawnOnePiece_Implementation(spawnPointTrans, 0);
		}

		DestructibleEffect_Implementation(spawnPointTrans); //VFX AND SOUNDS

		//MakeSound
		if (Cast<AADestructibleObj>(GetOwner())->characterRef)
		{
			Cast<AADestructibleObj>(GetOwner())->characterRef->PawnMakeNoise(
				1.0f, spawnPointTrans.GetLocation(), true, Cast<AADestructibleObj>(GetOwner())->characterRef);
		}

		DestroyDestructibleObj_Implementation(spawnPointTrans); //Destroy Object
	}
}

void UACDestructibleObjectComponent::DestroyDestructibleObj_Implementation(FTransform spawnPointTrans)
{
	GetOwner()->Destroy();
}

void UACDestructibleObjectComponent::CountdownToMakeNoise_Implementation()
{
	waitingToMakeNoise += 1;

	if (waitingToMakeNoise >= 5)
	{
		Cast<AADestructibleObj>(GetOwner())->soundPlayed = false;
		//UE_LOG(LogTemp, Warning, TEXT("Lets gona make some Noise"));
		GetWorld()->GetTimerManager().PauseTimer(TimerHandleNoise);
		GetWorld()->GetTimerManager().ClearTimer(TimerHandleNoise);
		waitingToMakeNoise = 0;
	}
}

void UACDestructibleObjectComponent::MakingNoise_Implementation(FTransform spawnPointTrans, AActor* OverlapedActor)
{
	if (!Cast<AADestructibleObj>(GetOwner())->soundPlayed)
	{
		Cast<AADestructibleObj>(GetOwner())->characterRef = Cast<AKORCharacter>(OverlapedActor);

		if (Cast<AADestructibleObj>(GetOwner())->characterRef != nullptr)
		{
			//UE_LOG(LogTemp, Warning, TEXT("%s : is mAking Noise For Librarian"),*Cast<AADestructibleObj>(GetOwner())->characterRef->GetName());
			Cast<AADestructibleObj>(GetOwner())->characterRef->PawnMakeNoise(
				1.0f, spawnPointTrans.GetLocation(), true, Cast<AADestructibleObj>(GetOwner())->characterRef);
			Cast<AADestructibleObj>(GetOwner())->soundPlayed = true;

			GetWorld()->GetTimerManager().SetTimer(TimerHandleNoise, this,
			                                       &UACDestructibleObjectComponent::CountdownToMakeNoise_Implementation,
			                                       1.f, true
			                                       , 0.0);
		}
	}
}


// Sets default values for this component's properties
UACDestructibleObjectComponent::UACDestructibleObjectComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UACDestructibleObjectComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UACDestructibleObjectComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                   FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
