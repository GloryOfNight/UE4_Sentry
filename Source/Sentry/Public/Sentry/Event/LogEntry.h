#pragma once

#include "LogEntry.generated.h"

// https://develop.sentry.dev/sdk/event-payloads/types/#logentry
USTRUCT()
struct SENTRY_API FSentryLogEntry
{
	GENERATED_BODY()

	UPROPERTY()
	FString Message{};

	UPROPERTY()
	TArray<FString> Params{};
};
