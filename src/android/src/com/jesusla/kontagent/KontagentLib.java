package com.jesusla.kontagent;

import java.util.Map;

import com.jesusla.ane.Context;
import com.jesusla.ane.Extension;
import com.kontagent.Kontagent;

public class KontagentLib extends Context {
  private String apiKey;
  private boolean isDebugEnabled;

  public KontagentLib() {
    registerFunction("libraryVersion");
    registerFunction("initialize");
    registerFunction("trackApplicationAdded");
    registerFunction("trackEvent");
    registerFunction("trackRevenue");
    registerFunction("trackThirdPartyCommClick");
    registerFunction("sendDeviceInformation");
    registerFunction("genUniqueTrackingTag");
    registerFunction("enableDebug");
    registerFunction("disableDebug");
    registerFunction("debugEnabled");
    registerFunction("senderId");
  }

  @Override
  protected void initContext() {
    isDebugEnabled = getBooleanProperty("KTDebug");
    if (isDebugEnabled)
      Kontagent.enableDebug();
    apiKey = getProperty("KTAPIKey");
    if (apiKey != null) {
      boolean isTest = getBooleanProperty("KTTestMode");
      String mode = isTest ? Kontagent.TEST_MODE : Kontagent.PRODUCTION_MODE;
      Extension.debug("Auto-initializing Kontagent(%s,%s)", apiKey, mode);
      Kontagent.startSession(apiKey, getActivity(), mode, null, true);
    }
  }

  @Override
  public void dispose() {
    super.dispose();
    Kontagent.stopSession();
  }

  public String libraryVersion() {
    return Kontagent.libraryVersion();
  }

  public void initialize(String apiKey, String userId, boolean isTest) {
    if (this.apiKey != null) {
      // Avoid double-initialization
      Extension.warn("Kontagent: Session already initialized. Ignoring");
      return;
    }
    String mode = isTest ? Kontagent.TEST_MODE : Kontagent.PRODUCTION_MODE;
    this.apiKey = apiKey;
    Kontagent.startSession(apiKey, getActivity(), mode, userId, false);
  }


  public void trackApplicationAdded(Map<String, String> params) {
    Kontagent.applicationAdded(params);
  }

  public void trackEvent(String event, Map<String, String> optionalParams) {
    Kontagent.customEvent(event, optionalParams);
  }

  public void trackRevenue(int value, Map<String, String> optionalParams) {
    Kontagent.revenueTracking(value, optionalParams);
  }

  public void trackThirdPartyCommClick(boolean applicationInstalled, String type, Map<String, String> optionalParams) {
    Kontagent.undirectedCommunicationClick(applicationInstalled, type, optionalParams);
  }

  public void sendDeviceInformation(Map<String, String> optionalParams) {
    Kontagent.sendDeviceInformation(optionalParams);
  }

  public String genUniqueTrackingTag() {
    return Kontagent.generateUniqueTrackingTag();
  }

  public void enableDebug() {
    isDebugEnabled = true;
    Kontagent.enableDebug();
  }

  public void disableDebug() {
    isDebugEnabled = false;
    Kontagent.disableDebug();
  }

  public boolean debugEnabled() {
    return isDebugEnabled;
  }

  public String senderId() {
    return Kontagent.getSenderId();
  }
}