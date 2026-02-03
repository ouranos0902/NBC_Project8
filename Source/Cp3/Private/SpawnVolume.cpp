#include "SpawnVolume.h"
#include "Components/BoxComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

ASpawnVolume::ASpawnVolume()
{
    PrimaryActorTick.bCanEverTick = false;

    // 박스 컴포넌트를 생성하고, 이 액터의 루트로 설정
    Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
    SetRootComponent(Scene);

    SpawningBox = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawningBox"));
    SpawningBox->SetupAttachment(Scene);

    ItemDataTable = nullptr;
}

AActor* ASpawnVolume::SpawnRandomItem()
{
    if (FItemSpawnRow* SelectedRow = GetRandomItem())
    {
        if (UClass* ActualClass = SelectedRow->ItemClass.Get())
        {
            return SpawnItem(ActualClass);
        }
    }
    return nullptr;
}


FVector ASpawnVolume::GetRandomPointInVolume() const
{
    // 1) 박스 컴포넌트의 스케일된 Extent, 즉 x/y/z 방향으로 반지름(절반 길이)을 구함
    FVector BoxExtent = SpawningBox->GetScaledBoxExtent();
    // 2) 박스 중심 위치
    FVector BoxOrigin = SpawningBox->GetComponentLocation();

    // 3) 각 축별로 -Extent ~ +Extent 범위의 무작위 값 생성
    return BoxOrigin + FVector(
        FMath::FRandRange(-BoxExtent.X, BoxExtent.X),
        FMath::FRandRange(-BoxExtent.Y, BoxExtent.Y),
        FMath::FRandRange(-BoxExtent.Z, BoxExtent.Z)
    );
}


FItemSpawnRow* ASpawnVolume::GetRandomItem() const
{
    if (!ItemDataTable) return nullptr;

    TArray<FItemSpawnRow*> AllRows;

    static const FString ContextString(TEXT("ItemSpawnContext"));

    ItemDataTable->GetAllRows(ContextString, AllRows);

    if (AllRows.IsEmpty()) return nullptr;

    float TotalChance = 0.0f;
    for (const FItemSpawnRow* Row : AllRows)
    {
        if (Row)
        {
            TotalChance += Row->SpawnChance;
        }
    }

    const float RandValue = FMath::FRandRange(0.0f, TotalChance);
    float AccumulateChance = 0.0f;

    // 랜덤값 생성 -> 0.0~1.0 랜덤값이 0.7? -> 첫번째 아이템 a같은 경우 누적 확률 0.5 50%확률 b는 30% c는 20% 다 더하면 1.0
    //근데 다 더하면 0.7이 나왔다? 그러면 아이템 b가 나옴
    //이런 방식을 누적 확률 방식의 랜덤 뽑기


    for (FItemSpawnRow* Row : AllRows)
    {
        AccumulateChance += Row->SpawnChance;
        if (RandValue <= AccumulateChance)
        {
            return Row;
        }
    }
    return nullptr;
}



AActor* ASpawnVolume::SpawnItem(TSubclassOf<AActor> ItemClass)
{
    if (!ItemClass) return nullptr;

    AActor* SpawnActor = GetWorld()->SpawnActor<AActor>(
        ItemClass,
        GetRandomPointInVolume(),
        FRotator::ZeroRotator
    );

    return SpawnActor;
}