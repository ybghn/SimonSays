// Fill out your copyright notice in the Description page of Project Settings.


#include "TextBasedLevelCreator.h"



TextBasedLevelCreator::TextBasedLevelCreator(ACenterCube* _centerCube, TArray<AColorCube*> _cubes)
	: LevelCreatorBase(_cubes)
{
	centerCube = _centerCube;
}

TextBasedLevelCreator::~TextBasedLevelCreator()
{
}

void TextBasedLevelCreator::Execute()
{
	FString text = "";
	switch (Type())
	{
	case Red:
		text = "Kýrmýzý";
		break;
	case Blue :
		text = "Mavi";
		break;
	case Green:
		text = "Yeþil";
			break;
	case Yellow:
		text = "Sarý";
		break;
	default:
		break;
	}
	centerCube->SetText(text,GetFakeColor());


}

FColor TextBasedLevelCreator::GetFakeColor()
{
	TypeOfCube type;
	while (1)
	{
		 type= (TypeOfCube)FMath::RandRange(0, 3);
		if (type != Type()) break;
	}


	FColor tempColor;
	switch (type)
	{
	case Red:
		tempColor = FColor::Red;
		break;
	case Blue:
		tempColor = FColor::Blue;
		break;
	case Yellow:
		tempColor = FColor::Yellow;
		break;
	case Green:
		tempColor = FColor::Green;
		break;
	default:
		tempColor = FColor::Black; //

		break;
	}
	return tempColor;
}

