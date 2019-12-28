// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DialogueWidget.generated.h"

UCLASS()
class CYBERPUNKUNREAL_API UDialogueWidget : public UUserWidget
{
    GENERATED_BODY()
    float shownAmount;
    float shownTimeCountdown;
    FText text;
public:
    void UpdateDialogue(FName InName, const FText Text);
    virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

    UFUNCTION(BlueprintCallable, Category = Dialogue)
    void EndCrawl();

    inline void SkipTextCrawl() { shownAmount = text.ToString().Len(); };

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FName PName;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
    FString Speech;

    UPROPERTY(EditAnywhere)
    float CrawlSpeed;

    UPROPERTY(EditAnywhere)
    float ShownTime;

    UFUNCTION(BlueprintNativeEvent)
    void ShowDialogueOptions(const TArray<FText>& Options);
    void ShowDialogueOptions_Implementation(const TArray<FText>& Options);
};

USTRUCT(BlueprintType, Blueprintable)
struct FDialogueData
{
    GENERATED_USTRUCT_BODY()

public:

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
        TMap<FName, int32> Integers;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
        TMap<FName, int32> Floats;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
        TMap<FName, FName> Names;

    UPROPERTY(BlueprintReadWrite, VisibleAnywhere)
        TSet<FName> TrueBools;
};
