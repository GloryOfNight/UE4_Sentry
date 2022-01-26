#include "Sentry/SentryManager.h"

#include <Containers/UnrealString.h>
#include <Http.h>

#include "Sentry.h"

DEFINE_LOG_CATEGORY(LogSentryManager);

static FSentryApplicationInfo AppInfo;

FSentryManager::FSentryManager()
	: Url{}
	, Key{}
{
	const FString& DSN = USentrySettings::Get()->DSN;
	if(!DSN.IsEmpty())
	{
		LoadDSN(DSN, false);
	}
	else
	{
		UE_LOG(LogSentryManager, Display, TEXT("No DSN provided. Sentry will not work untill you setup DSN"));
	}
}

FSentryManager* FSentryManager::Get()
{
	return FSentryModule::GetManager();
}

FSentryApplicationInfo& FSentryManager::ApplicationInfo()
{
	return AppInfo;
}

void FSentryManager::SendException(ESentryLevel::Type Level, const FSentryException& Value)
{
	FSentryEvent_Json Event = FSentryEvent_Json()
								  .SetApplicationInfo(AppInfo)
								  .SetLevel(Level)
								  .SetException({Value});
	SendEventJson(std::move(Event));
}

void FSentryManager::SendLogEntry(ESentryLevel::Type Level, const FString& Message, TArray<FString>&& Params)
{
	SendLogEntry(Level, {Message, std::move(Params)});
}

void FSentryManager::SendLogEntry(ESentryLevel::Type Level, const FSentryLogEntry& Value)
{
	FSentryEvent_Json Event = FSentryEvent_Json()
								  .SetApplicationInfo(AppInfo)
								  .SetLevel(Level)
								  .SetLogEntry(Value);
	SendEventJson(std::move(Event));
}

void FSentryManager::SendEventJson(const FSentryEvent_Json& Value)
{
	SendJson(Value.ToJson());
}

void FSentryManager::SendEventJson(FSentryEvent_Json&& Value)
{
	SendJson(Value.ToJson());
}

void FSentryManager::SendJson(FString&& Json)
{
	if(Url.IsEmpty() || Key.IsEmpty())
	{
		UE_LOG(LogSentryManager, Error, TEXT("Cannot send, DSN not properly configured."))
		return;
	}

	const auto Settings = USentrySettings::Get();
#if WITH_EDITOR
	if(Settings->DisableInEditor)
	{
		return;
	}
#endif

	if(Settings->Enable)
	{
		FHttpModule* HttpModule = &FHttpModule::Get();
		FHttpRequestRef Request = HttpModule->CreateRequest();
		Request->SetURL(Url);
		Request->SetVerb("POST");
		Request->SetHeader("Content-Type", "application/json");
		Request->SetHeader("Accept", "application/json");

		const FString Auth = FString::Printf(TEXT("Sentry sentry_version=7, sentry_timestamp=%lld, sentry_key=%s"), FDateTime::UtcNow().ToUnixTimestamp(), *Key);
		Request->SetHeader("X-Sentry-Auth", Auth);
		Request->SetContentAsString(Json);

		Request->OnProcessRequestComplete().BindRaw(this, &FSentryManager::OnProcessRequestComplete);
		const bool Res = Request->ProcessRequest();
		if(Res)
		{
			UE_LOG(LogSentryManager, Verbose, TEXT("Sentry start processing http request - ok"))
		}
		else
		{
			UE_LOG(LogSentryManager, Error, TEXT("Sentry couldn't process http request"))
		}
	}
}

bool FSentryManager::LoadDSN(const FString& DSN, bool Reset)
{
	if(Reset)
	{
		Url = FString();
		Key = FString();
	}

	// 012345678.............................40....may vary.........
	// https://00112233445566778899aabbccddff00@sentry.companyname/0
	constexpr uint8 KeyLen = 32;
	constexpr uint8 KeyBegin = 8;
	constexpr uint8 KeyEnd = KeyBegin + KeyLen;

	int32 SlashIndex = INDEX_NONE;
	int32 AtIndex = INDEX_NONE;
	const bool IsValidDSN = DSN.Len() > 32 && DSN.FindLastChar('/', SlashIndex) && SlashIndex > KeyEnd &&
							DSN.FindLastChar('@', AtIndex) && AtIndex - KeyLen >= KeyBegin;

	if(IsValidDSN)
	{
		Key = FString(KeyLen, &DSN[KeyBegin]);

		const FString Domain = FString(SlashIndex - (KeyEnd + 1), &DSN[KeyEnd + 1]);
		const FString Project = FString(&DSN[SlashIndex], DSN.Len() - SlashIndex);
		Url = TEXT("https://") + Domain + TEXT("/api") + Project + TEXT("/store/");

		UE_LOG(LogSentryManager, Display, TEXT("DSN load - ok"));
	}
	else
	{
		UE_LOG(LogSentryManager, Error, TEXT("DSN load - failed"));
	}

	return IsValidDSN;
}

void FSentryManager::OnProcessRequestComplete(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bConnectedSuccessfully)
{
	if(bConnectedSuccessfully && Response->GetResponseCode() == EHttpResponseCodes::Ok)
	{
		UE_LOG(LogSentryManager, Verbose, TEXT("Sentry process request complete - ok"))
	}
	else
	{
		int32 ResponseCode{-1};
		if(Response) // not all platforms return valid Ptr to response when failed to process.
		{
			ResponseCode = Response->GetResponseCode();
		}
		UE_LOG(LogSentryManager, Error, TEXT("Sentry process request failed with: Response code: %i"), ResponseCode);
	}
	// TODO: retries
}