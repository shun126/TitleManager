# Change Log - Title Manager Plug-in

## 20260620-1.1 (2)
### Changes
- **Fix**: Corrected missing `%s` format specifiers in `TitleManagerComponent` error logs, which previously failed to output the category name and database name (`SetExperience` / `AddExperience` / `GetExperienceRatio` / `SetProficiency` / `AddProficiency`)
- **Fix**: Corrected an incorrect module name passed to the `IMPLEMENT_MODULE` macro in `TitleManagerEditorModule.cpp` (`TitleManagerEditorModule` → `TitleManagerEditor`)
### 変更点
- **Fix**: `TitleManagerComponent` のエラーログでフォーマット文字列に `%s` が欠落しており、カテゴリ名・データベース名が出力されない不具合を修正（`SetExperience` / `AddExperience` / `GetExperienceRatio` / `SetProficiency` / `AddProficiency`）
- **Fix**: `TitleManagerEditorModule.cpp` の `IMPLEMENT_MODULE` マクロに渡すモジュール名が誤っていた（`TitleManagerEditorModule` → `TitleManagerEditor`）問題を修正

## 20241101-v1.0 (1)
### Changes
* Initial release version
### 変更点
* 初回リリース版

