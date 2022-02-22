// Alejandro Ortiz


#include "Grabber.h"

#include "DrawDebugHelpers.h"
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

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (! PhysicsHandle)
	{
		UE_LOG(LogTemp,Error,TEXT("No se encuentra el Physics Handle Component dentro de %s"),*GetOwner()->GetName());
	}
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		UE_LOG(LogTemp, Warning, TEXT("OK ---> Se ha encontrado el componente dentro de %s"), *GetOwner()->GetName());
	}
	else {
		UE_LOG(LogTemp, Error, TEXT("No se encuentra el UInputComponent dentro de %s"), *GetOwner()->GetName());
	}
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	//Obtener el ViewPort de DefaultPawn_BP
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerPosition,PlayerRotation);
	//UE_LOG(LogTemp, Warning, TEXT("%s"),*PlayerPosition.ToString());
	//UE_LOG(LogTemp, Warning, TEXT("%s"),*PlayerRotation.ToString());

	// Dibujar una linea desde el jugador hasta un metro hacia donde mire

	//FVector LineTraceEnd = PlayerPosition + FVector(0.f,0.f,100.f);
	LineTraceEnd = PlayerPosition + PlayerRotation.Vector()*Reach;

	DrawDebugLine(
		GetWorld(),
		PlayerPosition,
		LineTraceEnd,
		FColor(50, 157, 168),
		false,
		0.f,
		0,
		5.f);

	//Ray-Cast hasta una determinada distancia (reach)
	
	

	InputComponent->BindAction(
		"Grab",
		IE_Pressed,
		this,
		&UGrabber::Grab);
	
	
	
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab action"));

	FCollisionQueryParams TraceParams(FName(""),false,GetOwner());

	bool HasImpacted = GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerPosition,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECC_PhysicsBody),
		TraceParams);
	
	//Comprobar que alcanzamos con el Ray-Cast

	if (HasImpacted)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"),*Hit.GetActor()->GetName());
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Release action"));
	//TODO
}
