// Fill out your copyright notice in the Description page of Project Settings.

#include "SCharacter.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
ASCharacter::ASCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("Spring Arm Component");
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>("Camera Component");
	CameraComponent->SetupAttachment(SpringArmComponent);
}

// Called to bind functionality to input
void ASCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ASCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Turn", this, &APawn::AddControllerYawInput);
}

void ASCharacter::MoveForward(float Value)
{
	AddMovementInput(GetActorForwardVector(), Value);
}
