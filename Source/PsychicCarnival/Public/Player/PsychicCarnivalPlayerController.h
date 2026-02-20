#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PsychicCarnivalPlayerController.generated.h"

/**
 * APsychicCarnivalPlayerController - Player controller for handling input and VR interaction
 * Manages player input from motion tracking suits, treadmill, and VR devices
 */
UCLASS()
class PSYCHICCARNIVAL_API APsychicCarnivalPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	APsychicCarnivalPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	virtual void Tick(float DeltaTime) override;

public:
	// Input Handling for Motion Tracking
	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnMotionInput(FVector HandPosition, FRotator HandRotation);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnTreadmillInput(FVector MovementVector);

	UFUNCTION(BlueprintCallable, Category = "Input")
	void OnVRActionInput(FString ActionName);

	// Network Replication
	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerReceiveMotionInput(FVector HandPosition, FRotator HandRotation);

	UFUNCTION(Server, Unreliable, WithValidation)
	void ServerReceiveTreadmillInput(FVector MovementVector);

	// Debug Functions
	UFUNCTION(BlueprintCallable, Category = "Debug")
	void PrintInputDebugInfo();
};