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
		text = "Red";
		break;
	case Blue :
		text = "Blue";
		break;
	case Green:
		text = "Green";
			break;
	case Yellow:
		text = "Yellow";
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
		tempColor = RedColor.ToFColor(true);
		break;
	case Blue:
		tempColor = BlueColor.ToFColor(1);
		break;
	case Yellow:
		tempColor = YellowColor.ToFColor(1);
		break;
	case Green:
		tempColor = GreenColor.ToFColor(1);
		break;
	default:
		tempColor = FColor::Black; //

		break;
	}
	return tempColor;
}

