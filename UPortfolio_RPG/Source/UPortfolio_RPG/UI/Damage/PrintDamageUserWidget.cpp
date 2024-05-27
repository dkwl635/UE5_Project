// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Damage/PrintDamageUserWidget.h"
#include "Enemy/Enemy.h"

void UPrintDamageUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FWidgetAnimationDynamicEvent Delegate;
	Delegate.BindUFunction(this, FName("OnAnimFinished"));
	BindToAnimationFinished(FloatingText_Enemy, Delegate);
	BindToAnimationFinished(FloatingText_Player, Delegate);
}

void UPrintDamageUserWidget::SetDamage(float InDamage)
{
	FText Damage = FText::AsNumber(int(InDamage));
	if(DamageText)
	{
		DamageText->SetText(Damage);
	}
}

void UPrintDamageUserWidget::SetOwner(AActor* Owner)
{
	if (Owner)
		OwningActor = Owner;
}

void UPrintDamageUserWidget::PlayAnimFromPawn(APawn* Pawn)
{
	if (AEnemy* Enemy = Cast<AEnemy>(Pawn))
	{
		PlayAnimation(FloatingText_Enemy);
	}
	else
	{
		PlayAnimation(FloatingText_Player);
	}
}

void UPrintDamageUserWidget::OnAnimFinished()
{
	UE_LOG(LogTemp, Log, TEXT("Damage animation finished!"));
	OwningActor->Destroy();
}
