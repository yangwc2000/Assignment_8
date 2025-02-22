#include "CustomPawn.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/PlayerController.h"

ACustomPawn::ACustomPawn()
{
    PrimaryActorTick.bCanEverTick = true;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    CapsuleComponent->InitCapsuleSize(34.0f, 88.0f);
    RootComponent = CapsuleComponent;
    CapsuleComponent->SetSimulatePhysics(false);

    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetSimulatePhysics(false);

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComponent"));
    SpringArmComponent->SetupAttachment(RootComponent); // CapsuleComponent에 부착
    SpringArmComponent->TargetArmLength = 300.0f;           // 카메라 거리: 300
    SpringArmComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f)); // 높이 50으로 조정
    SpringArmComponent->bUsePawnControlRotation = true;     // 마우스 입력으로 회전 가능하도록 설정
    SpringArmComponent->SetRelativeRotation(FRotator(-10.0f, 0.0f, 0.0f)); // 기본 -10도 기울임

    CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
    CameraComponent->SetupAttachment(SpringArmComponent, USpringArmComponent::SocketName);
    CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 10.0f)); // 카메라를 10 유닛 위로 이동
    CameraComponent->bUsePawnControlRotation = false; // 카메라 자체 회전은 사용하지 않음

    MoveSpeed = 600.0f;
    RotationSpeed = 90.0f;
}

void ACustomPawn::BeginPlay()
{
    Super::BeginPlay();

    // 선택 사항: EnhancedInputMapping Context 추가 가능 (필요 시)
    if (APlayerController* PC = Cast<APlayerController>(GetController()))
    {
        if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PC->GetLocalPlayer()))
        {
            // 예시: Subsystem->AddMappingContext(YourMappingContext, 0);
        }
    }
}

void ACustomPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        if (MoveAction)
        {
            EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACustomPawn::Move);
        }
        if (LookAction)
        {
            EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACustomPawn::Look);
        }
    }
}

void ACustomPawn::Move(const FInputActionValue& Value)
{
    FVector2D MovementVector = Value.Get<FVector2D>();

    if (!MovementVector.IsNearlyZero())
    {
        FVector Forward = GetActorForwardVector();
        FVector Right = GetActorRightVector();
        FVector MovementDirection = (Forward * MovementVector.X + Right * MovementVector.Y).GetClampedToMaxSize(1.0f);

        float DeltaTime = GetWorld()->GetDeltaSeconds();
        FVector MovementOffset = MovementDirection * MoveSpeed * DeltaTime;

        AddActorLocalOffset(MovementOffset, true);
    }
}

void ACustomPawn::Look(const FInputActionValue& Value)
{
    FVector2D LookAxis = Value.Get<FVector2D>();
    float DeltaTime = GetWorld()->GetDeltaSeconds();

    // Pawn의 Yaw 회전 처리
    float YawDelta = LookAxis.X * RotationSpeed * DeltaTime;
    FRotator CurrentRotation = GetActorRotation();
    CurrentRotation.Yaw += YawDelta;
    SetActorRotation(CurrentRotation);

    // SpringArm의 Pitch 회전 처리 (카메라 상하 각도)
    float PitchDelta = LookAxis.Y * RotationSpeed * DeltaTime;
    FRotator ArmRotation = SpringArmComponent->GetRelativeRotation();
    ArmRotation.Pitch = FMath::Clamp(ArmRotation.Pitch + PitchDelta, -80.0f, 80.0f);
    SpringArmComponent->SetRelativeRotation(ArmRotation);
}
