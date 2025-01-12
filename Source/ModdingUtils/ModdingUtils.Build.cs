using UnrealBuildTool;

public class ModdingUtils : ModuleRules
{
	public ModdingUtils(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		
		PublicIncludePaths.AddRange(
			new string[] {
			}
		);
				
		
		PrivateIncludePaths.AddRange(
			new string[] {
			}
		);
			
		
		PublicDependencyModuleNames.AddRange(
			new string[]
			{
				"Core",
                "CoreUObject",
				"Engine"
            }
		);
			
		
		PrivateDependencyModuleNames.AddRange(
			new string[]
			{
                "ApplicationCore",
                "ContentBrowser",
                "Core",
                "EditorStyle",
				"Slate",
				"SlateCore",
				"ToolMenus",
                "UnrealEd"
            }
        );
		
		
		DynamicallyLoadedModuleNames.AddRange(
			new string[]
			{
			}
		);
	}
}
