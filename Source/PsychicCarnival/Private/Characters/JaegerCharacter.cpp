#include "JaegerCharacter.h"

// Constructor
AJaegerCharacter::AJaegerCharacter() {
    Health = 100;
    MovementSpeed = 600;
    bIsAlive = true;
}

// Movement Function
void AJaegerCharacter::Move(FVector Direction) {
    if (bIsAlive) {
        FVector NewLocation = GetActorLocation() + (Direction * MovementSpeed * DeltaTime);
        SetActorLocation(NewLocation);
    }
}

// Combat Function
void AJaegerCharacter::Attack(AJaegerCharacter* Target) {
    if (Target && bIsAlive) {
        Target->TakeDamage(10); // Example damage
    }
}

// Health Management
void AJaegerCharacter::TakeDamage(int DamageAmount) {
    if (bIsAlive) {
        Health -= DamageAmount;
        if (Health <= 0) {
            Health = 0;
            bIsAlive = false;
        }
    }
}

void AJaegerCharacter::Heal(int HealAmount) {
    if (bIsAlive) {
        Health += HealAmount;
        Health = FMath::Min(Health, 100); // Max health example
    }
}

// State Management
bool AJaegerCharacter::IsAlive() const {
    return bIsAlive;
}

// Update function (to be called every frame)
void AJaegerCharacter::Update(float DeltaTime) {
    if (bIsAlive) {
        // Handle movement and other updates
    }
}