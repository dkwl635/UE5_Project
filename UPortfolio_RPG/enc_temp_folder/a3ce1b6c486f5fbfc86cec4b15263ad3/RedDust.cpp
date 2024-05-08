// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Skill/RedDust.h"
#include "Enemy/Enemy.h"

ARedDust::ARedDust()
{
	this->Sk_Name = TEXT("SpinningAttack");
	this->Sk_Desc = FText::FromString(TEXT("대검을 크게 올려치며 붉은 기운을 일으킨다. 자신의 공격력이 8초 간 6% 증가하며, 공격 적중 시 407의 피해를 준다."));
	this->Sk_CoolTime = 24.f;
	this->Sk_Damage = 407.f;
	this->Sk_ManaUsage = 101.f;
	this->bSuperArmor = false;
	this->bSuperStance = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	SetRootComponent(StaticMesh);
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
		ensure(Asset.Object);
		StaticMesh->SetStaticMesh(Asset.Object);
	}
	{
		static ConstructorHelpers::FObjectFinder<UAnimMontage> Asset(TEXT("/Script/Engine.AnimMontage'/Game/KSH/Character/Animation/Skill/RedDust_Montage.RedDust_Montage'"));
		ensure(Asset.Object);
		Montage = Asset.Object;
	}

	StaticMesh->SetRelativeLocation(FVector(180., 0., -88.));
	StaticMesh->SetRelativeScale3D(FVector(2.5, 0.5, 1.75));
	StaticMesh->SetCollisionProfileName(TEXT("PlayerSkill"));
}

void ARedDust::BeginPlay()
{
	Super::BeginPlay();

	if (Montage)
		SetSkillMontage(Montage);

	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnAttack);
}

float ARedDust::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	Owner = DamageCauser;

	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ARedDust::OnAttack(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy)
	{
		UE_LOG(LogTemp, Warning, TEXT("Red Dust Hit!"));
	}
}
