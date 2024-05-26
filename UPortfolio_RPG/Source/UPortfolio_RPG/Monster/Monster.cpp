// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Monster.h"
#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "Animation/AnimMontage.h"
#include "Animation/AnimInstance.h"
#include "Curves/CurveFloat.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "Monster/Actor/AttackRangeActor.h"
#include "DrawDebugHelpers.h"
#include "Monster/AI/MonsterAIController.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	IsScream = false;

	CurrentHP = MaxHP;

	SpawnedEffect = nullptr;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));
	Movement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("MovementComponent"));
	StatusWidget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Hpbarwidget"));

	Movement->MaxSpeed = 300.0f;
	Movement->Acceleration = 500.0f;
	Movement->Deceleration = 500.0f;

	StatusWidget->SetupAttachment(SkeletalMeshComponent);
	StatusWidget->SetWidgetSpace(EWidgetSpace::Screen);

	static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/LJY/UI/UI_MonsterHPBar.UI_MonsterHPBar_C'"));
	if (UI_HUD.Succeeded())
	{
		StatusWidget->SetWidgetClass(UI_HUD.Class);
		StatusWidget->SetDrawSize(FVector2D(300.f, 100.0f));
		StatusWidget->SetVisibility(false);
	}

	{
		static ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/AddContent/FourEvilDragonsHP/Meshes/DragonTheTerrorBringer/DragonTheTerrorBringerSK.DragonTheTerrorBringerSK'"));
		ensure(Asset.Object);
		SkeletalMeshComponent->SetSkeletalMesh(Asset.Object);
	}


	 

	//FireScream 공격 관리
	{ 
		
		{
			static ConstructorHelpers::FObjectFinder<UParticleSystem> Asset(TEXT("/Script/Engine.ParticleSystem'/Game/AddContent/Realistic_Starter_VFX_Pack_Vol2/Particles/Fire/P_Flamethrower.P_Flamethrower'"));
			ensure(Asset.Object);
			FireScreamEffect = Asset.Object;
		}
		{
			static ConstructorHelpers::FObjectFinder<UAnimMontage> Asset(TEXT("/Script/Engine.AnimMontage'/Game/LJY/BossMonster/Animation/MonsterScreamAnimMontage.MonsterScreamAnimMontage'"));
			ensure(Asset.Object);
			FireScreamMontage = Asset.Object;
		}
		{
			static ConstructorHelpers::FObjectFinder<UCurveFloat> Asset(TEXT("/Script/Engine.CurveFloat'/Game/LJY/BossMonster/FireScreamCurve.FireScreamCurve'"));
			ensure(Asset.Object);
			ScreamCurve = Asset.Object;
		}
	}

	// AttackRange 공격 관리
	{

		{
			static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Asset(TEXT("/Script/Niagara.NiagaraSystem'/Game/AddContent/KTP_Effect/Particles/Bottom/Bottom05-08.Bottom05-08'"));
			ensure(Asset.Object);
			AttackRangeEffect = Asset.Object;
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
			//ScreamTimeline.SetLooping(true);
			//ScreamTimeline.SetTimelineLengthMode(ETimelineLengthMode::TL_LastKeyFrame); // 타임라인 길이를 마지막 키프레임까지로 설정합니다.
			//ScreamTimeline->OnTimelineFinished.AddDynamic(this, &AMonster::OnFinishFire); // 타임라인이 완료될 때 호출될 함수 설정
			
			FOnTimelineEvent TimelineFinishCallback;
			TimelineFinishCallback.BindUFunction(this, FName("FinishFire"));
			ScreamTimeline.SetTimelineFinishedFunc(TimelineFinishCallback);
		}
		
}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	{
		MonsterAnim = Cast<UMonsterAnimInstance>(SkeletalMeshComponent->GetAnimInstance());
	}
	FVector HeadPosition = SkeletalMeshComponent->GetBoneLocation(TEXT("head"));
	StatusWidget->SetWorldLocation(HeadPosition + FVector(0.0f, 0.0f, 60.0f));

	UUserWidget* StatusUserWidget = StatusWidget->GetWidget();
	if (StatusUserWidget)
	{
		MonsterStatusUserWidget = Cast<UStatusbarUserWidget>(StatusUserWidget);
		if (MonsterStatusUserWidget)
		{
			MonsterStatusUserWidget->SetMonsterHP(this);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Error"));
		}
	}

	BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	//FireScream();
	//AttackRange();

}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ScreamTimeline.TickTimeline(DeltaTime);
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController && (IsMove || IsRange))
	{
		FVector PlayerLocation = PlayerController->GetPawn()->GetActorLocation();
		FVector MonsterLocation = GetActorLocation();
		FVector DirectionToPlayer = PlayerLocation - MonsterLocation;
		DirectionToPlayer.Z = 0.f;

		FRotator MonsterRotation = FRotationMatrix::MakeFromX(DirectionToPlayer).Rotator();
		MonsterRotation.Yaw -= 90.0f;

		SetActorRotation(MonsterRotation);
	}
}

float AMonster::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	// Call the base class version of TakeDamage
	float Damage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	CurrentHP = CurrentHP - Damage;

	DisplayDamage(Damage);
	UE_LOG(LogTemp, Warning, TEXT("Boss_HP : %f"), CurrentHP);
	if (MonsterStatusUserWidget)
	{
		MonsterStatusUserWidget->SetMonsterHP(this);
	}

	if (CurrentHP <= 0.f)
	{
		IsDead = true;
	}

	return Damage;
}


