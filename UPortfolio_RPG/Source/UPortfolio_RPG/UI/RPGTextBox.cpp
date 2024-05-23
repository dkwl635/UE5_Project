// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/RPGTextBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UObject/UnrealType.h"
#include "UI/UIManager.h"

void URPGTextBox::NativeConstruct()
{
	YesButton->OnClicked.AddDynamic(this, &URPGTextBox::OnClickedYesButton);
	NoButton->OnClicked.AddDynamic(this, &URPGTextBox::OnClickedNoButton);
}

void URPGTextBox::SetYesNoButton(FOnButtonCallBack NewYesButtonFunc, FOnButtonCallBack NewNoButtonFunc, FText NewBoxText)
{
	this->YesButtonFunc = NewYesButtonFunc;
	this->NoButtonFunc = NewNoButtonFunc;
	BoxInfo->SetText(NewBoxText);
}

void URPGTextBox::OnClickedYesButton()
{
	if (YesButtonFunc.IsBound())
	{
		YesButtonFunc.Execute();
	}
	
	AUIManager::UIManager->HideUI(this->UI_Type);

}

void URPGTextBox::OnClickedNoButton()
{
	if (NoButtonFunc.IsBound())
	{
		NoButtonFunc.Execute();
	}



	AUIManager::UIManager->HideUI(this->UI_Type);

}
