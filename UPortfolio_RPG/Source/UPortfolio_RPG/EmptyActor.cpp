// Fill out your copyright notice in the Description page of Project Settings.

/*#include "NavigationSystem.h"
#include "EmptyActor.h"

// Sets default values
AEmptyActor::AEmptyActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEmptyActor::BeginPlay()
{
    Super::BeginPlay();

    

    // Get the world
    UWorld* World = GetWorld();
    if (World)
    {
        // Get the navigation system
        UNavigationSystemV1* NavSystem = FNavigationSystem::GetCurrent<UNavigationSystemV1>(World);
        if (NavSystem)
        {
            // Get the navigation mesh bounds
            FBox Bounds = NavSystem->GetNavigableWorldBounds();

            // Generate a random point within the navigation mesh bounds
            FVector RandomLocation = FMath::RandPointInBox(Bounds);

            // Set the actor's location to the random location
            SetActorLocation(RandomLocation);
        }
    }
        
	
}

// Called every frame
void AEmptyActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector AEmptyActor::GetEmptyActorLocation() const
{
	return FVector();
}

*/