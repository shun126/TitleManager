/**
\author		Shun Moriya
\copyright	2024- Shun Moriya
All Rights Reserved.
*/

using UnrealBuildTool;

public class TitleManagerEditor : ModuleRules
{
	public TitleManagerEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(new string[] {});
		PrivateIncludePaths.AddRange(new string[] {});

		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
            }
		);
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
				"Projects",
				"InputCore",
				"ToolMenus",
				"CoreUObject",
				"Engine",
            }
        );
        if (Target.bBuildEditor)
        {
            PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "UnrealEd",
                    "Slate",
                    "SlateCore",
                    "TitleManager",
                });
        }

        BuildVersion Version;
        if (BuildVersion.TryRead(BuildVersion.GetDefaultFileName(), out Version))
        {
            if (Version.MajorVersion == 5)
            {
                PrivateDependencyModuleNames.AddRange(new string[] { "EditorFramework" });
            }
        }
    }
}
