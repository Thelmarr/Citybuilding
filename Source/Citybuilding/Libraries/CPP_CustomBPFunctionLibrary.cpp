// Fill out your copyright notice in the Description page of Project Settings.


#include "CPP_CustomBPFunctionLibrary.h"
#include "Classes/Engine/Engine.h"

FString UCPP_CustomBPFunctionLibrary::GetLeadingZerosInt(int NumberToConvert, int Digits) {
	//Get digits of input number
	//correct for 0 and 1 input
	int NumSize = 0;
	if (NumberToConvert == 0 || NumberToConvert == 1 || NumberToConvert < 1 && NumberToConvert > 0) {
		NumSize = 1;
	}
	else if (NumberToConvert > 1) {
		//ceil of log base 10 gives number of digits (i.e. log10 of 11 = 2)
		float WholeLogs = FMath::LogX(10.f, NumberToConvert);
		NumSize = FMath::CeilToInt(WholeLogs);

		//increase number size for logs of base 10 (i.e. 10, 100, 1000, etc)
		//otherwise: rounding error

		if (NumberToConvert % 10 == 0 || NumberToConvert % 100 == 0 || NumberToConvert % 1000 == 0) {
			NumSize++;
		}
	}


	//Determine number of leading zeros needed
	int NumDif = Digits - NumSize;

	if (NumDif <= 0) {
		return FString::FromInt(NumberToConvert);
	}
	else {
		FString ZeroString = "";
		for (int i = 0; i < NumDif; i++) {
			ZeroString.Append("0");
		}
		return ZeroString.Append(FString::FromInt(NumberToConvert));
	}
}