#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "SpartaCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UWidgetComponent;
struct FInputActionValue;

UCLASS()
class SPARTAPROJECT_API ASpartaCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ASpartaCharacter();

	// ------------------------------
	// Camera & UI
	// ------------------------------
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	USpringArmComponent* SpringArmComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	UCameraComponent* CameraComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "UI")
	UWidgetComponent* OverheadWidget;

	// ------------------------------
	// Health ����
	// ------------------------------
	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth() const;

	UFUNCTION(BlueprintCallable, Category = "Health")
	void AddHealth(float Amount);

protected:
	// Health ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;

	// ------------------------------
	// �Է� ���� (�̵�, ����, Look, Sprint)
	// ------------------------------
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void Move(const FInputActionValue& Value);

	UFUNCTION()
	void StartJump(const FInputActionValue& Value);

	UFUNCTION()
	void StopJump(const FInputActionValue& Value);

	UFUNCTION()
	void Look(const FInputActionValue& Value);

	UFUNCTION()
	void StartSprint(const FInputActionValue& Value);

	UFUNCTION()
	void StopSprint(const FInputActionValue& Value);

	// ------------------------------
	// �����ֱ� / ������ ����
	// ------------------------------
	virtual void BeginPlay() override;
	virtual float TakeDamage(
		float DamageAmount,
		struct FDamageEvent const& DamageEvent,
		AController* EventInstigator,
		AActor* DamageCauser) override;

	void OnDeath();
	void UpdateOverheadHP();

	// ------------------------------
	// ����� (�̵� �ӵ� �� ��Ʈ�� ����)
	// ------------------------------
public:
	// HealingItem ��� ��: 5�ʰ� �̵��ӵ� 50% ����
	UFUNCTION(BlueprintCallable, Category = "Debuff")
	void ApplySpeedDebuff(float Duration, float SpeedMultiplier);

	// MineItem ���� ��: 5�ʰ� �̵� �Է� ����
	UFUNCTION(BlueprintCallable, Category = "Debuff")
	void ApplyReverseControlsDebuff(float Duration);

protected:
	UFUNCTION()
	void OnSpeedDebuffEnd();

	UFUNCTION()
	void OnReverseControlsDebuffEnd();

	// ------------------------------
	// ������Ʈ �� ����� ���� �ӵ� ���
	// ------------------------------
	void UpdateCharacterSpeed();

private:
	// �⺻ �� ������Ʈ �ӵ�
	float NormalSpeed;
	float SprintSpeedMultiplier;
	float SprintSpeed;

	// ������Ʈ ����
	bool bSprinting;

	// �̵� �ӵ� ����� ���� (������ 0.0~1.0)
	int32 SpeedDebuffStack;
	float CurrentSpeedMultiplier;

	// ��Ʈ�� ���� ����� ����
	int32 ReverseControlStack;
	bool bIsControlReversed;
};
