// Copyright Epic Games, Inc. All Rights Reserved.

#include "DeleteActorsStyle.h"
#include "DeleteActors.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FDeleteActorsStyle::StyleInstance = nullptr;

void FDeleteActorsStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FDeleteActorsStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FDeleteActorsStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("DeleteActorsStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FDeleteActorsStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("DeleteActorsStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("DeleteActors")->GetBaseDir() / TEXT("Resources"));

	Style->Set("DeleteActors.PluginAction", new IMAGE_BRUSH_SVG(TEXT("PlaceholderButtonIcon"), Icon20x20));
	return Style;
}

void FDeleteActorsStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FDeleteActorsStyle::Get()
{
	return *StyleInstance;
}
