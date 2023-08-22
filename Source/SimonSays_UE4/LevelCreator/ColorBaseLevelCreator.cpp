// Fill out your copyright notice in the Description page of Project Settings.


#include "ColorBaseLevelCreator.h"

ColorBaseLevelCreator::ColorBaseLevelCreator(TArray<AColorCube*> _cubes) : LevelCreatorBase(_cubes)
{
	for (AColorCube* c : _cubes)
	{
		if (Type() == c->Type())
		{
			myCube = c;
			break;
		}

	}
}

ColorBaseLevelCreator::~ColorBaseLevelCreator()
{
}

void ColorBaseLevelCreator::Execute()
{
	myCube->Blink();
}

