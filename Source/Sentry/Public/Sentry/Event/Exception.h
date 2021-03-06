#pragma once
#include "Containers/UnrealString.h"

#include "SentryMacroUtils.hxx"

#include "Exception.generated.h"

// https://develop.sentry.dev/sdk/event-payloads/types/#exception
USTRUCT()
struct SENTRY_API FSentryException
{
	GENERATED_BODY()

	UPROPERTY()
	FString Type;

	UPROPERTY()
	FString Value;

	UPROPERTY()
	FString Module;

	UPROPERTY()
	FString ThreadId;

	SENTRY_SETTER(FSentryException, FString, Type);
	SENTRY_SETTER(FSentryException, FString, Value);
	SENTRY_SETTER(FSentryException, FString, Module);
	SENTRY_SETTER(FSentryException, FString, ThreadId);
};
