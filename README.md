# Unreal Egnine 4 - Sentry
Unreal Engine 4 integration of Sentry monitoring

Plugin utilizes Sentry HTTP API to send Events data directly to your DSN.

Plugin was build and tested on 4.27.* version of engine.
Generaly it should work fine with most of engine versions, since its utilizes HTTP and Json modules that do not change much.

## Supported Event parts
* [x] Send Exceptions (stands for generals errors) [more info](https://develop.sentry.dev/sdk/event-payloads/types/#exception)
* [x] Send Log Entry (log message for sentry) [more info](https://develop.sentry.dev/sdk/event-payloads/types/#logentry)
* [x] Dist, Env, Release, ServerName - can be applied to each event
* [ ] Breadcrumbs [more info](https://develop.sentry.dev/sdk/event-payloads/types/#typedef-Breadcrumbs)
* [ ] Tags
* [ ] Partial or full BP support 

## Support
Checkout [wiki](https://github.com/GloryOfNight/UE4_Sentry/wiki) section for documentation and API examples.

If you found this plugin useful and want help, please consider givind a star.
If you encounter problems or have questions, please use Issues or Discussions section of this repo.

Feel free to submit your own work via Pull Requests.

Have a nice day! (or night, probably night, probably, yes.)
