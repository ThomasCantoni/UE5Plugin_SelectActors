// Copyright Epic Games, Inc. All Rights Reserved.

#include "DeleteActorsCommands.h"

#define LOCTEXT_NAMESPACE "FDeleteActorsModule"

void FDeleteActorsCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "DeleteActors", "Delete Selected Actors", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
