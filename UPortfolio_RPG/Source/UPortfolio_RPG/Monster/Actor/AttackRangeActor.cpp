// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Actor/AttackRangeActor.h"
#include "Monster/Monster.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AAttackRangeActor::AAttackRangeActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
    BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollisionComponent"));
    {
        static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
        ensure(Asset.Object);
        StaticMesh->SetStaticMesh(Asset.Object);
    }
    {
        static ConstructorHelpers::FObjectFinder<UMaterialInterface> Asset(TEXT("/Script/Engine.Material'/Game/KSH/Character/Skill/Material/M_Hotdog_Spark_VLerp_COLOUR.M_Hotdog_Spark_VLerp_COLOUR'"));
        ensure(Asset.Object);
        StaticMesh->SetMaterial(0, Asset.Object);
    }

    RootComponent = StaticMesh;
    BoxCollision->SetupAttachment(RootComponent);

    StaticMesh->SetWorldScale3D(FVector(3.f, 3.f, 0.005f));
    BoxCollision->SetRelativeLocation(FVector(0.f, 0.f, 2200.f));
    BoxCollision->SetBoxExtent(FVector(30.f, 30.f, 1000.f));

    BoxCollision->SetCollisionProfileName(TEXT("MonsterActor"));

    // Bind overlap event
    BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AAttackRangeActor::OnBoxBeginOverlap);

}

// Called when the game starts or when spawned
void AAttackRangeActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAttackRangeActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAttackRangeActor::OnBoxBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("BoxCollision Overlapped"));

    // Assuming AAttackRangeActor has access to an instance of AMonster
    AMonster* Monster = Cast<AMonster>(GetOwner());
    if (Monster)
    {
        float Damage = Monster->RangeAttackDamage; // Example damage value
        Monster->MonsterAttackDamage(OtherActor, Damage);
    }
}

