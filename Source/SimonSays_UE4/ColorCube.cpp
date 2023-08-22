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


void AColorCube::Blink()
{

	float half = offTime / 2;
	float target = 10;
	float increment = 0.5;
	brightnessValue = 0;
	float duration = 0.01f;
	blinkAnimationDlgt.BindUFunction(this, FName("BlinkLoopAnimation"), increment, target);
	GetWorldTimerManager().SetTimer(timerHandle, blinkAnimationDlgt, duration, true);

}

void AColorCube::BlinkLoopAnimation(float increment,float targetValue)
{
	FString msg = "Birghness : " + FString::SanitizeFloat(brightnessValue);
	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Red, msg);
	
	brightnessValue += increment;
	
	if (targetValue == 10)
	{
		if(brightnessValue>targetValue)
		{
			brightnessValue = 10;
			GetWorldTimerManager().ClearTimer(timerHandle);

			blinkAnimationDlgt.Unbind();;         // 
			blinkAnimationDlgt.BindUFunction(this, FName("BlinkLoopAnimation"), -increment, 0.f);
			GetWorldTimerManager().SetTimer(timerHandle, blinkAnimationDlgt, 0.01f, true);

		}
	}
	else if (targetValue == 0)
	{
		if (brightnessValue<0)
		{
			brightnessValue = 0;
			GetWorldTimerManager().ClearTimer(timerHandle);

		}
	}
	

	materialInstance->SetScalarParameterValue("Brightness", brightnessValue);
	mesh->SetMaterial(0, materialInstance);

}


