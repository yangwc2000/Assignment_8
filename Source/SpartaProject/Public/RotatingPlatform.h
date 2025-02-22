#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RotatingPlatform.generated.h"

UCLASS()
class SPARTAPROJECT_API ARotatingPlatform : public AActor
{
    GENERATED_BODY()

public:
    // 생성자: 기본 값 설정
    ARotatingPlatform();

protected:
    // 게임 시작 시 호출
    virtual void BeginPlay() override;

public:
    // 매 프레임 호출 (DeltaTime: 프레임 독립성을 위해 사용)
    virtual void Tick(float DeltaTime) override;

    // **Static Mesh Component**: 에디터에서 보이고 수정 가능하도록!
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
    UStaticMeshComponent* PlatformMesh;

    // 회전 속도 (초당 몇 도 회전할지)
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Platform Settings")
    float RotationSpeed;
};
