// Fill out your copyright notice in the Description page of Project Settings.
#include "NPC/NPC.h"
#include "NPCManager.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkinnedMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/GameplayStatics.h"




// Sets default values
ANPC::ANPC()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	BodyCollision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("CapsuleComponent"));
	Body = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Body"));
	TriggerCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereTrigger"));
	NPCCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("NPCCamera"));
	TopMessage = CreateDefaultSubobject<UWidgetComponent>(TEXT("TopMssage"));
	
	
	SetRootComponent(BodyCollision);
	Body->SetupAttachment(GetRootComponent());
	TriggerCollision->SetupAttachment(GetRootComponent());
	NPCCamera->SetupAttachment(GetRootComponent());
	TopMessage->SetupAttachment(GetRootComponent());
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();

	AActor* Find = UGameplayStatics::GetActorOfClass(GetWorld(), ANPCManager::StaticClass());
	NPCManager = Cast<ANPCManager>(Find);
	ensure(NPCManager.IsValid());
	
	TopMessage->SetVisibility(false);
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPC::BeginOverlapTrigger()
{
	if (NPCManager.IsValid())
	{
		NPCManager->BeginOverlapPlayer(this);
	}
	
	TopMessage->SetVisibility(true);
}

void ANPC::EndOverlapTrigger()
{
	if (NPCManager.IsValid())
	{
		NPCManager->EndOverlapPlayer(this);
	}

	TopMessage->SetVisibility(false);
}

void ANPC::StartInteraction()
{
	TopMessage->SetVisibility(false);
}

void ANPC::EndInteraction()
{
	TopMessage->SetVisibility(true);
}

