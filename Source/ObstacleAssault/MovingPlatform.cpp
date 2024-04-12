// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();

	UE_LOG(LogTemp, Display, TEXT("Platform %s start location %s"), *GetName(), *StartLocation.ToString());
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	FVector MoveVelocityWorld = GetActorTransform().TransformVectorNoScale(MoveVelocity);

	FVector CurrentLocation = GetActorLocation() + MoveVelocityWorld * DeltaTime;

	// New location will reach or surpass the move distance?
	if (FVector::Distance(StartLocation, CurrentLocation) >= MoveDistance)
	{
		// Reset the start location to the other extreme
		StartLocation += MoveVelocityWorld.GetSafeNormal() * MoveDistance;
		CurrentLocation = StartLocation;

		// Reverse the velocity to go in the opposite direction from the next frame
		MoveVelocity = -MoveVelocity;
	}

	SetActorLocation(CurrentLocation);
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	AddActorLocalRotation(RotateVelocity * DeltaTime);
}
