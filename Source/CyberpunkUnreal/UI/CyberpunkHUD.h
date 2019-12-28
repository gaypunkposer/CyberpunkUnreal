#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CyberpunkHUD.generated.h"

UCLASS()
class CYBERPUNKUNREAL_API ACyberpunkHUD : public AHUD
{
	GENERATED_BODY()
	float passiveDlgTime;
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> ActiveDlgBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> PassiveDlgBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> GameplayInfoBP;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Widgets")
	TSubclassOf<class UUserWidget> DebugBP;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	class UDialogueWidget* ActiveDialogue;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Widgets")
	class UDialogueWidget* PassiveDialogue;

	void BeginPlay() override;
	void BeginDialogue(bool Active);
	void ShowDialogueOptions(TArray<FText> Options);
	void EndDialogue();
	void UpdateDialogue(FName Name, const FText Text);
};
