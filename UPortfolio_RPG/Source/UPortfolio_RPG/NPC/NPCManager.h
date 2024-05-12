// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NPCManager.generated.h"

UCLASS()
class UPORTFOLIO_RPG_API ANPCManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ANPCManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

public:
	void BeginOverlapPlayer(class ANPC* Target);
	void EndOverlapPlayer(class ANPC* Target);

private:
	TWeakObjectPtr<class URPGMainUserWidget> PlayerUI;
	class URPGMainUserWidget* GetPlayerUI();
public:

	UFUNCTION(BlueprintCallable)
	void StartInteractiorNPC();

	UFUNCTION(BlueprintCallable)
	void EndInteractiorNPC();

	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveStartInteractiorNPC();
	UFUNCTION(BlueprintImplementableEvent)
	void ReceiveEndInteractiorNPC();

	UFUNCTION(BlueprintCallable)
	void InteractiorNPC();
	UFUNCTION(BlueprintCallable)
	void LeaveNPC();

public:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TWeakObjectPtr<class ANPC>  CurrentNPC;
	UPROPERTY(EditAnywhere , BlueprintReadWrite)
	bool bInteractior = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> NPCUserWidget;

	class UNPCTalkBoxUserwidget* NPCTalkBoxUserwidget;

public:
	//Shop
	UFUNCTION(BlueprintCallable)
	void OpenShopUI();
};
