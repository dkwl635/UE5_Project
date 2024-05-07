// Fill out your copyright notice in the Description page of Project Settings.
#include "NPC/NPC.h"
#include "NPCManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Components/SkinnedMeshComponent.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
ANPC::ANPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	//TriggerCollision = CreateDefaultSubobject<UShapeComponent>(TEXT("UShapeComponent"));
	TriggerCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTrigger"));
	SetRootComponent(BodyCollision);
	Body->SetupAttachment(GetRootComponent());
	TriggerCollision->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();

	AActor* Find = UGameplayStatics::GetActorOfClass(GetWorld(), ANPCManager::StaticClass());
	NPCManager = Cast<ANPCManager>(Find);
	ensure(NPCManager);
	
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

