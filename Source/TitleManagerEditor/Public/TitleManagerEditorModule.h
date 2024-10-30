/**
@author		Shun Moriya
@copyright	2024- Shun Moriya
All Rights Reserved.
*/

#pragma once
#include <Modules/ModuleManager.h>

class TITLEMANAGEREDITOR_API FTitleManagerEditorModule : public IModuleInterface
{
public:
	FTitleManagerEditorModule() = default;
	virtual ~FTitleManagerEditorModule() override = default;

	// IModuleInterface implementation
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
};
