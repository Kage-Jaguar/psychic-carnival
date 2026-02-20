#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PsychicCarnivalGameMode.generated.h"

/**
 * APsychicCarnivalGameMode - Main game mode for Psychic Carnival
 * Manages game rules, player spawning, and core game logic
 */
UCLASS()
class PSYCHICCARNIVAL_API APsychicCarnivalGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APsychicCarnivalGameMode();

protected:
	// Game State Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Game")
	int32 MaxPlayers = 2;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
	int32 CurrentPlayerCount = 0;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Game")
	bool bGameActive = false;

	virtual void BeginPlay() override;

public:
	// Game State Management
	UFUNCTION(BlueprintCallable, Category = "Game")
	void StartGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void EndGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void PauseGame();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void ResumeGame();

	// Player Management
	UFUNCTION(BlueprintCallable, Category = "Game")
	void OnPlayerJoined();

	UFUNCTION(BlueprintCallable, Category = "Game")
	void OnPlayerLeft();

	UFUNCTION(BlueprintCallable, Category = "Game")
	int32 GetCurrentPlayerCount() const;

	UFUNCTION(BlueprintCallable, Category = "Game")
	bool IsGameActive() const;
};