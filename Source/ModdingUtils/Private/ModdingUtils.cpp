#include "ModdingUtils.h"
#include "ContentBrowserModule.h"
#include "IContentBrowserSingleton.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"
#include "AssetRegistry/AssetRegistryModule.h"
#include "HAL/PlatformApplicationMisc.h"

void FModdingUtilsModule::StartupModule()
{
    FContentBrowserModule& ContentBrowserModule = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");

    ContentBrowserModule.GetAllAssetViewContextMenuExtenders().Add(
        FContentBrowserMenuExtender_SelectedAssets::CreateRaw(this, &FModdingUtilsModule::OnExtendContentBrowserAssetMenu)
    );
}

void FModdingUtilsModule::ShutdownModule()
{
    if (UObjectInitialized())
    {
        FContentBrowserModule* ContentBrowserModule = FModuleManager::GetModulePtr<FContentBrowserModule>("ContentBrowser");
        if (ContentBrowserModule)
        {
            ContentBrowserModule->GetAllAssetViewContextMenuExtenders().RemoveAll([this](const FContentBrowserMenuExtender_SelectedAssets& Extender) {
                return Extender.GetHandle() == ContentBrowserExtenderHandle;
            });
        }
    }
}

TSharedRef<FExtender> FModdingUtilsModule::OnExtendContentBrowserAssetMenu(const TArray<FAssetData>& SelectedAssets)
{
    TSharedRef<FExtender> Extender = MakeShared<FExtender>();

    Extender->AddMenuExtension(
        "CopyFilePath",
        EExtensionHook::After,
        nullptr,
        FMenuExtensionDelegate::CreateLambda([SelectedAssets](FMenuBuilder& MenuBuilder) {
            MenuBuilder.AddMenuEntry(
                FText::FromString("Copy Full Path"),
                FText::FromString("Copy the full asset path in /Game format to the clipboard."),
                FSlateIcon(FAppStyle::GetAppStyleSetName(), "GenericCommands.Copy"),
                FUIAction(FExecuteAction::CreateLambda([SelectedAssets]() {
                    if (SelectedAssets.Num() > 0)
                    {
                        const FString FullPath = SelectedAssets[0].ObjectPath.ToString();
                        FPlatformApplicationMisc::ClipboardCopy(*FullPath);
                    }
                }))
            );
        })
    );

    return Extender;
}

IMPLEMENT_MODULE(FModdingUtilsModule, ModdingUtils)