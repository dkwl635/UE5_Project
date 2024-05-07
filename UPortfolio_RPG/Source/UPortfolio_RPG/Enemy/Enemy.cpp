// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/Enemy.h"
#include "AI/EnemyAIController.h"
#include "Components/WidgetComponent.h"
#include "Enemy/Animation/EnemyAnimInstance.h"
//#include "PlayerController.h"

// Sets default values
AEnemy::AEnemy()
{
    IsAttacking = false;
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    //BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
    Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
    HPBarWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Hpbarwidget"));

    Movement->MaxSpeed = 100.0f;                  ///���� �ӵ� ����
    Movement->Acceleration = 500.0f;
    Movement->Deceleration = 500.0f;

    SetRootComponent(CapsuleComponent);
    SkeletalMeshComponent->SetupAttachment(GetRootComponent());
  //  SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    CapsuleComponent->SetCollisionProfileName(TEXT("Enemy"));

    HPBarWidget->SetupAttachment(SkeletalMeshComponent);
    HPBarWidget->SetRelativeLocation(FVector(0.0f, 0.0f, 500.f));
    HPBarWidget->SetWidgetSpace(EWidgetSpace::Screen);

    static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/LJY/UI_EnemyHPBar.UI_EnemyHPBar_C'"));
    if (UI_HUD.Succeeded())
    {
        
        HPBarWidget->SetWidgetClass(UI_HUD.Class);
        HPBarWidget->SetDrawSize(FVector2D(150.f, 50.0f));
    }

    //AIController설정
    AIControllerClass = AEnemyAIController::StaticClass(); //나중에 데이터 테이블화 시키기
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

AEnemy::~AEnemy()
{
}

void AEnemy::SetEnemyData(const FDataTableRowHandle& InDataTableRowHandle)
{
    DataTableRowHandle = InDataTableRowHandle;
    if (DataTableRowHandle.IsNull()) { return; }
    if (DataTableRowHandle.RowName == NAME_None) { return; }
    EnemyDataTableRow = DataTableRowHandle.GetRow<FEnemyDataTableRow>(TEXT(""));
    SetEnemyData(EnemyDataTableRow);
}

void AEnemy::SetEnemyData(const FEnemyDataTableRow* InData)
{
    ensure(InData);
    if (!ensure(InData))
    {
        UE_LOG(LogTemp, Error, TEXT("InData is nullptr!"));
        return;
    }
    EnemyDataTableRow = InData;

    CapsuleComponent->SetCapsuleRadius(InData->CapsuleRadius);
    CapsuleComponent->SetCapsuleHalfHeight(InData->CapsuleHalfHeight);

    SkeletalMeshComponent->SetSkeletalMesh(InData->SkeletalMesh);
    SkeletalMeshComponent->SetAnimClass(InData->AnimClass);
    SkeletalMeshComponent->SetRelativeTransform(InData->SkeletalMeshTransform);
    

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

void AEnemy::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
    SetEnemyData(DataTableRowHandle);
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

void AEnemy::PostInitializeComponents()
{
    Super::PostInitializeComponents();
    EnemyAnim = Cast<UEnemyAnimInstance>(SkeletalMeshComponent->GetAnimInstance());
    if (EnemyAnim)
    {
        EnemyAnim->OnMontageEnded.AddDynamic(this, &AEnemy::OnAttackMontageEnded);
    }

   // EnemyAnim->OnAttackHitCheck.AddUObject(this, &AEnemy::AttackCheck);
}

void AEnemy::Attack()
{
    if (IsAttacking) return;

    EnemyAnim->PlayAttackMontage();
    IsAttacking = true;
}

void AEnemy::AttackCheck()
{

}

void AEnemy::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    IsAttacking = false;
}

