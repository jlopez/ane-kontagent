/*
 *  Kontagent.h
 *  
 *  Created by macdrive on 6/10/11.
 *  Copyright (c) 2011 Kontagent. All rights reserved.
 *
 *  Umbrella header for Konatgent framework.
 *
 */

#ifndef KT_KONTAGENT_H
#define KT_KONTAGENT_H

#import <Foundation/Foundation.h>

extern NSString * const KT_PRODUCTION_API_URL_PREFIX;
extern NSString * const KT_TEST_API_URL_PREFIX;
extern NSString * const KT_UNIT_TEST_URL_PREFIX;

extern NSString * const KT_FUNCTION_APPLICATION_ADDED;
extern NSString * const KT_FUNCTION_CUSTOM_EVENT;
extern NSString * const KT_FUNCTION_GOAL_COUNT;
extern NSString * const KT_FUNCTION_INVITE_SENT;
extern NSString * const KT_FUNCTION_INVITE_RESPONSE;
extern NSString * const KT_FUNCTION_MESSAGE_SENT;
extern NSString * const KT_FUNCTION_MESSAGE_RECEIVED;
extern NSString * const KT_FUNCTION_PAGE_REQUEST;
extern NSString * const KT_FUNCTION_REVENUE_TRACKING;
extern NSString * const KT_FUNCTION_STREAM_POST;
extern NSString * const KT_FUNCTION_STREAM_POST_RESPONSE;
extern NSString * const KT_FUNCTION_UNDIRECTED_COMMUNICATION_CLICK;
extern NSString * const KT_FUNCTION_USER_INFORMATION;
extern NSString * const KT_FUNCTION_NOTIFICATION_EMAIL_SENT;
extern NSString * const KT_FUNCTION_NOTIFICATION_EMAIL_RESPONSE;
extern NSString * const KT_FUNCTION_FEATURE_INSTALLATION_TRACK;

extern NSString * const KT_FUNCTION_FEEDPUB;

extern NSString * const KT_PREFERENCE_NAME;
extern NSString * const KT_PREFERENCE_SENDER_ID_KEY;
extern NSString * const KT_PREFERENCE_MODE_KEY;
extern NSString * const KT_PREFERENCE_TIMESTAMP_PARAMETER_SUPPPORTED;

extern NSString * const KT_PASTEBOARD_SUID_PROPERTY_KEY;

// CONFIGURATION
extern NSString * const KT_SESSION_API_URL_CONFIG_KEY;
extern NSString * const KT_SESSION_API_KEY_CONFIG_KEY;
extern NSString * const KT_SESSION_API_KEY_FOR_TIMEZONE_CONFIG_KEY;
extern NSString * const KT_SESSION_API_KEY_TIMEZONE_OFFSET_CONFIG_KEY;
extern NSString * const KT_SESSION_SENDER_ID_CONFIG_KEY;
extern NSString * const KT_SESSION_MODE_CONFIG_KEY;
extern NSString * const KT_SESSION_DEBUG_CONFIG_KEY;
extern NSString * const KT_SESSION_APA_CONFIG_KEY;
extern NSString * const KT_SESSION_CUSTOM_ID_CONFIG_KEY;

#if defined(__cplusplus)
extern "C" {
#endif
    
enum _KTReturn
{
    /**
     * No error, the function call was successful.
     */
    kKTReturnSuccess = 0,
    
    /**
     * Unknown cause of failure.
     */
    kKTReturnUnknownError = -1,
    
    kKTReturnError = kKTReturnUnknownError,
    
    /**
     * This functionality is not supported.
     */
    kKTReturnNotSupported = -2,
    
    /**
     * One or more function parameters passed were not acceptable.
     */
    kKTReturnBadParameter = -3,
    
    /**
     * API Key validation error codes
     */
    
    //Indicates that API key should be 32 characters long
    kKTReturnApiKeyIsNot32CharsInLength = -4,
    
    //Indicates that API key must contain only lower case letters
    kKTReturnApiKeyContainsNotLowerCaseChars = -5,
    
    //Indicates that API key must contain only hexadecimal chars
    kKTReturnApiKeyContainsNonHexadecimalChars = -6,
    
    /**
     * Custom ID validation error codes
     */
    
    //Indicates that sanitized (after all non-hexadecimal chars are stripped) Custom ID's length is less than MIN (6 chars by default)
    kKTReturnSanitizedCustomIDMinLengthIsInvalid = -7,
    
    //Indicates that KTConfiguration failed to verify either Required or Optional config keys
    kKTReturnConfigurationGenericError = -8
    
};
typedef int32_t KTReturn;
    
#if defined(__cplusplus)
}
#endif


@interface KTParamMap : NSObject {
@private
    NSMutableDictionary* parameters;
}

@property(nonatomic, retain) NSMutableDictionary* parameters;

- (void)put:(NSString*)aKey value:(NSString*)aValue;

- (NSString*) urlParamString;

+ (KTParamMap*) cloneParamMap: (KTParamMap*)aMap andSkipKeys:(NSArray*)keysToSkip;

@end


