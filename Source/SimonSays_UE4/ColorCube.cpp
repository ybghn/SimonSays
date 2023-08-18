// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorCube.h"

// Sets default values
AColorCube::AColorCube()
{
	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	ConstructorHelpers::FObjectFinder<UStaticMesh> meshModel(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));

	if (meshModel.Object)
	{
		mesh->SetStaticMesh(meshModel.Object);

	}
	ConstructorHelpers::FObjectFinder<UMaterial> mat(TEXT("Material'/Game/CubeMaterials.CubeMaterials'"));
	if (mat.Object)
	{
		material = mat.Object;
	}

	materialInstance = UMaterialInstanceDynamic::Create(material, nullptr);


	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AColorCube::BeginPlay()
{
	Super::BeginPlay();

	
}




// Called every frame
void AColorCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AColorCube::SetType(TypeOfCube _type)
{
	type = _type;
	SetInitialColors();
}

void AColorCube::Blink()
{
	
	bCubeShining = 1;
	GetWorldTimerManager().SetTimer(timerHandle, this, &AColorCube::BlinkLoopAnimation, blinkDuration, true);


}

void AColorCube::SetInitialColors()
{

	materialInstance = UMaterialInstanceDynamic::Create(material, this);

	switch (type)
	{
	case Red:
		materialInstance->SetVectorParameterValue("Color", FLinearColor::Red);
		break;
	case Blue:
		materialInstance->SetVectorParameterValue("Color", FLinearColor::Blue);
		break;
	case Yellow:
		materialInstance->SetVectorParameterValue("Color", FLinearColor::Yellow);
		break;
	case Green:
		materialInstance->SetVectorParameterValue("Color", FLinearColor::Green);
		break;
	default:
		materialInstance->SetVectorParameterValue("Color", FLinearColor::Red);
		break;
	}
	mesh->SetMaterial(0, materialInstance);
}

void AColorCube::BlinkLoopAnimation()
{

	
	float increment = 0.8f;

	
	if (bCubeShining)
	{
		brightnessValue += increment;
	}
	else {

		brightnessValue -= increment;
	}
	if (brightnessValue < 0)
	{
		brightnessValue = 0;
		GetWorldTimerManager().ClearTimer(timerHandle);

	}
	if (brightnessValue > 10)
	{
		brightnessValue = 10;
		GetWorldTimerManager().ClearTimer(timerHandle);
		BlinkOff();
	}

	materialInstance->SetScalarParameterValue("Brightness", brightnessValue);
	mesh->SetMaterial(0, materialInstance);

}

void AColorCube::BlinkOff()
{
	bCubeShining = 0;
	GetWorldTimerManager().SetTimer(timerHandle, this, &AColorCube::BlinkLoopAnimation, blinkDuration, true);
}

