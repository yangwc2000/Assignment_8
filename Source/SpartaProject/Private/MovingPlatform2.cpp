#include "MovingPlatform2.h"
#include "Components/StaticMeshComponent.h"

// ������: �⺻ ����
AMovingPlatform2::AMovingPlatform2()
{
    PrimaryActorTick.bCanEverTick = true;

    // StaticMeshComponent ���� �� ��Ʈ�� ����
    PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
    RootComponent = PlatformMesh;

    // �⺻�� ����
    MoveSpeed = 200.0f;      // �ʴ� 200 ���� �̵�
    MaxRange = 500.0f;       // �ִ� 500 ���� ���� ������ �պ�
    MoveDirection = FVector(1, 0, 0); // X�� ���� �̵�
    bMovingForward = true;
}

// ���� ���� �� ȣ��
void AMovingPlatform2::BeginPlay()
{
    Super::BeginPlay();

    // �ʱ� ��ġ ����
    StartLocation = GetActorLocation();
}

// �� ������ ȣ��Ǵ� Tick �Լ�
void AMovingPlatform2::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // ���� ��ġ�� �ҷ����� �̵��� �Ÿ� ���
    FVector CurrentLocation = GetActorLocation();
    FVector DeltaMove = MoveDirection * MoveSpeed * DeltaTime;

    // �̵� ���⿡ ���� ��ȣ ����
    if (!bMovingForward)
    {
        DeltaMove = -DeltaMove;
    }

    FVector NewLocation = CurrentLocation + DeltaMove;

    // ���� ��ġ�κ��� �̵��� �Ÿ��� ��� (������ ����ȭ�� �������� ����)
    float DistanceMoved = FVector::DotProduct(NewLocation - StartLocation, MoveDirection.GetSafeNormal());

    // ���� �ִ� ������ �Ѿ��ٸ� �̵� ���� ����
    if (FMath::Abs(DistanceMoved) >= MaxRange)
    {
        bMovingForward = !bMovingForward;
        // overshoot ������ ���� ��ġ ���� (�ִ� ���� ���� �ְ� ��)
        NewLocation = StartLocation + MoveDirection.GetSafeNormal() * FMath::Clamp(DistanceMoved, -MaxRange, MaxRange);
    }

    // ���� �� ��ġ�� ������Ʈ
    SetActorLocation(NewLocation);
}
