// Alejandro Ortiz

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/BoxComponent.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FUERAPUZZLE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();
	

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DeltaTime);
	float TotalMassOfActorsInVolume() const;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
private:
	UPROPERTY(EditAnywhere)
	float RotationYaw = -90;
	float TargetYaw;
	float InitialYaw;
	
	UPROPERTY(EditAnywhere)
	float OpenSpeed = 2;
	UPROPERTY(EditAnywhere)
	float CloseSpeed = 2;
	
	UPROPERTY(EditAnywhere)
	UBoxComponent* pressurePlate = nullptr;
	
	UPROPERTY(EditAnywhere)
	float OpeningMass;
	
	UPROPERTY(EditAnywhere)
	float ClosingDelay = 2;
	float InitialTimeOpening;
	UAudioComponent* DoorSound = nullptr;
	bool IsDoorOpened = true;
	UPROPERTY(EditAnywhere)
	USoundBase* OpenSound = nullptr;
	UPROPERTY(EditAnywhere)
	USoundBase* CloseSound = nullptr;
	UMeshComponent* DoorMesh = nullptr;
	UPROPERTY(EditAnywhere)
	FName DOOR_MESH_NAME = "S_Door";
};
