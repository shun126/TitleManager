/**
@author		Shun Moriya
@copyright	2024- Shun Moriya
All Rights Reserved.
*/

#include "TitleManagerDatabaseFactory.h"
#include "TitleManagerDatabase.h"

UTitleManagerDatabaseFactory::UTitleManagerDatabaseFactory()
{
	SupportedClass = UTitleManagerDatabase::StaticClass();
	bCreateNew = true;
	bEditAfterNew = true;
}

UObject* UTitleManagerDatabaseFactory::FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn)
{
	return NewObject<UTitleManagerDatabase>(InParent, InClass, InName, Flags);
}
