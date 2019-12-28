#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CyberpunkGameMode.generated.h"

UCLASS()
class CYBERPUNKUNREAL_API ACyberpunkGameMode : public AGameModeBase
{
	GENERATED_BODY()

	class UDlgContext* DialogueContext;
	class ACyberpunkHUD* HUD;
	bool showingOptions;
	void UpdateDialogue();
public:
	UFUNCTION(BlueprintPure, Category = Dialogue)
	inline bool IsDialogueActive() { return DialogueContext != nullptr; };

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	void StartPassiveDialogue(UDlgDialogue* Dialogue, UObject* OtherParticipant, float Time);

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	void StartInterruptingDialogue(UDlgDialogue* Dialogue, UObject* OtherParticipant);
	
	UFUNCTION(BlueprintCallable, Category = Dialogue)
	void SelectOption(int Option);

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	void ProgressDialogue();

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	void ShowOptions();

	UFUNCTION(BlueprintCallable, Category = Dialogue)
	void EndDialogue();

	void BeginPlay() override;
};
