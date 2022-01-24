#include "Sentry/SentrySettings.h"

#include "Sentry/SentryManager.h"

USentrySettings* USentrySettings::Get()
{
	return GetMutableDefault<USentrySettings>();
}

#if WITH_EDITOR
void USentrySettings::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	if(PropertyChangedEvent.GetPropertyName() == GET_MEMBER_NAME_CHECKED(USentrySettings, DSN))
	{
		if(auto* Manager = FSentryManager::Get())
		{
			Manager->LoadDSN(DSN, true);
		}
	}
}
#endif