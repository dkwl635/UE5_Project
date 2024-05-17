// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/Monster.h"

// Sets default values
AMonster::AMonster()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMeshComponent"));

	{
		//static ConstructorHelpers::FObjectFinder<USkeletalMesh> Asset(TEXT(""));
		//ensure(Asset.Object);
		//SkeletalMeshComponent->SetSkeletalMesh(Asset.Object);
	}


	SetRootComponent(CapsuleComponent);
	SkeletalMeshComponent->SetupAttachment(GetRootComponent());


}

// Called when the game starts or when spawned
void AMonster::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMonster::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}



