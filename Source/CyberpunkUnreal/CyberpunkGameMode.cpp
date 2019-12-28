#include "CyberpunkGameMode.h"

#include "Kismet/GameplayStatics.h"
#include "UI/DialogueWidget.h"
#include "UI/CyberpunkHUD.h"
#include "DlgContext.h"
#include "DlgManager.h"

void ACyberpunkGameMode::StartInterruptingDialogue(UDlgDialogue* Dialogue, UObject* OtherParticipant)
{
	if (DialogueContext) return;
	APlayerController* player = GetWorld()->GetFirstPlayerController();
	DialogueContext = UDlgManager::StartDialogue2(Dialogue, player->GetPawn(), OtherParticipant);
	player->GetPawn()->DisableInput(player);
	player->bShowMouseCursor = true;
	HUD->BeginDialogue(true);
	UpdateDialogue();
}

void ACyberpunkGameMode::StartPassiveDialogue(UDlgDialogue* Dialogue, UObject* OtherParticipant, float Time)
{
	if (DialogueContext) return;
	APlayerController* player = GetWorld()->GetFirstPlayerController();
	DialogueContext = UDlgManager::StartDialogue2(Dialogue, player->GetPawn(), OtherParticipant);
	HUD->BeginDialogue(false);
	UpdateDialogue();
}

void ACyberpunkGameMode::SelectOption(int Option)
{
	if (!DialogueContext) return;
	if (Option >= DialogueContext->GetOptionNum() || Option < 0) return;
	if (!showingOptions)
	{
		ShowOptions();
		return;
	}

	if (!DialogueContext->ChooseChild(Option))
	{
		EndDialogue();
	}
	else
	{
		UpdateDialogue();
	}
		
}

void ACyberpunkGameMode::ProgressDialogue()
{
	if (!DialogueContext) return;
	if (DialogueContext->GetOptionNum() > 1)
	{
		ShowOptions();
		return;
	}

	SelectOption(0);
}

void ACyberpunkGameMode::ShowOptions()
{
	if (!DialogueContext) return;
	if (showingOptions) return;

	TArray<FText> options = TArray<FText>();
	for (int i = 0; i < DialogueContext->GetOptionNum(); i++)
	{
		FText option = DialogueContext->GetOptionText(i);
		if (!option.IsEmpty())
			options.Emplace(option);
	}
	HUD->ShowDialogueOptions(options);
	showingOptions = true;
}

void ACyberpunkGameMode::EndDialogue()
{
	DialogueContext = nullptr;
	APlayerController* player = GetWorld()->GetFirstPlayerController();
	player->GetPawn()->EnableInput(player);
	player->bShowMouseCursor = false;
	HUD->EndDialogue();
}

void ACyberpunkGameMode::BeginPlay()
{
	HUD = Cast<ACyberpunkHUD>(GetWorld()->GetFirstPlayerController()->GetHUD());
}

void ACyberpunkGameMode::UpdateDialogue()
{
	if (!DialogueContext) return;
	showingOptions = false;
	HUD->UpdateDialogue(DialogueContext->GetActiveNodeParticipantName(), DialogueContext->GetActiveNodeText());
	UE_LOG(LogTemp, Warning, TEXT("Active dialogue speaker: %s"), *DialogueContext->GetActiveNodeParticipantName().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Active dialogue speech: %s"), *DialogueContext->GetActiveNodeText().ToString());
}
