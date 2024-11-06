/**
@author		Shun Moriya
@copyright 2024 Shun Moriya All Rights Reserved.
*/

#pragma once
#include "TitleManagerDatabase.h"
#include "ExperienceCategoryValue.h"
#include <Components/ActorComponent.h>
#include "TitleManagerComponent.generated.h"

/**
 * Title Manager Serialization Data
 * 称号マネージャシリアライズデータ
 */
USTRUCT(BlueprintType)
struct TITLEMANAGER_API FTitleManagerSerializeData
{
	GENERATED_BODY()

	UPROPERTY()
	TMap<FString, FExperienceCategoryValue> ExperienceCategoryValue;
};

/**
 * Title Manager
 * 称号マネージャ
 */
UCLASS(Blueprintable, BlueprintType, ClassGroup = TitleManager, meta = (BlueprintSpawnableComponent))
class TITLEMANAGER_API UTitleManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	explicit UTitleManagerComponent(const FObjectInitializer& objectInitializer);
	virtual ~UTitleManagerComponent() override = default;

	/**
	 * Load
	 * ロード
	 * @param titleManagerSerializeData ロードするデータ
	 */
	UFUNCTION(BlueprintCallable, Category = "TitleManager")
	bool Load(const FTitleManagerSerializeData& titleManagerSerializeData);

	/**
	 * Save
	 * セーブ
	 * @return 経験値と熟練度
	 */
	UFUNCTION(BlueprintCallable, Category = "TitleManager")
	FTitleManagerSerializeData Save() const;

	/**
	 * Get experience.
	 * 経験値を取得します。
	 * @param categoryName	カテゴリ名
	 * @return 経験値
	 */
	UFUNCTION(BlueprintCallable, Category = "TitleManager|Experience")
	int32 GetExperience(const FString& categoryName);

	/**
	 * Set the experience points. The value is clamped within the ExperienceRange of the ExperienceCategory.
	 * 経験値を設定します。値はExperienceCategoryのExperienceRange範囲内に切り詰めます。
	 * @param categoryName	カテゴリ名
	 * @param experience	経験値
	 * @return 設定の結果
	 */
	UFUNCTION(BlueprintCallable, Category = "TitleManager|Experience")
	int32 SetExperience(const FString& categoryName, int32 experience);

	/**
	 * Add to the experience points. The value is clamped within the ExperienceRange of the ExperienceCategory.
	 * 経験値に加算します。値はExperienceCategoryのExperienceRange範囲内に切り詰めます。
	 * @param categoryName	カテゴリ名
	 * @param experience	増減経験値
	 * @return 加算後の結果
	 */
	UFUNCTION(BlueprintCallable, Category = "TitleManager|Experience")
	int32 AddExperience(const FString& categoryName, const int32 experience = 1);

	/**
	 * Get the experience points ratio.
	 * 経験値の比率を取得します。
	 * @param categoryName	カテゴリ名
	 * @return	0.0 ～ 1.0
	 */
	UFUNCTION(BlueprintCallable, Category = "TitleManager|Experience")
	float GetExperienceRatio(const FString& categoryName);

	/**
	 * Get the item's proficiency level.
	 * アイテムの熟練度を取得します。
	 * @param categoryName	カテゴリ名
	 * @param itemName		アイテム名
	 * @return 経験値
	 */
	UFUNCTION(BlueprintCallable, Category = "TitleManager|Proficiency")
	int32 GetProficiency(const FString& categoryName, const FString& itemName);

	/**
	 * Set the item's proficiency level. The value is clamped within the ProficiencyRange of the ExperienceCategory.
	 * アイテムの熟練度を設定します。値はExperienceCategoryのProficiencyRange範囲内に切り詰めます。
	 * @param categoryName	カテゴリ名
	 * @param itemName		アイテム名
	 * @param proficiency	経験値
	 * @return 経験値
	 */
	UFUNCTION(BlueprintCallable, Category = "TitleManager|Proficiency")
	int32 SetProficiency(const FString& categoryName, const FString& itemName, int32 proficiency);

	/**
	 * Add to the item's proficiency level. The value is clamped within the ProficiencyRange of the ExperienceCategory.
	 * アイテムの熟練度に加算します。値はExperienceCategoryのProficiencyRange範囲内に切り詰めます。
	 * @param categoryName	カテゴリ名
	 * @param itemName		アイテム名
	 * @param proficiency	増減経験値
	 * @return 加算後の結果
	 */
	UFUNCTION(BlueprintCallable, Category = "TitleManager|Proficiency")
	int32 AddProficiency(const FString& categoryName, const FString& itemName, const int32 proficiency = 1);

	/**
	 * Get the item's proficiency ratio.
	 * アイテムの熟練度の比率を取得します。
	 * @param categoryName	カテゴリ名
	 * @param itemName		アイテム名
	 * @return	0.0 ～ 1.0
	 */
	UFUNCTION(BlueprintCallable, Category = "TitleManager|Proficiency")
	float GetProficiencyRatio(const FString& categoryName, const FString& itemName);

	/**
	 * Get the quantity owned.
	 * 所有数を取得します
	 * @param categoryName	カテゴリ名
	 * @param itemName		アイテム名
	 * @return	所有数
	 */
	UFUNCTION(BlueprintCallable, Category = "TitleManager|Quantity")
	uint8 GetQuantity(const FString& categoryName, const FString& itemName);

	/**
	 * Set the quantity owned.
	 * 所有数を設定します
	 * @param categoryName	カテゴリ名
	 * @param itemName		アイテム名
	 * @param quantity		所有数
	 */
	UFUNCTION(BlueprintCallable, Category = "TitleManager|Quantity")
	void SetQuantity(const FString& categoryName, const FString& itemName, const uint8 quantity);

	/**
	 * Add to the quantity owned.
	 * 所有数を加算します
	 * @param categoryName	カテゴリ名
	 * @param itemName		アイテム名
	 * @param quantity		加算する所有数
	 * @return	所有数
	 */
	UFUNCTION(BlueprintCallable, Category = "TitleManager|Quantity")
	uint8 AddQuantity(const FString& categoryName, const FString& itemName, const int32 quantity = 1);

	/**
	 * Search for the highest experience points title.
	 * 最も経験値の高い称号を検索します
	 * @return 称号名
	 */
	UFUNCTION(BlueprintCallable, Category = "TitleManager")
	FString FindMaxExperienceTitle() const;

	/**
	 * Search for the titles in the category.
	 * カテゴリの称号を検索します
	 * @param categoryName カテゴリ名
	 * @return 称号名
	 */
	UFUNCTION(BlueprintCallable, Category = "TitleManager")
	FString FindCategoryTitle(const FString& categoryName) const;

