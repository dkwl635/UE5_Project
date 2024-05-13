// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Skill/RedDust.h"
#include "Enemy/Enemy.h"

ARedDust::ARedDust()
{
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
		this->Montage = Asset.Object;
	}
	StaticMesh->SetRelativeLocation(FVector(250., 0., -88.));
	StaticMesh->SetRelativeScale3D(FVector(5., 0.5, 1.75));
	StaticMesh->SetCollisionProfileName(TEXT("PlayerSkill"));
	StaticMesh->bHiddenInGame = false;

	Sk_Name = TEXT("Red Dust");
	Sk_Desc = FText::FromString(TEXT("검을 올려쳐 공격한다."));
	Sk_CoolTime = 3.f;
	Sk_Damage = 10.f;
	Sk_ManaUsage = 5.f;
}

void ARedDust::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnAttack);
}

void ARedDust::ActiveSkill(UAnimInstance* AnimInstance)
{
	Super::ActiveSkill(AnimInstance);

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
