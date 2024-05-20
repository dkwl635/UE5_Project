// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Monster.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Curves/CurveFloat.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsScream = false;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));

	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/AddContent/FourEvilDragonsHP/Meshes/DragonTheTerrorBringer/DragonTheTerrorBringerSK.DragonTheTerrorBringerSK'"));
		ensure(Asset.Object);
		SkeletalMeshComponent->SetSkeletalMesh(Asset.Object);
	}

	{
		static ConstructorHelpers::FClassFinder<UAnimInstance> Asset(TEXT("/Script/Engine.AnimBlueprint'/Game/LJY/BossMonster/BPA_DragonAnimBlueprint.BPA_DragonAnimBlueprint_C'"));
		ensure(Asset.Class);
		SkeletalMeshComponent->SetAnimInstanceClass(Asset.Class);
		MonsterAnim = Cast<UMonsterAnimInstance>(SkeletalMeshComponent->GetAnimInstance());
	}

	{ 
		//FireScream 공격 관리
		{
			static ConstructorHelpers::FObjectFinder<UParticleSystem> Asset(TEXT("/Script/Engine.ParticleSystem'/Game/AddContent/Realistic_Starter_VFX_Pack_Vol2/Particles/Fire/P_Flamethrower.P_Flamethrower'"));
			ensure(Asset.Object);
			FireScreamEffect = Asset.Object;
		}
		{
			static ConstructorHelpers::FObjectFinder<UAnimMontage> Asset(TEXT("/Script/Engine.AnimMontage'/Game/LJY/BossMonster/MonsterScreamAnimMontage.MonsterScreamAnimMontage'"));
			ensure(Asset.Object);
			FireScreamMontage = Asset.Object;
		}
		{
			static ConstructorHelpers::FObjectFinder<UCurveFloat> Asset(TEXT("/Script/Engine.CurveFloat'/Game/LJY/BossMonster/FireScreamCurve.FireScreamCurve'"));
			ensure(Asset.Object);
			ScreamCurve = Asset.Object;
		}
	}


	SetRootComponent(CapsuleComponent);
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());
	BoxCollision->SetupAttachment(GetRootComponent());

	CapsuleComponent->InitCapsuleSize(200.f, 250.f);
	BoxCollision->SetRelativeLocation(FVector(-310.f, 720.f, -100.f));
	BoxCollision->SetBoxExtent(FVector(100.f, 300.f, 10.f));
	SkeletalMeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -200.f));

	CapsuleComponent->SetCollisionProfileName(TEXT("Enemy"));
	BoxCollision->SetCollisionProfileName(TEXT("MonsterActor"));

	// BoxCollision 컴포넌트에 오버랩 이벤트 핸들러 바인딩
	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AMonster::OnBoxCollisionOverlap);

	// Initialize timeline
		if (ScreamCurve)
		{
			FOnTimelineFloat TimelineCallback;
			TimelineCallback.BindUFunction(this, FName("HandleScreamProgress"));
			ScreamTimeline.AddInterpFloat(ScreamCurve, TimelineCallback);
			ScreamTimeline.SetLooping(true);
		}
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FireScream();
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ScreamTimeline.TickTimeline(DeltaTime);
}

void AMonster::FireScream()
{
	if (FireScreamEffect)
	{
		UGameplayStatics::SpawnEmitterAttached(FireScreamEffect, SkeletalMeshComponent, FName(TEXT("FireAttack")));
	}

	if (FireScreamMontage && SkeletalMeshComponent->GetAnimInstance())
	{
		//SkeletalMeshComponent->GetAnimInstance()->Montage_SetEndDelegate(FOnMontageEnded::CreateUObject(this, &AMonster::OnMontageEnded));
		FOnMontageEnded AttackMontageDelegate;
		AttackMontageDelegate.BindUObject(this, &AMonster::OnMontageEnded);
		SkeletalMeshComponent->GetAnimInstance()->Montage_Play(FireScreamMontage);
		SkeletalMeshComponent->GetAnimInstance()->Montage_SetEndDelegate(AttackMontageDelegate, FireScreamMontage);
	
	}
}

void AMonster::HandleScreamProgress(float Value)
{
	BoxCollision->SetRelativeLocation(FVector(Value, 720, -100));
	UE_LOG(LogTemp, Warning, TEXT("Value 값 : %f"), Value);
}

void AMonster::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	GetWorldTimerManager().SetTimer(DelayTimerHandle, this, &AMonster::ScreamDelay, 1.0f, false); // 1초 지연
	
}

void AMonster::OnBoxCollisionOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	// 오버랩된 액터 출력
	if (OtherActor && OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("BoxCollision overlapped with: %s"), *OtherActor->GetName());
	}
}

void AMonster::ScreamDelay()
{
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	IsScream = true;
	ScreamTimeline.PlayFromStart();
}



