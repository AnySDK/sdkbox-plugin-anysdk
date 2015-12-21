#include "jsb_anysdk_auto.hpp"
#include "cocos2d_specifics.hpp"
#include "AgentManager.h"
#include "PluginManager.h"
#include "PluginFactory.h"
#include "PluginParam.h"
#include "PluginProtocol.h"
#include "ProtocolAds.h"
#include "ProtocolAnalytics.h"
#include "ProtocolIAP.h"
#include "ProtocolPush.h"
#include "ProtocolShare.h"
#include "ProtocolSocial.h"
#include "ProtocolUser.h"
#include "ProtocolREC.h"
#include "ProtocolCrash.h"
#include "ProtocolCustom.h"

template<class T>
static JSBool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	TypeTest<T> t;
	T* cobj = new T();
	cocos2d::CCObject *_ccobj = dynamic_cast<cocos2d::CCObject *>(cobj);
	if (_ccobj) {
		_ccobj->autorelease();
	}
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	assert(p);
	JSObject *_tmp = JS_NewObject(cx, p->jsclass, p->proto, p->parentProto);
	js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
	JS_AddObjectRoot(cx, &pp->obj);
	JS_SET_RVAL(cx, vp, OBJECT_TO_JSVAL(_tmp));

	return JS_TRUE;
}

static JSBool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	return JS_FALSE;
}


JSClass  *jsb_PluginParam_class;
JSObject *jsb_PluginParam_prototype;

