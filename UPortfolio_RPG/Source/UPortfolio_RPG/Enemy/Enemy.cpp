// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy/Enemy.h"
#include "AI/EnemyAIController.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
    IsAttacking = false;
    IsDead = false;
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
    //BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
    Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
    StatusWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Hpbarwidget"));
    EnemyState = CreateDefaultSubobject<UStatusComponent>(TEXT("EnemyState"));
    ParticleAttackSystemComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ParticleAttackSystemComponent"));
    ParticleAttackSystem = nullptr;

    Movement->MaxSpeed = 100.0f;                  ///���� �ӵ� ����
    Movement->Acceleration = 500.0f;
    Movement->Deceleration = 500.0f;

    SetRootComponent(CapsuleComponent);
    SkeletalMeshComponent->SetupAttachment(GetRootComponent());
    ParticleAttackSystemComponent->SetupAttachment(GetRootComponent());
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

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
    Init();
}

void AEnemy::OnConstruction(const FTransform& Transform)
{
    Super::OnConstruction(Transform);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
    APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
    if (PlayerController && !IsDead)
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
}

float AEnemy::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
    // Call the base class version of TakeDamage
    float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
    float CurrentHP = EnemyHP;
    float NewHP = CurrentHP - Damage;

    EnemyHP = NewHP;
    UE_LOG(LogTemp, Warning, TEXT("Enemy_HP : %f"), EnemyHP); 

    UUserWidget* StatusUserWidget = StatusWidget->GetWidget();
    if (StatusUserWidget)
    {
        EnemyStatusUserWidget = Cast<UStatusbarUserWidget>(StatusUserWidget);
        if (EnemyStatusUserWidget)
        {
            EnemyStatusUserWidget->SetHP(NewHP, MaxHP);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Error"));
        }

    }

    if (EnemyHP <= 0.f)
    {
        EnemyAnim->SetDeadAnim();
        IsDead = true;
        if(!EnemyAnim->Montage_IsPlaying(nullptr))
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
    auto PlayerCharacter = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
    if (PlayerCharacter)
    {
        FVector PlayerLocation = PlayerCharacter->GetActorLocation();
        FVector EnemyLocation = GetActorLocation();

        // 플레이어와 Enemy 사이의 거리 계산
        float Distance = FVector::Distance(PlayerLocation, EnemyLocation);

        // 공격 범위 내에 있는지 확인
        if (Distance <= 200.f)
        {
            ACharacter* Player = Cast<ACharacter>(PlayerCharacter);
            if (Player)
            {
                UGameplayStatics::ApplyDamage(Player, EnemyAttackDamage, GetController(), this, UDamageType::StaticClass());
            }
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("NoAttackRange"));
        }
    }
}

void AEnemy::OnAttackMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
    IsAttacking = false;
    UE_LOG(LogTemp, Warning, TEXT("AttackMontageEnd"));
}

void AEnemy::PlayAttackParticle()
{
    if (ParticleAttackSystem)
    {
        UGameplayStatics::SpawnEmitterAttached(ParticleAttackSystem, CapsuleComponent, "Impact",
            FVector( (SkeletalMeshComponent->GetRelativeLocation()+ParticleAttackSystemComponent->GetRelativeLocation())), 
            ParticleAttackSystemComponent->GetRelativeRotation(), FVector(ParticleAttackSystemComponent->GetRelativeScale3D()), EAttachLocation::KeepRelativeOffset, true);
    }
}
bool AEnemy::Init()
{
    DataSubsystem = GetGameInstance()->GetSubsystem<UDataSubsystem>();

    AddEnemy(EnemyTypes[FMath::RandRange(0, EnemyTypes.Num()-1)]);
    return true;
}

bool AEnemy::AddEnemy(const FName& InKey)
{
    FEnemyData* InData = DataSubsystem->FindEnemyData(InKey);
    if (!InData)
    {
        check(false);
        return false;
    }
    else
    {
        CapsuleComponent->SetCapsuleRadius(InData->CapsuleRadius);
        CapsuleComponent->SetCapsuleHalfHeight(InData->CapsuleHalfHeight);

        SkeletalMeshComponent->SetSkeletalMesh(InData->SkeletalMesh);
        SkeletalMeshComponent->SetAnimClass(InData->AnimClass);
        SkeletalMeshComponent->SetRelativeTransform(InData->SkeletalMeshTransform);

        EnemyHP = InData->EnemyHP;
        MaxHP = InData->EnemyHP;

        EnemyAttackDamage = InData->EnemyAttackDamage;


        UE_LOG(LogTemp, Warning, TEXT("Enemy_HP : %f"), EnemyHP);
        UE_LOG(LogTemp, Warning, TEXT("MaxHP : %f"), MaxHP);

        FVector HeadPosition = SkeletalMeshComponent->GetBoneLocation(TEXT("head"));
        StatusWidget->SetWorldLocation(HeadPosition + FVector(0.0f, 0.0f, 30.0f));

        ParticleAttackSystem = InData->ParticleAttackSystem;

        if (ParticleAttackSystem)
        {
            ParticleAttackSystemComponent->SetTemplate(ParticleAttackSystem);
        }
        ParticleAttackSystemComponent->SetRelativeTransform(InData->ParticleTransform);


        EnemyAnim = Cast<UEnemyAnimInstance>(SkeletalMeshComponent->GetAnimInstance());
        if (EnemyAnim != nullptr)
        {
               EnemyAnim->OnMontageEnded.AddDynamic(this, &AEnemy::OnAttackMontageEnded);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("Anim Cast Error!!"));
        }

        return true;
    }

}
//Impact

