
#include "CyberpunkHUD.h"
#include "UI/DialogueWidget.h"

void ACyberpunkHUD::BeginPlay()
{
	if (ActiveDlgBP)
	{
		ActiveDialogue = CreateWidget<UDialogueWidget>(GetWorld(), ActiveDlgBP);
		if (ActiveDialogue)
		{
			ActiveDialogue->AddToViewport();
			ActiveDialogue->SetVisibility(ESlateVisibility::Hidden);
		}
	}

	if (PassiveDlgBP)
	{
		PassiveDialogue = CreateWidget<UDialogueWidget>(GetWorld(), PassiveDlgBP);
		if (PassiveDialogue)
		{
			PassiveDialogue->AddToViewport();
			PassiveDialogue->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void ACyberpunkHUD::BeginDialogue(bool Active)
{
	if (Active && ActiveDialogue)
	{
		ActiveDialogue->SetVisibility(ESlateVisibility::Visible);
	}
	else if (ActiveDialogue)
	{
		PassiveDialogue->SetVisibility(ESlateVisibility::Visible);
	}
}

void ACyberpunkHUD::UpdateDialogue(FName Name, const FText Text)
{
	if (ActiveDialogue && ActiveDialogue->IsVisible())
	{
		ActiveDialogue->UpdateDialogue(Name, Text);
	}
	else if (PassiveDialogue && PassiveDialogue->IsVisible())
	{
		PassiveDialogue->UpdateDialogue(Name, Text);
	}
}

void ACyberpunkHUD::ShowDialogueOptions(TArray<FText> Options)
{
	if (ActiveDialogue && ActiveDialogue->IsVisible())
	{
		ActiveDialogue->ShowDialogueOptions(Options);
	}
}

void ACyberpunkHUD::EndDialogue()
{
	if (ActiveDialogue)
	{
		ActiveDialogue->SetVisibility(ESlateVisibility::Hidden);
	}

	if (PassiveDialogue)
	{
		PassiveDialogue->SetVisibility(ESlateVisibility::Hidden);
	}
}
