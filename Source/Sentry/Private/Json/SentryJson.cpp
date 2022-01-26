#include "Sentry/Json/SentryJson.h"

#include <JsonObjectConverter.h>

FSentryGeo_Json::FSentryGeo_Json(const FSentryUserGeoInfo& Value)
	: city{Value.City}
	, country_code{Value.CountryCode}
	, region{Value.Region}
{
}

FSentryGeo_Json::FSentryGeo_Json(FSentryUserGeoInfo&& Value)
	: city{std::move(Value.City)}
	, country_code{std::move(Value.CountryCode)}
	, region{std::move(Value.Region)}
{
}

FSentryUser_Json::FSentryUser_Json(const FSentryUserInfo& Value)
	: data{Value.Data}
	, email{Value.Email}
	, geo{FSentryGeo_Json(Value.Geo)}
	, id{Value.Id}
	, ip_address{Value.IpAddress}
	, name{Value.Name}
	, segment{Value.Segment}
	, username{Value.Username}

{
}

FSentryUser_Json::FSentryUser_Json(FSentryUserInfo&& Value)
	: data{std::move(Value.Data)}
	, email{std::move(Value.Email)}
	, geo{FSentryGeo_Json(std::move(Value.Geo))}
	, id{std::move(Value.Id)}
	, ip_address{std::move(Value.IpAddress)}
	, name{std::move(Value.Name)}
	, segment{std::move(Value.Segment)}
	, username{std::move(Value.Username)}
{
}

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

FSentryEvent_Json& FSentryEvent_Json::SetLevel(const ESentryLevel::Type& Value)
{
	level = ESentryLevel::ToString(Value);
	return *this;
}

FSentryEvent_Json& FSentryEvent_Json::SetApplicationInfo(const FSentryApplicationInfo& Value)
{
	dist = Value.Distribution;
	environment = Value.Environment;
	release = Value.Release;
	server_name = Value.ServerName;
	tags = Value.Tags;
	user = Value.User;
	return *this;
}