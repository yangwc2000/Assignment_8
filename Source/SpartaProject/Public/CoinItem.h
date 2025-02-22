#pragma once

#include "CoreMinimal.h"
#include "BaseItem.h"
#include "CoinItem.generated.h"

UCLASS()
class SPARTAPROJECT_API ACoinItem : public ABaseItem
{
	GENERATED_BODY()

public:
	ACoinItem();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void ActivateItem(AActor* Activator) override;

public:
	// Wave 3 ���� ��, �� �Լ��� ȣ���Ͽ� ������ ����(orbit) ��带 On/Off
	void SetWave3OrbitActive(bool bActive);

protected:
	// ������ ���ڸ����� ȸ���ϴ� �ӵ� (deg/sec)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	float SpinSpeed;

	// Wave 3 �� ���� ��� Ȱ��ȭ ����
	bool bOrbitMode;

	// ������ ������ ��ġ (������ �߽���)
	FVector OriginalSpawnLocation;

	// ���� ���� ���� (����: degree)
	float OrbitAngle;

	// ���� �ݰ� (�� �߽����κ����� �Ÿ�)
	float OrbitRadius;

	// ������ ȹ������ �� �����ϴ� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Coin")
	int32 PointValue;

private:
	// ������ ����(Spin) ������Ʈ �Լ�
	void UpdateSpin(float DeltaTime);

	// ����(Orbit) �̵� ������Ʈ �Լ� (Orbit ��� Ȱ�� ��)
	void UpdateOrbit(float DeltaTime);
};

