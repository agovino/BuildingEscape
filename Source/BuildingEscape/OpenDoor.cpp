// Copyright Marco Agovino 2018

#include "OpenDoor.h"
#include "GameFramework/Actor.h"
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
	// A Pointer to an Actor ... Find the owning Actor
	Owner = GetOwner();
	// Hole den SpielerKörper in der Welt
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	// Set the door rotation -> Create a rotator
	Owner->SetActorRotation(FRotator(0.0f, OpenAngle, 0.0f));
}
void UOpenDoor::CloseDoor()
{
	// Set the door rotation -> Create a rotator
	Owner->SetActorRotation(FRotator(0.0f, 0.0f, 0.0f));
}


// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Poll the Trigger Volume
	if (PressurPlate && PressurPlate->IsOverlappingActor(ActorThatOpens))
	{
		// If the ActorThatOpens is in the Volume
		OpenDoor();
		LastDoorOpenTime = GetWorld()->GetTimeSeconds(); // Aktuelle Sekunde speichern, wenn geöffnet wird

	}
	// Check if it's time to close the door
	// if CurrentTime - LastDoorOpenTime > 
	if (GetWorld()->GetTimeSeconds() - LastDoorOpenTime > DoorCloseDelay )
	{
		CloseDoor();
	}
}

