/**
@author		Shun Moriya
@copyright 2024 Shun Moriya All Rights Reserved.
*/

using UnrealBuildTool;
using System.Collections.Generic;

public class TitleManagerDemoTarget : TargetRules
{
	public TitleManagerDemoTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;
		IncludeOrderVersion = EngineIncludeOrderVersion.Latest;
		ExtraModuleNames.Add("TitleManagerDemo");
	}
}
