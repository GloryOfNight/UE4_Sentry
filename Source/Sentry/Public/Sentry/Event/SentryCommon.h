#pragma once
#include "SentryCommon.generated.h"

// https://develop.sentry.dev/sdk/event-payloads/types/#typedef-Level
UENUM()
namespace ESentryLevel
{
	enum Type
	{
		Debug,
		Error,
		Fatal,
		Info,
		Warning
	};
}

namespace ESentryLevel
{
	static TCHAR* ToString(ESentryLevel::Type Value) 
	{
		switch(Value)
		{
		case ESentryLevel::Debug:
			return TEXT("debug");
		case ESentryLevel::Error:
			return TEXT("error");
		case ESentryLevel::Fatal:
			return TEXT("fatal");
		case ESentryLevel::Info:
			return TEXT("info");
		case ESentryLevel::Warning:
			return TEXT("warning");
		}
		return TEXT("unhandled enum case");
	}
}