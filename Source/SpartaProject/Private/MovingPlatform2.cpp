#include "MovingPlatform2.h"
#include "Components/StaticMeshComponent.h"

// 생성자: 기본 설정
AMovingPlatform2::AMovingPlatform2()
{
    PrimaryActorTick.bCanEverTick = true;

    // StaticMeshComponent 생성 후 루트로 지정
    PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
    RootComponent = PlatformMesh;

    // 기본값 설정
    MoveSpeed = 200.0f;      // 초당 200 유닛 이동
    MaxRange = 500.0f;       // 최대 500 유닛 범위 내에서 왕복
    MoveDirection = FVector(1, 0, 0); // X축 방향 이동
    bMovingForward = true;
}

// 게임 시작 시 호출
void AMovingPlatform2::BeginPlay()
{
    Super::BeginPlay();

    // 초기 위치 저장
    StartLocation = GetActorLocation();
}

// 매 프레임 호출되는 Tick 함수
void AMovingPlatform2::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // 현재 위치를 불러오고 이동할 거리 계산
    FVector CurrentLocation = GetActorLocation();
    FVector DeltaMove = MoveDirection * MoveSpeed * DeltaTime;

    // 이동 방향에 따라 부호 반전
    if (!bMovingForward)
    {
        DeltaMove = -DeltaMove;
    }

    FVector NewLocation = CurrentLocation + DeltaMove;

    // 시작 위치로부터 이동한 거리를 계산 (벡터의 정규화된 방향으로 내적)
    float DistanceMoved = FVector::DotProduct(NewLocation - StartLocation, MoveDirection.GetSafeNormal());

    // 만약 최대 범위를 넘었다면 이동 방향 반전
    if (FMath::Abs(DistanceMoved) >= MaxRange)
    {
        bMovingForward = !bMovingForward;
        // overshoot 방지를 위해 위치 보정 (최대 범위 내에 있게 함)
        NewLocation = StartLocation + MoveDirection.GetSafeNormal() * FMath::Clamp(DistanceMoved, -MaxRange, MaxRange);
    }

    // 계산된 새 위치로 업데이트
    SetActorLocation(NewLocation);
}
