// Alejandro Ortiz


#include "OpenDoor.h"

#include <Actor.h>

#include "Components/AudioComponent.h"
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

	
	TargetYaw = RotationYaw + InitialYaw;

	DoorSound = GetOwner()->FindComponentByClass<UAudioComponent>();
	pressurePlate = GetOwner()->FindComponentByClass<UBoxComponent>();
	DoorMesh = Cast<UMeshComponent>(GetOwner()->GetDefaultSubobjectByName(DOOR_MESH_NAME));
	InitialYaw = DoorMesh->GetComponentRotation().Yaw;
	
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
	
	float nextStepYaw = FMath::FInterpTo(DoorMesh->GetComponentRotation().Yaw,TargetYaw,DeltaTime,OpenSpeed);

	FRotator Rotation90Yaw(DoorMesh->GetComponentRotation().Pitch,nextStepYaw,DoorMesh->GetComponentRotation().Roll);
	DoorMesh->SetWorldRotation(Rotation90Yaw);
	if (DoorSound && IsDoorOpened)
	{
		DoorSound->SetSound(OpenSound);
		DoorSound->Play();
		IsDoorOpened = false;
	}
}

void UOpenDoor::CloseDoor(float DeltaTime)
{
	float nextStepYaw = FMath::FInterpTo(DoorMesh->GetComponentRotation().Yaw,InitialYaw,DeltaTime,CloseSpeed);
	//UE_LOG(LogTemp, Warning, TEXT("closeDoor"));
	FRotator Rotation90Yaw(DoorMesh->GetComponentRotation().Pitch,nextStepYaw,DoorMesh->GetComponentRotation().Roll);
	DoorMesh->SetWorldRotation(Rotation90Yaw);
	if (DoorSound && !IsDoorOpened)
	{
		DoorSound->SetSound(CloseSound);
		DoorSound->Play();
		IsDoorOpened = true;
	}
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
		if (Actor->ActorHasTag(Tag)|| Actor->FindComponentByClass<UPrimitiveComponent>()->ComponentHasTag(Tag))
		{
			UPrimitiveComponent* PrimitiveComponent = Actor->FindComponentByClass<UPrimitiveComponent>();
			if (PrimitiveComponent)
			{
				TotalMass += PrimitiveComponent->GetMass();
			}
		}
		
	}

	return TotalMass;
}



