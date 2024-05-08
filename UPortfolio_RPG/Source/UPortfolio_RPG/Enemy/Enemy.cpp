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
    StatusWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Hpbarwidget"));
    EnemyState = CreateDefaultSubobject<UStatusComponent>(TEXT("EnemyState"));


    Movement->MaxSpeed = 100.0f;                  ///���� �ӵ� ����
    Movement->Acceleration = 500.0f;
    Movement->Deceleration = 500.0f;

    SetRootComponent(CapsuleComponent);
    SkeletalMeshComponent->SetupAttachment(GetRootComponent());
  //  SkeletalMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    CapsuleComponent->SetCollisionProfileName(TEXT("Enemy"));


    StatusWidget->SetupAttachment(SkeletalMeshComponent);
    
    StatusWidget->SetWidgetSpace(EWidgetSpace::Screen);

    static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/LJY/UI_EnemyHPBar.UI_EnemyHPBar_C'"));
    if (UI_HUD.Succeeded())
    {
        
        StatusWidget->SetWidgetClass(UI_HUD.Class);
        StatusWidget->SetDrawSize(FVector2D(150.f, 50.0f));
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

    EnemyState->SetEnemyHP(InData->EnemyHP);
    MaxHP = InData->EnemyHP;
    UE_LOG(LogTemp, Warning, TEXT("Enemy_HP : %f"), EnemyState->GetEnemyHP());
    UE_LOG(LogTemp, Warning, TEXT("MaxHP : %f"), MaxHP);

    FVector HeadPosition = SkeletalMeshComponent->GetBoneLocation(TEXT("head"));
    StatusWidget->SetWorldLocation(HeadPosition + FVector(0.0f, 0.0f, 30.0f));
    

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

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    // Call the base class version of TakeDamage
    float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

    // 적의 상태 객체에서 HP를 가져와서 데미지를 적용합니다.
    float CurrentHP = EnemyState->GetEnemyHP();
    float NewHP = CurrentHP - EnemyState->GetAttackDamage();
    EnemyState->SetEnemyHP(NewHP);
    UE_LOG(LogTemp, Warning, TEXT("Enemy_HP : %f"), EnemyState->GetEnemyHP()); 

    UUserWidget* StatusUserWidget = StatusWidget->GetWidget();
    if (StatusUserWidget)
    {
        EnemyStatusUserWidget = Cast<UStatusbarUserWidget>(StatusUserWidget);
        if (EnemyStatusUserWidget)
        {

            UE_LOG(LogTemp, Warning, TEXT("NewHP : %f"), NewHP);
            UE_LOG(LogTemp, Warning, TEXT("MaxHP : %f"), MaxHP);
            EnemyStatusUserWidget->SetHP(NewHP, MaxHP);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Error"));
        }

    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Err"));
    }

    if (EnemyState->GetEnemyHP() <= 0.f)
    {
        Destroy();
    }

    return Damage;
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

