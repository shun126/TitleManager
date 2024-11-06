/**
@author		Shun Moriya
@copyright 2024 Shun Moriya All Rights Reserved.
*/

#pragma once
#include <CoreMinimal.h>
#include <Factories/Factory.h>
#include "TitleManagerDatabaseFactory.generated.h"

UCLASS(ClassGroup = "TitleManager")
class TITLEMANAGEREDITOR_API UTitleManagerDatabaseFactory : public UFactory
{
	GENERATED_BODY()

public:
	UTitleManagerDatabaseFactory();
	virtual ~UTitleManagerDatabaseFactory() override = default;

	// UFactory overrides
	virtual UObject* FactoryCreateNew(UClass* InClass, UObject* InParent, FName InName, EObjectFlags Flags, UObject* Context, FFeedbackContext* Warn) override;
};
