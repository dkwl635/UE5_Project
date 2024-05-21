// Fill out your copyright notice in the Description page of Project Settings.


#include "Actors/Damage/PrintDamageTextActor.h"
#include "Components/WidgetComponent.h"
#include "UI/Damage/PrintDamageUserWidget.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APrintDamageTextActor::APrintDamageTextActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Widget = CreateDefaultSubobject<UWidgetComponent>(TEXT("Widget"));
    Widget->SetWidgetSpace(EWidgetSpace::Screen);
    Widget->SetupAttachment(GetRootComponent());
    {
        static ConstructorHelpers::FClassFinder<UUserWidget> UI_HUD(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/KSH/MainUI/PrintDamage/UI_Damage.UI_Damage_C'"));
        if (UI_HUD.Succeeded())
        {
            Widget->SetWidgetClass(UI_HUD.Class);
        }
    }
}

void APrintDamageTextActor::SetWidgetText(float InDamage, FVector InLocation)
{
    if (Widget)
    {
        UPrintDamageUserWidget* DamageWidget = Cast<UPrintDamageUserWidget>(Widget->GetWidget());
        if (DamageWidget)
        {
            DamageWidget->SetOwner(this);
            DamageWidget->SetDamage(InDamage);
        }
    }
}

// Called when the game starts or when spawned
void APrintDamageTextActor::BeginPlay()
{
	Super::BeginPlay();
}
