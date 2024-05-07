// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC/NPCManager.h"
#include "NPC/NPC.h"

// Sets default values
ANPCManager::ANPCManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANPCManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANPCManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANPCManager::BeginOverlapPlayer(ANPC* Target)
{
}

void ANPCManager::EndOverlapPlayer(ANPC* Target)
{
}

