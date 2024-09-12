#pragma once

#include "CoreMinimal.h"
#include "KorGMDefTable.generated.h"

class UKorGMDefinition;

USTRUCT()
struct FKorGMDefTable: public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UKorGMDefinition> GMDefinition;
};