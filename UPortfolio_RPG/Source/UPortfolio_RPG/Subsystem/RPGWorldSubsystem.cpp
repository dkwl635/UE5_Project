// Fill out your copyright notice in the Description page of Project Settings.


#include "Subsystem/RPGWorldSubsystem.h"
#include "NPC/NPCManager.h"
#include "Components/DropItemManager.h"
#include "UI/UIManager.h"

URPGWorldSubsystem::URPGWorldSubsystem()
{ 
    {
        static ConstructorHelpers::FClassFinder<AActor> ActorBPClass(TEXT("/Script/Engine.Blueprint'/Game/KJW/BP_Manager/BP_NPCManager.BP_NPCManager_C'"));
        if (ActorBPClass.Succeeded())
        {
            NPCManagerBP = ActorBPClass.Class;
        }
    }
    {
        static ConstructorHelpers::FClassFinder<AActor> ActorBPClass(TEXT("/Script/Engine.Blueprint'/Game/KJW/BP_Manager/BP_DropItemManager.BP_DropItemManager_C'"));
        if (ActorBPClass.Succeeded())
        {
            DropItemManagerBP = ActorBPClass.Class;
        }
    }
    {
        static ConstructorHelpers::FClassFinder<AActor> ActorBPClass(TEXT("/Script/Engine.Blueprint'/Game/KJW/BP_Manager/BP_UIManager.BP_UIManager_C'"));
        if (ActorBPClass.Succeeded())
        {
            UIManagerBP = ActorBPClass.Class;
        }
    }
}

void URPGWorldSubsystem::OnWorldBeginPlay(UWorld& InWorld)
{
    FVector Location = FVector(0.0f, 0.0f, 0.0f);
    FRotator Rotation = FRotator(0.0f, 0.0f, 0.0f);
    UWorld* World = (&InWorld);

    if (!World)
    {
        return;
    }

    if (NPCManagerBP)
    {
        AActor* SpawnedActor = World->SpawnActor<AActor>(NPCManagerBP, Location, Rotation);
        if (SpawnedActor)
        {
            NPCManager = Cast<ANPCManager>(SpawnedActor);
        }
    }

    if (DropItemManagerBP)
    {
        AActor* SpawnedActor = World->SpawnActor<AActor>(DropItemManagerBP, Location, Rotation);
        if (SpawnedActor)
        {
            DropItemManager = Cast<ADropItemManager>(SpawnedActor);
        }
    }
    
    if (UIManagerBP)
    {
        AActor* SpawnedActor = World->SpawnActor<AActor>(UIManagerBP, Location, Rotation);
        if (SpawnedActor)
        {
            UIManager = Cast<AUIManager>(SpawnedActor);
            UIManager->SpawnUI();
        }
    }
}

void URPGWorldSubsystem::Deinitialize()
{
    DropItemManager = nullptr;
    NPCManager = nullptr;
    UIManager = nullptr;
}
