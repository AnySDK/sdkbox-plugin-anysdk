#include "manualanysdkbindings.hpp"
#include "cocos2d_specifics.hpp"
#include "js_manual_conversions.h"
#include "jsb_anysdk_basic_conversions.h"
#include "AgentManager.h"
#include "PluginProtocol.h"
#include "ProtocolPush.h"
#include "PluginFactory.h"
#include "ProtocolAds.h"
#include "PluginManager.h"
#include "ProtocolAnalytics.h"
#include "ProtocolSocial.h"
#include "ProtocolIAP.h"
#include "ProtocolUser.h"
#include "mozilla/Maybe.h"

using namespace anysdk::framework;

template<class T>
static bool dummy_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedValue initializing(cx);
    bool isNewValid = true;
    if (isNewValid)
    {
        TypeTest<T> t;
        js_type_class_t *typeClass = nullptr;
        std::string typeName = t.s_name();
        auto typeMapIter = _js_global_type_map.find(typeName);
        CCASSERT(typeMapIter != _js_global_type_map.end(), "Can't find the class type!");
        typeClass = typeMapIter->second;
        CCASSERT(typeClass, "The value is null.");

        JS::RootedObject proto(cx, typeClass->proto.get());
        JS::RootedObject parent(cx, typeClass->parentProto.get());
        JS::RootedObject _tmp(cx, JS_NewObject(cx, typeClass->jsclass, proto, parent));
        
        T* cobj = new T();
        js_proxy_t *pp = jsb_new_proxy(cobj, _tmp);
        AddObjectRoot(cx, &pp->obj);
        args.rval().set(OBJECT_TO_JSVAL(_tmp));
        return true;
    }

    return false;
}

static bool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
    return false;
}

static bool js_is_native_obj(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    args.rval().setBoolean(true);
    return true;    
}
JSClass  *jsb_anysdk_framework_PluginProtocol_class;
JSObject *jsb_anysdk_framework_PluginProtocol_prototype;

