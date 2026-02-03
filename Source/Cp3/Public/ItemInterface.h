#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemInterface.generated.h"

UINTERFACE(MinimalAPI) //리플렉션을 위한 인터페이스, 수정할 필요가 없음.
class UItemInterface : public UInterface
{
	GENERATED_BODY()
};

class CP3_API IItemInterface
{
	GENERATED_BODY()

public: //순수가상함수 쓰는곳

	//플레이어가 진입했을 때 근데 꼭 액터만 아니어도 된다. 몬스터,드론 등 그때그때 캐스팅만 하면됨
	UFUNCTION()
	virtual void OnItemOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult) = 0;
	UFUNCTION()
	virtual void OnItemEndOverlap(
		UPrimitiveComponent* OverlappedComp,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex) = 0;
	//플레이어가 범위에 이탈했을 때?
	virtual void ActivateItem(AActor* Activator) = 0;
	//실질적으로 사용이 되었을 때 호출 되었을 때.
	virtual FName GetItemType() const = 0;
	//아이템을 구분해야되는 상황.리턴만 해주게 되니까 const
	//FName으로 하는 이유는 Type형이면 더 빠르고 가볍다. 비교할때 많이 쓴다. string이 생각보다 무겁다


};
