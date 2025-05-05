// Fill out your copyright notice in the Description page of Project Settings.


#include "Code/Actors/Projectile.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "../END2502.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"// For Poor Habit
#include "Kismet/GameplayStatics.h" 
// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SetRootComponent(SphereCollision);

	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>("SphereMesh");
	SphereMesh->SetupAttachment(GetRootComponent());
	SphereMesh->SetCollisionProfileName("NoCollision");
	SphereMesh->SetRelativeScale3D(FVector(0.6f));

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");
	ProjectileMovement->UpdatedComponent = SphereCollision;
	ProjectileMovement->InitialSpeed = 1900.0f;
	ProjectileMovement->MaxSpeed = 1900.0f;
	ProjectileMovement->ProjectileGravityScale = 0.f;

	SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::HandleOverlap);
	SphereCollision->SetWorldScale3D(FVector(0.18f));


	Damage = 1.f;



	

	//1 Right-Click the delegate and go to delcaration
	//2 Right-Click the type and go to definition
	//3 Copy form the back of thr macro how many inputs parameters there are
	//4 Create a function with same function signature
	//5 Get rid of extra commas
	//6 Define the function
	//SphereCollision->OnComponentHit.AddDynamic(this, &AProjectile::HandleHit);
	//Common error 
	//SphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AProjectile::HandleHit);
	//NOTE: Input to AddDynamic is the same as CreateEvent in blueprint

	
	
	//No Not do this Bad habit
	//Poor Habit
	//this is a bad example
	
	/*static ConstructorHelpers::FObjectFinder<UStaticMesh> Asset(TEXT("/Script/Engine.StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	SphereMesh->SetStaticMesh(Asset.Object);

	*/

	
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	AActor* ActorOwner = GetOwner();

	OwnerController = Cast<AController>(ActorOwner);

	if (!ActorOwner)
	{
		UE_LOG(LogTemp, Warning, TEXT("Projectile does not have a valid owner."));
		return;
	}

	OwnerController = Cast<AController>(ActorOwner->GetInstigatorController());

	if (!OwnerController)
	{
		UE_LOG(LogTemp, Error, TEXT("No Controller was set"));
	}

	// 5 of 6
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AProjectile::K2_DestroyActor, 3.f);


	
}



// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::HandleOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{

	if (OtherActor && OtherActor != this)
	{
		UGameplayStatics::ApplyDamage(OtherActor, Damage, OwnerController, this, UDamageType::StaticClass());
	}

	Destroy();
}

////This function will never get hit as the pbject is overlap all
//void AProjectile::HandleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
//{
//	UE_LOG(Game, Log, TEXT("Hello"));
//}



