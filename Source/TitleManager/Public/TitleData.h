/**
称号マネージャー
@author		Shun Moriya
@copyright	2024- Shun Moriya
All Rights Reserved.
*/

#pragma once
#include <CoreMinimal.h>
#include "TitleData.generated.h"

/**
 * Title
 * 称号
 */
USTRUCT(Blueprintable, BlueprintType)
struct TITLEMANAGER_API FTitleData
{
	GENERATED_BODY()

	/**
	 * Title Name
	 * 称号名
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TitleManager")
	FString TitleName;

	/**
	 * Experience to earn a title
	 * 称号を得る為の経験値
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TitleManager")
	int32 TitleAchievementExperience;
};
