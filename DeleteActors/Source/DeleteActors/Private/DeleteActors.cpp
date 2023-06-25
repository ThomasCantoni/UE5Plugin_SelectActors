// Copyright Epic Games, Inc. All Rights Reserved.

#include "DeleteActors.h"
#include "DeleteActorsStyle.h"
#include "DeleteActorsCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "Widgets/Input/SEditableTextBox.h"
#include "Editor.h"
#include "Framework/Docking/TabManager.h"
#include "Engine/Selection.h"

static const FName DeleteActorsTabName("TestDeleteActors");

#define LOCTEXT_NAMESPACE "FDeleteActorsModule"



void FDeleteActorsModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FDeleteActorsStyle::Initialize();
	FDeleteActorsStyle::ReloadTextures();
	
	FDeleteActorsCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);
	
	PluginCommands->MapAction(
		FDeleteActorsCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FDeleteActorsModule::PluginButtonClicked),
		FCanExecuteAction());
	
	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FDeleteActorsModule::RegisterMenus));



	const TSharedRef<FGlobalTabmanager> TM= FGlobalTabmanager::Get();
	 

	FTabSpawnerEntry spawner = TM->RegisterNomadTabSpawner(DeleteActorsTabName, FOnSpawnTab::CreateRaw(this, &FDeleteActorsModule::SpawnNomadTab));
	


}

void FDeleteActorsModule::TextCommitted(const FText& InText, ETextCommit::Type InCommitType)
{
	if (InCommitType == ETextCommit::OnEnter)
	{
		SelectActorsInOutliner(InText);
	}
}
TSharedRef<SDockTab> FDeleteActorsModule::SpawnNomadTab(const FSpawnTabArgs& TabSpawnArgs)
{
	return SNew(SDockTab).TabRole(ETabRole::NomadTab)
		[
			SNew(SVerticalBox) +
			SVerticalBox::Slot().AutoHeight().HAlign(EHorizontalAlignment::HAlign_Left).Padding(20,10,0,8)
			[
				SNew(STextBlock).Text(LOCTEXT("InsertTheSubstringToSearch", "Insert the substring to search"))
			]
			+
			SVerticalBox::Slot().AutoHeight().HAlign(EHorizontalAlignment::HAlign_Left).Padding(20, 10, 0, 8)
			[
				SNew(SEditableTextBox)
				.Text(LOCTEXT("", ""))
				.OnTextCommitted(FOnTextCommitted::CreateRaw(this, &FDeleteActorsModule::TextCommitted))
				.MinDesiredWidth(150)
			]
		];
}
void FDeleteActorsModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FDeleteActorsStyle::Shutdown();

	FDeleteActorsCommands::Unregister();
}

void FDeleteActorsModule::SelectActorsInOutliner(const FText& label)
{
	ULevel* worldContext = GEditor->GetEditorWorldContext().World()->GetCurrentLevel();
	
	TArray<AActor*> test = worldContext->Actors;
	for (AActor* actor : test)
	{
		if (actor != nullptr)
		{

		FString actorLabel = actor->GetActorLabel();
		if (actorLabel.Contains(label.ToString()))
		{
			GEditor->SelectActor(actor, true, true, false);

		}
		}
	}

	// Put your "OnButtonClicked" stuff here

}

bool FDeleteActorsModule::Exec(UWorld* world, const TCHAR* Cmd, FOutputDevice& Ar) 
{
	
	if (FParse::Command(&Cmd, TEXT("SelectActorsContaining")))
	{
		SelectActorsInOutliner(FText::FromString(Cmd));
		return true;
	}
	return false;
}

void FDeleteActorsModule::PluginButtonClicked()
{
	
	FText DialogText = FText::FromString("Delete selected actors?");
	if (FMessageDialog::Open(EAppMsgType::OkCancel, DialogText) == EAppReturnType::Ok)
	{

		TArray<AActor*> Actors;
		GEditor->GetSelectedActors()->GetSelectedObjects<AActor>(Actors);
		ULevel* worldContext = GEditor->GetEditorWorldContext().World()->GetCurrentLevel();
		
		

		for (AActor* actor : Actors)
		{
			actor->Destroy();
		}
	}
}

void FDeleteActorsModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FDeleteActorsCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FDeleteActorsCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FDeleteActorsModule, DeleteActors)