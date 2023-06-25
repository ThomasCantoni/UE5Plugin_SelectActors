// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Modules/ModuleManager.h"
#include "Kismet/GameplayStatics.h"


class FToolBarBuilder;
class FMenuBuilder;

class FDeleteActorsModule : public IModuleInterface, public FSelfRegisteringExec 
{
public:

	/** IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	
	/** This function will be bound to Command. */
	void PluginButtonClicked();
	void SelectActorsInOutliner(const FText& actorLabel);
	TSharedRef<SDockTab>SpawnNomadTab(const FSpawnTabArgs& TabSpawnArgs);
	void TextCommitted(const FText& InText, ETextCommit::Type InCommitType);
	virtual bool Exec(UWorld* world, const TCHAR* Cmd, FOutputDevice& Ar) override;
	
	TSharedPtr<class FUICommandList> PluginCommands;
	void RegisterMenus();
private:



private:
	
	
};
