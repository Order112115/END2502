// Fill out your copyright notice in the Description page of Project Settings.


#include "Both/ButtonWithText.h"
#include "Components/TextBlock.h" 
#include "Components/Button.h"

void UButtonWithText::NativePreConstruct()
{
	
	if (Information)
	{
		Information->SetText(Info);
	}
}

void UButtonWithText::NativeConstruct()
{

	if (BackgroundButton)
	{
		BackgroundButton->OnClicked.AddDynamic(this, &UButtonWithText::HandleClickButton);
	}
}

void UButtonWithText::HandleClickButton()
{
	OnClickedEvent.Broadcast();
}



