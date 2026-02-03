#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "ItemSpawnRow.generated.h"

USTRUCT(BlueprintType)
struct FItemSpawnRow : public FTableRowBase
{
	GENERATED_BODY()

public:



	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FName ItemName;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AActor> ItemClass;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SpawnChance;
	
	// TSubclassOf  하드 레퍼런스.
	// 클래스가 항상 메모리에 로드된 상태에서 바로 접근
	// 
	// TSoftClassPtr 소프트 레퍼선스
	//클래스의 경로만 유지.


};
