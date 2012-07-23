package com.jesusla.kontagent {
  import flash.data.EncryptedLocalStore;
  import flash.events.StatusEvent;
  import flash.external.ExtensionContext;
  import flash.utils.ByteArray;
  import flash.utils.getQualifiedClassName;
  import com.kontagent.KontagentApi;
  import com.kontagent.libs.adobe.crypto.Base64Encoder;

  /**
   * Kontagent extension
   */
  public class Kontagent {
    //---------------------------------------------------------------------
    //
    // Constants
    //
    //---------------------------------------------------------------------
    private static const EXTENSION_ID:String = "com.jesusla.kontagent";

    //---------------------------------------------------------------------
    //
    // Private Properties.
    //
    //---------------------------------------------------------------------
    private static var context:ExtensionContext;
    private static var _isSupported:Boolean;
    private static var _instance:Kontagent;
    private static var ktApi:KontagentApi;
    private static var _userId:Number;
    private static var _installed:Boolean;

    //---------------------------------------------------------------------
    //
    // Public Methods.
    //
    //---------------------------------------------------------------------
    public function Kontagent() {
      if (_instance)
        throw new Error("Singleton");
      _instance = this;
    }

    public static function get isSupported():Boolean {
      // We always fallback to AS3 if necessary
      return true;
    }

    public static function init(apiKey:String, userId:Object, useTestServer:Boolean = false):void {
      _userId = Number(userId);
      if (!_isSupported)
        ktApi = new KontagentApi(apiKey);
      else
        context.call("initialize", apiKey, _userId ? String(_userId) : null, useTestServer);
    }

    public static function get libraryVersion():String {
      if (!_isSupported)
        return "as3";
      return context.call("libraryVersion") as String;
    }

    public static function trackEvent(eventName:String, optionalParams:Object = null):void {
      ensureInitialized();
      if (_isSupported) {
        optionalParams = formatParams(optionalParams);
        context.call("trackEvent", eventName, optionalParams);
      }
      else
        ktApi.trackEvent(_userId, eventName, optionalParams);
    }

    public static function trackApplicationAdded(optionalParams:Object = null):void {
      ensureInitialized();
      if (_isSupported) {
        optionalParams = formatParams(optionalParams);
        context.call("trackApplicationAdded", optionalParams);
      }
      else
        ktApi.trackApplicationAdded(_userId, optionalParams);
    }

    public static function trackGoalCount(optionalParams:Object = null):void {
      ensureInitialized();
      if (_isSupported) {
        for (var ix:int = 1; ix <= 4; ++ix) {
          var key:String = "goalCount" + ix;
          if (key in optionalParams)
            context.call("trackGoalCount", ix, int(optionalParams[key]));
        }
      }
      else
        ktApi.trackGoalCount(_userId, optionalParams);
    }

    public static function trackInviteSent(recipientUserIds:String, uniqueTrackingTag:String, optionalParams:Object = null):void {
      ensureInitialized();
      if (_isSupported) {
        optionalParams = formatParams(optionalParams);
        context.call("trackInviteSent", recipientUserIds, uniqueTrackingTag, optionalParams);
      }
      else
        ktApi.trackInviteSent(_userId, recipientUserIds, uniqueTrackingTag, optionalParams);
    }

    public static function trackInviteResponse(uniqueTrackingTag:String, optionalParams:Object = null):void {
      ensureInitialized();
      if (_isSupported) {
        optionalParams = formatParams(optionalParams);
        context.call("trackInviteResponse", _installed, uniqueTrackingTag, optionalParams);
      }
      else
        ktApi.trackInviteResponse(uniqueTrackingTag, optionalParams);
    }

    public static function trackPageRequest(optionalParams:Object = null):void {
      ensureInitialized();
      if (_isSupported) {
        optionalParams = formatParams(optionalParams);
        context.call("trackPageRequest", optionalParams);
      }
      else
        ktApi.trackPageRequest(_userId, optionalParams);
    }

    public static function trackRevenue(value:int, optionalParams:Object = null):void {
      ensureInitialized();
      if (_isSupported) {
        optionalParams = formatParams(optionalParams);
        context.call("trackRevenue", value, optionalParams);
      }
      else
        ktApi.trackRevenue(_userId, value, optionalParams);
    }

    public static function trackStreamPost(uniqueTrackingTag:String, type:String, optionalParams:Object = null):void {
      ensureInitialized();
      if (_isSupported) {
        optionalParams = formatParams(optionalParams);
        context.call("trackStreamPost", type, uniqueTrackingTag, optionalParams);
      }
      else
        ktApi.trackStreamPost(_userId, uniqueTrackingTag, type, optionalParams);
    }

    public static function trackStreamPostResponse(uniqueTrackingTag:String, type:String, optionalParams:Object = null):void {
      ensureInitialized();
      if (_isSupported) {
        optionalParams = formatParams(optionalParams);
        context.call("trackStreamPostResponse", _installed, type, uniqueTrackingTag, optionalParams);
      }
      else
        ktApi.trackStreamPostResponse(uniqueTrackingTag, type, optionalParams);
    }

    public static function trackThirdPartyCommClick(type:String, optionalParams:Object = null):void {
      ensureInitialized();
      if (_isSupported) {
        var tag:String = optionalParams["shortUniqueTrackingTag"];
        optionalParams = formatParams(optionalParams);
        if (tag)
          context.call("trackThirdPartyCommClickTag", _installed, type, tag, optionalParams);
        else
          context.call("trackThirdPartyCommClick", _installed, type, optionalParams);
      }
      else
        ktApi.trackThirdPartyCommClick(type, optionalParams);
    }

    public static function trackNotificationEmailSent(recipientUserIds:String, uniqueTrackingTag:String, optionalParams:Object = null):void {
      ensureInitialized();
      if (_isSupported) {
        optionalParams = formatParams(optionalParams);
        context.call("trackNotificationEmailSent", recipientUserIds, uniqueTrackingTag, optionalParams);
      }
      else
        ktApi.trackNotificationEmailSent(_userId, recipientUserIds, uniqueTrackingTag, optionalParams);
    }

    public static function trackNotificationEmailResponse(uniqueTrackingTag:String, optionalParams:Object = null):void {
      ensureInitialized();
      if (_isSupported) {
        optionalParams = formatParams(optionalParams);
        context.call("trackNotificationEmailResponse", _installed, uniqueTrackingTag, optionalParams);
      }
      else
        ktApi.trackNotificationEmailResponse(uniqueTrackingTag, optionalParams);
    }

    public static function trackUserInformation(optionalParams:Object = null):void {
      ensureInitialized();
      if (_isSupported) {
        optionalParams = formatParams(optionalParams);
        context.call("trackUserInformation", optionalParams);
      }
      else
        ktApi.trackUserInformation(_userId, optionalParams);
    }

    public static function sendDeviceInformation(optionalParams:Object = null):void {
      if (!_isSupported)
        return
      optionalParams = formatParams(optionalParams);
      context.call("sendDeviceInformation", optionalParams);
    }

    public static function genUniqueTrackingTag():String {
      ensureInitialized();
      if (_isSupported)
        return context.call("genUniqueTrackingTag") as String;
      else
        return ktApi.genUniqueTrackingTag();
    }

    public static function genShortUniqueTrackingTag():String {
      ensureInitialized();
      return ktApi.genShortUniqueTrackingTag();
    }

    public static function enableDebug():void {
      if (_isSupported)
        context.call("enableDebug");
    }

    public static function disableDebug():void {
      if (_isSupported)
        context.call("disableDebug");
    }

    public static function get debugEnabled():Boolean {
      return _isSupported && context.call("debugEnabled");
    }

    public static function get userId():String {
      if (_isSupported)
        return context.call("senderId") as String;
      return String(_userId);
    }

    public function getQualifiedClassName(obj:Object):String {
      return flash.utils.getQualifiedClassName(obj);
    }

    public function enumerateObjectProperties(obj:Object):Array {
      var keys:Array = [];
      for (var key:String in obj)
        keys.push(key);
      return keys;
    }

    //---------------------------------------------------------------------
    //
    // Internal (package level) Methods.
    //
    //---------------------------------------------------------------------

    //---------------------------------------------------------------------
    //
    // Private Methods.
    //
    //---------------------------------------------------------------------
    private static function base64Encode(data:String):String {
      var b64:Base64Encoder = new Base64Encoder();
      b64.encode(data);
      return b64.toString();
    }

    private static function formatParams(optionalParams:Object):Object {
      if (optionalParams == null)
        return null;

      var params:Object = {}
      if (optionalParams.birthYear) { params.b = optionalParams.birthYear; }
      if (optionalParams.country) { params.lc = optionalParams.country.toUpperCase(); }
      if (optionalParams.data) { params.data = base64Encode(optionalParams.data); }
      if (optionalParams.friendCount) { params.f = optionalParams.friendCount; }
      if (optionalParams.gender) { params.g = optionalParams.gender; }
      if (optionalParams.goalCount1) { params.gc1 = optionalParams.goalCount1; }
      if (optionalParams.goalCount2) { params.gc2 = optionalParams.goalCount2; }
      if (optionalParams.goalCount3) { params.gc3 = optionalParams.goalCount3; }
      if (optionalParams.goalCount4) { params.gc4 = optionalParams.goalCount4; }
      if (optionalParams.ipAddress) { params.ip = optionalParams.ipAddress; }
      if (optionalParams.level != undefined) { params.l = optionalParams.level; }
      if (optionalParams.pageAddress) { params.u = optionalParams.pageAddress; }
      if (optionalParams.recipientUserId) { params.r = optionalParams.recipientUserId; }
      if (optionalParams.shortUniqueTrackingTag) { params.su = optionalParams.shortUniqueTrackingTag; }
      if (optionalParams.subtype1) { params.st1 = optionalParams.subtype1; }
      if (optionalParams.subtype1) { params.st1 = optionalParams.subtype1; }
      if (optionalParams.subtype2) { params.st2 = optionalParams.subtype2; }
      if (optionalParams.subtype3) { params.st3 = optionalParams.subtype3; }
      if (optionalParams.type) { params.tu = optionalParams.type; }
      if (optionalParams.uniqueTrackingTag) { params.u = optionalParams.uniqueTrackingTag; }
      if (optionalParams.userId) { params.s = optionalParams.userId; }
      if (optionalParams.value) { params.v = optionalParams.value; }
      return params;
    }

    private static function ensureInitialized():void {
      if (!_isSupported && ktApi == null)
        throw new Error("Kontagent not initialized");
    }

    private static const ELS_KT_FIRST_RUN:String = "KT_FIRST_RUN";
    private static function isFirstRun():Boolean {
      // May only be called when run on a device
      if (!EncryptedLocalStore.isSupported)
        throw new Error("Unsupported");
      var ba:ByteArray = EncryptedLocalStore.getItem(ELS_KT_FIRST_RUN);
      var firstRun:Boolean = ba == null;
      if (firstRun) {
        ba = new ByteArray();
        ba.writeBoolean(true);
        EncryptedLocalStore.setItem(ELS_KT_FIRST_RUN, ba);
      }
      return firstRun;
    }

    private static function context_statusEventHandler(event:StatusEvent):void {
      if (event.level == "TICKET")
        context.call("claimTicket", event.code);
    }

    {
      new Kontagent();
      context = ExtensionContext.createExtensionContext(EXTENSION_ID, "KontagentLib");
      if (context) {
        _isSupported = context.actionScriptData;
        context.addEventListener(StatusEvent.STATUS, context_statusEventHandler);
        if (_isSupported)
          context.call("setActionScriptThis", _instance);
        _installed = isFirstRun();
      }
    }
  }
}