public:
	/**
	 * Search for the experience points category.
	 * 経験値カテゴリを検索します
	 * @param categoryName カテゴリ名
	 * @return nullptrなら検索失敗
	 */
	const FExperienceCategoryData* FindExperienceCategoryData(const FString& categoryName) const;

	/**
	 * Get UTitleManagerDatabase
	 * UTitleManagerDatabaseを取得します
	 * @return UTitleManagerDatabase
	 */
	const UTitleManagerDatabase* GetTitleManagerDatabase() const noexcept;

	/**
	 * Gain experience and proficiency
	 * 経験値や熟練度を取得します
	 * @return TMap<FString, FExperienceCategoryValue>
	 */
	const TMap<FString, FExperienceCategoryValue>& GetExperienceCategoryValue() const noexcept;

public:
	virtual void InitializeComponent() override;

private:
	bool InitializeExperienceCategoryValue();

protected:
	/**
	 * Please specify the title database.
	 * 称号データベースを指定してください。
	 */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TitleManager")
	TObjectPtr<UTitleManagerDatabase> TitleManagerDatabase;

	/**
	 * Experience points and proficiency level.
	 * 経験値と熟練度
	 */
	UPROPERTY(VisibleInstanceOnly, BlueprintReadOnly, Category = "TitleManager")
	TMap<FString, FExperienceCategoryValue> ExperienceCategoryValue;
};
