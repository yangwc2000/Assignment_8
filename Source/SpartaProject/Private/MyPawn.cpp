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

    // 1. �浹 ������Ʈ (Capsule) ���� �� ��Ʈ�� ����
    CollisionComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CollisionComponent"));
    RootComponent = CollisionComponent;
    CollisionComponent->SetSimulatePhysics(false); // ���� �ùķ��̼� OFF

    // 2. Mesh ������Ʈ ���� �� ÷��
    MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComponent"));
    MeshComponent->SetupAttachment(RootComponent);
    MeshComponent->SetSimulatePhysics(false); // ���� �ùķ��̼� OFF

    // 3. Spring Arm ���� �� ÷��
    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
    SpringArmComponent->SetupAttachment(RootComponent);
    // (Spring Arm�� ����, ���� ������ �� �ʿ��ϸ� ���⼭ ����)

    // 4. Camera ���� �� ÷��
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
    // ���� Yaw�� Pitch ���
    FRotator CurrentRotation = GetActorRotation();
    CurrentRotation.Yaw += LookValue.X * 2.f; // �ΰ��� ����
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
            Subsystem->AddMappingContext(IMCAsset, 0);  // IMCAsset�� �����Ϳ��� ������ �� �ְ� UPROPERTY(EditAnywhere)�� ����
        }
    }
}

