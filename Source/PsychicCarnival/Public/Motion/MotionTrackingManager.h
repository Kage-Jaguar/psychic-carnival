#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MotionTrackingManager.generated.h"

UENUM(BlueprintType)
enum class ETrackedDevice : uint8
{
\tLeftHand UMETA(DisplayName = "Left Hand"),
\tRightHand UMETA(DisplayName = "Right Hand"),
\tLeftFoot UMETA(DisplayName = "Left Foot"),
\tRightFoot UMETA(DisplayName = "Right Foot"),
\tChest UMETA(DisplayName = "Chest"),
\tHead UMETA(DisplayName = "Head")
};

USTRUCT(BlueprintType)
struct FMotionTrackingData
{
\tGENERATED_BODY()

\tUPROPERTY(BlueprintReadWrite, Category = "Motion Tracking")
\tFVector Position;

\tUPROPERTY(BlueprintReadWrite, Category = "Motion Tracking")
\tFRotator Rotation;

\tUPROPERTY(BlueprintReadWrite, Category = "Motion Tracking")
\tFVector Velocity;

\tUPROPERTY(BlueprintReadWrite, Category = "Motion Tracking")
\tfloat Confidence;

\tUPROPERTY(BlueprintReadWrite, Category = "Motion Tracking")
\tETrackedDevice Device;
};

/**
 * UMotionTrackingManager - Handles all motion tracking data from custom suits and VR devices
 * Processes input from IMU sensors, SteamVR tracking, and treadmill input
 */
UCLASS()
class PSYCHICCARNIVAL_API UMotionTrackingManager : public UObject
{
\tGENERATED_BODY()

public:
\tUMotionTrackingManager();

\t// Initialization
\tUFUNCTION(BlueprintCallable, Category = "Motion Tracking")
\tvoid InitializeTracking();

\tUFUNCTION(BlueprintCallable, Category = "Motion Tracking")
\tvoid ShutdownTracking();

\t// SteamVR Integration
\tUFUNCTION(BlueprintCallable, Category = "Motion Tracking")
\tvoid InitializeSteamVR();

\tUFUNCTION(BlueprintCallable, Category = "Motion Tracking")
\tFMotionTrackingData GetTrackedDeviceData(ETrackedDevice Device);

\t// Suit Sensor Calibration
\tUFUNCTION(BlueprintCallable, Category = "Motion Tracking")
\tvoid CalibrateMotionSuit();

\tUFUNCTION(BlueprintCallable, Category = "Motion Tracking")
\tvoid SetSensorSensitivity(ETrackedDevice Device, float Sensitivity);

\t// Treadmill Input
\tUFUNCTION(BlueprintCallable, Category = "Motion Tracking")
\tvoid ProcessTreadmillInput(FVector MovementVector);

\tUFUNCTION(BlueprintCallable, Category = "Motion Tracking")
\tFVector GetTreadmillMovementVector() const;

\t// Haptic Feedback
\tUFUNCTION(BlueprintCallable, Category = "Motion Tracking")
\tvoid TriggerHapticFeedback(ETrackedDevice Device, float Intensity, float Duration);

\t// Data Processing
\tUFUNCTION(BlueprintCallable, Category = "Motion Tracking")
\tvoid SmoothMotionData(float DeltaTime);

\tUFUNCTION(BlueprintCallable, Category = "Motion Tracking")
\tvoid ApplyMotionFilter(ETrackedDevice Device);

protected:
\t// Internal tracking data storage
\tUPROPERTY(VisibleAnywhere, Category = "Motion Tracking")
\tTMap<ETrackedDevice, FMotionTrackingData> CurrentTracking;

\tUPROPERTY(VisibleAnywhere, Category = "Motion Tracking")
\tTMap<ETrackedDevice, FMotionTrackingData> PreviousTracking;

\t// Configuration
\tUPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Tracking")
\tfloat TrackingUpdateRate = 90.0f;

\tUPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Tracking")
\tfloat SmoothingFactor = 0.8f;

\tUPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Motion Tracking")
\tbEnableHapticFeedback = true;

\tvirtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction);
};