// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/Enemy.h"
#include "AI/EnemyAIController.h"
//#include "PlayerController.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
    Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
    Movement->MaxSpeed = 500.0f;
    Movement->Acceleration = 500.0f;
    Movement->Deceleration = 500.0f;

    BoxComponent->SetupAttachment(RootComponent);
    Mesh->SetupAttachment(BoxComponent);

    static ConstructorHelpers::FObjectFinder<USkeletalMesh> NormalMonster(TEXT("/Script/Engine.SkeletalMesh'/Game/AddContent/ParagonMinions/Characters/Minions/Prime_Helix/Meshes/Prime_Helix.Prime_Helix'"));
    if (NormalMonster.Succeeded())
    {
        Mesh->SetSkeletalMesh(NormalMonster.Object);
    }

    AIControllerClass = AEnemyAIController::StaticClass();
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController)
    {
        // 플레이어 캐릭터의 위치 가져오기
        FVector PlayerLocation = PlayerController->GetPawn()->GetActorLocation();

        // 몬스터의 위치 가져오기
        FVector MonsterLocation = GetActorLocation();

        // 플레이어를 향하는 벡터 계산
        FVector DirectionToPlayer = PlayerLocation - MonsterLocation;
        DirectionToPlayer.Z = 0.f; // Z 축 값은 무시하여 수평 방향으로만 회전하도록 함

        // 목표 회전값 계산
        FRotator MonsterRotation = FRotationMatrix::MakeFromX(DirectionToPlayer).Rotator();
        MonsterRotation.Yaw -= 90.0f; //플레이어와 축방향이 맞는 회전 값을 넣어줘야함

        // 목표 회전값 적용
        SetActorRotation(MonsterRotation);
    }
}

