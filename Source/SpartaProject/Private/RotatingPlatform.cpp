#include "RotatingPlatform.h"
#include "Components/StaticMeshComponent.h"

// 생성자: 기본 설정
ARotatingPlatform::ARotatingPlatform()
{
    // 매 프레임 Tick 함수를 호출하게 설정
    PrimaryActorTick.bCanEverTick = true;

    // StaticMeshComponent 생성 후 루트 컴포넌트로 지정
    PlatformMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlatformMesh"));
    RootComponent = PlatformMesh;

    // 회전 속도의 기본값 설정 (예: 90도/초)
    RotationSpeed = 90.0f;
}

// 게임 시작 시 호출
void ARotatingPlatform::BeginPlay()
{
    Super::BeginPlay();
}

// 매 프레임 호출되는 Tick 함수
void ARotatingPlatform::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // DeltaTime을 곱해서 회전 값 계산: 매 프레임 회전 적용
    FRotator DeltaRotation(0, RotationSpeed * DeltaTime, 0);
    AddActorLocalRotation(DeltaRotation);
}
