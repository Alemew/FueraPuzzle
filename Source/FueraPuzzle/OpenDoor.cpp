// Alejandro Ortiz


#include "OpenDoor.h"
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

	//FRotator currentRotation = GetOwner()-> GetActorRotation();
	//UE_LOG(LogTemp, Warning, TEXT("%s"),*currentRotation.ToString());
	//GetOwner() -> SetActorRotation(FRotator(0,-90,0));
	InitialYaw = GetOwner()->GetActorRotation().Yaw;
	TargetYaw = RotationYaw + InitialYaw;

	if (!ActorThatOpenDoor)
	{
		ActorThatOpenDoor = GetWorld()->GetFirstPlayerController()->GetPawn();
	}
	
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (pressurePlate->IsOverlappingActor(ActorThatOpenDoor))
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
	/*UE_LOG(LogTemp, Warning, TEXT("%s"),*GetOwner()->GetActorRotation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Yaw is: %f"),GetOwner()->GetActorRotation().Yaw);*/
	
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



