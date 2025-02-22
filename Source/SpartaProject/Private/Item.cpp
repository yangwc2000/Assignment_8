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

// 주요 라이프사이클 함수들 6가지

// 생성자 - 메모리에 생김. 딱 한번 호출.
// PostInitializeComponents() - 컴포넌트가 완성된 직후 호출. 컴포넌트끼리 데이터 주고받기, 상호작용
// BeginPlay() - 배치(스폰) 직후
// Tick(FLoat DeltaTime) - 매 프레임마다 호출됨.
// Destroyed() - 삭제 되기 직전에 호출된다.
// EndPlay() - 게임 종료, 파괴 (Destroyed()), 레벨 전환
