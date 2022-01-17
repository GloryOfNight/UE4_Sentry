#pragma once
#include "SentryCommon.generated.h"

// https://develop.sentry.dev/sdk/event-payloads/types/#typedef-Level
UENUM()
enum class ESentryLevel : uint8
{
	Debug,
	Error,
	Fatal,
	Info,
	Warning
};