// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Console/Cartridge.h"
#include "BullCowCartridge.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class BULLCOWGAME_API UBullCowCartridge : public UCartridge
{
	GENERATED_BODY()

	public:
		virtual void BeginPlay() override;
		virtual void OnInput(const FString& Input) override;
		void ResetTheGame();

	// Your declarations go below!
	private:
		TArray<FString> Isograms = {TEXT("helo"), TEXT("gaze"), TEXT("ansi")};
		FString HiddenWord;
		int32 Lives = 5;
	
};