//#include "UI/Damage/PrintDamageUserWidget.h"
//#include "Actors/Damage/PrintDamageTextActor.h"
	void AMonster::DisplayDamage(float InDamage)
	{
	/*	FTransform SpawnTransform = FTransform(FRotator::ZeroRotator, GetActorLocation(), FVector::OneVector);
		APrintDamageTextActor* Actor = GetWorld()->SpawnActor<APrintDamageTextActor>
			(APrintDamageTextActor::StaticClass(), SpawnTransform);
		Actor->SetWidgetText(this, InDamage, GetActorLocation() + FVector(0, 0, 100));*/
	}


void AMonster::FireScream()
{
	IsAttackFinish = false;

	if (FireScreamEffect)
	{
		SpawnedEffect = UGameplayStatics::SpawnEmitterAttached(FireScreamEffect, SkeletalMeshComponent, FName(TEXT("FireAttack")));
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

void AMonster::AttackRange()
{
	// Calculate spawn location
	IsAttackFinish = false;
	IsRange = true;

	FVector SpawnLocation = GetActorLocation(); 
	float RandomX = FMath::RandRange(SpawnLocation.X-1000.f, SpawnLocation.X +1000.f);
	float RandomY = FMath::RandRange(SpawnLocation.Y+200.f, SpawnLocation.Y +1000.f);	

	FVector SpawnActorLocation = FVector(RandomX, RandomY, 0.f); // Final spawn location

	// Spawn AttackRangeActor
	AAttackRangeActor* SpawnAttackRangeActor = GetWorld()->SpawnActor<AAttackRangeActor>(SpawnActorLocation, FRotator::ZeroRotator);
	
	AttackRangeActor = SpawnAttackRangeActor;
	AttackRangeLocation = AttackRangeActor->GetActorLocation();
	AttackRangeActor->BoxCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	GetWorldTimerManager().SetTimer(DelayTimerHandle, this, &AMonster::RangeSpawnDelay, 1.0f, false);

	

}

void AMonster::MonsterHitAttackTrace(FName SocketName, FVector Location)
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this); // Ignore sel

	if (SkeletalMeshComponent)
	{
		FVector SocketLocation = SkeletalMeshComponent->GetSocketLocation(SocketName);
		FVector SphereLocation = SocketLocation + Location; // Move 200 units in the negative Z direction

		FHitResult HitResult;
		FCollisionQueryParams CollisionQueryParams(NAME_None, false, this);
		bool bHit = UKismetSystemLibrary::SphereTraceSingle(
			GetWorld(),
			SphereLocation,
			SphereLocation,
			100.f,
			UEngineTypes::ConvertToTraceType(ECC_GameTraceChannel2), // Adjust to your specific trace channel
			false, // bTraceComplex
			ActorsToIgnore, // Actors to ignore
			EDrawDebugTrace::ForDuration, // Debug draw type
			HitResult,
			true // Ignore self
		);

		// Debug visualization
	//	

		if (bHit && HitResult.GetActor())
		{
			AActor* HitActor = HitResult.GetActor();
			if (HitActor->IsA<ACharacter>())
			{
				UE_LOG(LogTemp, Warning, TEXT("Mouth attack hit: %s"), *HitActor->GetName());
				float Damage = HitAttackDamage; 
				MonsterAttackDamage(HitActor, Damage);
			}
		}
	}
}

void AMonster::HandleScreamProgress(float Value)
{
	BoxCollision->SetRelativeLocation(FVector(Value, 720, -100));
	//충돌 디버그박스
	DrawDebugBox(GetWorld(), BoxCollision->GetComponentLocation(), BoxCollision->GetScaledBoxExtent(), FColor::Red, false, -1, 0, 2);
	
}

void AMonster::OnMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	GetWorldTimerManager().SetTimer(DelayTimerHandle, this, &AMonster::ScreamDelay, 1.0f, false); // 1초 지연
	
}

void AMonster::OnBoxCollisionOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor && OtherActor != this)
	{
		UE_LOG(LogTemp, Warning, TEXT("BoxCollision overlapped with: %s"), *OtherActor->GetName());
		float Damage = FireAttackDamage; // Example damage value
		MonsterAttackDamage(OtherActor, Damage);
	}
}

void AMonster::FinishFire()
{
	if (TimeLineCnt == 1) {
		IsScream = false;
		SpawnedEffect->DestroyComponent();
		IsAttackFinish = true;
		TimeLineCnt = 0;
	}
	else
	{
		++TimeLineCnt;
		//GetWorldTimerManager().SetTimer(DelayTimerHandle, this, &AMonster::ScreamDelay, 1.0f, false); // 1초 지연
		ScreamTimeline.PlayFromStart();
	}
}

void AMonster::MonsterAttackDamage(AActor* OtherActor, float Damage)
{
	ACharacter* Player = Cast<ACharacter>(OtherActor);
	if (Player)
	{
		UGameplayStatics::ApplyDamage(Player, Damage, GetController(), this, UDamageType::StaticClass());
	}
}

void AMonster::ScreamDelay()
{
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	IsScream = true;
	ScreamTimeline.PlayFromStart();
}

void AMonster::RangeSpawnDelay()
{
	AttackRangeActor->StaticMesh->SetVisibility(false);
	
	AttackRangeActor->BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);

	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), AttackRangeEffect, AttackRangeLocation, FRotator::ZeroRotator, FVector(1.0,1.0,1.0), true, true, ENCPoolMethod::None, true);

	GetWorldTimerManager().SetTimer(DelayTimerHandle, this, &AMonster::DestroyRangeActor, 2.0f, false);
}

void AMonster::DestroyRangeActor()
{
	AttackRangeActor->Destroy();

	if (RangeCnt == 5) {
		RangeCnt = 1;
		IsRange = false;
		IsAttackFinish = true;
		return;
	}
	else
	{
		++RangeCnt;
		AttackRange();
	}
}



