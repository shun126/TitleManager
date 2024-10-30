/**
称号マネージャー
@author		Shun Moriya
@copyright	2024- Shun Moriya
All Rights Reserved.
*/

#pragma once
#include <CoreMinimal.h>
#include "ProficiencyValue.generated.h"

/**
 * Proficiency Level
 * 熟練度
 */
USTRUCT(Blueprintable, BlueprintType)
struct TITLEMANAGER_API FProficiencyValue
{
	GENERATED_BODY()

	/**
	 * Item Proficiency Level
	 * アイテムの熟練度
	 */
	UPROPERTY(BlueprintReadWrite, Category = "TitleManager")
	int32 Proficiency;

	/**
	 * Quantity
	 * 所有数
	 */
	UPROPERTY(BlueprintReadWrite, Category = "TitleManager")
	uint8 Quantity = 0;
};
