// Fill out your copyright notice in the Description page of Project Settings.

#include "Act_Wall.h"
#include "ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"

// Sets default values
AAct_Wall::AAct_Wall()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>("WallMesh");

	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset1(TEXT("/Game/_Assets/Environment/SM_Wall_A"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset2(TEXT("/Game/_Assets/Environment/SM_Wall_B"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh>MeshAsset3(TEXT("/Game/_Assets/Environment/SM_Wall_C"));

	UStaticMesh* Asset = MeshAsset1.Object;
	int32 const wallMesh = FMath::RandRange(1,3);

	switch (wallMesh) // Select random look for the wall
	{
	case 1:
		break;
	case 2:
		Asset = MeshAsset2.Object;
		break;
	case 3:
		Asset = MeshAsset3.Object;
		break;
	}

    m_pMesh->SetStaticMesh(Asset);
	// Make mesh the root
	RootComponent = m_pMesh;
}

// Called when the game starts or when spawned
void AAct_Wall::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<AAct_PickupGenerator> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		m_pPickupGeneratorActor = *ActorItr;
	}
	
	for (TActorIterator<AAct_WallGenerator> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		m_pWallGeneratorActor = *ActorItr;
	}
	m_TotalWallLength = m_pWallGeneratorActor->GetLength();
}

// Called every frame
void AAct_Wall::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float frontX = m_pPickupGeneratorActor->GetFrontRunnerXPos();
	float curX = GetActorLocation().X;
	if (frontX > curX + 2000) // Teleport wall to front if too far away from frontrunner (20 tiles in this case)
		SetActorLocation(FVector(GetActorLocation().X + m_TotalWallLength * m_WallLength,GetActorLocation().Y,0));
}

