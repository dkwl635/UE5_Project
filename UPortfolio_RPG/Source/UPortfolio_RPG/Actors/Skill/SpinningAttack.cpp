// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Skill/SpinningAttack.h"
#include "Enemy/Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Controller/BasicPlayerController.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "Components/StatusComponent.h"
#include "Engine/DamageEvents.h"

ASpinningAttack::ASpinningAttack()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	SetRootComponent(StaticMesh);
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Torus.Shape_Torus'"));
		ensure(Asset.Object);
		StaticMesh->SetStaticMesh(Asset.Object);
	}
	{
		static ConstructorHelpers::FObjectFinder<UAnimMontage> Asset(TEXT("/Script/Engine.AnimMontage'/Game/KSH/Character/Animation/Skill/SpinningAttack_Montage.SpinningAttack_Montage'"));
		ensure(Asset.Object);
		this->Montage = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UTexture2D> Asset(TEXT("/Script/Engine.Texture2D'/Game/KSH/Character/Skill/Icon/TempestSlash.TempestSlash'"));
		ensure(Asset.Object);
		this->Sk_Image = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UTexture2D> Asset(TEXT("/Script/Engine.Texture2D'/Game/KSH/Character/Skill/Icon/TempestSlashDark.TempestSlashDark'"));
		ensure(Asset.Object);
		this->Sk_Image_Cool = Asset.Object;
	}
	StaticMesh->SetRelativeScale3D(FVector(4.565000, 3.735000, 1.660000));
	StaticMesh->SetCollisionProfileName(TEXT("PlayerSkill"));
	StaticMesh->bHiddenInGame = false;

	Sk_Name = TEXT("Spinning Attack");
	Sk_Desc = FText::FromString(TEXT("검을 크게 휘둘러 공격한다."));
	Sk_CoolTime = 3.f;
	Sk_Damage = 10.f;
	Sk_ManaUsage = 5.f;
}

void ASpinningAttack::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnAttack);
}

float ASpinningAttack::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void ASpinningAttack::OnAttack(UPrimitiveComponent* OverlappedComp,
	AActor* OtherActor,
	UPrimitiveComponent* OtherComp,
	int32 OtherBodyIndex,
	bool bFromSweep,
	const FHitResult& SweepResult)
{
	ABasicPlayerController* Controller = Cast<ABasicPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	APlayerCharacter* Player = Cast<APlayerCharacter>(Controller->GetPawn());
	float Damage = Sk_Damage + Player->GetStatusComponent()->GetAttackDamage();
	
	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if(Enemy)
	{
		UE_LOG(LogTemp, Warning, TEXT("Spinning Attack Hit!"));
		FDamageEvent DamageEvent;
		Enemy->TakeDamage(Damage, DamageEvent, Controller, Player);
	}
}