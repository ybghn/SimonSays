// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelManager.h"
#include "Kismet/GamePlayStatics.h"
// Sets default values
ALevelManager::ALevelManager()
{

	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelManager::BeginPlay()
{
	Super::BeginPlay();

	int coeff = 100;
	FVector redPos = FVector::ForwardVector * coeff; // forward
	FVector bluePos = FVector::RightVector * -coeff; // left
	FVector yellowPos = FVector::ForwardVector * -coeff; // back
	FVector greenPos = FVector::RightVector * coeff;
	FVector centerPos = FVector::ZeroVector;


	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	auto redCube = GetWorld()->SpawnActor<AColorCube>(AColorCube::StaticClass(), redPos, FRotator::ZeroRotator, spawnParams);
	redCube->SetType(Red);
	redCube->SetActorLabel("RedCube");

	auto blueCube = GetWorld()->SpawnActor<AColorCube>(AColorCube::StaticClass(), bluePos, FRotator::ZeroRotator, spawnParams);
	blueCube->SetType(Blue);

	auto greenCube = GetWorld()->SpawnActor<AColorCube>(AColorCube::StaticClass(), greenPos, FRotator::ZeroRotator, spawnParams);
	greenCube->SetType(Green);

	auto yellowCube = GetWorld()->SpawnActor<AColorCube>(AColorCube::StaticClass(), yellowPos, FRotator::ZeroRotator, spawnParams);
	yellowCube->SetType(Yellow);


	cubes.Add(redCube);
	cubes.Add(yellowCube);
	cubes.Add(blueCube);;
	cubes.Add(greenCube);



	centerCube = GetWorld()->SpawnActor<ACenterCube>(ACenterCube::StaticClass(), centerPos, FRotator::ZeroRotator, spawnParams);


	auto playerController = Cast<APlayerController>(GetController());
	if (!playerController) return;
	playerController->SetShowMouseCursor(true);


}


// Called every frame
void ALevelManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ALevelManager::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("LeftMouse", EInputEvent::IE_Pressed, this, &ALevelManager::OnLeftMousePressed);
	PlayerInputComponent->BindAction("StartGame", EInputEvent::IE_Pressed, this, &ALevelManager::StartGame);
}



void ALevelManager::CreateNewTurn()
{

	auto newLevel = GetRandomLevel();
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Emerald, FString::FromInt(newLevel->Type()));
	levels.Add(newLevel);
	turnCounter = 0;
	StartTurnAnimation();
}

void ALevelManager::StartTurnAnimation()
{
	if (turnCounter == levels.Num())
	{
		
		bPlayMode = true;
		turnCounter = 0;
		return;
	}
	levels[turnCounter]->Execute();
	turnCounter++;
	GetWorldTimerManager().SetTimer(timerHandler, this, &ALevelManager::StartTurnAnimation, delayBetweenTurns, false);
}

void ALevelManager::StartGame()
{
	bPlayMode = false;
	listOfPointedCubes.Empty();
	levels.Empty();
	score = 0;
	CreateNewTurn();

}

LevelCreatorBase* ALevelManager::GetRandomLevel()
{
	

	if (score < 6)
	{

		return new ColorBaseLevelCreator(cubes);
	
	}
	else if (score >= 6 && score < 11)
	{
		int rand = FMath::RandRange(0, 1);
		if (rand)
		{

		return new ColorBaseLevelCreator(cubes);
			
		}
		else {

			return new ArrowBasedLevelCreator(centerCube, cubes);
		}


	}
	else {
		int rand = FMath::RandRange(0, 2);
		if (rand== 0)
		{

			return new ColorBaseLevelCreator(cubes);
		
		}
		else if(rand ==1) {

			return new ArrowBasedLevelCreator(centerCube, cubes);
		
		}
		else if (rand == 2)
		{

			return new TextBasedLevelCreator(centerCube, cubes);
		}

	}


	return nullptr;
}



void ALevelManager::EvaulateResult()
{
	bPlayMode = false;
	bool result = true;
	for (int i = 0; i < levels.Num(); i++)
	{
		result = (levels[i]->Type() == listOfPointedCubes[i]);
		if (!result)
		{
			GameOver();
			return;
		}
	}
	FTimerHandle tempHandler;

	GetWorldTimerManager().SetTimer(tempHandler, this, &ALevelManager::CreateNewTurn, delayBetweenTurns, false);
	listOfPointedCubes.Empty();
	score++;
}

void ALevelManager::GameOver()
{
	bPlayMode = false;

	listOfPointedCubes.Empty();
	levels.Empty();
	score = 0;

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, "GameOver");
}

void ALevelManager::OnLeftMousePressed()
{
	if (!bPlayMode) return;

	GEngine->AddOnScreenDebugMessage(-1, 3, FColor::Emerald, "Left Click");
	auto playerController = Cast<APlayerController>(GetController());
	if (!playerController) return;
	FHitResult hitResult;
	playerController->GetHitResultUnderCursor(ECollisionChannel::ECC_Camera, false, hitResult);
	if (!hitResult.GetActor()) return;

	AColorCube* targetActor = Cast<AColorCube>(hitResult.GetActor());
	if (!targetActor) return;
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Emerald, targetActor->GetFName().ToString());
	targetActor->Blink();

	listOfPointedCubes.Add(targetActor->Type());

	if (levels.Num() == listOfPointedCubes.Num())
	{
		EvaulateResult();
	}
	 if (levels.Num() < listOfPointedCubes.Num())
	{
		GameOver();
	}
}
