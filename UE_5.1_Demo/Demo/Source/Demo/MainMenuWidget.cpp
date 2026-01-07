// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "AppsFlyerSDKCallbacks.h"
#include "Engine/World.h"
#include "EngineUtils.h"
#include "GameFramework/Actor.h"

DEFINE_LOG_CATEGORY(LogMainMenu);

void UMainMenuWidget::NativeConstruct()
{
    Super::NativeConstruct();

    if (ensureMsgf(DoPurchaseButton, TEXT("PlayButton is missing or name mismatch in WB_MainMenu")))
    {
        DoPurchaseButton->OnClicked.AddDynamic(this, &UMainMenuWidget::DoPurchaseButtonClicked);
    }
    // Try to find any UAppsFlyerSDKCallbacks in the world
    for (TActorIterator<AActor> ActorIterator(GetWorld()); ActorIterator; ++ActorIterator)
    {
        if (UAppsFlyerSDKCallbacks* Callbacks = (*ActorIterator)->FindComponentByClass<UAppsFlyerSDKCallbacks>())
        {
            UE_LOG(LogMainMenu, Log, TEXT("Found UAppsFlyerSDKCallbacks component on actor: %s"), *(*ActorIterator)->GetName());
            Callbacks->OnValidateAndLogInAppPurchaseComplete.AddDynamic(this, &UMainMenuWidget::OnValidateAndLogInAppPurchaseComplete);
            break;
        }
    }
}

void UMainMenuWidget::DoPurchaseButtonClicked()
{
    UE_LOG(LogMainMenu, Log, TEXT("DoPurchaseButtonClicked clicked!"));
    
    // Create purchase details
    FAFSDKPurchaseDetails PurchaseDetails;
    PurchaseDetails.ProductId = TEXT("com.appsflyer.product.one");
    PurchaseDetails.TransactionId = TEXT("transaction_123");
    PurchaseDetails.PurchaseType = EAFPurchaseType::OneTimePurchase;
    
    // Optional additional details
    TMap<FString, FString> PurchaseAdditionalDetails;
    PurchaseAdditionalDetails.Add(TEXT("custom_data"), TEXT("custom_value"));
    
    // Call ValidateAndLogInAppPurchase (results will be broadcast via multicast delegate)
    UAppsFlyerSDKBlueprint::ValidateAndLogInAppPurchase(PurchaseDetails, PurchaseAdditionalDetails);
}

void UMainMenuWidget::OnValidateAndLogInAppPurchaseComplete(const FAppsFlyerPurchaseResponse& Response)
{
    switch (Response.Status)
    {
        case EAFValidateAndLogStatus::Success:
            UE_LOG(LogMainMenu, Log, TEXT("ValidateAndLogInAppPurchase succeeded"));
            UE_LOG(LogMainMenu, Log, TEXT("ResultJson: %s"), *Response.ResultJson);
            break;
            
        case EAFValidateAndLogStatus::Error:
            UE_LOG(LogMainMenu, Error, TEXT("ValidateAndLogInAppPurchase error: %s"), *Response.Error);
            break;
    }
}
