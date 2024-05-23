// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Skill/RedDust.h"
#include "Enemy/Enemy.h"
#include "Kismet/GameplayStatics.h"
#include "Actors/Controller/BasicPlayerController.h"
#include "Actors/PlayerCharacter/PlayerCharacter.h"
#include "Components/StatusComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraSystem.h"
#include "Engine/DamageEvents.h"

ARedDust::ARedDust()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	Effect = CreateDefaultSubobject<UNiagaraComponent>(TEXT("Niagara"));
	SetRootComponent(StaticMesh);
	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
		ensure(Asset.Object);
		StaticMesh->SetStaticMesh(Asset.Object);
	}
	{
		static ConstructorHelpers::FObjectFinder<UMaterial> Asset(TEXT("/Script/Engine.Material'/Game/KSH/Character/Skill/Material/MT_Invisible.MT_Invisible'"));
		ensure(Asset.Object);
		StaticMesh->SetMaterial(0, Asset.Object);
	}
	{
		static ConstructorHelpers::FObjectFinder<UNiagaraSystem> Asset(TEXT("/Script/Niagara.NiagaraSystem'/Game/KSH/Character/Skill/Effect/Slash.Slash'"));
		ensure(Asset.Object);
		Effect->SetAsset(Asset.Object);
	}
	{
		static ConstructorHelpers::FObjectFinder<UAnimMontage> Asset(TEXT("/Script/Engine.AnimMontage'/Game/KSH/Character/Animation/Skill/RedDust_Montage.RedDust_Montage'"));
		ensure(Asset.Object);
		this->Montage = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UTexture2D> Asset(TEXT("/Script/Engine.Texture2D'/Game/KSH/Character/Skill/Icon/RedDust.RedDust'"));
		ensure(Asset.Object);
		this->Sk_Image = Asset.Object;
	}
	{
		static ConstructorHelpers::FObjectFinder<UTexture2D> Asset(TEXT("/Script/Engine.Texture2D'/Game/KSH/Character/Skill/Icon/RedDustDark.RedDustDark'"));
		ensure(Asset.Object);
		this->Sk_Image_Cool = Asset.Object;
	}
	StaticMesh->SetRelativeLocation(FVector(250., 0., -88.));
	StaticMesh->SetRelativeScale3D(FVector(6., 1, 1.75));
	StaticMesh->SetCollisionProfileName(TEXT("PlayerSkill"));
	StaticMesh->bHiddenInGame = false;
	Effect->SetupAttachment(StaticMesh);
	Effect->SetRelativeLocation(FVector(-36, 0, 120));
	Effect->SetRelativeRotation(FRotator(-41, 29, 48));

	Sk_Name = TEXT("Red Dust");
	Sk_Desc = FText::FromString(TEXT("검을 올려쳐 공격한다."));
	Sk_CoolTime = 3.f;
	Sk_Damage = 50.f;
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

void ARedDust::OnAttack(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABasicPlayerController* Controller = Cast<ABasicPlayerController>(UGameplayStatics::GetPlayerController(this, 0));
	APlayerCharacter* Player = Cast<APlayerCharacter>(Controller->GetPawn());
	float Damage = FMath::RandRange(Player->GetStatusComponent()->GetMinAttackDamage(), Player->GetStatusComponent()->GetMaxAttackDamage());
	Damage += Sk_Damage;

	AEnemy* Enemy = Cast<AEnemy>(OtherActor);
	if (Enemy)
	{
		UE_LOG(LogTemp, Warning, TEXT("RedDust Hit!"));
		FDamageEvent DamageEvent;
		Enemy->TakeDamage(Damage, DamageEvent, Controller, Player);
	}
}