bool js_anysdk_framework_PluginProtocol_getPluginName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::PluginProtocol* cobj = (anysdk::framework::PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_PluginProtocol_getPluginName : Invalid Native Object");
    if (argc == 0) {
        const char* ret = cobj->getPluginName();
        jsval jsret = JSVAL_NULL;
        jsret = c_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_PluginProtocol_getPluginName : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_PluginProtocol_getPluginVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::PluginProtocol* cobj = (anysdk::framework::PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_PluginProtocol_getPluginVersion : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getPluginVersion();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_PluginProtocol_getPluginVersion : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_PluginProtocol_setPluginName(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::PluginProtocol* cobj = (anysdk::framework::PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_PluginProtocol_setPluginName : Invalid Native Object");
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_PluginProtocol_setPluginName : Error processing arguments");
        cobj->setPluginName(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_PluginProtocol_setPluginName : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_anysdk_framework_PluginProtocol_getSDKVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::PluginProtocol* cobj = (anysdk::framework::PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_PluginProtocol_getSDKVersion : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getSDKVersion();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_PluginProtocol_getSDKVersion : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

void js_anysdk_framework_PluginProtocol_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginProtocol)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        anysdk::framework::PluginProtocol *nobj = static_cast<anysdk::framework::PluginProtocol *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_anysdk_framework_PluginProtocol(JSContext *cx, JS::HandleObject global) {
    jsb_anysdk_framework_PluginProtocol_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_anysdk_framework_PluginProtocol_class->name = "PluginProtocol";
    jsb_anysdk_framework_PluginProtocol_class->addProperty = JS_PropertyStub;
    jsb_anysdk_framework_PluginProtocol_class->delProperty = JS_DeletePropertyStub;
    jsb_anysdk_framework_PluginProtocol_class->getProperty = JS_PropertyStub;
    jsb_anysdk_framework_PluginProtocol_class->setProperty = JS_StrictPropertyStub;
    jsb_anysdk_framework_PluginProtocol_class->enumerate = JS_EnumerateStub;
    jsb_anysdk_framework_PluginProtocol_class->resolve = JS_ResolveStub;
    jsb_anysdk_framework_PluginProtocol_class->convert = JS_ConvertStub;
    jsb_anysdk_framework_PluginProtocol_class->finalize = js_anysdk_framework_PluginProtocol_finalize;
    jsb_anysdk_framework_PluginProtocol_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getPluginName", js_anysdk_framework_PluginProtocol_getPluginName, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPluginVersion", js_anysdk_framework_PluginProtocol_getPluginVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setPluginName", js_anysdk_framework_PluginProtocol_setPluginName, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSDKVersion", js_anysdk_framework_PluginProtocol_getSDKVersion, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_anysdk_framework_PluginProtocol_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_anysdk_framework_PluginProtocol_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "PluginProtocol", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<anysdk::framework::PluginProtocol> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_anysdk_framework_PluginProtocol_class;
        p->proto = jsb_anysdk_framework_PluginProtocol_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_anysdk_framework_PluginFactory_class;
JSObject *jsb_anysdk_framework_PluginFactory_prototype;

bool js_anysdk_framework_PluginFactory_purgeFactory(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        anysdk::framework::PluginFactory::purgeFactory();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_anysdk_framework_PluginFactory_purgeFactory : wrong number of arguments");
    return false;
}

bool js_anysdk_framework_PluginFactory_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        anysdk::framework::PluginFactory* ret = anysdk::framework::PluginFactory::getInstance();
        jsval jsret = JSVAL_NULL;
        do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::PluginFactory>(cx, ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_anysdk_framework_PluginFactory_getInstance : wrong number of arguments");
    return false;
}



void js_anysdk_framework_PluginFactory_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginFactory)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        anysdk::framework::PluginFactory *nobj = static_cast<anysdk::framework::PluginFactory *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_anysdk_framework_PluginFactory(JSContext *cx, JS::HandleObject global) {
    jsb_anysdk_framework_PluginFactory_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_anysdk_framework_PluginFactory_class->name = "PluginFactory";
    jsb_anysdk_framework_PluginFactory_class->addProperty = JS_PropertyStub;
    jsb_anysdk_framework_PluginFactory_class->delProperty = JS_DeletePropertyStub;
    jsb_anysdk_framework_PluginFactory_class->getProperty = JS_PropertyStub;
    jsb_anysdk_framework_PluginFactory_class->setProperty = JS_StrictPropertyStub;
    jsb_anysdk_framework_PluginFactory_class->enumerate = JS_EnumerateStub;
    jsb_anysdk_framework_PluginFactory_class->resolve = JS_ResolveStub;
    jsb_anysdk_framework_PluginFactory_class->convert = JS_ConvertStub;
    jsb_anysdk_framework_PluginFactory_class->finalize = js_anysdk_framework_PluginFactory_finalize;
    jsb_anysdk_framework_PluginFactory_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("purgeFactory", js_anysdk_framework_PluginFactory_purgeFactory, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInstance", js_anysdk_framework_PluginFactory_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_anysdk_framework_PluginFactory_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_anysdk_framework_PluginFactory_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "PluginFactory", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<anysdk::framework::PluginFactory> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_anysdk_framework_PluginFactory_class;
        p->proto = jsb_anysdk_framework_PluginFactory_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_anysdk_framework_PluginManager_class;
JSObject *jsb_anysdk_framework_PluginManager_prototype;

bool js_anysdk_framework_PluginManager_unloadPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::PluginManager* cobj = (anysdk::framework::PluginManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_PluginManager_unloadPlugin : Invalid Native Object");
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_PluginManager_unloadPlugin : Error processing arguments");
        cobj->unloadPlugin(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        const char* arg0;
        int arg1;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_PluginManager_unloadPlugin : Error processing arguments");
        cobj->unloadPlugin(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_PluginManager_unloadPlugin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_anysdk_framework_PluginManager_loadPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::PluginManager* cobj = (anysdk::framework::PluginManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_PluginManager_loadPlugin : Invalid Native Object");
    if (argc == 2) {
        const char* arg0;
        int arg1;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_PluginManager_loadPlugin : Error processing arguments");
        anysdk::framework::PluginProtocol* ret = cobj->loadPlugin(arg0, arg1);
        jsval jsret = JSVAL_NULL;
        do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::PluginProtocol>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_PluginManager_loadPlugin : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_anysdk_framework_PluginManager_end(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        anysdk::framework::PluginManager::end();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_anysdk_framework_PluginManager_end : wrong number of arguments");
    return false;
}

bool js_anysdk_framework_PluginManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        anysdk::framework::PluginManager* ret = anysdk::framework::PluginManager::getInstance();
        jsval jsret = JSVAL_NULL;
        do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::PluginManager>(cx, ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_anysdk_framework_PluginManager_getInstance : wrong number of arguments");
    return false;
}



void js_anysdk_framework_PluginManager_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (PluginManager)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        anysdk::framework::PluginManager *nobj = static_cast<anysdk::framework::PluginManager *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_anysdk_framework_PluginManager(JSContext *cx, JS::HandleObject global) {
    jsb_anysdk_framework_PluginManager_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_anysdk_framework_PluginManager_class->name = "PluginManager";
    jsb_anysdk_framework_PluginManager_class->addProperty = JS_PropertyStub;
    jsb_anysdk_framework_PluginManager_class->delProperty = JS_DeletePropertyStub;
    jsb_anysdk_framework_PluginManager_class->getProperty = JS_PropertyStub;
    jsb_anysdk_framework_PluginManager_class->setProperty = JS_StrictPropertyStub;
    jsb_anysdk_framework_PluginManager_class->enumerate = JS_EnumerateStub;
    jsb_anysdk_framework_PluginManager_class->resolve = JS_ResolveStub;
    jsb_anysdk_framework_PluginManager_class->convert = JS_ConvertStub;
    jsb_anysdk_framework_PluginManager_class->finalize = js_anysdk_framework_PluginManager_finalize;
    jsb_anysdk_framework_PluginManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("unloadPlugin", js_anysdk_framework_PluginManager_unloadPlugin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadPlugin", js_anysdk_framework_PluginManager_loadPlugin, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("end", js_anysdk_framework_PluginManager_end, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInstance", js_anysdk_framework_PluginManager_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_anysdk_framework_PluginManager_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_anysdk_framework_PluginManager_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "PluginManager", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<anysdk::framework::PluginManager> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_anysdk_framework_PluginManager_class;
        p->proto = jsb_anysdk_framework_PluginManager_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_anysdk_framework_ProtocolAnalytics_class;
JSObject *jsb_anysdk_framework_ProtocolAnalytics_prototype;

bool js_anysdk_framework_ProtocolAnalytics_isFunctionSupported(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolAnalytics_isFunctionSupported : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_ProtocolAnalytics_isFunctionSupported : Error processing arguments");
        bool ret = cobj->isFunctionSupported(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolAnalytics_isFunctionSupported : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_anysdk_framework_ProtocolAnalytics_logTimedEventBegin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolAnalytics_logTimedEventBegin : Invalid Native Object");
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_ProtocolAnalytics_logTimedEventBegin : Error processing arguments");
        cobj->logTimedEventBegin(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolAnalytics_logTimedEventBegin : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_anysdk_framework_ProtocolAnalytics_logError(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolAnalytics_logError : Invalid Native Object");
    if (argc == 2) {
        const char* arg0;
        const char* arg1;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        std::string arg1_tmp; ok &= jsval_to_std_string(cx, args.get(1), &arg1_tmp); arg1 = arg1_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_ProtocolAnalytics_logError : Error processing arguments");
        cobj->logError(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolAnalytics_logError : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}
bool js_anysdk_framework_ProtocolAnalytics_setCaptureUncaughtException(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolAnalytics_setCaptureUncaughtException : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_ProtocolAnalytics_setCaptureUncaughtException : Error processing arguments");
        cobj->setCaptureUncaughtException(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolAnalytics_setCaptureUncaughtException : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_anysdk_framework_ProtocolAnalytics_setSessionContinueMillis(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolAnalytics_setSessionContinueMillis : Invalid Native Object");
    if (argc == 1) {
        long arg0;
        ok &= jsval_to_long(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_ProtocolAnalytics_setSessionContinueMillis : Error processing arguments");
        cobj->setSessionContinueMillis(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolAnalytics_setSessionContinueMillis : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_anysdk_framework_ProtocolAnalytics_startSession(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolAnalytics_startSession : Invalid Native Object");
    if (argc == 0) {
        cobj->startSession();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolAnalytics_startSession : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_ProtocolAnalytics_stopSession(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolAnalytics_stopSession : Invalid Native Object");
    if (argc == 0) {
        cobj->stopSession();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolAnalytics_stopSession : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_ProtocolAnalytics_logTimedEventEnd(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolAnalytics* cobj = (anysdk::framework::ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolAnalytics_logTimedEventEnd : Invalid Native Object");
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_ProtocolAnalytics_logTimedEventEnd : Error processing arguments");
        cobj->logTimedEventEnd(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolAnalytics_logTimedEventEnd : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

extern JSObject *jsb_anysdk_framework_PluginProtocol_prototype;

void js_anysdk_framework_ProtocolAnalytics_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolAnalytics)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        anysdk::framework::ProtocolAnalytics *nobj = static_cast<anysdk::framework::ProtocolAnalytics *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_anysdk_framework_ProtocolAnalytics(JSContext *cx, JS::HandleObject global) {
    jsb_anysdk_framework_ProtocolAnalytics_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_anysdk_framework_ProtocolAnalytics_class->name = "ProtocolAnalytics";
    jsb_anysdk_framework_ProtocolAnalytics_class->addProperty = JS_PropertyStub;
    jsb_anysdk_framework_ProtocolAnalytics_class->delProperty = JS_DeletePropertyStub;
    jsb_anysdk_framework_ProtocolAnalytics_class->getProperty = JS_PropertyStub;
    jsb_anysdk_framework_ProtocolAnalytics_class->setProperty = JS_StrictPropertyStub;
    jsb_anysdk_framework_ProtocolAnalytics_class->enumerate = JS_EnumerateStub;
    jsb_anysdk_framework_ProtocolAnalytics_class->resolve = JS_ResolveStub;
    jsb_anysdk_framework_ProtocolAnalytics_class->convert = JS_ConvertStub;
    jsb_anysdk_framework_ProtocolAnalytics_class->finalize = js_anysdk_framework_ProtocolAnalytics_finalize;
    jsb_anysdk_framework_ProtocolAnalytics_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("isFunctionSupported", js_anysdk_framework_ProtocolAnalytics_isFunctionSupported, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("logTimedEventBegin", js_anysdk_framework_ProtocolAnalytics_logTimedEventBegin, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("logError", js_anysdk_framework_ProtocolAnalytics_logError, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setCaptureUncaughtException", js_anysdk_framework_ProtocolAnalytics_setCaptureUncaughtException, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setSessionContinueMillis", js_anysdk_framework_ProtocolAnalytics_setSessionContinueMillis, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("startSession", js_anysdk_framework_ProtocolAnalytics_startSession, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("stopSession", js_anysdk_framework_ProtocolAnalytics_stopSession, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("logTimedEventEnd", js_anysdk_framework_ProtocolAnalytics_logTimedEventEnd, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_anysdk_framework_ProtocolAnalytics_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_anysdk_framework_PluginProtocol_prototype),
        jsb_anysdk_framework_ProtocolAnalytics_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ProtocolAnalytics", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<anysdk::framework::ProtocolAnalytics> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_anysdk_framework_ProtocolAnalytics_class;
        p->proto = jsb_anysdk_framework_ProtocolAnalytics_prototype;
        p->parentProto = jsb_anysdk_framework_PluginProtocol_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_anysdk_framework_ProtocolIAP_class;
JSObject *jsb_anysdk_framework_ProtocolIAP_prototype;

bool js_anysdk_framework_ProtocolIAP_getPluginId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolIAP* cobj = (anysdk::framework::ProtocolIAP *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolIAP_getPluginId : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getPluginId();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolIAP_getPluginId : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_ProtocolIAP_getOrderId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolIAP* cobj = (anysdk::framework::ProtocolIAP *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolIAP_getOrderId : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getOrderId();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolIAP_getOrderId : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_ProtocolIAP_resetPayState(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        anysdk::framework::ProtocolIAP::resetPayState();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_anysdk_framework_ProtocolIAP_resetPayState : wrong number of arguments");
    return false;
}


extern JSObject *jsb_anysdk_framework_PluginProtocol_prototype;

void js_anysdk_framework_ProtocolIAP_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolIAP)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        anysdk::framework::ProtocolIAP *nobj = static_cast<anysdk::framework::ProtocolIAP *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_anysdk_framework_ProtocolIAP(JSContext *cx, JS::HandleObject global) {
    jsb_anysdk_framework_ProtocolIAP_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_anysdk_framework_ProtocolIAP_class->name = "ProtocolIAP";
    jsb_anysdk_framework_ProtocolIAP_class->addProperty = JS_PropertyStub;
    jsb_anysdk_framework_ProtocolIAP_class->delProperty = JS_DeletePropertyStub;
    jsb_anysdk_framework_ProtocolIAP_class->getProperty = JS_PropertyStub;
    jsb_anysdk_framework_ProtocolIAP_class->setProperty = JS_StrictPropertyStub;
    jsb_anysdk_framework_ProtocolIAP_class->enumerate = JS_EnumerateStub;
    jsb_anysdk_framework_ProtocolIAP_class->resolve = JS_ResolveStub;
    jsb_anysdk_framework_ProtocolIAP_class->convert = JS_ConvertStub;
    jsb_anysdk_framework_ProtocolIAP_class->finalize = js_anysdk_framework_ProtocolIAP_finalize;
    jsb_anysdk_framework_ProtocolIAP_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getPluginId", js_anysdk_framework_ProtocolIAP_getPluginId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getOrderId", js_anysdk_framework_ProtocolIAP_getOrderId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("resetPayState", js_anysdk_framework_ProtocolIAP_resetPayState, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_anysdk_framework_ProtocolIAP_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_anysdk_framework_PluginProtocol_prototype),
        jsb_anysdk_framework_ProtocolIAP_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ProtocolIAP", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<anysdk::framework::ProtocolIAP> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_anysdk_framework_ProtocolIAP_class;
        p->proto = jsb_anysdk_framework_ProtocolIAP_prototype;
        p->parentProto = jsb_anysdk_framework_PluginProtocol_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_anysdk_framework_ProtocolAds_class;
JSObject *jsb_anysdk_framework_ProtocolAds_prototype;

bool js_anysdk_framework_ProtocolAds_showAds(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolAds* cobj = (anysdk::framework::ProtocolAds *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolAds_showAds : Invalid Native Object");
    if (argc == 1) {
        anysdk::framework::AdsType arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_ProtocolAds_showAds : Error processing arguments");
        cobj->showAds(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        anysdk::framework::AdsType arg0;
        int arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_ProtocolAds_showAds : Error processing arguments");
        cobj->showAds(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolAds_showAds : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_anysdk_framework_ProtocolAds_hideAds(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolAds* cobj = (anysdk::framework::ProtocolAds *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolAds_hideAds : Invalid Native Object");
    if (argc == 1) {
        anysdk::framework::AdsType arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_ProtocolAds_hideAds : Error processing arguments");
        cobj->hideAds(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        anysdk::framework::AdsType arg0;
        int arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_ProtocolAds_hideAds : Error processing arguments");
        cobj->hideAds(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolAds_hideAds : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_anysdk_framework_ProtocolAds_queryPoints(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolAds* cobj = (anysdk::framework::ProtocolAds *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolAds_queryPoints : Invalid Native Object");
    if (argc == 0) {
        double ret = cobj->queryPoints();
        jsval jsret = JSVAL_NULL;
        jsret = DOUBLE_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolAds_queryPoints : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_ProtocolAds_isAdTypeSupported(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolAds* cobj = (anysdk::framework::ProtocolAds *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolAds_isAdTypeSupported : Invalid Native Object");
    if (argc == 1) {
        anysdk::framework::AdsType arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_ProtocolAds_isAdTypeSupported : Error processing arguments");
        bool ret = cobj->isAdTypeSupported(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolAds_isAdTypeSupported : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_anysdk_framework_ProtocolAds_preloadAds(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolAds* cobj = (anysdk::framework::ProtocolAds *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolAds_preloadAds : Invalid Native Object");
    if (argc == 1) {
        anysdk::framework::AdsType arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_ProtocolAds_preloadAds : Error processing arguments");
        cobj->preloadAds(arg0);
        args.rval().setUndefined();
        return true;
    }
    if (argc == 2) {
        anysdk::framework::AdsType arg0;
        int arg1;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        ok &= jsval_to_int32(cx, args.get(1), (int32_t *)&arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_ProtocolAds_preloadAds : Error processing arguments");
        cobj->preloadAds(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolAds_preloadAds : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_anysdk_framework_ProtocolAds_spendPoints(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolAds* cobj = (anysdk::framework::ProtocolAds *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolAds_spendPoints : Invalid Native Object");
    if (argc == 1) {
        int arg0;
        ok &= jsval_to_int32(cx, args.get(0), (int32_t *)&arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_ProtocolAds_spendPoints : Error processing arguments");
        cobj->spendPoints(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolAds_spendPoints : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

extern JSObject *jsb_anysdk_framework_PluginProtocol_prototype;

void js_anysdk_framework_ProtocolAds_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolAds)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        anysdk::framework::ProtocolAds *nobj = static_cast<anysdk::framework::ProtocolAds *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_anysdk_framework_ProtocolAds(JSContext *cx, JS::HandleObject global) {
    jsb_anysdk_framework_ProtocolAds_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_anysdk_framework_ProtocolAds_class->name = "ProtocolAds";
    jsb_anysdk_framework_ProtocolAds_class->addProperty = JS_PropertyStub;
    jsb_anysdk_framework_ProtocolAds_class->delProperty = JS_DeletePropertyStub;
    jsb_anysdk_framework_ProtocolAds_class->getProperty = JS_PropertyStub;
    jsb_anysdk_framework_ProtocolAds_class->setProperty = JS_StrictPropertyStub;
    jsb_anysdk_framework_ProtocolAds_class->enumerate = JS_EnumerateStub;
    jsb_anysdk_framework_ProtocolAds_class->resolve = JS_ResolveStub;
    jsb_anysdk_framework_ProtocolAds_class->convert = JS_ConvertStub;
    jsb_anysdk_framework_ProtocolAds_class->finalize = js_anysdk_framework_ProtocolAds_finalize;
    jsb_anysdk_framework_ProtocolAds_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("showAds", js_anysdk_framework_ProtocolAds_showAds, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("hideAds", js_anysdk_framework_ProtocolAds_hideAds, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("queryPoints", js_anysdk_framework_ProtocolAds_queryPoints, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isAdTypeSupported", js_anysdk_framework_ProtocolAds_isAdTypeSupported, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("preloadAds", js_anysdk_framework_ProtocolAds_preloadAds, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("spendPoints", js_anysdk_framework_ProtocolAds_spendPoints, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_anysdk_framework_ProtocolAds_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_anysdk_framework_PluginProtocol_prototype),
        jsb_anysdk_framework_ProtocolAds_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ProtocolAds", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<anysdk::framework::ProtocolAds> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_anysdk_framework_ProtocolAds_class;
        p->proto = jsb_anysdk_framework_ProtocolAds_prototype;
        p->parentProto = jsb_anysdk_framework_PluginProtocol_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_anysdk_framework_ProtocolSocial_class;
JSObject *jsb_anysdk_framework_ProtocolSocial_prototype;

bool js_anysdk_framework_ProtocolSocial_showLeaderboard(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolSocial* cobj = (anysdk::framework::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolSocial_showLeaderboard : Invalid Native Object");
    if (argc == 1) {
        const char* arg0;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_ProtocolSocial_showLeaderboard : Error processing arguments");
        cobj->showLeaderboard(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolSocial_showLeaderboard : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_anysdk_framework_ProtocolSocial_signOut(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolSocial* cobj = (anysdk::framework::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolSocial_signOut : Invalid Native Object");
    if (argc == 0) {
        cobj->signOut();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolSocial_signOut : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_ProtocolSocial_showAchievements(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolSocial* cobj = (anysdk::framework::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolSocial_showAchievements : Invalid Native Object");
    if (argc == 0) {
        cobj->showAchievements();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolSocial_showAchievements : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_ProtocolSocial_signIn(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolSocial* cobj = (anysdk::framework::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolSocial_signIn : Invalid Native Object");
    if (argc == 0) {
        cobj->signIn();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolSocial_signIn : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_ProtocolSocial_submitScore(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolSocial* cobj = (anysdk::framework::ProtocolSocial *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolSocial_submitScore : Invalid Native Object");
    if (argc == 2) {
        const char* arg0;
        long arg1;
        std::string arg0_tmp; ok &= jsval_to_std_string(cx, args.get(0), &arg0_tmp); arg0 = arg0_tmp.c_str();
        ok &= jsval_to_long(cx, args.get(1), &arg1);
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_ProtocolSocial_submitScore : Error processing arguments");
        cobj->submitScore(arg0, arg1);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolSocial_submitScore : wrong number of arguments: %d, was expecting %d", argc, 2);
    return false;
}

extern JSObject *jsb_anysdk_framework_PluginProtocol_prototype;

void js_anysdk_framework_ProtocolSocial_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolSocial)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        anysdk::framework::ProtocolSocial *nobj = static_cast<anysdk::framework::ProtocolSocial *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_anysdk_framework_ProtocolSocial(JSContext *cx, JS::HandleObject global) {
    jsb_anysdk_framework_ProtocolSocial_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_anysdk_framework_ProtocolSocial_class->name = "ProtocolSocial";
    jsb_anysdk_framework_ProtocolSocial_class->addProperty = JS_PropertyStub;
    jsb_anysdk_framework_ProtocolSocial_class->delProperty = JS_DeletePropertyStub;
    jsb_anysdk_framework_ProtocolSocial_class->getProperty = JS_PropertyStub;
    jsb_anysdk_framework_ProtocolSocial_class->setProperty = JS_StrictPropertyStub;
    jsb_anysdk_framework_ProtocolSocial_class->enumerate = JS_EnumerateStub;
    jsb_anysdk_framework_ProtocolSocial_class->resolve = JS_ResolveStub;
    jsb_anysdk_framework_ProtocolSocial_class->convert = JS_ConvertStub;
    jsb_anysdk_framework_ProtocolSocial_class->finalize = js_anysdk_framework_ProtocolSocial_finalize;
    jsb_anysdk_framework_ProtocolSocial_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("showLeaderboard", js_anysdk_framework_ProtocolSocial_showLeaderboard, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("signOut", js_anysdk_framework_ProtocolSocial_signOut, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("showAchievements", js_anysdk_framework_ProtocolSocial_showAchievements, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("signIn", js_anysdk_framework_ProtocolSocial_signIn, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("submitScore", js_anysdk_framework_ProtocolSocial_submitScore, 2, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_anysdk_framework_ProtocolSocial_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_anysdk_framework_PluginProtocol_prototype),
        jsb_anysdk_framework_ProtocolSocial_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ProtocolSocial", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<anysdk::framework::ProtocolSocial> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_anysdk_framework_ProtocolSocial_class;
        p->proto = jsb_anysdk_framework_ProtocolSocial_prototype;
        p->parentProto = jsb_anysdk_framework_PluginProtocol_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_anysdk_framework_ProtocolUser_class;
JSObject *jsb_anysdk_framework_ProtocolUser_prototype;

bool js_anysdk_framework_ProtocolUser_isFunctionSupported(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolUser* cobj = (anysdk::framework::ProtocolUser *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolUser_isFunctionSupported : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_ProtocolUser_isFunctionSupported : Error processing arguments");
        bool ret = cobj->isFunctionSupported(arg0);
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolUser_isFunctionSupported : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_anysdk_framework_ProtocolUser_isLogined(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolUser* cobj = (anysdk::framework::ProtocolUser *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolUser_isLogined : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isLogined();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolUser_isLogined : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_ProtocolUser_getUserID(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolUser* cobj = (anysdk::framework::ProtocolUser *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolUser_getUserID : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getUserID();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolUser_getUserID : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_ProtocolUser_login(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;

    JS::RootedObject obj(cx);
    anysdk::framework::ProtocolUser* cobj = NULL;
    obj = args.thisv().toObjectOrNull();
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    cobj = (anysdk::framework::ProtocolUser *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolUser_login : Invalid Native Object");
    do {
        if (argc == 1) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            cobj->login(arg0);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 2) {
            std::string arg0;
            ok &= jsval_to_std_string(cx, args.get(0), &arg0);
            if (!ok) { ok = true; break; }
            std::string arg1;
            ok &= jsval_to_std_string(cx, args.get(1), &arg1);
            if (!ok) { ok = true; break; }
            cobj->login(arg0, arg1);
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    do {
        if (argc == 0) {
            cobj->login();
            args.rval().setUndefined();
            return true;
        }
    } while(0);

    JS_ReportError(cx, "js_anysdk_framework_ProtocolUser_login : wrong number of arguments");
    return false;
}
bool js_anysdk_framework_ProtocolUser_getPluginId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolUser* cobj = (anysdk::framework::ProtocolUser *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolUser_getPluginId : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getPluginId();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolUser_getPluginId : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}

extern JSObject *jsb_anysdk_framework_PluginProtocol_prototype;

void js_anysdk_framework_ProtocolUser_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolUser)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        anysdk::framework::ProtocolUser *nobj = static_cast<anysdk::framework::ProtocolUser *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_anysdk_framework_ProtocolUser(JSContext *cx, JS::HandleObject global) {
    jsb_anysdk_framework_ProtocolUser_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_anysdk_framework_ProtocolUser_class->name = "ProtocolUser";
    jsb_anysdk_framework_ProtocolUser_class->addProperty = JS_PropertyStub;
    jsb_anysdk_framework_ProtocolUser_class->delProperty = JS_DeletePropertyStub;
    jsb_anysdk_framework_ProtocolUser_class->getProperty = JS_PropertyStub;
    jsb_anysdk_framework_ProtocolUser_class->setProperty = JS_StrictPropertyStub;
    jsb_anysdk_framework_ProtocolUser_class->enumerate = JS_EnumerateStub;
    jsb_anysdk_framework_ProtocolUser_class->resolve = JS_ResolveStub;
    jsb_anysdk_framework_ProtocolUser_class->convert = JS_ConvertStub;
    jsb_anysdk_framework_ProtocolUser_class->finalize = js_anysdk_framework_ProtocolUser_finalize;
    jsb_anysdk_framework_ProtocolUser_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("isFunctionSupported", js_anysdk_framework_ProtocolUser_isFunctionSupported, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isLogined", js_anysdk_framework_ProtocolUser_isLogined, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUserID", js_anysdk_framework_ProtocolUser_getUserID, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("login", js_anysdk_framework_ProtocolUser_login, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPluginId", js_anysdk_framework_ProtocolUser_getPluginId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_anysdk_framework_ProtocolUser_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_anysdk_framework_PluginProtocol_prototype),
        jsb_anysdk_framework_ProtocolUser_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ProtocolUser", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<anysdk::framework::ProtocolUser> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_anysdk_framework_ProtocolUser_class;
        p->proto = jsb_anysdk_framework_ProtocolUser_prototype;
        p->parentProto = jsb_anysdk_framework_PluginProtocol_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_anysdk_framework_ProtocolPush_class;
JSObject *jsb_anysdk_framework_ProtocolPush_prototype;

bool js_anysdk_framework_ProtocolPush_startPush(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolPush* cobj = (anysdk::framework::ProtocolPush *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolPush_startPush : Invalid Native Object");
    if (argc == 0) {
        cobj->startPush();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolPush_startPush : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_ProtocolPush_closePush(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolPush* cobj = (anysdk::framework::ProtocolPush *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolPush_closePush : Invalid Native Object");
    if (argc == 0) {
        cobj->closePush();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolPush_closePush : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_ProtocolPush_delAlias(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolPush* cobj = (anysdk::framework::ProtocolPush *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolPush_delAlias : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_ProtocolPush_delAlias : Error processing arguments");
        cobj->delAlias(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolPush_delAlias : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_anysdk_framework_ProtocolPush_setAlias(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::ProtocolPush* cobj = (anysdk::framework::ProtocolPush *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_ProtocolPush_setAlias : Invalid Native Object");
    if (argc == 1) {
        std::string arg0;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_ProtocolPush_setAlias : Error processing arguments");
        cobj->setAlias(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_ProtocolPush_setAlias : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}

extern JSObject *jsb_anysdk_framework_PluginProtocol_prototype;

void js_anysdk_framework_ProtocolPush_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolPush)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        anysdk::framework::ProtocolPush *nobj = static_cast<anysdk::framework::ProtocolPush *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_anysdk_framework_ProtocolPush(JSContext *cx, JS::HandleObject global) {
    jsb_anysdk_framework_ProtocolPush_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_anysdk_framework_ProtocolPush_class->name = "ProtocolPush";
    jsb_anysdk_framework_ProtocolPush_class->addProperty = JS_PropertyStub;
    jsb_anysdk_framework_ProtocolPush_class->delProperty = JS_DeletePropertyStub;
    jsb_anysdk_framework_ProtocolPush_class->getProperty = JS_PropertyStub;
    jsb_anysdk_framework_ProtocolPush_class->setProperty = JS_StrictPropertyStub;
    jsb_anysdk_framework_ProtocolPush_class->enumerate = JS_EnumerateStub;
    jsb_anysdk_framework_ProtocolPush_class->resolve = JS_ResolveStub;
    jsb_anysdk_framework_ProtocolPush_class->convert = JS_ConvertStub;
    jsb_anysdk_framework_ProtocolPush_class->finalize = js_anysdk_framework_ProtocolPush_finalize;
    jsb_anysdk_framework_ProtocolPush_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("startPush", js_anysdk_framework_ProtocolPush_startPush, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("closePush", js_anysdk_framework_ProtocolPush_closePush, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("delAlias", js_anysdk_framework_ProtocolPush_delAlias, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setAlias", js_anysdk_framework_ProtocolPush_setAlias, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    JSFunctionSpec *st_funcs = NULL;

    jsb_anysdk_framework_ProtocolPush_prototype = JS_InitClass(
        cx, global,
        JS::RootedObject(cx, jsb_anysdk_framework_PluginProtocol_prototype),
        jsb_anysdk_framework_ProtocolPush_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "ProtocolPush", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<anysdk::framework::ProtocolPush> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_anysdk_framework_ProtocolPush_class;
        p->proto = jsb_anysdk_framework_ProtocolPush_prototype;
        p->parentProto = jsb_anysdk_framework_PluginProtocol_prototype;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

JSClass  *jsb_anysdk_framework_AgentManager_class;
JSObject *jsb_anysdk_framework_AgentManager_prototype;

bool js_anysdk_framework_AgentManager_getSocialPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_AgentManager_getSocialPlugin : Invalid Native Object");
    if (argc == 0) {
        anysdk::framework::ProtocolSocial* ret = cobj->getSocialPlugin();
        jsval jsret = JSVAL_NULL;
        do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::ProtocolSocial>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_AgentManager_getSocialPlugin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_AgentManager_unloadAllPlugins(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_AgentManager_unloadAllPlugins : Invalid Native Object");
    if (argc == 0) {
        cobj->unloadAllPlugins();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_AgentManager_unloadAllPlugins : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_AgentManager_loadAllPlugins(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_AgentManager_loadAllPlugins : Invalid Native Object");
    if (argc == 0) {
        cobj->loadAllPlugins();
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_AgentManager_loadAllPlugins : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_AgentManager_getCustomParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_AgentManager_getCustomParam : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getCustomParam();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_AgentManager_getCustomParam : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_AgentManager_setIsAnaylticsEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_AgentManager_setIsAnaylticsEnabled : Invalid Native Object");
    if (argc == 1) {
        bool arg0;
        arg0 = JS::ToBoolean(args.get(0));
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_AgentManager_setIsAnaylticsEnabled : Error processing arguments");
        cobj->setIsAnaylticsEnabled(arg0);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_AgentManager_setIsAnaylticsEnabled : wrong number of arguments: %d, was expecting %d", argc, 1);
    return false;
}
bool js_anysdk_framework_AgentManager_getUserPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_AgentManager_getUserPlugin : Invalid Native Object");
    if (argc == 0) {
        anysdk::framework::ProtocolUser* ret = cobj->getUserPlugin();
        jsval jsret = JSVAL_NULL;
        do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::ProtocolUser>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_AgentManager_getUserPlugin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_AgentManager_init(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    bool ok = true;
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_AgentManager_init : Invalid Native Object");
    if (argc == 4) {
        std::string arg0;
        std::string arg1;
        std::string arg2;
        std::string arg3;
        ok &= jsval_to_std_string(cx, args.get(0), &arg0);
        ok &= jsval_to_std_string(cx, args.get(1), &arg1);
        ok &= jsval_to_std_string(cx, args.get(2), &arg2);
        ok &= jsval_to_std_string(cx, args.get(3), &arg3);
        JSB_PRECONDITION2(ok, cx, false, "js_anysdk_framework_AgentManager_init : Error processing arguments");
        cobj->init(arg0, arg1, arg2, arg3);
        args.rval().setUndefined();
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_AgentManager_init : wrong number of arguments: %d, was expecting %d", argc, 4);
    return false;
}
bool js_anysdk_framework_AgentManager_isAnaylticsEnabled(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_AgentManager_isAnaylticsEnabled : Invalid Native Object");
    if (argc == 0) {
        bool ret = cobj->isAnaylticsEnabled();
        jsval jsret = JSVAL_NULL;
        jsret = BOOLEAN_TO_JSVAL(ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_AgentManager_isAnaylticsEnabled : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_AgentManager_getAdsPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_AgentManager_getAdsPlugin : Invalid Native Object");
    if (argc == 0) {
        anysdk::framework::ProtocolAds* ret = cobj->getAdsPlugin();
        jsval jsret = JSVAL_NULL;
        do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::ProtocolAds>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_AgentManager_getAdsPlugin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_AgentManager_getPushPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_AgentManager_getPushPlugin : Invalid Native Object");
    if (argc == 0) {
        anysdk::framework::ProtocolPush* ret = cobj->getPushPlugin();
        jsval jsret = JSVAL_NULL;
        do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::ProtocolPush>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_AgentManager_getPushPlugin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_AgentManager_getSharePlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_AgentManager_getSharePlugin : Invalid Native Object");
    if (argc == 0) {
        anysdk::framework::ProtocolShare* ret = cobj->getSharePlugin();
        jsval jsret = JSVAL_NULL;
        do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::ProtocolShare>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_AgentManager_getSharePlugin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_AgentManager_getAnalyticsPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_AgentManager_getAnalyticsPlugin : Invalid Native Object");
    if (argc == 0) {
        anysdk::framework::ProtocolAnalytics* ret = cobj->getAnalyticsPlugin();
        jsval jsret = JSVAL_NULL;
        do {
			if (ret) {
				js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::ProtocolAnalytics>(cx, ret);
				jsret = OBJECT_TO_JSVAL(proxy->obj);
			} else {
				jsret = JSVAL_NULL;
			}
		} while (0);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_AgentManager_getAnalyticsPlugin : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_AgentManager_getChannelId(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    JS::RootedObject obj(cx, args.thisv().toObjectOrNull());
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    anysdk::framework::AgentManager* cobj = (anysdk::framework::AgentManager *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "js_anysdk_framework_AgentManager_getChannelId : Invalid Native Object");
    if (argc == 0) {
        std::string ret = cobj->getChannelId();
        jsval jsret = JSVAL_NULL;
        jsret = std_string_to_jsval(cx, ret);
        args.rval().set(jsret);
        return true;
    }

    JS_ReportError(cx, "js_anysdk_framework_AgentManager_getChannelId : wrong number of arguments: %d, was expecting %d", argc, 0);
    return false;
}
bool js_anysdk_framework_AgentManager_end(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        anysdk::framework::AgentManager::end();
        args.rval().setUndefined();
        return true;
    }
    JS_ReportError(cx, "js_anysdk_framework_AgentManager_end : wrong number of arguments");
    return false;
}

bool js_anysdk_framework_AgentManager_getInstance(JSContext *cx, uint32_t argc, jsval *vp)
{
    JS::CallArgs args = JS::CallArgsFromVp(argc, vp);
    if (argc == 0) {
        anysdk::framework::AgentManager* ret = anysdk::framework::AgentManager::getInstance();
        jsval jsret = JSVAL_NULL;
        do {
		if (ret) {
			js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::AgentManager>(cx, ret);
			jsret = OBJECT_TO_JSVAL(proxy->obj);
		} else {
			jsret = JSVAL_NULL;
		}
	} while (0);
        args.rval().set(jsret);
        return true;
    }
    JS_ReportError(cx, "js_anysdk_framework_AgentManager_getInstance : wrong number of arguments");
    return false;
}



void js_anysdk_framework_AgentManager_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (AgentManager)", obj);
    js_proxy_t* nproxy;
    js_proxy_t* jsproxy;
    jsproxy = jsb_get_js_proxy(obj);
    if (jsproxy) {
        nproxy = jsb_get_native_proxy(jsproxy->ptr);

        anysdk::framework::AgentManager *nobj = static_cast<anysdk::framework::AgentManager *>(nproxy->ptr);
        if (nobj)
            delete nobj;
        
        jsb_remove_proxy(nproxy, jsproxy);
    }
}

void js_register_anysdk_framework_AgentManager(JSContext *cx, JS::HandleObject global) {
    jsb_anysdk_framework_AgentManager_class = (JSClass *)calloc(1, sizeof(JSClass));
    jsb_anysdk_framework_AgentManager_class->name = "AgentManager";
    jsb_anysdk_framework_AgentManager_class->addProperty = JS_PropertyStub;
    jsb_anysdk_framework_AgentManager_class->delProperty = JS_DeletePropertyStub;
    jsb_anysdk_framework_AgentManager_class->getProperty = JS_PropertyStub;
    jsb_anysdk_framework_AgentManager_class->setProperty = JS_StrictPropertyStub;
    jsb_anysdk_framework_AgentManager_class->enumerate = JS_EnumerateStub;
    jsb_anysdk_framework_AgentManager_class->resolve = JS_ResolveStub;
    jsb_anysdk_framework_AgentManager_class->convert = JS_ConvertStub;
    jsb_anysdk_framework_AgentManager_class->finalize = js_anysdk_framework_AgentManager_finalize;
    jsb_anysdk_framework_AgentManager_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

    static JSPropertySpec properties[] = {
        JS_PSG("__nativeObj", js_is_native_obj, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_PS_END
    };

    static JSFunctionSpec funcs[] = {
        JS_FN("getSocialPlugin", js_anysdk_framework_AgentManager_getSocialPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("unloadAllPlugins", js_anysdk_framework_AgentManager_unloadAllPlugins, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("loadAllPlugins", js_anysdk_framework_AgentManager_loadAllPlugins, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getCustomParam", js_anysdk_framework_AgentManager_getCustomParam, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setIsAnaylticsEnabled", js_anysdk_framework_AgentManager_setIsAnaylticsEnabled, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getUserPlugin", js_anysdk_framework_AgentManager_getUserPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("init", js_anysdk_framework_AgentManager_init, 4, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("isAnaylticsEnabled", js_anysdk_framework_AgentManager_isAnaylticsEnabled, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAdsPlugin", js_anysdk_framework_AgentManager_getAdsPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getPushPlugin", js_anysdk_framework_AgentManager_getPushPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getSharePlugin", js_anysdk_framework_AgentManager_getSharePlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getAnalyticsPlugin", js_anysdk_framework_AgentManager_getAnalyticsPlugin, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getChannelId", js_anysdk_framework_AgentManager_getChannelId, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    static JSFunctionSpec st_funcs[] = {
        JS_FN("end", js_anysdk_framework_AgentManager_end, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("getInstance", js_anysdk_framework_AgentManager_getInstance, 0, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
    };

    jsb_anysdk_framework_AgentManager_prototype = JS_InitClass(
        cx, global,
        JS::NullPtr(), // parent proto
        jsb_anysdk_framework_AgentManager_class,
        empty_constructor, 0,
        properties,
        funcs,
        NULL, // no static properties
        st_funcs);
    // make the class enumerable in the registered namespace
//  bool found;
//FIXME: Removed in Firefox v27 
//  JS_SetPropertyAttributes(cx, global, "AgentManager", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

    // add the proto and JSClass to the type->js info hash table
    TypeTest<anysdk::framework::AgentManager> t;
    js_type_class_t *p;
    std::string typeName = t.s_name();
    if (_js_global_type_map.find(typeName) == _js_global_type_map.end())
    {
        p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
        p->jsclass = jsb_anysdk_framework_AgentManager_class;
        p->proto = jsb_anysdk_framework_AgentManager_prototype;
        p->parentProto = NULL;
        _js_global_type_map.insert(std::make_pair(typeName, p));
    }
}

void register_all_anysdk_framework(JSContext* cx, JS::HandleObject obj) {
    // Get the ns
    JS::RootedObject ns(cx);
    get_or_create_js_obj(cx, obj, "anysdk", &ns);

    js_register_anysdk_framework_PluginProtocol(cx, ns);
    js_register_anysdk_framework_ProtocolUser(cx, ns);
    js_register_anysdk_framework_PluginFactory(cx, ns);
    js_register_anysdk_framework_ProtocolIAP(cx, ns);
    js_register_anysdk_framework_AgentManager(cx, ns);
    js_register_anysdk_framework_ProtocolSocial(cx, ns);
    js_register_anysdk_framework_ProtocolAnalytics(cx, ns);
    js_register_anysdk_framework_ProtocolAds(cx, ns);
    js_register_anysdk_framework_PluginManager(cx, ns);
    js_register_anysdk_framework_ProtocolPush(cx, ns);
}

