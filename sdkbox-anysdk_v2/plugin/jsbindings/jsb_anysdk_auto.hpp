#ifndef __anysdk_h__
#define __anysdk_h__

#include "jsapi.h"
#include "jsfriendapi.h"


extern JSClass  *jsb_PluginParam_class;
extern JSObject *jsb_PluginParam_prototype;

JSBool js_anysdk_PluginParam_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_anysdk_PluginParam_finalize(JSContext *cx, JSObject *obj);
void js_register_anysdk_PluginParam(JSContext *cx, JSObject *global);
void register_all_anysdk(JSContext* cx, JSObject* obj);
JSBool js_anysdk_PluginParam_getBoolValue(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_PluginParam_getCurrentType(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_PluginParam_getFloatValue(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_PluginParam_getStringValue(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_PluginParam_getIntValue(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_PluginProtocol_class;
extern JSObject *jsb_PluginProtocol_prototype;

JSBool js_anysdk_PluginProtocol_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_anysdk_PluginProtocol_finalize(JSContext *cx, JSObject *obj);
void js_register_anysdk_PluginProtocol(JSContext *cx, JSObject *global);
void register_all_anysdk(JSContext* cx, JSObject* obj);
JSBool js_anysdk_PluginProtocol_getPluginName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_PluginProtocol_getPluginVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_PluginProtocol_setPluginName(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_PluginProtocol_getSDKVersion(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_PluginProtocol_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_PluginFactory_class;
extern JSObject *jsb_PluginFactory_prototype;

JSBool js_anysdk_PluginFactory_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_anysdk_PluginFactory_finalize(JSContext *cx, JSObject *obj);
void js_register_anysdk_PluginFactory(JSContext *cx, JSObject *global);
void register_all_anysdk(JSContext* cx, JSObject* obj);
JSBool js_anysdk_PluginFactory_purgeFactory(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_PluginFactory_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_PluginManager_class;
extern JSObject *jsb_PluginManager_prototype;

JSBool js_anysdk_PluginManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_anysdk_PluginManager_finalize(JSContext *cx, JSObject *obj);
void js_register_anysdk_PluginManager(JSContext *cx, JSObject *global);
void register_all_anysdk(JSContext* cx, JSObject* obj);
JSBool js_anysdk_PluginManager_unloadPlugin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_PluginManager_loadPlugin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_PluginManager_end(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_PluginManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ProtocolIAP_class;
extern JSObject *jsb_ProtocolIAP_prototype;

JSBool js_anysdk_ProtocolIAP_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_anysdk_ProtocolIAP_finalize(JSContext *cx, JSObject *obj);
void js_register_anysdk_ProtocolIAP(JSContext *cx, JSObject *global);
void register_all_anysdk(JSContext* cx, JSObject* obj);
JSBool js_anysdk_ProtocolIAP_getPluginId(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolIAP_getOrderId(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolIAP_resetPayState(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ProtocolAnalytics_class;
extern JSObject *jsb_ProtocolAnalytics_prototype;

JSBool js_anysdk_ProtocolAnalytics_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_anysdk_ProtocolAnalytics_finalize(JSContext *cx, JSObject *obj);
void js_register_anysdk_ProtocolAnalytics(JSContext *cx, JSObject *global);
void register_all_anysdk(JSContext* cx, JSObject* obj);
JSBool js_anysdk_ProtocolAnalytics_logTimedEventBegin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolAnalytics_logError(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolAnalytics_setCaptureUncaughtException(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolAnalytics_setSessionContinueMillis(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolAnalytics_startSession(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolAnalytics_stopSession(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolAnalytics_isFunctionSupported(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolAnalytics_logTimedEventEnd(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ProtocolAds_class;
extern JSObject *jsb_ProtocolAds_prototype;

JSBool js_anysdk_ProtocolAds_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_anysdk_ProtocolAds_finalize(JSContext *cx, JSObject *obj);
void js_register_anysdk_ProtocolAds(JSContext *cx, JSObject *global);
void register_all_anysdk(JSContext* cx, JSObject* obj);
JSBool js_anysdk_ProtocolAds_showAds(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolAds_hideAds(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolAds_preloadAds(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolAds_queryPoints(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolAds_spendPoints(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolAds_isAdTypeSupported(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ProtocolSocial_class;
extern JSObject *jsb_ProtocolSocial_prototype;

JSBool js_anysdk_ProtocolSocial_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_anysdk_ProtocolSocial_finalize(JSContext *cx, JSObject *obj);
void js_register_anysdk_ProtocolSocial(JSContext *cx, JSObject *global);
void register_all_anysdk(JSContext* cx, JSObject* obj);
JSBool js_anysdk_ProtocolSocial_showLeaderboard(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolSocial_signOut(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolSocial_showAchievements(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolSocial_signIn(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolSocial_submitScore(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ProtocolUser_class;
extern JSObject *jsb_ProtocolUser_prototype;

JSBool js_anysdk_ProtocolUser_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_anysdk_ProtocolUser_finalize(JSContext *cx, JSObject *obj);
void js_register_anysdk_ProtocolUser(JSContext *cx, JSObject *global);
void register_all_anysdk(JSContext* cx, JSObject* obj);
JSBool js_anysdk_ProtocolUser_isLogined(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolUser_getUserID(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolUser_isFunctionSupported(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolUser_login(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolUser_getPluginId(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_ProtocolPush_class;
extern JSObject *jsb_ProtocolPush_prototype;

JSBool js_anysdk_ProtocolPush_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_anysdk_ProtocolPush_finalize(JSContext *cx, JSObject *obj);
void js_register_anysdk_ProtocolPush(JSContext *cx, JSObject *global);
void register_all_anysdk(JSContext* cx, JSObject* obj);
JSBool js_anysdk_ProtocolPush_startPush(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolPush_closePush(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolPush_delAlias(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_ProtocolPush_setAlias(JSContext *cx, uint32_t argc, jsval *vp);

extern JSClass  *jsb_AgentManager_class;
extern JSObject *jsb_AgentManager_prototype;

JSBool js_anysdk_AgentManager_constructor(JSContext *cx, uint32_t argc, jsval *vp);
void js_anysdk_AgentManager_finalize(JSContext *cx, JSObject *obj);
void js_register_anysdk_AgentManager(JSContext *cx, JSObject *global);
void register_all_anysdk(JSContext* cx, JSObject* obj);
JSBool js_anysdk_AgentManager_getSocialPlugin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_AgentManager_unloadALLPlugin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_AgentManager_loadALLPlugin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_AgentManager_unloadAllPlugins(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_AgentManager_loadAllPlugins(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_AgentManager_getCustomParam(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_AgentManager_getUserPlugin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_AgentManager_init(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_AgentManager_getAdsPlugin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_AgentManager_getPushPlugin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_AgentManager_getSharePlugin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_AgentManager_getAnalyticsPlugin(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_AgentManager_getChannelId(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_AgentManager_end(JSContext *cx, uint32_t argc, jsval *vp);
JSBool js_anysdk_AgentManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp);
#endif

