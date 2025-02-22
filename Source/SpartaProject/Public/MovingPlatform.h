#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class SPARTAPROJECT_API AMovingPlatform : public AActor
{
    GENERATED_BODY()

public:
    // 생성자: 기본 값 설정
    AMovingPlatform();

protected:
    // 게임 시작 시 호출
    virtual void BeginPlay() override;

public:
    // 매 프레임 호출 (DeltaTime: 프레임 독립성을 위해 사용)
    virtual void Tick(float DeltaTime) override;

    // Static Mesh Component
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* PlatformMesh;

    // 이동 속도 (유닛/초)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
    float MoveSpeed;

    // 최대 이동 범위 (시작 위치로부터의 거리)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
    float MaxRange;

    // 이동 방향 (예: X축 방향)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
    FVector MoveDirection;

private:
    // 초기 시작 위치 저장
    FVector StartLocation;
    // 현재 이동 방향 여부 (정방향/역방향)
    bool bMovingForward;
};
