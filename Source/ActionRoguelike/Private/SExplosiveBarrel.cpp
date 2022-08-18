// Fill out your copyright notice in the Description page of Project Settings.


#include "SExplosiveBarrel.h"

#include "PhysicsEngine/RadialForceComponent.h"

// Sets default values
ASExplosiveBarrel::ASExplosiveBarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh Component"));
	MeshComponent->SetSimulatePhysics(true);
	RootComponent = MeshComponent;

	ForceComponent = CreateDefaultSubobject<URadialForceComponent>(TEXT("Force Component"));
	ForceComponent->SetupAttachment(false);

	// Leaving this on applies small constant force via component 'tick' optional
	ForceComponent->SetAutoActivate(false);

	ForceComponent->Radius = 750.f;
	// Alternative: 200000.0 if bImpulseVelChange = false
	// Optional, ignores 'Mass' of other objects (if false, the impulse strength will be much higher to push must objects depending on Mass)
	ForceComponent->ImpulseStrength = 250.f;
	ForceComponent->bImpulseVelChange = true;

	// Optional, default constructor of component already adds 4 object type to affect, excluding WorldDynamic
	ForceComponent->AddCollisionChannelToAffect(ECC_WorldDynamic);
}

// Called when the game starts or when spawned
void ASExplosiveBarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

void ASExplosiveBarrel::PostInitializeComponents()
{
	Super::PostInitializeComponents();

	MeshComponent->OnComponentHit.AddDynamic(this, &ASExplosiveBarrel::OnActorHit);
}

void ASExplosiveBarrel::OnActorHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ForceComponent->FireImpulse();
}
