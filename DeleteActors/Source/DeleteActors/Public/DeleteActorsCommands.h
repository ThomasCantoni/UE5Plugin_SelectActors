// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "DeleteActorsStyle.h"

class FDeleteActorsCommands : public TCommands<FDeleteActorsCommands>
{
public:

	FDeleteActorsCommands()
		: TCommands<FDeleteActorsCommands>(TEXT("DeleteActors"), NSLOCTEXT("Contexts", "DeleteActors", "DeleteActors Plugin"), NAME_None, FDeleteActorsStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
