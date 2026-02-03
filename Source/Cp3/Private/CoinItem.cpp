#include "CoinItem.h"
#include "Engine/World.h"
#include "SpartaGameState.h"

ACoinItem::ACoinItem()
{

    // 점수 기본값을 0으로 설정
    PointValue = 0;
    ItemType = "DefaultCoin";
}

void ACoinItem::ActivateItem(AActor* Activator)
{
    // 플레이어 태그 확인
    if (Activator && Activator->ActorHasTag("Player"))
    {
        if (UWorld* World = GetWorld())
        {
            if (ASpartaGameState* GameState = World->GetGameState<ASpartaGameState>())
            {
                GameState->AddScore(PointValue);
                GameState->OnCoinCollected();
           }
        }
        DestroyItem();
    }
}