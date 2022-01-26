#pragma once
#include "Containers/UnrealString.h"

#include "SentryMacroUtils.hxx"

#include "LogEntry.generated.h"

// https://develop.sentry.dev/sdk/event-payloads/types/#logentry
USTRUCT()
struct SENTRY_API FSentryLogEntry
{
	GENERATED_BODY()

	UPROPERTY()
	FString Message;

	UPROPERTY()
	TArray<FString> Params;

	SENTRY_SETTER(FSentryLogEntry, FString, Message);
	SENTRY_SETTER(FSentryLogEntry, TArray<FString>, Params);
};