/*! \mainpage Kontagent SDK
 *
 * In order to begin usage of SDK, you should perform the next pre-requisite steps:
 *  -# Ensure that you have an API key.
 *  -# Add Kontagent.framework to the project and exclude it from target membership.<br>
 *         It will be linked via -force_load option.  
 *  -# Add the following options to OTHER_LDFLAGS in Xcode:<br>
 *         -framework SystemConfiguration -framework CoreData <br> 
 *         -weak_framework CoreTelephony -weak_framework IOKit <br> 
 *         -force_load "$(PATH_TO_KONTAGENT)/Kontagent.framework/Kontagent"
 *  -# Add DBModel.xcdatamodeld (from Kontagent.framework/Resources/) to project resources.<br>
 *      
 *
 * Before sending any requests to the server, you must create and start a server session:
 * @code
 *      [Kontagent startSession:ApiKey senderId:@"SenderId" mode:kKontagentSDKMode_TEST];
 * @endcode
 * 
 * Parameter "mode" function defines what server sdk will be using: test or production.
 * Parameter "senderId" function can be nil.
 * You can find all necessary constants in <Kontagent/KontagentLibTypes.h>, 
 * <Kontagent/KontagentLib.h> and <Kontagent/KontagentLibReturn.h>. 
 *  
 * When "start" is called for the first time, an "Application added" request will be sent to server.
 *
 * To stop session you need to call:
 * @code
 *      [Kontagent stopSession];
 * @endcode
 * Do not forget to call this "stopSession" on application's exit or when server session is no more needed.
 * "stopSession" writes all unsaved requests to database on the disk.
 *
 * After that, you can instrument your code by calling API methods like this:
 * @code
 *      [Kontagent messageSent:@"1543" trackingId:[Kontagent generateUniqueTrackingTag] optionalParams:nil];
 *      [Kontagent pageRequest:nil];
 * @endcode
 * If you would like to enable/disable SDK logging then you must enable/disable debugging mode:
 * @code
 *      [Kontagent enableDebug];
 *      [Kontagent disableDebug];
 * @endcode
 */

