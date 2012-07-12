Kontagent ANE
=================

Usage
-----
Set KTAPIKey and KTMode (production/test) in Info.plist.

Call API methods on the AS3 Kontagent class:

        // Methods
        Kontagent.init(key, userId, params = null)
        Kontagent.trackEvent(name, params = null)
        Kontagent.trackApplicationAdded(params = null)
        Kontagent.trackGoalCount(params = null)
        Kontagent.trackInviteSent(ids, tag, params = null)
        Kontagent.trackInviteResponse(tag, params = null)
        Kontagent.trackPageRequest(params = null)
        Kontagent.trackRevenue(value, params = null)
        Kontagent.trackStreamPost(tag, type, params = null)
        Kontagent.trackStreamPostResponse(tag, type, params = null)
        Kontagent.trackThirdPartyCommClick(type, params = null)
        Kontagent.trackNotificationEmailSent(ids, tag, params = null)
        Kontagent.trackNotificationEmailResponse(trag, params = null)
        Kontagent.trackUserInformation(params = null)
        Kontagent.sendDeviceInformation(params = null)
        Kontagent.genUniqueTrackingTag()
        Kontagent.genShortUniqueTrackingTag()
        Kontagent.enableDebug()
        Kontagent.disableDebug()

        // Properties (read-only)
        Kontagent.isSupported
        Kontagent.libraryVersion
        Kontagent.debugEnabled
        Kontagent.userId

Mobile notes
============
init() and trackApplicationAdded() are ignored in mobile.
Both are called automatically during app startup.

Web notes
=========
sendDeviceInformation(), enableDebug() & disableDebug() are ignored
in web mode.
