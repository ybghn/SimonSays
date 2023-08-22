// Fill out your copyright notice in the Description page of Project Settings.


#include "ArrowBasedLevelCreator.h"
#include <SimonSays_UE4/CenterCube.h>


ArrowBasedLevelCreator::ArrowBasedLevelCreator(ACenterCube* _centerCube, TArray<AColorCube*> _cubes)
	:LevelCreatorBase(_cubes)
{	
	centerCube = _centerCube;

}

ArrowBasedLevelCreator::~ArrowBasedLevelCreator()
{
}

void ArrowBasedLevelCreator::Execute()
{
	AColorCube* fakeCube = GetFakeCube();
	if(fakeCube)
		fakeCube->Blink();
	
	centerCube->SetArrowEnable(Type());

}

AColorCube* ArrowBasedLevelCreator::GetFakeCube()
{
	TypeOfCube tempColor;

	while (1)
	{
		 tempColor = (TypeOfCube)FMath::RandRange(0, 3);

		if (tempColor != Type())
		{
			break;
			
		}
	}

	for (auto c : cubesInScene)
	{
		if (c->Type() == tempColor)
		{
			return c;
		}
	}


	return nullptr;
	
}
