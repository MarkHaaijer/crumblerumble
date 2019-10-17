// Fill out your copyright notice in the Description page of Project Settings.

#include "Act_Tile.h"
#include "ConstructorHelpers.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine.h"
#include "NiagaraComponent.h"
#include <nvtesslib/inc/nvtess.h>

// Sets default values
AAct_Tile::AAct_Tile()
{
	m_BoxExtent = {49.f,49.f,55.f};

 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//collision component
	m_pBoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	m_pBoxComp->SetBoxExtent(m_BoxExtent);
	m_pBoxComp->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
	m_pBoxComp->SetCollisionProfileName("Trigger");

	//call on overlap begin when you start colliding
	m_pBoxComp->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	RootComponent = m_pBoxComp;

	m_pBoxComp->OnComponentBeginOverlap.AddDynamic(this, &AAct_Tile::OnOverlapBegin);

	// Create Tile Mesh with Cube shape
	m_pMesh = CreateDefaultSubobject<UStaticMeshComponent>("TileMesh");
	m_pMesh->SetupAttachment(RootComponent);

	// Create Tile particle
	m_pParticle = CreateDefaultSubobject<UNiagaraComponent>("Particle");
	m_pParticle->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void AAct_Tile::BeginPlay()
{
	int32 const tileMesh = FMath::RandRange(1, 3);
	// Fix for random tile looks

	switch (tileMesh) // Select random look for the tile
	{
	case 1:
		m_pMesh->SetStaticMesh(m_pTileMesh1);
		m_pParticle->SetAsset(m_FallParticle1);
		break;
	case 2:
		m_pMesh->SetStaticMesh(m_pTileMesh2);
		m_pParticle->SetAsset(m_FallParticle2);
		break;
	case 3:
		m_pMesh->SetStaticMesh(m_pTileMesh3);
		m_pParticle->SetAsset(m_FallParticle3);
		break;
	}

	// Give tile random rotation
	float const rotation = FMath::RandRange(1, 4);
	m_pMesh->SetRelativeRotation(FRotator(0.f, 90.f*rotation, 0.f));
	m_pParticle->SetNiagaraVariableVec3("User.rot", FVector(0.f,0.f, 90.f*rotation));
	m_pParticle->Deactivate();
	for (TActorIterator<AAct_TileGenerator> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		m_pTileGeneratorActor = *ActorItr;
	}

	for (TActorIterator<AAct_PickupGenerator> ActorItr(GetWorld()); ActorItr; ++ActorItr)
	{
		m_pPickupGeneratorActor = *ActorItr;
	}
	Super::BeginPlay();
}

// Called every frame
void AAct_Tile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (m_pTileGeneratorActor->GetIsActive())
	{
		m_ElapsedTime += DeltaTime;

		// Lower Health and destroy tiles
		if (m_Health < 5.f)
		{
			m_pMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			m_pMesh->SetVisibility(false);
			if (!m_pParticle->IsActive())
				m_pParticle->Activate(true);
		}
		// Lower Health when alive for too long and when too far away from frontrunner (20 tiles)
		if (m_Health > 0.f && !m_Draining && (GetActorLocation().X < m_ElapsedTime*m_FallRate || GetActorLocation().X + 2000.f < m_pPickupGeneratorActor->GetFrontRunnerXPos()))
			m_Draining = true;
		else if (m_Health <= -10.f)
		{
			m_pParticle->Deactivate();
			uint32 widthPos = m_pTileGeneratorActor->GetWidthPos();
			uint32 length = m_pTileGeneratorActor->GetLength();
			m_pTileGeneratorActor->AdaptWidthPos();

			m_Draining = false;
			m_Health = FMath::RandRange(m_MinHealth, m_MaxHealth);
			SetActorLocation(FVector(length*m_TileSize, widthPos*m_TileSize, 0));
			m_pMesh->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
			m_pMesh->SetVisibility(true);

			m_HealthDrain = m_StartHealthDrain;
		}

		if (m_Draining)
			m_Health -= m_HealthDrain*DeltaTime;
	}
}

void AAct_Tile::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (OtherActor && (OtherActor != this))
		if(OtherActor->ActorHasTag("player"))
		{
			m_Draining = true;
			m_HealthDrain = m_NewHealthDrain;
		}
}

bool AAct_Tile::TakeDamage_Implementation(float health)
{
	m_Health -= health;
	m_Draining = true;
	if (m_Health < 0)m_Health = 2.0f;

	return true;
}


