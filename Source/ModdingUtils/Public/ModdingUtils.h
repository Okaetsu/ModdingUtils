#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "ToolMenus.h"

class FModdingUtilsModule : public IModuleInterface
{
public:
    virtual void StartupModule() override;
    virtual void ShutdownModule() override;

private:
    TSharedRef<FExtender> OnExtendContentBrowserAssetMenu(const TArray<FAssetData>& SelectedAssets);
    FDelegateHandle ContentBrowserExtenderHandle;
};
