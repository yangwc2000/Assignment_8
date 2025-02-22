#include "MyPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"

AMyPawn::AMyPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    // 1. 충돌 컴포넌트 (Capsule) 생성 및 루트로 설정
    CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
    RootComponent = CollisionComponent;
    CollisionComponent->SetSimulatePhysics(false); // 물리 시뮬레이션 OFF

    // 2. Mesh 컴포넌트 생성 및 첨부
    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetSimulatePhysics(false); // 물리 시뮬레이션 OFF

    // 3. Spring Arm 생성 및 첨부
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComponent->SetupAttachment(RootComponent);
    // (Spring Arm의 길이, 소켓 오프셋 등 필요하면 여기서 설정)

    // 4. Camera 생성 및 첨부
    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    CameraComponent->SetupAttachment(SpringArmComponent);
}

void AMyPawn::MoveForward(const FInputActionValue& Value)
{
    float AxisValue = Value.Get<float>();
    if (FMath::Abs(AxisValue) > KINDA_SMALL_NUMBER)
    {
        FVector Delta = GetActorForwardVector() * AxisValue * 600.f * GetWorld()->GetDeltaSeconds();
        AddActorLocalOffset(Delta, true);
    }
}

void AMyPawn::MoveRight(const FInputActionValue& Value)
{
    float AxisValue = Value.Get<float>();
    if (FMath::Abs(AxisValue) > KINDA_SMALL_NUMBER)
    {
        FVector Delta = GetActorRightVector() * AxisValue * 600.f * GetWorld()->GetDeltaSeconds();
        AddActorLocalOffset(Delta, true);
    }
}

void AMyPawn::Look(const FInputActionValue& Value)
{
    FVector2D LookValue = Value.Get<FVector2D>();
    // 직접 Yaw와 Pitch 계산
    FRotator CurrentRotation = GetActorRotation();
    CurrentRotation.Yaw += LookValue.X * 2.f; // 민감도 조절
    CurrentRotation.Pitch = FMath::Clamp(CurrentRotation.Pitch + LookValue.Y * 2.f, -80.f, 80.f);
    SetActorRotation(CurrentRotation);
}

void AMyPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComp = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComp->BindAction(MoveForwardAction, ETriggerEvent::Triggered, this, &AMyPawn::MoveForward);
        EnhancedInputComp->BindAction(MoveRightAction, ETriggerEvent::Triggered, this, &AMyPawn::MoveRight);
        EnhancedInputComp->BindAction(LookAction, ETriggerEvent::Triggered, this, &AMyPawn::Look);
    }
}

void AMyPawn::BeginPlay()
{
    Super::BeginPlay();

    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            Subsystem->AddMappingContext(IMCAsset, 0);  // IMCAsset은 에디터에서 지정할 수 있게 UPROPERTY(EditAnywhere)로 선언
        }
    }
}

