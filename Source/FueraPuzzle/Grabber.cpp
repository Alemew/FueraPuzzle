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

	FindPhysicsHandle();
	SetupInputComponent();
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	if (PhysicsHandle->GrabbedComponent)
	{
		PhysicsHandle->SetTargetLocation(GetPlayerReach());
	}
	
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Warning, TEXT("Grab action"));
	//Posible problema con hit añadir una nueva variable en vez de usar Hit
	Hit = GetFirstPhysicsBodyInReach();
	if (Hit.GetActor())
	{
		UE_LOG(LogTemp,Warning,TEXT("Estas mirando a %s"),*Hit.GetActor()->GetName());
		UPrimitiveComponent* ComponentToGrab = Hit.GetComponent();
		PhysicsHandle->GrabComponentAtLocation(ComponentToGrab,NAME_None,GetPlayerReach());
	}
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Release action"));
	PhysicsHandle->ReleaseComponent();
}

void UGrabber::FindPhysicsHandle()
{
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (! PhysicsHandle)
	{
		UE_LOG(LogTemp,Error,TEXT("No se encuentra el Physics Handle Component dentro de %s"),*GetOwner()->GetName());
	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		
		InputComponent->BindAction("Grab",IE_Pressed,this,&UGrabber::Grab);
	
		InputComponent->BindAction("Grab",IE_Released,this,&UGrabber::Release);
	}
	
}

FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	
	FCollisionQueryParams TraceParams(FName(""),false,GetOwner());

	//Comprobamos que alcanzamos con el raycast
	GetWorld()->LineTraceSingleByObjectType(
		Hit,
		PlayerPosition,
		GetPlayerReach(),
		FCollisionObjectQueryParams(ECC_PhysicsBody),
		TraceParams);

	AActor* ActorHit = Hit.GetActor();
	
	//Actor con el que choca el Ray-Cast

	/*if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"),*ActorHit->GetName());
	}*/

	return Hit;
}

FVector UGrabber::GetPlayerReach()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(PlayerPosition,PlayerRotation);

	//Vector hasta el objeto que este a una determinada distancia
	LineTraceEnd = PlayerPosition + PlayerRotation.Vector()*Reach;

	return  LineTraceEnd;
}
