// Fill out your copyright notice in the Description page of Project Settings.


#include "WorldPosition.h"
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UWorldPosition::UWorldPosition()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UWorldPosition::BeginPlay()
{
	Super::BeginPlay();

	FString Log = TEXT("Hola");
	FString* PtrLog = &Log;


	//UE_LOG(LogTemp,Warning,TEXT("%s"),**PtrLog);
	

	/*int32 longitudCadena = Log.Len();
	int32 longitudCadena2 = (*PtrLog).Len();
	int32 longitudCadena3 = PtrLog -> Len();
	UE_LOG(LogTemp,Warning,TEXT("%d"),longitudCadena);
	UE_LOG(LogTemp,Warning,TEXT("%d"),longitudCadena2);
	UE_LOG(LogTemp,Warning,TEXT("%d"),longitudCadena3);*/
	
	
	/*FString Log = TEXT("Hola");
	UE_LOG(LogTemp,Warning,TEXT("%s"),*Log);*/

	
	/*UE_LOG(LogTemp,Warning,TEXT("Message"));
	UE_LOG(LogTemp,Error,TEXT("Error"));
	UE_LOG(LogTemp,Display,TEXT("informacion"));*/
	
	UE_LOG(LogTemp,Warning,TEXT("%s"),*GetOwner()->GetActorLocation().ToString());
	
}


// Called every frame
void UWorldPosition::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