#if defined(__cplusplus)
extern "C" {
#endif
    
/**
 *  SDK Modes 
 */
enum 
{
    kKontagentSDKMode_PRODUCTION  = 0,
    kKontagentSDKMode_TEST        = 1
};        
    
@class KTSession;    
@interface Kontagent : NSObject {
    
}

+ (id)instance;

//----------------------------------------------------------
// Versions
//----------------------------------------------------------

+ (NSString*) libraryVersion;

/**
 * \brief   Set SDK mode
 * 
 * @param[in] aMode     PRODUCTION or TEST (kKontagentSDKMode_PRODUCTION/kKontagentSDKMode_TEST).
 */
+ (void) setMode:(NSUInteger)aMode;

/**
 * \brief   First method that should be called initialize SDK 
 * 
 * @param[in] anApiKey  This is autogenerated by the Kontagent system when you setup an application.
 * @param[in] aSenderId Unique long UInt64 value in the form of NSString. It can be nil. In such case UID will be generated within SDK.
 *                      anApiKey is used as unique session id. Sender Id is stored to the internal Hash<anApiKey,aSenderId> for further re-use.
 * @param[in] aMode     PRODUCTION or TEST (kKontagentSDKMode_PRODUCTION/kKontagentSDKMode_TEST).
 */
+ (OSStatus) startSession:(NSString*)anApiKey senderId:(NSString*)aSenderId mode:(NSUInteger)aMode;

/**
 * \brief   First method that should be called initialize SDK 
 * 
 * @param[in] anApiKey  This is autogenerated by the Kontagent system when you setup an application.
 * @param[in] aMode     PRODUCTION or TEST (kKontagentSDKMode_PRODUCTION/kKontagentSDKMode_TEST).
 */
+ (OSStatus) startSession:(NSString*)anApiKey mode:(NSUInteger)aMode;

/**
 * \brief   First method that should be called initialize SDK 
 * 
 * @param[in] anApiKey  This is autogenerated by the Kontagent system when you setup an application.
 * @param[in] aSenderId Unique long UInt64 value in the form of NSString. It can be nil. In such case UID will be generated within SDK.
 *                      anApiKey is used as unique session id. Sender Id is stored to the internal Hash<anApiKey,aSenderId> for further re-use.
 * @param[in] aMode     PRODUCTION or TEST (kKontagentSDKMode_PRODUCTION/kKontagentSDKMode_TEST).
 * @param[in] aFlag     When TRUE - "applicationAdded" request will be sent automatically from "startSession" method.
 */
+ (OSStatus) startSession:(NSString*)anApiKey senderId:(NSString*)aSenderId mode:(NSUInteger)aMode shouldSendApplicationAddedAutomatically:(BOOL)aFlag;

/**
 * \brief   First method that should be called initialize SDK 
 * 
 * @param[in] anApiKey  This is autogenerated by the Kontagent system when you setup an application.
 * @param[in] aMode     PRODUCTION or TEST (kKontagentSDKMode_PRODUCTION/kKontagentSDKMode_TEST).
 * @param[in] aFlag     When TRUE - "applicationAdded" request will be sent automatically from "startSession" method.
 */
+ (OSStatus) startSession:(NSString*)anApiKey mode:(NSUInteger)aMode shouldSendApplicationAddedAutomatically:(BOOL)aFlag;

/**
 * \brief   First method that should be called initialize SDK 
 * 
 * @param[in] anApiKey  This is autogenerated by the Kontagent system when you setup an application.
 * @param[in] aSenderId Unique long UInt64 value in the form of NSString. It can be nil. In such case UID will be generated within SDK.
 *                      anApiKey is used as unique session id. Sender Id is stored to the internal Hash<anApiKey,aSenderId> for further re-use.
 * @param[in] aMode     PRODUCTION or TEST (kKontagentSDKMode_PRODUCTION/kKontagentSDKMode_TEST).
 * @param[in] aFlag     When TRUE - "applicationAdded" request will be sent automatically from "startSession" method.
 * @param[in] aCustomID customer specified ID which will be a part of su-tag for "UCC" and "APA" messages
 */
+ (OSStatus) startSession:(NSString*)anApiKey senderId:(NSString*)aSenderId mode:(NSUInteger)aMode shouldSendApplicationAddedAutomatically:(BOOL)aFlag customID:(NSString*)aCustomID;

/**
 * \brief   First method that should be called initialize SDK 
 * 
 * @param[in] aConfiguration  This is dictionary with configuration parameters:
 * <TABLE>
 * <TR>
 *      <TD>Key</TD> 
 *      <TD>Type</TD> <TD>Status</TD>
 *      <TD>Comments</TD>
 * </TR>
 * <TR>
 *      <TD>KT_SESSION_API_KEY_CONFIG_KEY</TD> 
 *      <TD>NSString</TD> <TD>REQUIRED</TD>
 *      <TD>This is autogenerated by the Kontagent system when you setup an application.</TD>
 * </TR>
 * <TR>
 *      <TD>KT_SESSION_CUSTOM_ID_KEY_CONFIG_KEY</TD> 
 *      <TD>NSString</TD> <TD>OPTIONAL</TD>
 *      <TD>Provide Custom ID if you want one to be included into "su" param of "UCC" and "APA" messages.
 *          Please be aware that Custom ID is processed by internal hashing algorithm and will be different to it's initial value.
 *          Custom ID should contain only hexadecimal characters and it's MIN length should be greater than 6.</TD>
 * </TR>

 * <TR>
 *      <TD>KT_SESSION_API_URL_CONFIG_KEY</TD> 
 *      <TD>NSString</TD><TD>OPTIONAL</TD>
 *      <TD>This is an URL to Kontagent system backend. This key overloads built-in URL prefix for PRODUCTION and TEST modes.</TD>
 * </TR>
 * <TR>
 *      <TD>KT_SESSION_SENDER_ID_CONFIG_KEY</TD>
 *      <TD>NSString</TD> <TD>OPTIONAL</TD>    
 *      <TD>Unique long UInt64 value in the form of NSString. By default UID will be generated within SDK.</TD>
 * </TR><TR>
 *      <TD>KT_SESSION_MODE_CONFIG_KEY</TD>     
 *      <TD>NSNumber</TD> <TD>OPTIONAL</TD>    
 *      <TD>PRODUCTION or TEST (kKontagentSDKMode_PRODUCTION/kKontagentSDKMode_TEST). 
 *          Default value is equal to mode that was set with [Kontagent setMode:] function.
 *          kKontagentSDKMode_PRODUCTION is set on SDK init.</TD>
 * </TR><TR>
 *      <TD>KT_SESSION_DEBUG_CONFIG_KEY</TD>         
 *      <TD>NSNumber</TD> <TD>OPTIONAL</TD>    
 *      <TD>This enables certain SDK methods to send messages to the console log.
 *          Debug is disabled by default and should be disabled in production applications.
 *          Default value is 0. To enable DEBUG set value to 1.</TD>
 * </TR><TR>
 *      <TD>KT_SESSION_APA_CONFIG_KEY</TD>           
 *      <TD>NSNumber</TD> <TD>OPTIONAL</TD>    
 *      <TD>This enables SDK to send "applicationAdded" request automatically from "startSession" method. Default value is 1.</TD>
 * </TR>
 * </TABLE>
 * @return  kKTReturnSuccess on success, otherwise - kKTReturnError.
 */
+ (OSStatus) startSession:(NSDictionary*)aConfiguration;

/**
 * \brief   This method should be called to finalize SDK 
 * 
 */
+ (void) stopSession;

/**
 * \brief   This message is sent first time the Kontagent SDK is launched on a device.
 *  
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/application-added/
 * 
 * @param[in]   anOptionalParams    Optional Parameters.
 */
+ (void) applicationAdded:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message is sent when an user triggers an application-defined action. 
 *          For more information on how to correctly structure an event, see Understanding Events, Subtypes, and Tags.
 *  
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/custom-event/
 * 
 * @param[in]   aName               A name, up to 32 characters long, describing the event 
 *                                  (should only contain characters a-z, A-Z, 0-9, _ ).
 *
 * @param[in]   anOptionalParams    Optional Parameters.
 */
+ (void) customEvent:(NSString*)aName optionalParams:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message provides information for incrementing goal counts for individual users.
 *          A goal count is an arbitrary number, or milestone/goal, that you can define to track. 
 *          For example, you can set a goal count to track when a defined number of users reach a certain
 *          level in a game, or when a certain number of items are purchased. This goal count value can be 
 *          assigned to track any action.
 *          At a maximum, there are four goal count variables you can use for tracking, gc1, gc2, gc3, and gc4.
 *  
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/goal-counts/
 * 
 * @param[in]   aGoalCountId    A label to identify the goal count name, a positive integer from 1 to 4.
 * @param[in]   aValue          The value of each label is an integer value in the range of -16384 to 16384.
 */
+ (void) goalCount:(NSInteger)aGoalCountId value:(NSInteger)aValue;

/**
 * \brief   This message is sent when an invite to add (install) an application occurs.
 *          Multiple recipients can be specified in this message.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/invite-sent/
 * 
 * @param[in] aRecipientUIDs        Recipient UID of the user(s), or the Request ID of the invite.
 *                                  The list of recipient UIDs or request IDs separated by commas.
 * @param[in] anUniqueTrackingTag   A 16-digit unique hexadecimal string (0-9, A-F) tracking tag that is used
 *                                  to match Invite Sent messages to Invite Response (inr) messages.
 *                                  See the Unique Tracking Tag section for more details.
 * @param[in] anOptionalParams      Optional Parameters.
 */
+ (void) inviteSent:(NSString*)aRecipientUIDs trackingId:(NSString*)anUniqueTrackingTag optionalParams:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message is sent when an invite recipient responds to an invite to add (install) an application.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/invite-response/
 * 
 * @param[in] anApplicationInstalled    Indicates whether the recipient has already installed the app (1 or 0).
 * @param[in] anUniqueTrackingTag       A 16-digit unique hexadecimal string (0-9, A-F) tracking tag that is used 
 *                                      to match Invite Response messages to Invite Sent (ins) messages.
 *                                      See the Unique Tracking Tag section for more details.    
 * @param[in] anOptionalParams          Optional Parameters.
 */
+ (void) inviteResponse:(BOOL)anApplicationInstalled trackingId:(NSString*)anUniqueTrackingTag optionalParams:(KTParamMap*)anOptionalParams;

/**
 * See http://developers.kontagent.com/social_gaming_api_spec.html
 * 
 * @param[in] aRecipientUIDs        Recipient UID of the user(s), or the Request ID of the invite.
 * @param[in] anUniqueTrackingTag   A 16-digit unique hexadecimal string (0-9, A-F) tracking tag.
 * @param[in] anOptionalParams      Optional Parameters.
 */
+ (void) messageSent:(NSString*)aRecipientUIDs trackingId:(NSString*)anUniqueTrackingTag optionalParams:(KTParamMap*)anOptionalParams;

/**
 * See http://developers.kontagent.com/social_gaming_api_spec.html
 * 
 * @param[in] anApplicationInstalled    Indicates whether the recipient has already installed the app (1 or 0).
 * @param[in] anUniqueTrackingTag       A 16-digit unique hexadecimal string (0-9, A-F) tracking tag.
 * @param[in] anOptionalParams          Optional Parameters.
 */
+ (void) messageResponse:(BOOL)anApplicationInstalled trackingId:(NSString*)anUniqueTrackingTag optionalParams:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message is sent when a page request is made by a user. Should be implemented as 
 *          an embedded "pixel" on the browser side. It should be noted that the browser IP is used 
 *          to determine the location of the user, and as such, it is critical that the pixel be 
 *          loaded by the browser and not the application server.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/page-request-and-user-location/
 * 
 * @param[in] anOptionalParams  Optional Parameters.
 */
+ (void) pageRequest:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message provides information for tracking revenue and monetization transactions by users.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/revenue-tracking/
 * 
 * @param[in] aValue            The revenue generated for the user in cents. All values must be passed in 
 *                              cents, and not dollars. Example: $1.25 should be passed as 125.
 * @param[in] anOptionalParams  Optional Parameters.
 */
+ (void) revenueTracking:(NSInteger)aValue optionalParams:(KTParamMap*)anOptionalParams;

/**
 * \brief This message is sent when a users posts to a stream. For Facebook, 
 *        the tu parameter is required, and must be set as tu = stream.publish.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/stream-post/
 * 
 * @param[in] aType                 Facebook or other social network stream equivalent channel type. 
 *                                  As of this version, stream.publish is supported. For other social networks, 
 *                                  pass the appropriate stream channel equivalent in the tu parameter.
 * @param[in] anUniqueTrackingTag   A 16-digit unique hexadecimal string (0-9, A-F) tracking tag that is used to 
 *                                  match this message with Stream Post Response messages. See the Unique Tracking 
 *                                  Tag section for more details.
 * @param[in] anOptionalParams      Optional Parameters.
 */
+ (void) streamPost:(NSString*)aType trackingId:(NSString*)anUniqueTrackingTag optionalParams:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message is sent when a user clicks on a link in a post made using one of the channels in the pst API call.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/stream-post-response/
 * 
 * @param[in] anApplicationInstalled    This message is sent when a user clicks on a link in a post made 
 *                                      using one of the channels in the pst API call.
 * @param[in] aType                     Facebook or other social network stream equivalent channel type. 
 *                                      As of this version, stream.publish is supported. For other social networks, 
 *                                      pass the appropriate stream channel equivalent in the tu parameter.
 * @param[in] anUniqueTrackingTag       A 16-digit unique hexadecimal string (0-9, A-F) tracking tag that is used to 
 *                                      match this message with Stream Post messages. See the Unique Tracking Tag section
 *                                      for more details.
 * @param[in] anOptionalParams          Optional Parameters.
 */
+ (void) streamPostResponse:(BOOL)anApplicationInstalled type:(NSString*)aType 
                 trackingId:(NSString*)anUniqueTrackingTag optionalParams:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message is sent when a click from an undirected communication source, 
 *          such as an advertisement or partner link is detected. Note that the user may not have yet 
 *          installed the application, so a UID may not be sent. If the user chooses to install the application, 
 *          an apa API message call must be sent following the ucc API message call.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/third-party-communication-click/
 * 
 * @param[in] anApplicationInstalled    Indicates whether the recipient has already installed the application (1 or 0).
 * @param[in] aType                     An advertisement or partner.
 * @param[in] anOptionalParams          Optional Parameters.
 */
+ (void) undirectedCommunicationClick:(BOOL)anApplicationInstalled type:(NSString*)aType optionalParams:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message is sent when a click from an undirected communication source, 
 *          such as an advertisement or partner link is detected. Note that the user may not have yet 
 *          installed the application, so a UID may not be sent. If the user chooses to install the application, 
 *          an apa API message call must be sent following the ucc API message call.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/third-party-communication-click/
 * 
 * @param[in] anApplicationInstalled    Indicates whether the recipient has already installed the application (1 or 0).
 * @param[in] aType                     An advertisement or partner.
 * @param[in] aTrackingTag              Short Tracking Tag. 
 * @param[in] anOptionalParams          Optional Parameters.
 */
+ (void) undirectedCommunicationClick:(BOOL)anApplicationInstalled type:(NSString*)aType trackingTag:(NSString*)aTrackingTag optionalParams:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message is sent when an email newsletter is sent. Multiple recipients can be specified.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/notification-email-sent/
 *
 * @param[in] aRecipientUIDs        The recipient UID(s) of the user(s) receiving the email newsletter, separated by commas.
 * @param[in] anUniqueTrackingTag   A 16-digit unique hexadecimal string (0-9, A-F) tracking tag that is used to match this 
 *                                  message with Notification Email Response messages. 
 *                                  See the Unique Tracking Tag section for more details.
 * @param[in] anOptionalParams      Optional Parameters.
 */
+ (void) emailSent:(NSString*)aRecipientUIDs trackingId:(NSString*)anUniqueTrackingTag optionalParams:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message is sent when an email newsletter recipient responds by clicking on the accompanying 
 *           email newsletter link and visits the application.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/notification-email-response/
 *
 * @param[in] anApplicationInstalled    Indicates whether the recipient has already installed the application (1 or 0).
 * @param[in] anUniqueTrackingTag       A 16-digit unique hexadecimal string (0-9, A-F) tracking tag that is used to match
 *                                      this message with Notification Email Sent messages. 
 *                                      See the Unique Tracking Tag section for more details.
 * @param[in] anOptionalParams          Optional Parameters.
 */
+ (void) emailResponse:(BOOL)anApplicationInstalled trackingId:(NSString*)anUniqueTrackingTag optionalParams:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message is sent to provide information regarding a specific user.
 *          One common question regarding the cpu message is when and how often this call should be made.
 *          Our recommendation is that you place the code that retrieves and sends user data in a common place in your application. 
 *          Ideally, this would be the landing page or a common page where every user will visit, 
 *          allowing the cpu to be set on each new user login. Additionally, we recommend a cookie is also set that indicates
 *          if the user data was retrieved and sent for that day.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/user-information/
 * 
 * @param[in] anOptionalParams  Optional Parameters.
 */
+ (void) userInformation:(KTParamMap*)anOptionalParams;

// Convenience methods that wrap the API.
/**
 * \brief   This method gathers manufacturer, model, os version, and carrier on launch.
 * 
 */
+ (void) sendDeviceInformation:(KTParamMap*)anOptionalParams;

/**
 * \brief   Helper method to generate a 16 char tracking tag.
 * 
 * See http://www.kontagent.com/docs/getting-started/understanding-events/
 * @return A 16-digit unique hexadecimal string (0-9, A-F) tracking tag.
 */
+ (NSString*) generateUniqueTrackingTag;

/**
 * \brief   This enables certain SDK methods to send messages to the console log.  
 *          Debug is disabled by default and should be disabled in production applications.
 * 
 */
+ (void) enableDebug;

/**
 * \brief   Disables debugging features.
 */
+ (void) disableDebug;

/**
 * \brief   Determines whether the application is in debug mode.
 * @return  TRUE if debug is enabled, otherwise FALSE.  Default is FALSE.
 */
+ (BOOL) debugEnabled;

/**
 * \brief   Return senderId which corresponds to ApiKey
 * 
 * @param[in] anApiKey  This is autogenerated by the Kontagent system when you setup an application.
 */

+ (NSString*)getSenderId:(NSString*)anApiKey;

/**
 * \brief   This method should be called to create SDK session
 * 
 * @param[in] anApiKey    This is autogenerated by the Kontagent system when you setup an application.
 * @param[in] aSenderId   
 */
+ (KTSession*) createSession:(NSString*)anApiKey senderId:(NSString*)aSenderId;

/**
 * \brief   This method should be called to create SDK session
 * 
 * @param[in] anApiKey    This is autogenerated by the Kontagent system when you setup an application.
 * @param[in] aSenderId
 * @param[in] aFlag       When TRUE - "applicationAdded" request will be sent automatically from "start" method of KTSession object.
 */

+ (KTSession*) createSession:(NSString*)anApiKey senderId:(NSString*)aSenderId shouldSendApplicationAddedAutomatically:(BOOL)aFlag;

/**
 * \brief   This method should be called to create SDK session
 * 
 * @param[in] aConfiguration  This is dictionary with configuration parameters:
 * <TABLE>
 * <TR>
 *      <TD>Key</TD> 
 *      <TD>Type</TD> <TD>Status</TD>
 *      <TD>Comments</TD>
 * </TR>
 * <TR>
 *      <TD>KT_SESSION_API_KEY_CONFIG_KEY</TD> 
 *      <TD>NSString</TD> <TD>REQUIRED</TD>
 *      <TD>This is autogenerated by the Kontagent system when you setup an application.</TD>
 * </TR>
 * <TR>
 *      <TD>KT_SESSION_API_URL_CONFIG_KEY</TD> 
 *      <TD>NSString</TD><TD>OPTIONAL</TD>
 *      <TD>This is an URL to Kontagent system backend. This key overloads built-in URL prefix for PRODUCTION and TEST modes.</TD>
 * </TR>
 * <TR>
 *      <TD>KT_SESSION_SENDER_ID_CONFIG_KEY</TD>
 *      <TD>NSString</TD> <TD>OPTIONAL</TD>    
 *      <TD>Unique long UInt64 value in the form of NSString. By default UID will be generated within SDK.</TD>
 * </TR><TR>
 *      <TD>KT_SESSION_MODE_CONFIG_KEY</TD>     
 *      <TD>NSNumber</TD> <TD>OPTIONAL</TD>    
 *      <TD>PRODUCTION or TEST (kKontagentSDKMode_PRODUCTION/kKontagentSDKMode_TEST). 
 *          Default value is equal to mode that was set with [Kontagent setMode:] function.
 *          kKontagentSDKMode_PRODUCTION is set on SDK init.</TD>
 * </TR><TR>
 *      <TD>KT_SESSION_DEBUG_CONFIG_KEY</TD>         
 *      <TD>NSNumber</TD> <TD>OPTIONAL</TD>    
 *      <TD>This enables certain SDK methods to send messages to the console log.
 *          Debug is disabled by default and should be disabled in production applications.
 *          Default value is 0. To enable DEBUG set value to 1.</TD>
 * </TR><TR>
 *      <TD>KT_SESSION_APA_CONFIG_KEY</TD>           
 *      <TD>NSNumber</TD> <TD>OPTIONAL</TD>    
 *      <TD>This enables SDK to send "applicationAdded" request automatically from "startSession" method. Default value is 1.</TD>
 * </TR>
 * </TABLE>
 * @return  KTSession object reference if creation was successful, otherwise nil.
 */
+ (KTSession*) createSession:(NSDictionary*)aConfiguration;

@end
    
#if defined(__cplusplus)
}
#endif


