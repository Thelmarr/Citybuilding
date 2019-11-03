// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "string.h"
#include "CPP_CustomBPFunctionLibrary.generated.h"


/**
 * 
 */
UCLASS(BlueprintType)
class CITYBUILDING_API UCPP_CustomBPFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Conversions")
	static FString GetLeadingZerosInt(int NumberToConvert, int Digits);
};

#pragma region ENUMs

UENUM(BlueprintType)
namespace EMonthName {
	enum Type {
		January,
		February,
		March,
		April,
		May,
		June,
		July,
		August,
		September,
		October,
		November,
		December
	};
}

#pragma endregion ENUMs

#pragma region STRUCTs



#pragma endregion STRUCTs