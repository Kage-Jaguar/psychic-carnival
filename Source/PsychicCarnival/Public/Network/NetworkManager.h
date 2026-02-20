#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NetworkManager.generated.h"

UENUM(BlueprintType)
enum class ENetworkEventType : uint8
{
	PlayerMovement UMETA(DisplayName = "Player Movement"),
	PlayerAttack UMETA(DisplayName = "Player Attack"),
	PlayerDamage UMETA(DisplayName = "Player Damage"),
	GameStateUpdate UMETA(DisplayName = "Game State Update"),
	ChatMessage UMETA(DisplayName = "Chat Message")
};

USTRUCT(BlueprintType)
struct FNetworkPacket
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadWrite, Category = "Network")
	ENetworkEventType EventType;

	UPROPERTY(BlueprintReadWrite, Category = "Network")
	FString PlayerID;

	UPROPERTY(BlueprintReadWrite, Category = "Network")
	FVector Data;

	UPROPERTY(BlueprintReadWrite, Category = "Network")
	float Timestamp;
};

/**
 * ANetworkManager - Manages client-server networking and real-time synchronization
 * Handles player connection, state synchronization, and message routing
 */
UCLASS()
class PSYCHICCARNIVAL_API ANetworkManager : public AActor
{
	GENERATED_BODY()

public:
	ANetworkManager();

protected:
	// Network Properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network")
	FString ServerAddress = "localhost";

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network")
	int32 ServerPort = 8080;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Network")
	bool bConnected = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Network")
	float NetworkLatency = 0.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Network")
	float PacketSendRate = 60.0f;

	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

public:
	// Connection Management
	UFUNCTION(BlueprintCallable, Category = "Network")
	void ConnectToServer(const FString& Address, int32 Port);

	UFUNCTION(BlueprintCallable, Category = "Network")
	void DisconnectFromServer();

	UFUNCTION(BlueprintCallable, Category = "Network")
	bool IsConnected() const;

	UFUNCTION(BlueprintCallable, Category = "Network")
	float GetLatency() const;

	// Packet Sending
	UFUNCTION(BlueprintCallable, Category = "Network")
	void SendPacket(const FNetworkPacket& Packet);

	UFUNCTION(BlueprintCallable, Category = "Network")
	void SendPlayerMovement(FVector Position, FRotator Rotation);

	UFUNCTION(BlueprintCallable, Category = "Network")
	void SendPlayerAction(ENetworkEventType ActionType, FVector ActionData);

	// Packet Receiving
	UFUNCTION(BlueprintCallable, Category = "Network")
	void OnPacketReceived(const FNetworkPacket& Packet);

	UFUNCTION(BlueprintCallable, Category = "Network")
	void ProcessGameStateUpdate(const FString& StateData);

	// State Synchronization
	UFUNCTION(BlueprintCallable, Category = "Network")
	void SynchronizeGameState();

	UFUNCTION(BlueprintCallable, Category = "Network")
	void InterpolateRemotePlayerState(float DeltaTime);

protected:
	// Internal network handling
	UPROPERTY(VisibleAnywhere, Category = "Network")
	TQueue<FNetworkPacket> OutgoingPackets;

	UPROPERTY(VisibleAnywhere, Category = "Network")
	TQueue<FNetworkPacket> IncomingPackets;

	void ProcessOutgoingPackets();
	void ProcessIncomingPackets();
} ;