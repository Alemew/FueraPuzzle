// Alejandro Ortiz


#include "OpenDoor.h"

#include <Actor.h>

#include "Engine/World.h"
#include "GameFramework/PlayerController.h"



// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	
	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	TargetYaw = RotationYaw + InitialYaw;
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (pressurePlate && TotalMassOfActorsInVolume() > OpeningMass)
	{
		OpenDoor(DeltaTime);
		InitialTimeOpening = GetWorld()->GetTimeSeconds();
	}
	if (InitialTimeOpening < GetWorld()->GetTimeSeconds() - ClosingDelay)
	{
		CloseDoor(DeltaTime);
	}
}

void UOpenDoor::OpenDoor(float DeltaTime)
{
	
	float nextStepYaw = FMath::FInterpTo(GetOwner()->GetActorRotation().Yaw,TargetYaw,DeltaTime,OpenSpeed);

	FRotator Rotation90Yaw(0.f,nextStepYaw,0.f);
	GetOwner()->SetActorRotation(Rotation90Yaw);
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	float nextStepYaw = FMath::FInterpTo(GetOwner()->GetActorRotation().Yaw,InitialYaw,DeltaTime,CloseSpeed);

	FRotator Rotation90Yaw(0.f,nextStepYaw,0.f);
	GetOwner()->SetActorRotation(Rotation90Yaw);
}

float UOpenDoor::TotalMassOfActorsInVolume() const
{
	float TotalMass = 0.f;
	TArray<AActor*> OverlappingActors;

	if (pressurePlate)
	{
		pressurePlate->GetOverlappingActors(OverlappingActors);
	}

	for (AActor* Actor : OverlappingActors)
	{
		UPrimitiveComponent* PrimitiveComponent = Actor->FindComponentByClass<UPrimitiveComponent>();
		if (PrimitiveComponent)
		{
			TotalMass += PrimitiveComponent->GetMass();
		}
	}

	return TotalMass;
}



