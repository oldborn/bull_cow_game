// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Isograms.h"

struct BullsAndCows {
    int32 Bulls = 0;
    int32 Cows = 0;
};

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

static void BULLS_AND_COWS(const FString& Guess, const FString& Word, int32& bulls, int32& cows) {
    // a silly optimization that will remember the last Word is given
    // probably we don't need to do that since
    // to check equality c++ probably checks each character
    // while checking them we can also add them to characters set
    // but I wanted to remember static function variables
    static FString TheWord = Word;
    static TSet<TCHAR> characters;

    bulls = 0;
    cows = 0;
    
    if (TheWord != Word || characters.Num() == 0) {
        UE_LOG(LogTemp, Warning, TEXT("The word has changed to : %s"), *Word);
        TheWord = Word;
        characters.Empty();
        for (TCHAR c : Word) {
            characters.Add(c);
        }
    }


    for (int i = 0; i < Guess.Len(); i++) {
        TCHAR GuessedChar = (*Guess)[i];
        TCHAR WordChar = (*Word)[i];
        if (GuessedChar == WordChar) {
            (bulls)++;
        }else if (characters.Contains(GuessedChar)) {
            (cows)++;
        }

        
    }

    return;
}

// A wrapper just for the course sake
static BullsAndCows GetBullsAndCows(const FString& Guess, const FString& Word) {
    BullsAndCows BAC;
    BULLS_AND_COWS(Guess, Word, BAC.Bulls, BAC.Cows);
    return BAC;
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
        BullsAndCows BAC = GetBullsAndCows(Input, HiddenWord);
        UE_LOG(LogTemp, Warning, TEXT("Bulls: %d and Cows: %d"), BAC.Bulls, BAC.Cows);
        PrintLine(TEXT("Bulls: %d, Cows: %d, Lives: %d"), BAC.Bulls, BAC.Cows, --Lives);
        if (Lives == 0) {
            ClearScreen();
            PrintLine(TEXT("You are out of lives, starting over."));
            ResetTheGame();
        }
    }
}

void UBullCowCartridge::ResetTheGame() {
    int32 selectedIsogram = FMath::RandRange(0, Isograms.Num()-1);
    HiddenWord = Isograms[selectedIsogram];
    UE_LOG(LogTemp, Warning, TEXT("%s"), *HiddenWord);
    Lives = HiddenWord.Len();
    PrintLine(TEXT("Please make your first guess to continue."));
    PrintLine(TEXT("Your word's length is: %d"),HiddenWord.Len());
}
