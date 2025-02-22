#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputMappingContext.h"
#include "MyPawn.generated.h"

class UCapsuleComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class UCameraComponent;
class UInputAction;

UCLASS()
class SPARTAPROJECT_API AMyPawn : public APawn
{
    GENERATED_BODY()

public:
    AMyPawn();

protected:
    virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
    virtual void BeginPlay() override;

    // **������Ʈ��**
    UPROPERTY(VisibleAnywhere)
    UCapsuleComponent* CollisionComponent;

    UPROPERTY(VisibleAnywhere)
    USkeletalMeshComponent* MeshComponent;

    UPROPERTY(VisibleAnywhere)
    USpringArmComponent* SpringArmComponent;

    UPROPERTY(VisibleAnywhere)
    UCameraComponent* CameraComponent;

    // **�Է� �׼ǵ� (Enhanced Input��)**
    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* MoveForwardAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* MoveRightAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputAction* LookAction;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
    UInputMappingContext* IMCAsset;


    // **�Լ���**
    void MoveForward(const FInputActionValue& Value);
    void MoveRight(const FInputActionValue& Value);
    void Look(const FInputActionValue& Value);
};

