#include "CoinItem.h"
#include "SpartaGameState.h"
#include "Engine/World.h"

ACoinItem::ACoinItem()
	: SpinSpeed(180.f)
	, bOrbitMode(false)
	, OrbitAngle(0.f)
	, OrbitRadius(100.f)
	, PointValue(10)
{
	PrimaryActorTick.bCanEverTick = true;
}

void ACoinItem::BeginPlay()
{
	Super::BeginPlay();

	// ������ ������ ��ġ�� ������ �߽������� ����
	OriginalSpawnLocation = GetActorLocation();
}

void ACoinItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	UpdateSpin(DeltaTime);

	if (bOrbitMode)
	{
		UpdateOrbit(DeltaTime);
	}
}

void ACoinItem::UpdateSpin(float DeltaTime)
{
	// ������ Yaw�� �������� ȸ����Ŵ
	AddActorLocalRotation(FRotator(0.f, SpinSpeed * DeltaTime, 0.f));
}

void ACoinItem::UpdateOrbit(float DeltaTime)
{
	// OrbitSpeed�� 100 deg/sec (�ʿ� �� �Ӽ����� �и� ����)
	const float OrbitSpeed = 100.f;
	OrbitAngle += OrbitSpeed * DeltaTime;

	// ������ ���� ������ ��ȯ
	const float Radians = FMath::DegreesToRadians(OrbitAngle);

	// ���� �������� �̿��Ͽ� X/Y ��ġ ��� (Z�� ����)
	FVector NewPosition = OriginalSpawnLocation;
	NewPosition.X += OrbitRadius * FMath::Cos(Radians);
	NewPosition.Y += OrbitRadius * FMath::Sin(Radians);

	SetActorLocation(NewPosition);
}

void ACoinItem::ActivateItem(AActor* Activator)
{
	Super::ActivateItem(Activator);

	// �÷��̾ ������ ȹ���� ���
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

void ACoinItem::SetWave3OrbitActive(bool bActive)
{
	bOrbitMode = bActive;
}