/**
 * @page session_api Session API of Kontagent SDK
 *
 * 
 * Before sending any requests to the server, you must create and start a server session:
 * @code
 *      [Kontagent setMode:kKontagentSDKMode_TEST];
 *      KTSession* theSession = [Kontagent createSession:@"ApiKey" senderId:@"SenderId"];
 *      [theSession start];
 * @endcode
 * 
 * Parameter of "setMode" function defines what server sdk will be using: test or production. 
 * You can find all necessary constants in <Kontagent/KontagentLibTypes.h>, 
 * <Kontagent/KontagentLib.h> and <Kontagent/KontagentLibReturn.h>. 
 *  
 * When "start" is called for the first time, an "Application added" request will be sent to server.
 *
 * To stop session you need to call:
 * @code
 *      [theSession stop] 
 * @endcode
 * Do not forget to call this "stop" on application's exit or when server session is no more needed.
 * "stop" writes all unsaved requests to database on the disk.
 *
 * After that, you can instrument your code by calling API methods like this:
 * @code
 *      [theSession messageSent:@"1543" trackingId:[Kontagent generateUniqueTrackingTag] optionalParams:nil];
 *      [theSession pageRequest:nil];
 * @endcode
 * If you would like to delete particular session object simply call:
 * @code
 *      [theSession release];
 * @endcode
 */

