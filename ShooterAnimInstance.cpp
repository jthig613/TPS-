// Fill out your copyright notice in the Description page of Project Settings.

#include "ShooterAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ShooterCharacter.h"



void UShooterAnimInstance::NativeInitializeAnimation() 
{
    ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
}

void UShooterAnimInstance::UpdateAnimationProperties(float DeltaTime) 
{
    if(ShooterCharacter == nullptr)
    {
        ShooterCharacter = Cast<AShooterCharacter>(TryGetPawnOwner());
    }

    if(ShooterCharacter)
    {
        FVector velocity{ShooterCharacter->GetVelocity()};
        velocity.Z = 0;
        Speed = velocity.Size(); //get lateral speed //

        bIsInAir = ShooterCharacter->GetCharacterMovement()->IsFalling();
        bAiming = ShooterCharacter->GetAiming();

    // is the character accelerating?
        if (ShooterCharacter->GetCharacterMovement()->GetCurrentAcceleration().Size() > 0.f)
        {
            bIsAccelerating = true;
        }
        else
        {
            bIsAccelerating = false;
        }

        FRotator AimRotation = ShooterCharacter->GetBaseAimRotation();
        //FString RotationMessage = FString::Printf(TEXT("Base Aim Rotation: %f"), AimRotation.Yaw);
        FRotator MovementRotation = UKismetMathLibrary::MakeRotFromX(ShooterCharacter->GetVelocity());
        //FString MovementRotationMessage = FString::Printf(TEXT("Movement Base Aim Rotation: %f"), MovementRotation.Yaw);

        MovementOffsetYaw = UKismetMathLibrary::NormalizedDeltaRotator(MovementRotation, AimRotation).Yaw;
        FString OffsetYawMessage = FString::Printf(TEXT("Movement Base Aim Rotation: %f"), MovementOffsetYaw);

        if(ShooterCharacter->GetVelocity().Size() > 0.f)
        {
            LastMovementOffsetYaw = MovementOffsetYaw;
        }


        if(GEngine)
         {
             GEngine->AddOnScreenDebugMessage(1, 0.f, FColor::White, OffsetYawMessage);
        }
    }
}


