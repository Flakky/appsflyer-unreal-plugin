// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Button.h"
#include "AppsFlyerSDKBlueprint.h"
#include "MainMenuWidget.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(LogMainMenu, Log, All);

/**
 * 
 */
UCLASS()
class DEMO_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
    virtual void NativeConstruct() override;
    
    UPROPERTY(meta = (BindWidget))
    UButton* DoPurchaseButton;

    UFUNCTION()
    void DoPurchaseButtonClicked();

    UFUNCTION()
    void OnValidateAndLogInAppPurchaseComplete(const FAppsFlyerPurchaseResponse& Response);
};
