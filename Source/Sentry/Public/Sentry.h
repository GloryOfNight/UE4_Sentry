// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <CoreMinimal.h>
#include <Modules/ModuleManager.h>

#include "Sentry/SentryManager.h"
#include "Sentry/SentrySettings.h"

class FSentryModule : public IModuleInterface
{
public:
	/** IModuleInterface implementation begin */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;
	/** IModuleInterface implementation end */
	
	/** @return pointer to SentryManager or nullptr if module not created correctly */
	SENTRY_API static FSentryManager* GetManager();

private:
	FSentryManager Manager = FSentryManager();
};
