// Alejandro Ortiz


#include "Grabber.h"
#include "Engine/World.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Obtener el ViewPort de DefaultPawn_BP
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerPosition,PlayerRotation);
	UE_LOG(LogTemp, Warning, TEXT("%s"),*PlayerPosition.ToString());
	UE_LOG(LogTemp, Warning, TEXT("%s"),*PlayerRotation.ToString());

	//Ray-Cast hasta una determinada distancia (reach)

	//Comprobar que alcanzamos con el Ray-Cast
}

