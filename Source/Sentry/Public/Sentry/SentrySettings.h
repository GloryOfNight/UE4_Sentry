#pragma once

#include <UObject/Object.h>

#include "SentrySettings.generated.h"

UCLASS(Config = Engine)
class SENTRY_API USentrySettings : public UObject
{
	GENERATED_BODY()
public:
	static USentrySettings* Get();

public:
	/** Enable Sentry sending events, turn it off and Sentry will no longer send events */
	UPROPERTY(Config, EditAnywhere, Category = "Sentry")
	bool Enable = true;

#if WITH_EDITOR
	/** Enable Sentry sending events in editor, turn it off if you don't send events from editor */
	UPROPERTY(Config, EditAnywhere, Category = "Sentry")
	bool EnableInEditor = true;
#endif

	/** DSN of Sentry project */
	UPROPERTY(Config, EditAnywhere, Category = "Sentry")
	FString DSN;

#if WITH_EDITOR
	void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;
#endif
};