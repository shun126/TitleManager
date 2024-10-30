/**
称号マネージャー
@author		Shun Moriya
@copyright	2024- Shun Moriya
All Rights Reserved.
*/

#pragma once
#include <CoreMinimal.h>

DECLARE_LOG_CATEGORY_EXTERN(TitleManagerLogger, Log, All);
#define TITLE_MANAGER_ERROR(Format, ...)	UE_LOG(TitleManagerLogger, Error, Format, ##__VA_ARGS__)
#define TITLE_MANAGER_WARNING(Format, ...)	UE_LOG(TitleManagerLogger, Warning, Format, ##__VA_ARGS__)
#define TITLE_MANAGER_DISPLAY(Format, ...)	UE_LOG(TitleManagerLogger, Display, Format, ##__VA_ARGS__)
#define TITLE_MANAGER_LOG(Format, ...)		UE_LOG(TitleManagerLogger, Log, Format, ##__VA_ARGS__)
#define TITLE_MANAGER_VERBOSE(Format, ...)	UE_LOG(TitleManagerLogger, Verbose, Format, ##__VA_ARGS__)
