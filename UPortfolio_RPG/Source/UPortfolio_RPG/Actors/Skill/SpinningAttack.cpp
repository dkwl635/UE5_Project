// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Skill/SpinningAttack.h"

ASpinningAttack::ASpinningAttack()
{
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));

	{
		static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Game/StarterContent/Shapes/Shape_Torus.Shape_Torus'"));
		ensure(Asset.Object);
		StaticMesh->SetStaticMesh(Asset.Object);
	}
	{
		static ConstructorHelpers::FObjectFinder<UMaterialInstance> Asset(TEXT("/Script/Engine.MaterialInstanceConstant'/Game/KSH/Character/Skill/Material/MI_Hotdog_Spark_VLerp_Colour_Shockwave_Slow.MI_Hotdog_Spark_VLerp_Colour_Shockwave_Slow'"));
		ensure(Asset.Object);
		StaticMesh->SetMaterial(0, Asset.Object);
	}
	StaticMesh->SetRelativeScale3D(FVector(4.565000, 3.735000, 1.660000));
	StaticMesh->SetCollisionProfileName(TEXT("PlayerSkill"));
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
	UE_LOG(LogTemp, Warning, TEXT("Skill Hit!"));
}
