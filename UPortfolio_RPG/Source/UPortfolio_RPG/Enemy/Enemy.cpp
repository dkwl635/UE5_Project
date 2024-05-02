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

    /*static ConstructorHelpers::FObjectFinder<USkeletalMesh> NormalMonster(TEXT("/Script/Engine.SkeletalMesh'/Game/AddContent/ParagonMinions/Characters/Minions/Prime_Helix/Meshes/Prime_Helix.Prime_Helix'"));
    if (NormalMonster.Succeeded())
    {
        Mesh->SetSkeletalMesh(NormalMonster.Object);
    }*/

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
        // �÷��̾� ĳ������ ��ġ ��������
        FVector PlayerLocation = PlayerController->GetPawn()->GetActorLocation();

        // ������ ��ġ ��������
        FVector MonsterLocation = GetActorLocation();

        // �÷��̾ ���ϴ� ���� ���
        FVector DirectionToPlayer = PlayerLocation - MonsterLocation;
        DirectionToPlayer.Z = 0.f; // Z �� ���� �����Ͽ� ���� �������θ� ȸ���ϵ��� ��

        // ��ǥ ȸ���� ���
        FRotator MonsterRotation = FRotationMatrix::MakeFromX(DirectionToPlayer).Rotator();
        MonsterRotation.Yaw -= 90.0f; //�÷��̾�� ������� �´� ȸ�� ���� �־������

        // ��ǥ ȸ���� ����
        SetActorRotation(MonsterRotation);
    }
}

