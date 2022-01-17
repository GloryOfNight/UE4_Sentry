// Copyright Epic Games, Inc. All Rights Reserved.

#include "Sentry/Sentry.h"

#define LOCTEXT_NAMESPACE "FSentryModule"

void FSentryModule::StartupModule()
{
	if(!Manager)
	{
		Manager = NewObject<USentryManager>();
	}
}

void FSentryModule::ShutdownModule()
{
	Manager->FinishDestroy();
	Manager = nullptr;
}

USentryManager* FSentryModule::GetManager()
{
	static FSentryModule* Module = nullptr;
	if(!Module)
	{
		Module = FModuleManager::GetModulePtr<FSentryModule>("FSentryModule");
	}
	return Module ? Module->Manager : nullptr;
}

#undef LOCTEXT_NAMESPACE

IMPLEMENT_MODULE(FSentryModule, Sentry)