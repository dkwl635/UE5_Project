// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Skill/SpinningAttack.h"
#include "Enemy/Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Controller/BasicPlayerController.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "Components/StatusComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Engine/DamageEvents.h"

ASpinningAttack::ASpinningAttack()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	SetRootComponent(StaticMesh);
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Game/KSH/Character/Skill/Mesh/SM_Torus_Simple.SM_Torus_Simple'"));
		ensure(Asset.Object);
		StaticMesh->SetStaticMesh(Asset.Object);
	}
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> Asset(TEXT("/Script/Engine.Material'/Game/KSH/Character/Skill/Material/MT_Invisible.MT_Invisible'"));
		ensure(Asset.Object);
		StaticMesh->SetMaterial(0, Asset.Object);
	}
	{
		static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Asset(TEXT("/Script/Niagara.NiagaraSystem'/Game/KSH/Character/Skill/Effect/Spinning.Spinning'"));
		ensure(Asset.Object);
		Effect->SetAsset(Asset.Object);
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
	
	//StaticMesh->SetRelativeLocation(FVector(0., 0., 196.));
	StaticMesh->SetRelativeScale3D(FVector(3.5, 3.5, 3.5));
	StaticMesh->SetCollisionProfileName(TEXT("PlayerSkill"));
	StaticMesh->bHiddenInGame = false;
	Effect->SetupAttachment(StaticMesh);

	Sk_Name = TEXT("Spinning Attack");
	Sk_Desc = FText::FromString(TEXT("검을 크게 휘둘러 공격한다."));
	Sk_CoolTime = 3.f;
	Sk_Damage = 30.f;
	Sk_ManaUsage = 5.f;
}

void ASpinningAttack::BeginPlay()
{
	Super::BeginPlay();

	StaticMesh->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnAttack);
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