JSBool js_anysdk_PluginParam_getBoolValue(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginParam* cobj = (anysdk::framework::PluginParam *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->getBoolValue();
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_PluginParam_getCurrentType(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginParam* cobj = (anysdk::framework::PluginParam *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		anysdk::framework::PluginParam::ParamType ret = cobj->getCurrentType();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_PluginParam_getFloatValue(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginParam* cobj = (anysdk::framework::PluginParam *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		float ret = cobj->getFloatValue();
		jsval jsret;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_PluginParam_getStringValue(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginParam* cobj = (anysdk::framework::PluginParam *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getStringValue();
		jsval jsret;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_PluginParam_getIntValue(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginParam* cobj = (anysdk::framework::PluginParam *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		int ret = cobj->getIntValue();
		jsval jsret;
		jsret = int32_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_PluginParam_getStrMapValue(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginParam* cobj = (anysdk::framework::PluginParam *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, false, "jsb_anysdk_PluginParam_getStrMapValue : Invalid Native Object");
	if (argc == 0) {
		StringMap values = cobj->getStrMapValue();
		JSObject *tmp = JS_NewObject(cx, NULL, NULL, NULL);
    	if (!tmp) return false;

    	StringMap::iterator iter;
    	bool ok = true;
    	for (iter = values.begin(); iter != values.end(); iter++)
    	{
    		std::string str_key = ((std::string)(iter->first));
    		std::string str_tmp = ((std::string)(iter->second));
			ok &= JS_DefineProperty(cx, tmp, str_key.c_str(), std_string_to_jsval(cx, str_tmp), NULL, NULL, JSPROP_ENUMERATE | JSPROP_PERMANENT);
    	}

		jsval jsret = JSVAL_NULL;
		jsret = OBJECT_TO_JSVAL(tmp);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}



void js_anysdk_PluginParam_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginParam)", obj);
}

void js_register_anysdk_PluginParam(JSContext *cx, JSObject *global) {
	jsb_PluginParam_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_PluginParam_class->name = "PluginParam";
	jsb_PluginParam_class->addProperty = JS_PropertyStub;
	jsb_PluginParam_class->delProperty = JS_PropertyStub;
	jsb_PluginParam_class->getProperty = JS_PropertyStub;
	jsb_PluginParam_class->setProperty = JS_StrictPropertyStub;
	jsb_PluginParam_class->enumerate = JS_EnumerateStub;
	jsb_PluginParam_class->resolve = JS_ResolveStub;
	jsb_PluginParam_class->convert = JS_ConvertStub;
	jsb_PluginParam_class->finalize = js_anysdk_PluginParam_finalize;
	jsb_PluginParam_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getBoolValue", js_anysdk_PluginParam_getBoolValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getCurrentType", js_anysdk_PluginParam_getCurrentType, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getFloatValue", js_anysdk_PluginParam_getFloatValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getStringValue", js_anysdk_PluginParam_getStringValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getIntValue", js_anysdk_PluginParam_getIntValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getStrMapValue", js_anysdk_PluginParam_getStrMapValue, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_PluginParam_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_PluginParam_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "PluginParam", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::PluginParam> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_PluginParam_class;
		p->proto = jsb_PluginParam_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_PluginProtocol_class;
JSObject *jsb_PluginProtocol_prototype;

JSBool js_anysdk_PluginProtocol_isFunctionSupported(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::PluginProtocol* cobj = (anysdk::framework::PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        bool ret = cobj->isFunctionSupported(arg0);
        jsval jsret;
        jsret = BOOLEAN_TO_JSVAL(ret);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}

JSBool js_anysdk_PluginProtocol_getPluginName(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginProtocol* cobj = (anysdk::framework::PluginProtocol *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		const char* ret = cobj->getPluginName();
		jsval jsret;
		jsret = c_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_PluginProtocol_getPluginVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginProtocol* cobj = (anysdk::framework::PluginProtocol *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getPluginVersion();
		jsval jsret;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_PluginProtocol_setPluginName(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginProtocol* cobj = (anysdk::framework::PluginProtocol *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setPluginName(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_anysdk_PluginProtocol_getSDKVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginProtocol* cobj = (anysdk::framework::PluginProtocol *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getSDKVersion();
		jsval jsret;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_PluginProtocol_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp)
{
     CCLOG("\n********** \n setDebugMode was deprecated.\n**********");
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginProtocol* cobj = (anysdk::framework::PluginProtocol *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setDebugMode(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}



void js_anysdk_PluginProtocol_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginProtocol)", obj);
}

void js_register_anysdk_PluginProtocol(JSContext *cx, JSObject *global) {
	jsb_PluginProtocol_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_PluginProtocol_class->name = "PluginProtocol";
	jsb_PluginProtocol_class->addProperty = JS_PropertyStub;
	jsb_PluginProtocol_class->delProperty = JS_PropertyStub;
	jsb_PluginProtocol_class->getProperty = JS_PropertyStub;
	jsb_PluginProtocol_class->setProperty = JS_StrictPropertyStub;
	jsb_PluginProtocol_class->enumerate = JS_EnumerateStub;
	jsb_PluginProtocol_class->resolve = JS_ResolveStub;
	jsb_PluginProtocol_class->convert = JS_ConvertStub;
	jsb_PluginProtocol_class->finalize = js_anysdk_PluginProtocol_finalize;
	jsb_PluginProtocol_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	static JSFunctionSpec funcs[] = {
        JS_FN("isFunctionSupported", js_anysdk_PluginProtocol_isFunctionSupported, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPluginName", js_anysdk_PluginProtocol_getPluginName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPluginVersion", js_anysdk_PluginProtocol_getPluginVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setPluginName", js_anysdk_PluginProtocol_setPluginName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getSDKVersion", js_anysdk_PluginProtocol_getSDKVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setDebugMode", js_anysdk_PluginProtocol_setDebugMode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_PluginProtocol_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_PluginProtocol_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "PluginProtocol", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::PluginProtocol> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_PluginProtocol_class;
		p->proto = jsb_PluginProtocol_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_PluginFactory_class;
JSObject *jsb_PluginFactory_prototype;

JSBool js_anysdk_PluginFactory_purgeFactory(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		anysdk::framework::PluginFactory::purgeFactory();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

JSBool js_anysdk_PluginFactory_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		anysdk::framework::PluginFactory* ret = anysdk::framework::PluginFactory::getInstance();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::PluginFactory>(cx, ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}




void js_anysdk_PluginFactory_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginFactory)", obj);
}

void js_register_anysdk_PluginFactory(JSContext *cx, JSObject *global) {
	jsb_PluginFactory_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_PluginFactory_class->name = "PluginFactory";
	jsb_PluginFactory_class->addProperty = JS_PropertyStub;
	jsb_PluginFactory_class->delProperty = JS_PropertyStub;
	jsb_PluginFactory_class->getProperty = JS_PropertyStub;
	jsb_PluginFactory_class->setProperty = JS_StrictPropertyStub;
	jsb_PluginFactory_class->enumerate = JS_EnumerateStub;
	jsb_PluginFactory_class->resolve = JS_ResolveStub;
	jsb_PluginFactory_class->convert = JS_ConvertStub;
	jsb_PluginFactory_class->finalize = js_anysdk_PluginFactory_finalize;
	jsb_PluginFactory_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	JSFunctionSpec *funcs = NULL;

	static JSFunctionSpec st_funcs[] = {
		JS_FN("purgeFactory", js_anysdk_PluginFactory_purgeFactory, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getInstance", js_anysdk_PluginFactory_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_PluginFactory_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_PluginFactory_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "PluginFactory", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::PluginFactory> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_PluginFactory_class;
		p->proto = jsb_PluginFactory_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_PluginManager_class;
JSObject *jsb_PluginManager_prototype;

JSBool js_anysdk_PluginManager_unloadPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginManager* cobj = (anysdk::framework::PluginManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->unloadPlugin(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	if (argc == 2) {
		const char* arg0;
		int arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->unloadPlugin(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_anysdk_PluginManager_loadPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::PluginManager* cobj = (anysdk::framework::PluginManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		int arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&arg1);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		anysdk::framework::PluginProtocol* ret = cobj->loadPlugin(arg0, arg1);
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::PluginProtocol>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_anysdk_PluginManager_end(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		anysdk::framework::PluginManager::end();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

JSBool js_anysdk_PluginManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		anysdk::framework::PluginManager* ret = anysdk::framework::PluginManager::getInstance();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::PluginManager>(cx, ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}




void js_anysdk_PluginManager_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginManager)", obj);
}

void js_register_anysdk_PluginManager(JSContext *cx, JSObject *global) {
	jsb_PluginManager_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_PluginManager_class->name = "PluginManager";
	jsb_PluginManager_class->addProperty = JS_PropertyStub;
	jsb_PluginManager_class->delProperty = JS_PropertyStub;
	jsb_PluginManager_class->getProperty = JS_PropertyStub;
	jsb_PluginManager_class->setProperty = JS_StrictPropertyStub;
	jsb_PluginManager_class->enumerate = JS_EnumerateStub;
	jsb_PluginManager_class->resolve = JS_ResolveStub;
	jsb_PluginManager_class->convert = JS_ConvertStub;
	jsb_PluginManager_class->finalize = js_anysdk_PluginManager_finalize;
	jsb_PluginManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("unloadPlugin", js_anysdk_PluginManager_unloadPlugin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadPlugin", js_anysdk_PluginManager_loadPlugin, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("end", js_anysdk_PluginManager_end, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getInstance", js_anysdk_PluginManager_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_PluginManager_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_PluginManager_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "PluginManager", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::PluginManager> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_PluginManager_class;
		p->proto = jsb_PluginManager_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_ProtocolIAP_class;
JSObject *jsb_ProtocolIAP_prototype;

JSBool js_anysdk_ProtocolIAP_getPluginId(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolIAP* cobj = (anysdk::framework::ProtocolIAP *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getPluginId();
		jsval jsret;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolIAP_getOrderId(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolIAP* cobj = (anysdk::framework::ProtocolIAP *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getOrderId();
		jsval jsret;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolIAP_resetPayState(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		anysdk::framework::ProtocolIAP::resetPayState();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}



extern JSObject *jsb_PluginProtocol_prototype;

void js_anysdk_ProtocolIAP_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolIAP)", obj);
}

void js_register_anysdk_ProtocolIAP(JSContext *cx, JSObject *global) {
	jsb_ProtocolIAP_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_ProtocolIAP_class->name = "ProtocolIAP";
	jsb_ProtocolIAP_class->addProperty = JS_PropertyStub;
	jsb_ProtocolIAP_class->delProperty = JS_PropertyStub;
	jsb_ProtocolIAP_class->getProperty = JS_PropertyStub;
	jsb_ProtocolIAP_class->setProperty = JS_StrictPropertyStub;
	jsb_ProtocolIAP_class->enumerate = JS_EnumerateStub;
	jsb_ProtocolIAP_class->resolve = JS_ResolveStub;
	jsb_ProtocolIAP_class->convert = JS_ConvertStub;
	jsb_ProtocolIAP_class->finalize = js_anysdk_ProtocolIAP_finalize;
	jsb_ProtocolIAP_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	static JSFunctionSpec funcs[] = {
		JS_FN("getPluginId", js_anysdk_ProtocolIAP_getPluginId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getOrderId", js_anysdk_ProtocolIAP_getOrderId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("resetPayState", js_anysdk_ProtocolIAP_resetPayState, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_ProtocolIAP_prototype = JS_InitClass(
		cx, global,
		jsb_PluginProtocol_prototype,
		jsb_ProtocolIAP_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ProtocolIAP", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::ProtocolIAP> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_ProtocolIAP_class;
		p->proto = jsb_ProtocolIAP_prototype;
		p->parentProto = jsb_PluginProtocol_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_ProtocolAnalytics_class;
JSObject *jsb_ProtocolAnalytics_prototype;

JSBool js_anysdk_ProtocolAnalytics_logTimedEventBegin(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->logTimedEventBegin(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolAnalytics_logError(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		const char* arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->logError(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolAnalytics_setCaptureUncaughtException(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setCaptureUncaughtException(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolAnalytics_setSessionContinueMillis(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		long arg0;
		#pragma warning NO CONVERSION TO NATIVE FOR long;
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setSessionContinueMillis(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolAnalytics_startSession(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->startSession();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolAnalytics_stopSession(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->stopSession();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolAnalytics_logTimedEventEnd(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->logTimedEventEnd(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}


extern JSObject *jsb_PluginProtocol_prototype;

void js_anysdk_ProtocolAnalytics_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolAnalytics)", obj);
}

void js_register_anysdk_ProtocolAnalytics(JSContext *cx, JSObject *global) {
	jsb_ProtocolAnalytics_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_ProtocolAnalytics_class->name = "ProtocolAnalytics";
	jsb_ProtocolAnalytics_class->addProperty = JS_PropertyStub;
	jsb_ProtocolAnalytics_class->delProperty = JS_PropertyStub;
	jsb_ProtocolAnalytics_class->getProperty = JS_PropertyStub;
	jsb_ProtocolAnalytics_class->setProperty = JS_StrictPropertyStub;
	jsb_ProtocolAnalytics_class->enumerate = JS_EnumerateStub;
	jsb_ProtocolAnalytics_class->resolve = JS_ResolveStub;
	jsb_ProtocolAnalytics_class->convert = JS_ConvertStub;
	jsb_ProtocolAnalytics_class->finalize = js_anysdk_ProtocolAnalytics_finalize;
	jsb_ProtocolAnalytics_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	static JSFunctionSpec funcs[] = {
		JS_FN("logTimedEventBegin", js_anysdk_ProtocolAnalytics_logTimedEventBegin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("logError", js_anysdk_ProtocolAnalytics_logError, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setCaptureUncaughtException", js_anysdk_ProtocolAnalytics_setCaptureUncaughtException, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setSessionContinueMillis", js_anysdk_ProtocolAnalytics_setSessionContinueMillis, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("startSession", js_anysdk_ProtocolAnalytics_startSession, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("stopSession", js_anysdk_ProtocolAnalytics_stopSession, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("logTimedEventEnd", js_anysdk_ProtocolAnalytics_logTimedEventEnd, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_ProtocolAnalytics_prototype = JS_InitClass(
		cx, global,
		jsb_PluginProtocol_prototype,
		jsb_ProtocolAnalytics_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ProtocolAnalytics", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::ProtocolAnalytics> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_ProtocolAnalytics_class;
		p->proto = jsb_ProtocolAnalytics_prototype;
		p->parentProto = jsb_PluginProtocol_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_ProtocolAds_class;
JSObject *jsb_ProtocolAds_prototype;

JSBool js_anysdk_ProtocolAds_showAds(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAds* cobj = (anysdk::framework::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		anysdk::framework::AdsType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->showAds(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	else if (argc == 2)
	{
		anysdk::framework::AdsType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

		int idx;
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&idx);
		cobj->showAds(arg0, idx);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolAds_hideAds(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAds* cobj = (anysdk::framework::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		anysdk::framework::AdsType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->hideAds(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	else if (argc == 2)
	{
		anysdk::framework::AdsType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

		int idx;
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&idx);
		cobj->showAds(arg0, idx);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolAds_preloadAds(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAds* cobj = (anysdk::framework::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		anysdk::framework::AdsType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->preloadAds(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	else if (argc == 2)
	{
		anysdk::framework::AdsType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");

		int idx;
		ok &= jsval_to_int32(cx, argv[1], (int32_t *)&idx);
		cobj->preloadAds(arg0, idx);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolAds_queryPoints(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAds* cobj = (anysdk::framework::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		float ret = cobj->queryPoints();
		jsval jsret;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolAds_spendPoints(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAds* cobj = (anysdk::framework::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		int arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->spendPoints(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolAds_isAdTypeSupported(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolAds* cobj = (anysdk::framework::ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		anysdk::framework::AdsType arg0;
		ok &= jsval_to_int32(cx, argv[0], (int32_t *)&arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		bool ret = cobj->isAdTypeSupported(arg0);
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}


extern JSObject *jsb_PluginProtocol_prototype;

void js_anysdk_ProtocolAds_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolAds)", obj);
}

void js_register_anysdk_ProtocolAds(JSContext *cx, JSObject *global) {
	jsb_ProtocolAds_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_ProtocolAds_class->name = "ProtocolAds";
	jsb_ProtocolAds_class->addProperty = JS_PropertyStub;
	jsb_ProtocolAds_class->delProperty = JS_PropertyStub;
	jsb_ProtocolAds_class->getProperty = JS_PropertyStub;
	jsb_ProtocolAds_class->setProperty = JS_StrictPropertyStub;
	jsb_ProtocolAds_class->enumerate = JS_EnumerateStub;
	jsb_ProtocolAds_class->resolve = JS_ResolveStub;
	jsb_ProtocolAds_class->convert = JS_ConvertStub;
	jsb_ProtocolAds_class->finalize = js_anysdk_ProtocolAds_finalize;
	jsb_ProtocolAds_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	static JSFunctionSpec funcs[] = {
		JS_FN("showAds", js_anysdk_ProtocolAds_showAds, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("hideAds", js_anysdk_ProtocolAds_hideAds, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("preloadAds", js_anysdk_ProtocolAds_preloadAds, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("queryPoints", js_anysdk_ProtocolAds_queryPoints, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("spendPoints", js_anysdk_ProtocolAds_spendPoints, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isAdTypeSupported", js_anysdk_ProtocolAds_isAdTypeSupported, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_ProtocolAds_prototype = JS_InitClass(
		cx, global,
		jsb_PluginProtocol_prototype,
		jsb_ProtocolAds_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ProtocolAds", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::ProtocolAds> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_ProtocolAds_class;
		p->proto = jsb_ProtocolAds_prototype;
		p->parentProto = jsb_PluginProtocol_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_ProtocolSocial_class;
JSObject *jsb_ProtocolSocial_prototype;

JSBool js_anysdk_ProtocolSocial_showLeaderboard(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolSocial* cobj = (anysdk::framework::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		const char* arg0;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->showLeaderboard(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolSocial_signOut(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolSocial* cobj = (anysdk::framework::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->signOut();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolSocial_showAchievements(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolSocial* cobj = (anysdk::framework::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->showAchievements();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolSocial_signIn(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolSocial* cobj = (anysdk::framework::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->signIn();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolSocial_submitScore(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolSocial* cobj = (anysdk::framework::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 2) {
		const char* arg0;
		long arg1;
		std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
		#pragma warning NO CONVERSION TO NATIVE FOR long;
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->submitScore(arg0, arg1);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
	return JS_FALSE;
}


extern JSObject *jsb_PluginProtocol_prototype;

void js_anysdk_ProtocolSocial_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolSocial)", obj);
}

void js_register_anysdk_ProtocolSocial(JSContext *cx, JSObject *global) {
	jsb_ProtocolSocial_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_ProtocolSocial_class->name = "ProtocolSocial";
	jsb_ProtocolSocial_class->addProperty = JS_PropertyStub;
	jsb_ProtocolSocial_class->delProperty = JS_PropertyStub;
	jsb_ProtocolSocial_class->getProperty = JS_PropertyStub;
	jsb_ProtocolSocial_class->setProperty = JS_StrictPropertyStub;
	jsb_ProtocolSocial_class->enumerate = JS_EnumerateStub;
	jsb_ProtocolSocial_class->resolve = JS_ResolveStub;
	jsb_ProtocolSocial_class->convert = JS_ConvertStub;
	jsb_ProtocolSocial_class->finalize = js_anysdk_ProtocolSocial_finalize;
	jsb_ProtocolSocial_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	static JSFunctionSpec funcs[] = {
		JS_FN("showLeaderboard", js_anysdk_ProtocolSocial_showLeaderboard, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("signOut", js_anysdk_ProtocolSocial_signOut, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("showAchievements", js_anysdk_ProtocolSocial_showAchievements, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("signIn", js_anysdk_ProtocolSocial_signIn, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("submitScore", js_anysdk_ProtocolSocial_submitScore, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_ProtocolSocial_prototype = JS_InitClass(
		cx, global,
		jsb_PluginProtocol_prototype,
		jsb_ProtocolSocial_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ProtocolSocial", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::ProtocolSocial> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_ProtocolSocial_class;
		p->proto = jsb_ProtocolSocial_prototype;
		p->parentProto = jsb_PluginProtocol_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_ProtocolUser_class;
JSObject *jsb_ProtocolUser_prototype;

JSBool js_anysdk_ProtocolUser_isLogined(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolUser* cobj = (anysdk::framework::ProtocolUser *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->isLogined();
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolUser_getUserID(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolUser* cobj = (anysdk::framework::ProtocolUser *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getUserID();
		jsval jsret;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}

JSBool js_anysdk_ProtocolUser_login(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;

	JSObject *obj = NULL;
	anysdk::framework::ProtocolUser* cobj = NULL;
	obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	cobj = (anysdk::framework::ProtocolUser *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	do {
		if (argc == 1) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			if (!ok) { ok = JS_TRUE; break; }
			cobj->login(arg0);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
		else if (argc == 2) {
			std::string arg0;
			ok &= jsval_to_std_string(cx, argv[0], &arg0);
			std::string arg1;
			ok &= jsval_to_std_string(cx, argv[1], &arg1);
			if (!ok) { ok = JS_TRUE; break; }
			cobj->login(arg0, arg1);
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	do {
		if (argc == 0) {
			cobj->login();
			JS_SET_RVAL(cx, vp, JSVAL_VOID);
			return JS_TRUE;
		}
	} while(0);

	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolUser_getPluginId(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolUser* cobj = (anysdk::framework::ProtocolUser *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getPluginId();
		jsval jsret;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}


extern JSObject *jsb_PluginProtocol_prototype;

void js_anysdk_ProtocolUser_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolUser)", obj);
}

void js_register_anysdk_ProtocolUser(JSContext *cx, JSObject *global) {
	jsb_ProtocolUser_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_ProtocolUser_class->name = "ProtocolUser";
	jsb_ProtocolUser_class->addProperty = JS_PropertyStub;
	jsb_ProtocolUser_class->delProperty = JS_PropertyStub;
	jsb_ProtocolUser_class->getProperty = JS_PropertyStub;
	jsb_ProtocolUser_class->setProperty = JS_StrictPropertyStub;
	jsb_ProtocolUser_class->enumerate = JS_EnumerateStub;
	jsb_ProtocolUser_class->resolve = JS_ResolveStub;
	jsb_ProtocolUser_class->convert = JS_ConvertStub;
	jsb_ProtocolUser_class->finalize = js_anysdk_ProtocolUser_finalize;
	jsb_ProtocolUser_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	static JSFunctionSpec funcs[] = {
		JS_FN("isLogined", js_anysdk_ProtocolUser_isLogined, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getUserID", js_anysdk_ProtocolUser_getUserID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("login", js_anysdk_ProtocolUser_login, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPluginId", js_anysdk_ProtocolUser_getPluginId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_ProtocolUser_prototype = JS_InitClass(
		cx, global,
		jsb_PluginProtocol_prototype,
		jsb_ProtocolUser_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ProtocolUser", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::ProtocolUser> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_ProtocolUser_class;
		p->proto = jsb_ProtocolUser_prototype;
		p->parentProto = jsb_PluginProtocol_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}


JSClass  *jsb_ProtocolPush_class;
JSObject *jsb_ProtocolPush_prototype;

JSBool js_anysdk_ProtocolPush_startPush(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolPush* cobj = (anysdk::framework::ProtocolPush *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->startPush();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolPush_closePush(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolPush* cobj = (anysdk::framework::ProtocolPush *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->closePush();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolPush_delAlias(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolPush* cobj = (anysdk::framework::ProtocolPush *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->delAlias(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}
JSBool js_anysdk_ProtocolPush_setAlias(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolPush* cobj = (anysdk::framework::ProtocolPush *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		std::string arg0;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setAlias(arg0);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}


extern JSObject *jsb_PluginProtocol_prototype;

void js_anysdk_ProtocolPush_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolPush)", obj);
}

void js_register_anysdk_ProtocolPush(JSContext *cx, JSObject *global) {
	jsb_ProtocolPush_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_ProtocolPush_class->name = "ProtocolPush";
	jsb_ProtocolPush_class->addProperty = JS_PropertyStub;
	jsb_ProtocolPush_class->delProperty = JS_PropertyStub;
	jsb_ProtocolPush_class->getProperty = JS_PropertyStub;
	jsb_ProtocolPush_class->setProperty = JS_StrictPropertyStub;
	jsb_ProtocolPush_class->enumerate = JS_EnumerateStub;
	jsb_ProtocolPush_class->resolve = JS_ResolveStub;
	jsb_ProtocolPush_class->convert = JS_ConvertStub;
	jsb_ProtocolPush_class->finalize = js_anysdk_ProtocolPush_finalize;
	jsb_ProtocolPush_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	static JSFunctionSpec funcs[] = {
		JS_FN("startPush", js_anysdk_ProtocolPush_startPush, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("closePush", js_anysdk_ProtocolPush_closePush, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("delAlias", js_anysdk_ProtocolPush_delAlias, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setAlias", js_anysdk_ProtocolPush_setAlias, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_ProtocolPush_prototype = JS_InitClass(
		cx, global,
		jsb_PluginProtocol_prototype,
		jsb_ProtocolPush_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ProtocolPush", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::ProtocolPush> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_ProtocolPush_class;
		p->proto = jsb_ProtocolPush_prototype;
		p->parentProto = jsb_PluginProtocol_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}

JSClass  *jsb_ProtocolCrash_class;
JSObject *jsb_ProtocolCrash_prototype;

JSBool js_anysdk_ProtocolCrash_reportException(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolCrash* cobj = (anysdk::framework::ProtocolCrash *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    if (argc == 2) {
        const char* arg0;
        const char* arg1;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, argv[0], &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, argv[1], &arg1_tmp); arg1 = arg1_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        cobj->reportException(arg0, arg1);
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 2);
    return JS_FALSE;
}
JSBool js_anysdk_ProtocolCrash_setUserIdentifier(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolCrash* cobj = (anysdk::framework::ProtocolCrash *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        cobj->setUserIdentifier(arg0.c_str());
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}
JSBool js_anysdk_ProtocolCrash_leaveBreadcrumb(JSContext *cx, uint32_t argc, jsval *vp)
{
    jsval *argv = JS_ARGV(cx, vp);
    JSBool ok = JS_TRUE;
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolCrash* cobj = (anysdk::framework::ProtocolCrash *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, argv[0], &arg0);
        JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
        cobj->leaveBreadcrumb(arg0.c_str());
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
    return JS_FALSE;
}


extern JSObject *jsb_PluginProtocol_prototype;

void js_anysdk_ProtocolCrash_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolCrash)", obj);
}

void js_register_anysdk_ProtocolCrash(JSContext *cx, JSObject *global) {
    jsb_ProtocolCrash_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_ProtocolCrash_class->name = "ProtocolCrash";
    jsb_ProtocolCrash_class->addProperty = JS_PropertyStub;
    jsb_ProtocolCrash_class->delProperty = JS_PropertyStub;
    jsb_ProtocolCrash_class->getProperty = JS_PropertyStub;
    jsb_ProtocolCrash_class->setProperty = JS_StrictPropertyStub;
    jsb_ProtocolCrash_class->enumerate = JS_EnumerateStub;
    jsb_ProtocolCrash_class->resolve = JS_ResolveStub;
    jsb_ProtocolCrash_class->convert = JS_ConvertStub;
    jsb_ProtocolCrash_class->finalize = js_anysdk_ProtocolCrash_finalize;
    jsb_ProtocolCrash_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    JSPropertySpec *properties = NULL;
    
    static JSFunctionSpec funcs[] = {
        JS_FN("reportException", js_anysdk_ProtocolCrash_reportException, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setUserIdentifier", js_anysdk_ProtocolCrash_setUserIdentifier,1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("leaveBreadcrumb", js_anysdk_ProtocolCrash_leaveBreadcrumb, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    JSFunctionSpec *st_funcs = NULL;
    
    jsb_ProtocolCrash_prototype = JS_InitClass(
                                              cx, global,
                                              jsb_PluginProtocol_prototype,
                                              jsb_ProtocolCrash_class,
                                              empty_constructor, 0,
                                              properties,
                                              funcs,
                                              NULL, // no static properties
                                              st_funcs);
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "ProtocolCrash", JSPROP_ENUMERATE | JSPROP_READONLY, &found);
    
    // add the proto and JSClass to the type->js info hash table
    TypeTest<anysdk::framework::ProtocolCrash> t;
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    if (!p) {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->type = typeId;
        p->jsclass = jsb_ProtocolCrash_class;
        p->proto = jsb_ProtocolCrash_prototype;
        p->parentProto = jsb_PluginProtocol_prototype;
        HASH_ADD_INT(_js_global_type_ht, type, p);
    }
}

JSClass  *jsb_ProtocolREC_class;
JSObject *jsb_ProtocolREC_prototype;

JSBool js_anysdk_ProtocolREC_startRecording(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolREC* cobj = (anysdk::framework::ProtocolREC *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    if (argc == 0) {
        cobj->startRecording();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return JS_FALSE;
}
JSBool js_anysdk_ProtocolREC_stopRecording(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolREC* cobj = (anysdk::framework::ProtocolREC *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    if (argc == 0) {
        cobj->stopRecording();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return JS_FALSE;
}

extern JSObject *jsb_PluginProtocol_prototype;

void js_anysdk_ProtocolREC_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolREC)", obj);
}

void js_register_anysdk_ProtocolREC(JSContext *cx, JSObject *global) {
    jsb_ProtocolREC_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_ProtocolREC_class->name = "ProtocolREC";
    jsb_ProtocolREC_class->addProperty = JS_PropertyStub;
    jsb_ProtocolREC_class->delProperty = JS_PropertyStub;
    jsb_ProtocolREC_class->getProperty = JS_PropertyStub;
    jsb_ProtocolREC_class->setProperty = JS_StrictPropertyStub;
    jsb_ProtocolREC_class->enumerate = JS_EnumerateStub;
    jsb_ProtocolREC_class->resolve = JS_ResolveStub;
    jsb_ProtocolREC_class->convert = JS_ConvertStub;
    jsb_ProtocolREC_class->finalize = js_anysdk_ProtocolREC_finalize;
    jsb_ProtocolREC_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    JSPropertySpec *properties = NULL;
    
    static JSFunctionSpec funcs[] = {
        JS_FN("startRecording", js_anysdk_ProtocolREC_startRecording, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stopRecording", js_anysdk_ProtocolREC_stopRecording, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };
    
    JSFunctionSpec *st_funcs = NULL;
    
    jsb_ProtocolREC_prototype = JS_InitClass(
                                              cx, global,
                                              jsb_PluginProtocol_prototype,
                                              jsb_ProtocolREC_class,
                                              empty_constructor, 0,
                                              properties,
                                              funcs,
                                              NULL, // no static properties
                                              st_funcs);
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "ProtocolREC", JSPROP_ENUMERATE | JSPROP_READONLY, &found);
    
    // add the proto and JSClass to the type->js info hash table
    TypeTest<anysdk::framework::ProtocolREC> t;
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    if (!p) {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->type = typeId;
        p->jsclass = jsb_ProtocolREC_class;
        p->proto = jsb_ProtocolREC_prototype;
        p->parentProto = jsb_PluginProtocol_prototype;
        HASH_ADD_INT(_js_global_type_ht, type, p);
    }
}

JSClass  *jsb_ProtocolCustom_class;
JSObject *jsb_ProtocolCustom_prototype;



extern JSObject *jsb_PluginProtocol_prototype;

void js_anysdk_ProtocolCustom_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolCustom)", obj);
}

void js_register_anysdk_ProtocolCustom(JSContext *cx, JSObject *global) {
    jsb_ProtocolCustom_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_ProtocolCustom_class->name = "ProtocolCustom";
    jsb_ProtocolCustom_class->addProperty = JS_PropertyStub;
    jsb_ProtocolCustom_class->delProperty = JS_PropertyStub;
    jsb_ProtocolCustom_class->getProperty = JS_PropertyStub;
    jsb_ProtocolCustom_class->setProperty = JS_StrictPropertyStub;
    jsb_ProtocolCustom_class->enumerate = JS_EnumerateStub;
    jsb_ProtocolCustom_class->resolve = JS_ResolveStub;
    jsb_ProtocolCustom_class->convert = JS_ConvertStub;
    jsb_ProtocolCustom_class->finalize = js_anysdk_ProtocolCustom_finalize;
    jsb_ProtocolCustom_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);
    
    JSPropertySpec *properties = NULL;
    
    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };
    
    JSFunctionSpec *st_funcs = NULL;
    
    jsb_ProtocolCustom_prototype = JS_InitClass(
                                              cx, global,
                                              jsb_PluginProtocol_prototype,
                                              jsb_ProtocolCustom_class,
                                              empty_constructor, 0,
                                              properties,
                                              funcs,
                                              NULL, // no static properties
                                              st_funcs);
    // make the class enumerable in the registered namespace
    JSBool found;
    JS_SetPropertyAttributes(cx, global, "ProtocolCustom", JSPROP_ENUMERATE | JSPROP_READONLY, &found);
    
    // add the proto and JSClass to the type->js info hash table
    TypeTest<anysdk::framework::ProtocolCustom> t;
    js_type_class_t *p;
    uint32_t typeId = t.s_id();
    HASH_FIND_INT(_js_global_type_ht, &typeId, p);
    if (!p) {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->type = typeId;
        p->jsclass = jsb_ProtocolCustom_class;
        p->proto = jsb_ProtocolCustom_prototype;
        p->parentProto = jsb_PluginProtocol_prototype;
        HASH_ADD_INT(_js_global_type_ht, type, p);
    }
}


JSClass  *jsb_AgentManager_class;
JSObject *jsb_AgentManager_prototype;

JSBool js_anysdk_AgentManager_getSocialPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		anysdk::framework::ProtocolSocial* ret = cobj->getSocialPlugin();
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::ProtocolSocial>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_AgentManager_unloadALLPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
     CCLOG("\n********** \nunloadALLPlugin was deprecated, please use unloadAllPlugins instead.\n**********");
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->unloadALLPlugin();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_AgentManager_loadALLPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
     CCLOG("\n********** \nloadALLPlugin was deprecated, please use loadAllPlugins instead.\n**********");
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		cobj->loadALLPlugin();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}

JSBool js_anysdk_AgentManager_unloadAllPlugins(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    if (argc == 0) {
        cobj->unloadAllPlugins();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return JS_FALSE;
}
JSBool js_anysdk_AgentManager_loadAllPlugins(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    if (argc == 0) {
        cobj->loadAllPlugins();
        JS_SET_RVAL(cx, vp, JSVAL_VOID);
        return JS_TRUE;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return JS_FALSE;
}

JSBool js_anysdk_AgentManager_getCustomParam(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getCustomParam();
		jsval jsret;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_AgentManager_getUserPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		anysdk::framework::ProtocolUser* ret = cobj->getUserPlugin();
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::ProtocolUser>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_AgentManager_init(JSContext *cx, uint32_t argc, jsval *vp)
{
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 4) {
		std::string arg0;
		std::string arg1;
		std::string arg2;
		std::string arg3;
		ok &= jsval_to_std_string(cx, argv[0], &arg0);
		ok &= jsval_to_std_string(cx, argv[1], &arg1);
		ok &= jsval_to_std_string(cx, argv[2], &arg2);
		ok &= jsval_to_std_string(cx, argv[3], &arg3);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->init(arg0, arg1, arg2, arg3);
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 4);
	return JS_FALSE;
}
JSBool js_anysdk_AgentManager_getAdsPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		anysdk::framework::ProtocolAds* ret = cobj->getAdsPlugin();
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::ProtocolAds>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_AgentManager_getPushPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		anysdk::framework::ProtocolPush* ret = cobj->getPushPlugin();
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::ProtocolPush>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_AgentManager_getSharePlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		anysdk::framework::ProtocolShare* ret = cobj->getSharePlugin();
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::ProtocolShare>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_AgentManager_getAnalyticsPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		anysdk::framework::ProtocolAnalytics* ret = cobj->getAnalyticsPlugin();
		jsval jsret;
		do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::ProtocolAnalytics>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}

JSBool js_anysdk_AgentManager_getCrashPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    if (argc == 0) {
        anysdk::framework::ProtocolCrash* ret = cobj->getCrashPlugin();
        jsval jsret;
        do {
            if (ret) {
                js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::ProtocolCrash>(cx, ret);
                jsret = OBJECT_TO_JSVAL(proxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return JS_FALSE;
}

JSBool js_anysdk_AgentManager_getCustomPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    if (argc == 0) {
        anysdk::framework::ProtocolCustom* ret = cobj->getCustomPlugin();
        jsval jsret;
        do {
            if (ret) {
                js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::ProtocolCustom>(cx, ret);
                jsret = OBJECT_TO_JSVAL(proxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return JS_FALSE;
}

JSBool js_anysdk_AgentManager_getRECPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
    if (argc == 0) {
        anysdk::framework::ProtocolREC* ret = cobj->getRECPlugin();
        jsval jsret;
        do {
            if (ret) {
                js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::ProtocolREC>(cx, ret);
                jsret = OBJECT_TO_JSVAL(proxy->obj);
            } else {
                jsret = JSVAL_NULL;
            }
        } while (0);
        JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    
    JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
    return JS_FALSE;
}

JSBool js_anysdk_AgentManager_getChannelId(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		std::string ret = cobj->getChannelId();
		jsval jsret;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_AgentManager_setIsAnaylticsEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		jsval *argv = JS_ARGV(cx, vp);
		bool arg = JSVAL_TO_BOOLEAN( argv[0] );
		cobj->setIsAnaylticsEnabled(arg);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_AgentManager_isAnaylticsEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 0) {
		bool ret = cobj->isAnaylticsEnabled();
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 0);
	return JS_FALSE;
}
JSBool js_anysdk_AgentManager_end(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		anysdk::framework::AgentManager::end();
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}

JSBool js_anysdk_AgentManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
	if (argc == 0) {
		anysdk::framework::AgentManager* ret = anysdk::framework::AgentManager::getInstance();
		jsval jsret;
		do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::AgentManager>(cx, ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
		JS_SET_RVAL(cx, vp, jsret);
		return JS_TRUE;
	}
	JS_ReportError(cx, "wrong number of arguments");
	return JS_FALSE;
}




void js_anysdk_AgentManager_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (AgentManager)", obj);
}

void js_register_anysdk_AgentManager(JSContext *cx, JSObject *global) {
	jsb_AgentManager_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_AgentManager_class->name = "AgentManager";
	jsb_AgentManager_class->addProperty = JS_PropertyStub;
	jsb_AgentManager_class->delProperty = JS_PropertyStub;
	jsb_AgentManager_class->getProperty = JS_PropertyStub;
	jsb_AgentManager_class->setProperty = JS_StrictPropertyStub;
	jsb_AgentManager_class->enumerate = JS_EnumerateStub;
	jsb_AgentManager_class->resolve = JS_ResolveStub;
	jsb_AgentManager_class->convert = JS_ConvertStub;
	jsb_AgentManager_class->finalize = js_anysdk_AgentManager_finalize;
	jsb_AgentManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	static JSPropertySpec properties[] = {
		{0, 0, 0, JSOP_NULLWRAPPER, JSOP_NULLWRAPPER}
	};

	static JSFunctionSpec funcs[] = {
		JS_FN("getSocialPlugin", js_anysdk_AgentManager_getSocialPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("unloadALLPlugin", js_anysdk_AgentManager_unloadALLPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("loadALLPlugin", js_anysdk_AgentManager_loadALLPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("unloadAllPlugins", js_anysdk_AgentManager_unloadAllPlugins, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadAllPlugins", js_anysdk_AgentManager_loadAllPlugins, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getCustomParam", js_anysdk_AgentManager_getCustomParam, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getUserPlugin", js_anysdk_AgentManager_getUserPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("init", js_anysdk_AgentManager_init, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getAdsPlugin", js_anysdk_AgentManager_getAdsPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getPushPlugin", js_anysdk_AgentManager_getPushPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getSharePlugin", js_anysdk_AgentManager_getSharePlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getAnalyticsPlugin", js_anysdk_AgentManager_getAnalyticsPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getRECPlugin", js_anysdk_AgentManager_getRECPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCustomPlugin", js_anysdk_AgentManager_getCustomPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCrashPlugin", js_anysdk_AgentManager_getCrashPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getChannelId", js_anysdk_AgentManager_getChannelId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setIsAnaylticsEnabled", js_anysdk_AgentManager_setIsAnaylticsEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("isAnaylticsEnabled", js_anysdk_AgentManager_isAnaylticsEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	static JSFunctionSpec st_funcs[] = {
		JS_FN("end", js_anysdk_AgentManager_end, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("getInstance", js_anysdk_AgentManager_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FS_END
	};

	jsb_AgentManager_prototype = JS_InitClass(
		cx, global,
		NULL, // parent proto
		jsb_AgentManager_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "AgentManager", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::AgentManager> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_AgentManager_class;
		p->proto = jsb_AgentManager_prototype;
		p->parentProto = NULL;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}

void register_all_anysdk(JSContext* cx, JSObject* obj) {
	// first, try to get the ns
	jsval nsval;
	JSObject *ns;
	JS_GetProperty(cx, obj, "anysdk", &nsval);
	if (nsval == JSVAL_VOID) {
		ns = JS_NewObject(cx, NULL, NULL, NULL);
		nsval = OBJECT_TO_JSVAL(ns);
		JS_SetProperty(cx, obj, "anysdk", &nsval);
	} else {
		JS_ValueToObject(cx, nsval, &ns);
	}
	obj = ns;

	js_register_anysdk_PluginProtocol(cx, obj);
	js_register_anysdk_ProtocolUser(cx, obj);
	js_register_anysdk_PluginFactory(cx, obj);
	js_register_anysdk_ProtocolIAP(cx, obj);
	js_register_anysdk_PluginParam(cx, obj);
	js_register_anysdk_AgentManager(cx, obj);
	js_register_anysdk_ProtocolSocial(cx, obj);
	js_register_anysdk_ProtocolAnalytics(cx, obj);
	js_register_anysdk_ProtocolAds(cx, obj);
	js_register_anysdk_PluginManager(cx, obj);
	js_register_anysdk_ProtocolPush(cx, obj);
    js_register_anysdk_ProtocolREC(cx, obj);
    js_register_anysdk_ProtocolCustom(cx, obj);
    js_register_anysdk_ProtocolCrash(cx, obj);
}

