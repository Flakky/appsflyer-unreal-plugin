//
//  AppsFlyerSDKCallback.h
//
//  Created by AndreyG-AF on 1/31/19.
//  Copyright © 2019 Epic Games, Inc. All rights reserved.
//

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AppsFlyerSDKCallbacks.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAppOpenAttribution, const FString&, attributionData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConversionDataReceived, const struct FAppsFlyerConversionData&, installData);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAppOpenAttributionFailure, const FString&, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnConversionDataRequestFailure, const FString&, error);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnValidateAndLogInAppPurchaseComplete, const struct FAppsFlyerPurchaseResponse&, Response);

UCLASS(ClassGroup=(AppsFlyerSDK), meta=(BlueprintSpawnableComponent))
class APPSFLYERSDK_API UAppsFlyerSDKCallbacks : public UActorComponent
{
    GENERATED_BODY()
    
public:
    
    UAppsFlyerSDKCallbacks(const FObjectInitializer& ObjectInitializer);
    
    
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "AppsFlyerSDK")
    FOnAppOpenAttribution OnAppOpenAttribution;
    
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "AppsFlyerSDK")
    FOnConversionDataReceived OnConversionDataReceived;
    
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "AppsFlyerSDK")
    FOnAppOpenAttributionFailure OnAppOpenAttributionFailure;
    
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "AppsFlyerSDK")
    FOnConversionDataRequestFailure OnConversionDataRequestFailure;
    
    /**
     * Called when ValidateAndLogInAppPurchase completes
     * @param Response - Contains the validation result, success data, or error information
     */
    UPROPERTY(BlueprintAssignable, BlueprintCallable, Category = "AppsFlyerSDK")
    FOnValidateAndLogInAppPurchaseComplete OnValidateAndLogInAppPurchaseComplete;
    
};
