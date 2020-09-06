// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

bool static IS_ISOGRAM(const FString& Input) {
    TSet<TCHAR> charSet;
    for (TCHAR c : Input) {
        bool isAlreadInIt = false;
        charSet.Add(c, &isAlreadInIt);
        if (isAlreadInIt) {
            return false;
        }
    }
    return true;
}

void static BULLS_AND_COWS(const FString& Guess, const FString& Word, int32 *bulls, int32 *cows) {
    TSet<TCHAR> characters;
    for (TCHAR c : Word) {
        characters.Add(c);
    }

    for (int i = 0; i < Guess.Len(); i++) {
        TCHAR GuessedChar = (*Guess)[i];
        TCHAR WordChar = (*Word)[i];
        if (GuessedChar == WordChar) {
            (*bulls)++;
        }else if (characters.Contains(GuessedChar)) {
            (*cows)++;
        }

        
    }

    return;
}

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    UE_LOG(LogTemp, Warning, TEXT("Game begin."));
    PrintLine(TEXT("Welcome to Bull & Cow game."));
    ResetTheGame();
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    UE_LOG(LogTemp, Warning, TEXT("New input arrived: %s"), *Input);

    if (Input.Len() != HiddenWord.Len()) {
        PrintLine("The Guess' length is not equal to HiddenWord!");
        return;
    }

    if (!IS_ISOGRAM(Input)) {
        UE_LOG(LogTemp, Warning, TEXT("The Guess is not an ISOGRAM."));
        PrintLine("The Guess is not an ISOGRAM!");
        return;
    }

    if (Input == HiddenWord) {
        UE_LOG(LogTemp, Warning, TEXT("The Guess is right :)"));
        ClearScreen();
        PrintLine("Congratulations You have won!");
        ResetTheGame();
    }
    else {
        UE_LOG(LogTemp, Warning, TEXT("The Guess is wrong :("));
        int32 bulls = 0;
        int32 cows = 0;
        BULLS_AND_COWS(Input, HiddenWord, &bulls, &cows);
        UE_LOG(LogTemp, Warning, TEXT("Bulls: %d and Cows: %d"), bulls, cows);
        PrintLine(TEXT("Bulls: %d, Cows: %d, Lives: %d"), bulls, cows, --Lives);
        if (Lives == 0) {
            ClearScreen();
            PrintLine(TEXT("You are out of lives, starting over."));
            ResetTheGame();
        }
    }
}

void UBullCowCartridge::ResetTheGame() {
    int32 selectedIsogram = rand() % Isograms.Num();
    HiddenWord = Isograms[selectedIsogram];
    UE_LOG(LogTemp, Warning, TEXT("%s"), *HiddenWord);
    Lives = HiddenWord.Len();
    PrintLine(TEXT("Please make your first guess to continue."));
    PrintLine(TEXT("Your word's length is: %d"),HiddenWord.Len());
}
