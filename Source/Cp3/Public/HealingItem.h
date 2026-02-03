#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "HealingItem.generated.h"


UCLASS()
class CP3_API AHealingItem : public ABaseItem
{
	GENERATED_BODY()
	
public:
        AHealingItem();

protected:
    // 회복량
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Healing")
    int32 HealAmount;

    virtual void ActivateItem(AActor* Activator) override;
};