#if defined(__cplusplus)
extern "C" {
#endif
    
@interface KTSession : NSObject {
@private
    NSString*  apiKey;
    NSString*  senderId;
    NSUInteger sdkMode;
    
    id selfWeakRef;
    
    id observer; // KTSessionObserver
}

/**
 * \brief   Start SDK session 
 * 
 */
- (OSStatus) start;

/**
 * \brief   Stop SDK session 
 * 
 */
- (void) stop;

/**
 * \brief   This message is sent first time the Kontagent SDK is launched on a device.
 *  
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/application-added/
 * 
 * @param[in]   anOptionalParams    Optional Parameters.
 */
- (void) applicationAdded:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message is sent when an user triggers an application-defined action. 
 *          For more information on how to correctly structure an event, see Understanding Events, Subtypes, and Tags.
 *  
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/custom-event/
 * 
 * @param[in]   aName               A name, up to 32 characters long, describing the event 
 *                                  (should only contain characters a-z, A-Z, 0-9, _ ).
 *
 * @param[in]   anOptionalParams    Optional Parameters.
 */
- (void) customEvent:(NSString*)aName optionalParams:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message provides information for incrementing goal counts for individual users.
 *          A goal count is an arbitrary number, or milestone/goal, that you can define to track. 
 *          For example, you can set a goal count to track when a defined number of users reach a certain
 *          level in a game, or when a certain number of items are purchased. This goal count value can be 
 *          assigned to track any action.
 *          At a maximum, there are four goal count variables you can use for tracking, gc1, gc2, gc3, and gc4.
 *  
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/goal-counts/
 * 
 * @param[in]   aGoalCountId    A label to identify the goal count name, a positive integer from 1 to 4.
 * @param[in]   aValue          The value of each label is an integer value in the range of -16384 to 16384.
 */
- (void) goalCount:(NSInteger)aGoalCountId value:(NSInteger)aValue;

/**
 * \brief   This message is sent when an invite to add (install) an application occurs.
 *          Multiple recipients can be specified in this message.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/invite-sent/
 * 
 * @param[in] aRecipientUIDs        Recipient UID of the user(s), or the Request ID of the invite.
 *                                  The list of recipient UIDs or request IDs separated by commas.
 * @param[in] anUniqueTrackingTag   A 16-digit unique hexadecimal string (0-9, A-F) tracking tag that is used
 *                                  to match Invite Sent messages to Invite Response (inr) messages.
 *                                  See the Unique Tracking Tag section for more details.
 * @param[in] anOptionalParams      Optional Parameters.
 */
- (void) inviteSent:(NSString*)aRecipientUIDs trackingId:(NSString*)anUniqueTrackingTag optionalParams:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message is sent when an invite recipient responds to an invite to add (install) an application.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/invite-response/
 * 
 * @param[in] anApplicationInstalled    Indicates whether the recipient has already installed the app (1 or 0).
 * @param[in] anUniqueTrackingTag       A 16-digit unique hexadecimal string (0-9, A-F) tracking tag that is used 
 *                                      to match Invite Response messages to Invite Sent (ins) messages.
 *                                      See the Unique Tracking Tag section for more details.    
 * @param[in] anOptionalParams          Optional Parameters.
 */
- (void) inviteResponse:(BOOL)anApplicationInstalled trackingId:(NSString*)anUniqueTrackingTag optionalParams:(KTParamMap*)anOptionalParams;

/**
 * See http://developers.kontagent.com/social_gaming_api_spec.html
 * 
 * @param[in] aRecipientUIDs        Recipient UID of the user(s), or the Request ID of the invite.
 * @param[in] anUniqueTrackingTag   A 16-digit unique hexadecimal string (0-9, A-F) tracking tag.
 * @param[in] anOptionalParams      Optional Parameters.
 */
- (void) messageSent:(NSString*)aRecipientUIDs trackingId:(NSString*)anUniqueTrackingTag optionalParams:(KTParamMap*)anOptionalParams;

/**
 * See http://developers.kontagent.com/social_gaming_api_spec.html
 * 
 * @param[in] anApplicationInstalled    Indicates whether the recipient has already installed the app (1 or 0).
 * @param[in] anUniqueTrackingTag       A 16-digit unique hexadecimal string (0-9, A-F) tracking tag.
 * @param[in] anOptionalParams          Optional Parameters.
 */
- (void) messageResponse:(BOOL)anApplicationInstalled trackingId:(NSString*)anUniqueTrackingTag optionalParams:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message is sent when a page request is made by a user. Should be implemented as 
 *          an embedded "pixel" on the browser side. It should be noted that the browser IP is used 
 *          to determine the location of the user, and as such, it is critical that the pixel be 
 *          loaded by the browser and not the application server.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/page-request-and-user-location/
 * 
 * @param[in] anOptionalParams  Optional Parameters.
 */
- (void) pageRequest:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message provides information for tracking revenue and monetization transactions by users.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/revenue-tracking/
 * 
 * @param[in] aValue            The revenue generated for the user in cents. All values must be passed in 
 *                              cents, and not dollars. Example: $1.25 should be passed as 125.
 * @param[in] anOptionalParams  Optional Parameters.
 */
- (void) revenueTracking:(NSInteger)aValue optionalParams:(KTParamMap*)anOptionalParams;

/**
 * \brief This message is sent when a users posts to a stream. For Facebook, 
 *        the tu parameter is required, and must be set as tu = stream.publish.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/stream-post/
 * 
 * @param[in] aType                 Facebook or other social network stream equivalent channel type. 
 *                                  As of this version, stream.publish is supported. For other social networks, 
 *                                  pass the appropriate stream channel equivalent in the tu parameter.
 * @param[in] anUniqueTrackingTag   A 16-digit unique hexadecimal string (0-9, A-F) tracking tag that is used to 
 *                                  match this message with Stream Post Response messages. See the Unique Tracking 
 *                                  Tag section for more details.
 * @param[in] anOptionalParams      Optional Parameters.
 */
- (void) streamPost:(NSString*)aType trackingId:(NSString*)anUniqueTrackingTag optionalParams:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message is sent when a user clicks on a link in a post made using one of the channels in the pst API call.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/stream-post-response/
 * 
 * @param[in] anApplicationInstalled    This message is sent when a user clicks on a link in a post made 
 *                                      using one of the channels in the pst API call.
 * @param[in] aType                     Facebook or other social network stream equivalent channel type. 
 *                                      As of this version, stream.publish is supported. For other social networks, 
 *                                      pass the appropriate stream channel equivalent in the tu parameter.
 * @param[in] anUniqueTrackingTag       A 16-digit unique hexadecimal string (0-9, A-F) tracking tag that is used to 
 *                                      match this message with Stream Post messages. See the Unique Tracking Tag section
 *                                      for more details.
 * @param[in] anOptionalParams          Optional Parameters.
 */
- (void) streamPostResponse:(BOOL)anApplicationInstalled type:(NSString*)aType 
                 trackingId:(NSString*)anUniqueTrackingTag optionalParams:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message is sent when a click from an undirected communication source, 
 *          such as an advertisement or partner link is detected. Note that the user may not have yet 
 *          installed the application, so a UID may not be sent. If the user chooses to install the application, 
 *          an apa API message call must be sent following the ucc API message call.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/third-party-communication-click/
 * 
 * @param[in] anApplicationInstalled    Indicates whether the recipient has already installed the application (1 or 0).
 * @param[in] aType                     An advertisement or partner.
 * @param[in] anOptionalParams          Optional Parameters.
 */
- (void) undirectedCommunicationClick:(BOOL)anApplicationInstalled type:(NSString*)aType optionalParams:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message is sent when a click from an undirected communication source, 
 *          such as an advertisement or partner link is detected. Note that the user may not have yet 
 *          installed the application, so a UID may not be sent. If the user chooses to install the application, 
 *          an apa API message call must be sent following the ucc API message call.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/third-party-communication-click/
 * 
 * @param[in] anApplicationInstalled    Indicates whether the recipient has already installed the application (1 or 0).
 * @param[in] aType                     An advertisement or partner.
 * @param[in] aTrackingTag              Short Tracking Tag.
 * @param[in] anOptionalParams          Optional Parameters.
 */
- (void) undirectedCommunicationClick:(BOOL)anApplicationInstalled type:(NSString*)aType trackingTag:(NSString*)aTrackingTag optionalParams:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message is sent when an email newsletter is sent. Multiple recipients can be specified.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/notification-email-sent/
 *
 * @param[in] aRecipientUIDs        The recipient UID(s) of the user(s) receiving the email newsletter, separated by commas.
 * @param[in] anUniqueTrackingTag   A 16-digit unique hexadecimal string (0-9, A-F) tracking tag that is used to match this 
 *                                  message with Notification Email Response messages. 
 *                                  See the Unique Tracking Tag section for more details.
 * @param[in] anOptionalParams      Optional Parameters.
 */
- (void) emailSent:(NSString*)aRecipientUIDs trackingId:(NSString*)anUniqueTrackingTag optionalParams:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message is sent when an email newsletter recipient responds by clicking on the accompanying 
 *           email newsletter link and visits the application.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/notification-email-response/
 *
 * @param[in] anApplicationInstalled    Indicates whether the recipient has already installed the application (1 or 0).
 * @param[in] anUniqueTrackingTag       A 16-digit unique hexadecimal string (0-9, A-F) tracking tag that is used to match
 *                                      this message with Notification Email Sent messages. 
 *                                      See the Unique Tracking Tag section for more details.
 * @param[in] anOptionalParams          Optional Parameters.
 */
- (void) emailResponse:(BOOL)anApplicationInstalled trackingId:(NSString*)anUniqueTrackingTag optionalParams:(KTParamMap*)anOptionalParams;

/**
 * \brief   This message is sent to provide information regarding a specific user.
 *          One common question regarding the cpu message is when and how often this call should be made.
 *          Our recommendation is that you place the code that retrieves and sends user data in a common place in your application. 
 *          Ideally, this would be the landing page or a common page where every user will visit, 
 *          allowing the cpu to be set on each new user login. Additionally, we recommend a cookie is also set that indicates
 *          if the user data was retrieved and sent for that day.
 *
 * See http://www.kontagent.com/docs/api-libraries/rest-api-advanced/user-information/
 * 
 * @param[in] anOptionalParams  Optional Parameters.
 */
- (void) userInformation:(KTParamMap*)anOptionalParams;

// Convenience methods that wrap the API.
/**
 * \brief   This method gathers manufacturer, model, os version, and carrier on launch.
 * 
 */
- (void) sendDeviceInformation:(KTParamMap*)anOptionalParams;

@end    
    
#if defined(__cplusplus)
}
#endif

#endif // KT_KONTAGENT_H
