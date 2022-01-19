#include "Sentry/Json/SentryJson.h"

#include <JsonObjectConverter.h>

FSentryEvent_Exception_Json::FSentryEvent_Exception_Json(const FSentryException& Value)
	: module{Value.Module}
	, thread_id{Value.ThreadId}
	, type{Value.Type}
	, value{Value.Value}
{
}

FSentryEvent_Exception_Json::FSentryEvent_Exception_Json(FSentryException&& Value)
	: module{std::move(Value.Module)}
	, thread_id{std::move(Value.ThreadId)}
	, type{std::move(Value.Type)}
	, value{std::move(Value.Value)}
{
}

FSentryEvent_LogEntry_Json::FSentryEvent_LogEntry_Json(const FSentryLogEntry& Value)
	: message{Value.Message}
	, params{Value.Params}
{
}

FSentryEvent_LogEntry_Json::FSentryEvent_LogEntry_Json(FSentryLogEntry&& Value)
	: message{std::move(Value.Message)}
	, params{std::move(Value.Params)}
{
}

FSentryEvent_Json::FSentryEvent_Json()
	: event_id{FGuid::NewGuid().ToString(EGuidFormats::Digits).ToLower()}
	, platform(TEXT("other"))
	, timestamp{FDateTime::UtcNow().ToUnixTimestamp()}
{
}

FString FSentryEvent_Json::ToJson() const
{
	auto Json = FJsonObjectConverter::UStructToJsonObject<FSentryEvent_Json>(*this);

	FString OutputString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&OutputString);
	FJsonSerializer::Serialize(Json.ToSharedRef(), Writer);

	return OutputString;
}

FSentryEvent_Json& FSentryEvent_Json::SetException(const TArray<FSentryException>& Values)
{
	exception.Reserve(Values.Num());
	for(const auto& Val : Values)
	{
		exception.Add(FSentryEvent_Exception_Json(Val));
	}
	return *this;
}

FSentryEvent_Json& FSentryEvent_Json::SetException(TArray<FSentryException>&& Values)
{
	exception.Reserve(Values.Num());
	for(auto& Val : Values)
	{
		exception.Add(FSentryEvent_Exception_Json(std::move(Val)));
	}
	return *this;
}

FSentryEvent_Json& FSentryEvent_Json::SetLogEntry(const FSentryLogEntry& Value)
{
	logentry = FSentryEvent_LogEntry_Json(Value);
	return *this;
}

FSentryEvent_Json& FSentryEvent_Json::SetLogEntry(FSentryLogEntry&& Value)
{
	logentry = FSentryEvent_LogEntry_Json(std::move(Value));
	return *this;
}

FSentryEvent_Json& FSentryEvent_Json::SetLevel(const ESentryLevel& Value)
{
	switch(Value)
	{
	case ESentryLevel::Debug:
		level = TEXT("debug");
		break;
	case ESentryLevel::Error:
		level = TEXT("error");
		break;
	case ESentryLevel::Fatal:
		level = TEXT("fatal");
		break;
	case ESentryLevel::Info:
		level = TEXT("info");
		break;
	case ESentryLevel::Warning:
		level = TEXT("warning");
		break;
	default:;
	}
	return *this;
}

FSentryEvent_Json& FSentryEvent_Json::SetApplicationInfo(const FSentryApplicationInfo& Value)
{
	dist = Value.Distribution;
	environment = Value.Environment;
	release = Value.Release;
	server_name = Value.ServerName;
	return *this;
}
