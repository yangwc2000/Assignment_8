#include "Item.h"

DEFINE_LOG_CATEGORY(LogSparta);

AItem::AItem()
{
	
	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	SetRootComponent(SceneRoot);

	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMeshComp->SetupAttachment(SceneRoot);

	//'/Game/Resources/Props/SM_Chair.SM_Chair'
	//'/Game/Resources/Materials/M_Coin_A.M_Coin_A'

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshAsset(TEXT("/Game/Resources/Props/SM_Chair.SM_Chair"));
	if (MeshAsset.Succeeded())
	{
		StaticMeshComp->SetStaticMesh(MeshAsset.Object);
	}
	
	static ConstructorHelpers::FObjectFinder<UMaterial> MaterialAsset(TEXT("/Game/Resources/Materials/M_Coin_A.M_Coin_A"));
	if (MaterialAsset.Succeeded())
	{
		StaticMeshComp->SetMaterial(0, MaterialAsset.Object);
	}

	UE_LOG(LogSparta, Warning, TEXT("%s Constructor"), *GetName());
}

void AItem::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	UE_LOG(LogSparta, Warning, TEXT("%s PostInitializeComponents"), *GetName());
}

void AItem::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogSparta, Warning, TEXT("%s BeginPlay"), *GetName());
}

void AItem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItem::Destroyed()
{
	UE_LOG(LogSparta, Warning, TEXT("%s Destroyed"), *GetName());
	Super::Destroyed();
}

void AItem::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogSparta, Warning, TEXT("%s EndPlay"), *GetName());
	Super::EndPlay(EndPlayReason);
}

// �ֿ� ����������Ŭ �Լ��� 6����

// ������ - �޸𸮿� ����. �� �ѹ� ȣ��.
// PostInitializeComponents() - ������Ʈ�� �ϼ��� ���� ȣ��. ������Ʈ���� ������ �ְ�ޱ�, ��ȣ�ۿ�
// BeginPlay() - ��ġ(����) ����
// Tick(FLoat DeltaTime) - �� �����Ӹ��� ȣ���.
// Destroyed() - ���� �Ǳ� ������ ȣ��ȴ�.
// EndPlay() - ���� ����, �ı� (Destroyed()), ���� ��ȯ
