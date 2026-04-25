/**
@author		Shun Moriya
@copyright 2024 Shun Moriya All Rights Reserved.
*/

using UnrealBuildTool;
using System.Collections.Generic;

public class TitleManagerDemoEditorTarget : TargetRules
{
	public TitleManagerDemoEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("TitleManagerDemo");
	}
}
