// Fill out your copyright notice in the Description page of Project Settings.

#include "Act_BaseObstacle.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"

// Sets default values
AAct_BaseObstacle::AAct_BaseObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//creating mesh component
	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Obstacle Mesh"));
	int32 const obstacleMesh = FMath::RandRange(1,4);

	RootComponent = m_pMesh;

	// Temporary fix for random obstacle looks
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset1(TEXT("/Game/_Assets/Environment/SM_Column_A"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset2(TEXT("/Game/_Assets/Environment/SM_Column_B"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset3(TEXT("/Game/_Assets/Environment/SM_CollapsedWall_A"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset4(TEXT("/Game/_Assets/Environment/SM_CollapsedWall_B"));

	UStaticMesh* Asset = MeshAsset1.Object;

	switch (obstacleMesh) // Select random look for the tile
	{
	case 1:
		break;
	case 2:
		Asset = MeshAsset2.Object;
		break;
	case 3:
		Asset = MeshAsset3.Object;
		break;
	case 4:
		Asset = MeshAsset3.Object;
		break;
	}
	
    m_pMesh->SetStaticMesh(Asset);

	// Give obstacle random rotation
	float const rotation = FMath::RandRange(1,4);
	m_pMesh->SetRelativeRotation(FRotator(0.f, 90.f*rotation, 0.f));
}

// Called when the game starts or when spawned
void AAct_BaseObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAct_BaseObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	m_ElapsedTime += DeltaTime;

	if (m_ElapsedTime >= 20.f)
		Destroy();
}