// Fill out your copyright notice in the Description page of Project Settings.


#include "CenterCube.h"

// Sets default values
ACenterCube::ACenterCube()
{
	PrimaryActorTick.bCanEverTick = true;


	mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	SetRootComponent(mesh);

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

	ConstructorHelpers::FObjectFinder<UPaperSprite> arrowSprite(TEXT("PaperSprite'/Game/2D/ArrowSprite.ArrowSprite'"));
	
	UPaperSprite* sprite  = nullptr;

	
	if (arrowSprite.Object)
	{

		sprite = arrowSprite.Object;

	}


	UMaterialInstanceDynamic* instanceMat = UMaterialInstanceDynamic::Create(material, nullptr);
	instanceMat->SetVectorParameterValue("Color", FLinearColor::Gray);
	mesh->SetMaterial(0, instanceMat);

	int coeff = 51;
	 redSprite = CreateDefaultSubobject<UPaperSpriteComponent>("red");
	redSprite->AttachToComponent(mesh, FAttachmentTransformRules::KeepWorldTransform);
	redSprite->SetRelativeLocation(FVector(coeff, 0, 2*coeff));
	redSprite->SetRelativeRotation(FRotator::MakeFromEuler(FVector(270,0,270)));


	 blueSprite = CreateDefaultSubobject<UPaperSpriteComponent>("blue");
	blueSprite->AttachToComponent(mesh, FAttachmentTransformRules::KeepWorldTransform);
	blueSprite->SetRelativeLocation(FVector(0, -coeff, 2*coeff));
	blueSprite->SetRelativeRotation(FRotator::MakeFromEuler(FVector(90, 0, 0)));

	greenSprite = CreateDefaultSubobject<UPaperSpriteComponent>("green");
	greenSprite->AttachToComponent(mesh, FAttachmentTransformRules::KeepWorldTransform);
	greenSprite->SetRelativeLocation(FVector(0, coeff, 2*coeff));
	greenSprite->SetRelativeRotation(FRotator::MakeFromEuler(FVector(270, 0, 0)));


	 yellowSprite = CreateDefaultSubobject<UPaperSpriteComponent>("yellow");
	yellowSprite->AttachToComponent(mesh, FAttachmentTransformRules::KeepWorldTransform);
	yellowSprite->SetRelativeLocation(FVector(-coeff, 0, 2*coeff));
	yellowSprite->SetRelativeRotation(FRotator::MakeFromEuler(FVector(270, 0, 90)));


	arrows.Add(redSprite);
	arrows.Add(yellowSprite);
	arrows.Add(blueSprite);
	arrows.Add(greenSprite);
	for (auto a : arrows)
	{
		a->SetSprite(sprite);
		a->SetWorldScale3D(FVector(0.05));
	
	}

	text = CreateDefaultSubobject<UTextRenderComponent>("CenterText");
	text->AttachToComponent(mesh, FAttachmentTransformRules::KeepWorldTransform);
	text->SetRelativeLocation(FVector(0, 0, 2 * coeff));
	text->SetRelativeRotation(FRotator::MakeFromEuler(FVector(-45, 90, 0)));
	text->SetText("");


}

// Called when the game starts or when spawned
void ACenterCube::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ACenterCube::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACenterCube::SetText(FString _text, FColor _color)
{
	text->SetText(_text);
	text->SetTextRenderColor(_color);
	FTimerHandle temp;
	GetWorldTimerManager().SetTimer(temp, this, &ACenterCube::SetOffEveryThing, offTime, false); 
}

void ACenterCube::SetArrowEnable(TypeOfCube _correctColor)
{
	for (auto a : arrows)
	{
		a->SetVisibility(false);
	}

	switch (_correctColor)
	{
	case Red:
		redSprite->SetVisibility(true);
		break;
	case Blue:
		blueSprite->SetVisibility(true);

		break;
	case Yellow:
		yellowSprite->SetVisibility(true);

		break;
	case Green:
		greenSprite->SetVisibility(true);

		break;
	default:
		break;
	}
	FTimerHandle temp;
	GetWorldTimerManager().SetTimer(temp, this, &ACenterCube::SetOffEveryThing, offTime, false);
}

void ACenterCube::SetOffEveryThing()
{
	for (auto a : arrows)
	{
		a->SetVisibility(false);
	}text->SetText("");
	 
}

