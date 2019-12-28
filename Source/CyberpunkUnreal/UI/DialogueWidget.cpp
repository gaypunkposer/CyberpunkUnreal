#include "DialogueWidget.h"
#include "CyberpunkGameMode.h"

void UDialogueWidget::UpdateDialogue(FName InName, const FText Text)
{
	PName = InName;
	text = Text;
	shownAmount = 0;
	shownTimeCountdown = ShownTime;
}

void UDialogueWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	//Show the text character by character
	UE_LOG(LogTemp, Warning, TEXT("I AM WIDGET AND I SHALL TICK"));
	if (shownAmount < text.ToString().Len())
	{
		shownAmount += InDeltaTime * CrawlSpeed;
	}
	else
	{
		//Once all the text has been shown, start counting down to the next line
		if (ShownTime > 0)
		{
			shownTimeCountdown -= InDeltaTime;
			if (shownTimeCountdown <= 0)
			{
				Cast<ACyberpunkGameMode>(GetWorld()->GetAuthGameMode())->ProgressDialogue();
			}
		} 
		else
		{
			Cast<ACyberpunkGameMode>(GetWorld()->GetAuthGameMode())->ShowOptions();
		}
	}

	Speech = text.ToString().Left((int)shownAmount);
}

void UDialogueWidget::EndCrawl()
{
	shownAmount = text.ToString().Len();
}

void UDialogueWidget::ShowDialogueOptions_Implementation(const TArray<FText>& Options)
{

}
