// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/Damage/PrintDamageUserWidget.h"

void UPrintDamageUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FWidgetAnimationDynamicEvent Delegate;
	Delegate.BindUFunction(this, FName("OnAnimFinished"));
	BindToAnimationFinished(FloatingText, Delegate);

	PlayAnimation(FloatingText);
}

void UPrintDamageUserWidget::SetDamage(float InDamage)
{
	FText Damage = FText::AsNumber(InDamage);
	if(DamageText)
		DamageText->SetText(Damage);
}

void UPrintDamageUserWidget::SetOwner(AActor* Owner)
{
	if (Owner)
		OwningActor = Owner;
}

void UPrintDamageUserWidget::OnAnimFinished()
{
	UE_LOG(LogTemp, Log, TEXT("Damage animation finished!"));
	OwningActor->Destroy();
}
