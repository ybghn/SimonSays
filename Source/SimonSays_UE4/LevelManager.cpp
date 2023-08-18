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

	TArray<AActor*> placers;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Place", placers);
	if (placers.Num() != 4) return;
	// Todo : Hata mesajý yazýlabilinir
	FVector redPos = placers[0]->GetActorLocation();
	FVector bluePos = placers[1]->GetActorLocation();
	FVector yellowPos = placers[2]->GetActorLocation();
	FVector greenPos = placers[3]->GetActorLocation();


	FActorSpawnParameters spawnParams;
	spawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	
	auto redCube = GetWorld()->SpawnActor<AColorCube>(AColorCube::StaticClass(), redPos, FRotator::ZeroRotator, spawnParams);
	redCube->SetType(Red);
	redCube->SetActorLabel("RedCube");

	auto blueCube = GetWorld()->SpawnActor<AColorCube>(AColorCube::StaticClass(), bluePos, FRotator::ZeroRotator, spawnParams);
	blueCube->SetType(Blue);

	auto greenCube = GetWorld()->SpawnActor<AColorCube>(AColorCube::StaticClass(), greenPos, FRotator::ZeroRotator, spawnParams);
	greenCube->SetType(Green);

	auto yellowCube = GetWorld()->SpawnActor<AColorCube>(AColorCube::StaticClass(),yellowPos, FRotator::ZeroRotator, spawnParams);
	yellowCube->SetType(Yellow);


	cubes.Add(redCube);
	cubes.Add(yellowCube);
	cubes.Add(blueCube);;
	cubes.Add(greenCube);
		

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

void ALevelManager::SelectRandomColor()
{

	int random = FMath::RandRange(0,3);
	for (auto c : cubes)
	{
		if (c->Type() == (TypeOfCube)random)
		{
			current = c;
		}
	}
}

void ALevelManager::CreateNewTurn()
{
	
	

	if (listOfTempCubes.Num() > 0)
	{
		auto last = listOfTempCubes[0];
		listOfTempCubes.RemoveAt(0);
	
		GetWorldTimerManager().SetTimer(timerHandler,this,&ALevelManager::CreateNewTurn, delayBtweenBlinks, false);
		for (auto c : cubes)
		{
			if (c->Type() == last)
			{
				c->Blink();
			}
		}
		

	}
	else {
		current->Blink();
		listOfCube.Add(current->Type());
		bPlayMode = true;
	}

	
}

void ALevelManager::StartGame()
{
	bPlayMode = false;
	SelectRandomColor();
	listOfTempCubes = listOfCube;
	CreateNewTurn();

}

void ALevelManager::EvaulateResult()
{
	bool result  =  true;
	for (int i = 0; i < listOfCube.Num(); i++)
	{
		result = (listOfCube[i] == listOfPointedCubes[i]);
		if (!result) 
		{
			GameOver();
			}
	}
	FTimerHandle tempHandler;

	GetWorldTimerManager().SetTimer(tempHandler, this, &ALevelManager::StartGame, delayBetweenTurns, false);
	listOfPointedCubes.Empty();
	score++;
}

void ALevelManager::GameOver()
{
	listOfCube.Empty();
	listOfPointedCubes.Empty();
	listOfTempCubes.Empty();
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

	if (listOfCube.Num() == listOfPointedCubes.Num())
	{
		EvaulateResult();
	}
	if (listOfCube.Num() < listOfPointedCubes.Num())
	{
		GameOver();
	}
}
