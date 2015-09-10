#include "jsb_anysdk_manual.hpp"
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
#include "cocos2d.h"

USING_NS_CC;
using namespace anysdk::framework;


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
	CCLog("222");
	return JS_TRUE;
}

static JSBool empty_constructor(JSContext *cx, uint32_t argc, jsval *vp) {
	return JS_TRUE;
}

JSClass  *jsb_ProtocolShare_class;
JSObject *jsb_ProtocolShare_prototype;

JSBool js_anysdk_ProtocolShare_share(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLog("in function share.");
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	anysdk::framework::ProtocolShare* cobj = (anysdk::framework::ProtocolShare *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc != 1) {
		JS_ReportError(cx, "jsb_anysdk_ProtocolShare_share : wrong number of arguments: %d, was expecting %d", argc, 0);
		return JS_FALSE;
	}
	CCLog("will share");
	jsval *argv = JS_ARGV(cx, vp);
    jsval arg0 = argv[0];
	if ( arg0.isObject() ){
		JSObject* tmp = JSVAL_TO_OBJECT(arg0);
	    if (!tmp) {
	        CCLOG("%s", "jsval_to_ccvaluemap: the jsval is not an object.");
	        return false;
	    }
	    
	    JSObject* it = JS_NewPropertyIterator(cx, tmp);

	    TShareInfo arg;
	    
	    while (true)
	    {
	        jsid idp;
	        jsval key;
	        if (! JS_NextProperty(cx, it, &idp) || ! JS_IdToValue(cx, idp, &key)) {
	            return false; // error
	        }
	        
	        if (key == JSVAL_VOID) {
	            break; // end of iteration
	        }
	        
	        if (!JSVAL_IS_STRING(key)) {
	            continue; // ignore integer properties
	        }
	        
	        JSStringWrapper keyWrapper(JSVAL_TO_STRING(key), cx);

			std::string v1;
			std::string v2;

	        v1 = keyWrapper.get();
	        jsval value;
        	JS_GetPropertyById(cx, tmp, idp, &value);
	        if (value.isString())
	        {
	            bool ok = jsval_to_std_string(cx, value, &v2);
	            if (ok){
	            	CCLog("key:%s, value: %s.",v1.c_str(), v2.c_str());
	        		arg.insert( std::map<std::string,std::string>::value_type(v1, v2) );
	            }
	            else{
	            	CCLog("wrong param in stringmap.\n");
	            }
	        }
	    }
	    cobj->share( arg );
	}
	return JS_TRUE;
}

class ProtocolShareActionListener : public ShareResultListener
{
public:
    ProtocolShareActionListener():m_bNeedUnroot(false), _jsCallback(JSVAL_VOID), _jsThisObj(JSVAL_VOID)
    {
    }
    ~ProtocolShareActionListener()
    {
    	CCLOG("on share action result ~listener");
    }

    virtual void onShareResult(ShareResultCode ret, const char* msg)
    {
        CCLOG("on share action result: %d, msg: %s.", ret, msg);
    	JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    	JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);

	    jsval retval;
	    if (_jsCallback != JSVAL_VOID)
	    {
	        jsval resultCode = INT_TO_JSVAL(ret);
	        // JSString* jsstr = JS_NewStringCopyZ(cx, msg);

	        jsval valArr[2];
	        valArr[0] = resultCode;
	        valArr[1] = std_string_to_jsval(cx, msg);

	        JS_AddValueRoot(cx, valArr);
	        JS_CallFunctionValue(cx, thisObj, _jsCallback, 2, valArr, &retval);
	        JS_RemoveValueRoot(cx, valArr);
	    }
    }

    void setJSCallbackThis(jsval jsThisObj)
    {
        _jsThisObj = jsThisObj;
        
        JSObject *thisObj = JSVAL_TO_OBJECT(jsThisObj);
	    js_proxy *p = jsb_get_js_proxy(thisObj);
	    if (!p)
	    {
	        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
	        m_bNeedUnroot = true;
	        m_bNeedUnroot &= JS_AddValueRoot(cx, &jsThisObj);
	    }
    }
    void setJSCallbackFunc(jsval func) {
    	_jsCallback = func;
    	JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
		// Root the callback function.
    	JS_AddNamedValueRoot(cx, &_jsCallback, "JSCallbackWrapper_callback_func");
	}

    static ProtocolShareActionListener* _instance;
    static ProtocolShareActionListener* getInstance(){
        if (_instance == NULL){
            _instance = new ProtocolShareActionListener();
        }
        return _instance;
    }
    static void purge(){
        if (_instance)
        {
            delete _instance;
            _instance = NULL;
        }
    }
private:
    jsval _jsCallback;
    jsval _jsThisObj;
    bool m_bNeedUnroot;
};
ProtocolShareActionListener* ProtocolShareActionListener::_instance = NULL;

JSBool js_anysdk_framework_ProtocolShare_setResultListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolUser_setActionListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolShare* cobj = (ProtocolShare *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 2)
    {
		JS_ReportError(cx, "jsb_anysdk_framework_ProtocolUser_setActionListener : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return false;
    }
	jsval *argv = JS_ARGV(cx, vp);
    ProtocolShareActionListener* listener = ProtocolShareActionListener::getInstance();
    listener->setJSCallbackFunc( argv[0] );
    listener->setJSCallbackThis( argv[1] );
    cobj->setResultListener(listener);
	return true;
}
JSBool jsb_anysdk_framework_ProtocolShare_removeListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolShare_removeListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolShare* cobj = (ProtocolShare *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (ProtocolShareActionListener::_instance != NULL)
    {
        ProtocolShareActionListener::purge();
    }
    if(argc != 0)
    	CCLOG("ProtocolShare_removeListener has wrong number of arguments.");
	return true;
}

JSBool jsb_anysdk_framework_ProtocolShare_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("\n**********\n setDebugMode was deprecated.\n**********");
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ProtocolShare* cobj = (ProtocolShare *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setDebugMode(arg0);
		CCLOG("ProtocolShare setDebugMode");
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

extern JSObject *jsb_PluginProtocol_prototype;

void js_anysdk_ProtocolShare_finalize(JSFreeOp *fop, JSObject *obj) {
    CCLOGINFO("jsbindings: finalizing JS object %p (ProtocolShare)", obj);
}
void js_register_anysdk_ProtocolShare(JSContext *cx, JSObject *global) {
	jsb_ProtocolShare_class = (JSClass *)calloc(1, sizeof(JSClass));
	jsb_ProtocolShare_class->name = "ProtocolShare";
	jsb_ProtocolShare_class->addProperty = JS_PropertyStub;
	jsb_ProtocolShare_class->delProperty = JS_PropertyStub;
	jsb_ProtocolShare_class->getProperty = JS_PropertyStub;
	jsb_ProtocolShare_class->setProperty = JS_StrictPropertyStub;
	jsb_ProtocolShare_class->enumerate = JS_EnumerateStub;
	jsb_ProtocolShare_class->resolve = JS_ResolveStub;
	jsb_ProtocolShare_class->convert = JS_ConvertStub;
	jsb_ProtocolShare_class->finalize = js_anysdk_ProtocolShare_finalize;
	jsb_ProtocolShare_class->flags = JSCLASS_HAS_RESERVED_SLOTS(2);

	JSPropertySpec *properties = NULL;

	static JSFunctionSpec funcs[] = {
		JS_FN("share", js_anysdk_ProtocolShare_share, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("setResultListener", js_anysdk_framework_ProtocolShare_setResultListener, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
		JS_FN("removeListener", jsb_anysdk_framework_ProtocolShare_removeListener, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FN("setDebugMode", jsb_anysdk_framework_ProtocolShare_setDebugMode, 1, JSPROP_PERMANENT | JSPROP_ENUMERATE),
        JS_FS_END
	};

	JSFunctionSpec *st_funcs = NULL;

	jsb_ProtocolShare_prototype = JS_InitClass(
		cx, global,
		jsb_PluginProtocol_prototype,
		jsb_ProtocolShare_class,
		empty_constructor, 0,
		properties,
		funcs,
		NULL, // no static properties
		st_funcs);
	// make the class enumerable in the registered namespace
	JSBool found;
	JS_SetPropertyAttributes(cx, global, "ProtocolShare", JSPROP_ENUMERATE | JSPROP_READONLY, &found);

	// add the proto and JSClass to the type->js info hash table
	TypeTest<anysdk::framework::ProtocolShare> t;
	js_type_class_t *p;
	uint32_t typeId = t.s_id();
	HASH_FIND_INT(_js_global_type_ht, &typeId, p);
	if (!p) {
		p = (js_type_class_t *)malloc(sizeof(js_type_class_t));
		p->type = typeId;
		p->jsclass = jsb_ProtocolShare_class;
		p->proto = jsb_ProtocolShare_prototype;
		p->parentProto = jsb_PluginProtocol_prototype;
		HASH_ADD_INT(_js_global_type_ht, type, p);
	}
}

class ProtocolPushActionListener : public PushActionListener
{
public:
    ProtocolPushActionListener():m_bNeedUnroot(false), _jsCallback(JSVAL_VOID), _jsThisObj(JSVAL_VOID)
    {
    }
    ~ProtocolPushActionListener()
    {
    	CCLOG("on Push result ~listener");
    }

    virtual void onActionResult(ProtocolPush* pPlugin, PushActionResultCode code, const char* msg)
    {
        CCLOG("on push result: %d, msg: %s.", code, msg);
    	JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    	JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);

		js_proxy_t *proxy = js_get_or_create_proxy(cx, pPlugin);
	    jsval retval;
	    if (_jsCallback != JSVAL_VOID)
	    {
	        jsval resultCode = INT_TO_JSVAL(code);
	        // JSString* jsstr = JS_NewStringCopyZ(cx, msg);

	        jsval valArr[3];
	        valArr[0] = OBJECT_TO_JSVAL(proxy->obj);
	        valArr[1] = resultCode;
	        valArr[2] = std_string_to_jsval(cx, msg);

	        JS_AddValueRoot(cx, valArr);
	        JS_CallFunctionValue(cx, thisObj, _jsCallback, 3, valArr, &retval);
	        JS_RemoveValueRoot(cx, valArr);
	    }
    }

    void setJSCallbackThis(jsval jsThisObj)
    {
        _jsThisObj = jsThisObj;
        
        JSObject *thisObj = JSVAL_TO_OBJECT(jsThisObj);
	    js_proxy *p = jsb_get_js_proxy(thisObj);
	    if (!p)
	    {
	        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
	        m_bNeedUnroot = true;
	        m_bNeedUnroot &= JS_AddValueRoot(cx, &jsThisObj);
	    }
    }
    void setJSCallbackFunc(jsval func) {
    	_jsCallback = func;
    	JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
		// Root the callback function.
    	JS_AddNamedValueRoot(cx, &_jsCallback, "JSCallbackWrapper_callback_func");
	}

    static ProtocolPushActionListener* _instance;
    static ProtocolPushActionListener* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new ProtocolPushActionListener();
        }
        return _instance;
    }
    static void purge()
    {
        if (_instance != NULL)
        {
            delete _instance;
            _instance = NULL;
        }
    }
private:
    jsval _jsCallback;
    jsval _jsThisObj;
    bool m_bNeedUnroot;
};
ProtocolPushActionListener* ProtocolPushActionListener::_instance = NULL;

JSBool jsb_anysdk_framework_ProtocolPush_setActionListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolPush_setActionListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolPush* cobj = (ProtocolPush *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 2)
    {
		JS_ReportError(cx, "jsb_anysdk_framework_ProtocolPush_setActionListener : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return false;
    }
	jsval *argv = JS_ARGV(cx, vp);
    ProtocolPushActionListener* listener = ProtocolPushActionListener::getInstance();
    listener->setJSCallbackFunc( argv[0] );
    listener->setJSCallbackThis( argv[1] );
    cobj->setActionListener(listener);
	return true;
}

JSBool jsb_anysdk_framework_ProtocolPush_removeListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolPush_removeListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolPush* cobj = (ProtocolPush *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (ProtocolPushActionListener::_instance != NULL)
    {
        ProtocolPushActionListener::purge();
    }
    if(argc != 0)
    	CCLOG("ProtocolPush_removeListener has wrong number of arguments.");
	return true;
}

JSBool jsb_anysdk_framework_ProtocolPush_setTags(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolPush_setActionListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolPush* cobj = (ProtocolPush *)(proxy ? proxy->ptr : NULL);
    if (argc != 1)
    {
		JS_ReportError(cx, "jsb_anysdk_framework_ProtocolPush_setTags : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return true;
    }
    jsval *argv = JS_ARGV(cx, vp);
    jsval arg0 = argv[0];
	if ( arg0.isObject() ){
	    list<std::string> arg;

	    JSObject *jsobj;
	    JSBool ok = JS_ValueToObject( cx, arg0, &jsobj );
	    JSB_PRECONDITION3( ok, cx, JS_FALSE, "Error converting value to object");
	    JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj), cx, JS_FALSE, "Object must be an array");

	    uint32_t len;
	    JS_GetArrayLength(cx, jsobj, &len);
	    
	    for( uint32_t i=0; i< len;i++ ) {
	        jsval valarg;
	        JS_GetElement(cx, jsobj, i, &valarg);

	        if( valarg.isString() )
	        {
	        	CCLOG("value is string");
	        	std::string key;
	        	bool ok = jsval_to_std_string(cx, valarg, &key);
	        	if (ok)
	        	{
	        		CCLOG("key: %s.", key.c_str());
	        		arg.push_back( key );
	        	}
	        }
	    }
	    cobj->setTags(arg);
	}
	return true;
}

JSBool jsb_anysdk_framework_ProtocolPush_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp)
{
     CCLOG("\n********** \nsetDebugMode was deprecated.\n**********");
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ProtocolPush* cobj = (ProtocolPush *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setDebugMode(arg0);
		CCLOG("ProtocolPush setDebugMode");
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool jsb_anysdk_framework_ProtocolPush_delTags(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolPush_setActionListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolPush* cobj = (ProtocolPush *)(proxy ? proxy->ptr : NULL);
    if (argc != 1)
    {
		JS_ReportError(cx, "jsb_anysdk_framework_ProtocolPush_delTags : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return true;
    }
    jsval *argv = JS_ARGV(cx, vp);
    jsval arg0 = argv[0];
	if ( arg0.isObject() ){
	    list<std::string> arg;

	    JSObject *jsobj;
	    JSBool ok = JS_ValueToObject( cx, arg0, &jsobj );
	    JSB_PRECONDITION3( ok, cx, JS_FALSE, "Error converting value to object");
	    JSB_PRECONDITION3( jsobj && JS_IsArrayObject( cx, jsobj), cx, JS_FALSE, "Object must be an array");

	    uint32_t len;
	    JS_GetArrayLength(cx, jsobj, &len);
	    
	    for( uint32_t i=0; i< len;i++ ) {
	        jsval valarg;
	        JS_GetElement(cx, jsobj, i, &valarg);

	        if( valarg.isString() )
	        {
	        	CCLOG("value is string;");
	        	std::string key;
	        	bool ok = jsval_to_std_string(cx, valarg, &key);
	        	if (ok)
	        	{
	        		CCLOG("key: %s.", key.c_str());
	        		arg.push_back( key );
	        	}
	        }
	    }
	    cobj->delTags(arg);
	}
	return true;
}

class ProtocolSocialListener : public SocialListener
{
public:
    ProtocolSocialListener():m_bNeedUnroot(false), _jsCallback(JSVAL_VOID), _jsThisObj(JSVAL_VOID)
    {
    }
    ~ProtocolSocialListener()
    {
    	CCLOG("on social result ~listener");
    }

    virtual void onSocialResult(SocialRetCode code, const char* msg)
    {
        CCLOG("on action result: %d, msg: %s.", code, msg);
    	JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    	JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);

	    jsval retval;
	    if (_jsCallback != JSVAL_VOID)
	    {
	        jsval resultCode = INT_TO_JSVAL(code);
	        // JSString* jsstr = JS_NewStringCopyZ(cx, msg);

	        jsval valArr[2];
	        valArr[0] = resultCode;
	        valArr[1] = std_string_to_jsval(cx, msg);

	        JS_AddValueRoot(cx, valArr);
	        JS_CallFunctionValue(cx, thisObj, _jsCallback, 2, valArr, &retval);
	        JS_RemoveValueRoot(cx, valArr);
	    }
    }

    void setJSCallbackThis(jsval jsThisObj)
    {
        _jsThisObj = jsThisObj;
        
        JSObject *thisObj = JSVAL_TO_OBJECT(jsThisObj);
	    js_proxy *p = jsb_get_js_proxy(thisObj);
	    if (!p)
	    {
	        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
	        m_bNeedUnroot = true;
	        m_bNeedUnroot &= JS_AddValueRoot(cx, &jsThisObj);
	    }
    }
    void setJSCallbackFunc(jsval func) {
    	_jsCallback = func;
    	JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
		// Root the callback function.
    	JS_AddNamedValueRoot(cx, &_jsCallback, "JSCallbackWrapper_callback_func");
	}

    static ProtocolSocialListener* _instance;
    static ProtocolSocialListener* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new ProtocolSocialListener();
        }
        return _instance;
    }
    static void purge()
    {
        if (_instance != NULL)
        {
            delete _instance;
            _instance = NULL;
        }
    }
private:
    jsval _jsCallback;
    jsval _jsThisObj;
    bool m_bNeedUnroot;
};
ProtocolSocialListener* ProtocolSocialListener::_instance = NULL;

JSBool jsb_anysdk_framework_ProtocolSocial_setListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolSocial_setListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolSocial* cobj = (ProtocolSocial *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 2)
    {
		JS_ReportError(cx, "jsb_anysdk_framework_ProtocolSocial_setListener : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return false;
    }
	jsval *argv = JS_ARGV(cx, vp);
    ProtocolSocialListener* listener = ProtocolSocialListener::getInstance();
    listener->setJSCallbackFunc( argv[0] );
    listener->setJSCallbackThis( argv[1] );
    cobj->setListener(listener);
	return true;
}

JSBool jsb_anysdk_framework_ProtocolSocial_removeListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolSocial_removeListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolSocial* cobj = (ProtocolSocial *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (ProtocolSocialListener::_instance != NULL)
    {
        ProtocolSocialListener::purge();
    }
    if(argc != 0)
    	CCLOG("ProtocolSocial_removeListener has wrong number of arguments.");
	return true;
}

JSBool jsb_anysdk_framework_ProtocolSocial_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp)
{
   CCLOG("\n********** \nsetDebugMode was deprecated.\n**********");
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ProtocolSocial* cobj = (ProtocolSocial *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setDebugMode(arg0);
		CCLOG("ProtocolSocial setDebugMode");
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool jsb_anysdk_framework_ProtocolSocial_unlockAchievement(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolSocial_unlockAchievement, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolSocial* cobj = (ProtocolSocial *)(proxy ? proxy->ptr : NULL);
    if (argc != 1)
    {
		JS_ReportError(cx, "jsb_anysdk_framework_ProtocolSocial_unlockAchievement : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return false;
    }
	jsval *argv = JS_ARGV(cx, vp);
	jsval arg0 = argv[0];
	if ( arg0.isObject() ){
		JSObject* tmp = JSVAL_TO_OBJECT(arg0);
	    if (!tmp) {
	        CCLOG("%s", "jsval_to_ccvaluemap: the jsval is not an object.");
	        return false;
	    }
	    
	    JSObject* it = JS_NewPropertyIterator(cx, tmp);

	    TAchievementInfo arg;
	    
	    while (true)
	    {
	        jsid idp;
	        jsval key;
	        if (! JS_NextProperty(cx, it, &idp) || ! JS_IdToValue(cx, idp, &key)) {
	            return false; // error
	        }
	        
	        if (key == JSVAL_VOID) {
	            break; // end of iteration
	        }
	        
	        if (!JSVAL_IS_STRING(key)) {
	            continue; // ignore integer properties
	        }
	        
	        JSStringWrapper keyWrapper(JSVAL_TO_STRING(key), cx);

			std::string v1;
			std::string v2;

	        v1 = keyWrapper.get();
	        jsval value;
        	JS_GetPropertyById(cx, tmp, idp, &value);
	        if (value.isString())
	        {
	            bool ok = jsval_to_std_string(cx, value, &v2);
	            if (ok){
	            	CCLog("key:%s, value: %s.",v1.c_str(), v2.c_str());
	        		arg.insert( std::map<std::string,std::string>::value_type(v1, v2) );
	            }
	            else{
	            	CCLog("wrong param in stringmap.\n");
	            }
	        }
	    }
	    cobj->unlockAchievement( arg );
	}
	return true;
}

class ProtocolIAPResultListener : public PayResultListener
{
public:
    ProtocolIAPResultListener():m_bNeedUnroot(false), _jsCallback(JSVAL_VOID), _jsThisObj(JSVAL_VOID)
    {
    }
    ~ProtocolIAPResultListener()
    {
    	CCLOG("on IAP result ~listener");
    }

    virtual void onPayResult(PayResultCode code, const char* msg, TProductInfo info)
    {
        CCLOG("on pay result: %d, msg: %s.", code, msg);
    	JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    	JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);
	    jsval retval;
	    if (_jsCallback != JSVAL_VOID)
	    {
		    std::string vec="{";
		    TProductInfo::iterator iter;
	        for (iter = info.begin(); iter != info.end(); ++iter)
		    {
		        std::string key = std::string(iter->first);
		        std::string value = (std::string)(iter->second);
		        // CCLOG("productInfo key: %s, value: %s.", key.c_str(), value.c_str());
		        vec += key + ":" +value+ ",";
		    }
		    vec.replace(vec.length() - 1, 1, "}");
	        jsval resultCode = INT_TO_JSVAL(code);
	        jsval valArr[3];
	        valArr[0] = resultCode;
	        valArr[1] = std_string_to_jsval(cx, msg);
	        valArr[2] = std_string_to_jsval(cx, vec);

	        JS_AddValueRoot(cx, valArr);
	        JS_CallFunctionValue(cx, thisObj, _jsCallback, 3, valArr, &retval);
	        JS_RemoveValueRoot(cx, valArr);
	    }
    }
    
    virtual void onRequestResult(RequestResultCode code, const char* msg, AllProductsInfo info)
    {
        CCLOG("on request result: %d, msg: %s.", code, msg);
        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
        JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);
        jsval retval;
        if (_jsCallback != JSVAL_VOID)
        {
            string value = "{";
            map<string, TProductInfo >::iterator iterParent;
            iterParent = info.begin();
            while(iterParent != info.end())
            {
                value.append(iterParent->first);
                value.append("={");
                map<string, string> infoChild = iterParent->second;
                map<string, string >::iterator iterChild;
                iterChild = infoChild.begin();
                while(iterChild != infoChild.end())
                {
                    value.append(iterChild->first);
                    value.append("=");
                    value.append(iterChild->second);
                    iterChild++;
                    if(iterChild != infoChild.end())
                        value.append(", ");
                }
                iterParent++;
                if(iterParent != info.end())
                    value.append("}, ");
            }
            value.append("}");
            jsval resultCode = INT_TO_JSVAL(code);
            jsval valArr[3];
            valArr[0] = resultCode;
            valArr[1] = std_string_to_jsval(cx, msg);
            valArr[2] = std_string_to_jsval(cx, value);
            
            JS_AddValueRoot(cx, valArr);
            JS_CallFunctionValue(cx, thisObj, _jsCallback, 3, valArr, &retval);
            JS_RemoveValueRoot(cx, valArr);
        }
    }

    void setJSCallbackThis(jsval jsThisObj)
    {
        _jsThisObj = jsThisObj;
        
        JSObject *thisObj = JSVAL_TO_OBJECT(jsThisObj);
	    js_proxy *p = jsb_get_js_proxy(thisObj);
	    if (!p)
	    {
	        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
	        m_bNeedUnroot = true;
	        m_bNeedUnroot &= JS_AddValueRoot(cx, &jsThisObj);
	    }
    }
    void setJSCallbackFunc(jsval func) {
    	_jsCallback = func;
    	JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
		// Root the callback function.
    	JS_AddNamedValueRoot(cx, &_jsCallback, "JSCallbackWrapper_callback_func");
	}
	void setJsObject(JSObject* cx){
		_jsObj = cx;
	}

    typedef std::map<std::string, ProtocolIAPResultListener*> STD_MAP;
    typedef std::map<std::string, ProtocolIAPResultListener*>::iterator STD_MAP_ITERATOR;

    static STD_MAP std_map;
    static ProtocolIAPResultListener* getListenerByKey(std::string key)
    {
        ProtocolIAPResultListener* listener = std_map[key];
        if (listener == NULL) {
            listener = new ProtocolIAPResultListener();
            std_map[key] = listener;
        }
        return listener;
    }
    static void purge(std::string key)
    {
        ProtocolIAPResultListener* listener = std_map[key];
        delete listener;
        listener = NULL;
        std_map.erase(key);
    }
    static void purge()
    {
        for (STD_MAP_ITERATOR it = std_map.begin(); it != std_map.end(); ++it)
        {
            ProtocolIAPResultListener* listener = it->second;
            delete listener;
        }
        std_map.clear();
    }
private:
	JSObject* _jsObj;
    jsval _jsCallback;
    jsval _jsThisObj;
    bool m_bNeedUnroot;
};
ProtocolIAPResultListener::STD_MAP ProtocolIAPResultListener::std_map;

JSBool jsb_anysdk_framework_ProtocolIAP_setResultListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolAds_setAdsListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolIAP* cobj = (ProtocolIAP *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 2)
    {
		JS_ReportError(cx, "jsb_anysdk_framework_ProtocolAds_setAdsListener : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return true;
    }
	jsval *argv = JS_ARGV(cx, vp);
	std::string p_id = cobj->getPluginId();
    if (p_id.length() < 1)
    {
        p_id = "no_plugin";
    }
    if (ProtocolIAPResultListener::std_map[p_id] == NULL)
    {
        CCLOG("will set listener:");
        ProtocolIAPResultListener* listener = ProtocolIAPResultListener::getListenerByKey(p_id);
	    listener->setJSCallbackFunc( argv[0] );
	    listener->setJSCallbackThis( argv[1] );
	    cobj->setResultListener(listener);
    }

	return true;
}

JSBool jsb_anysdk_framework_ProtocolIAP_removeListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolIAP_removeListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolIAP* cobj = (ProtocolIAP *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    std::string p_id = cobj->getPluginId();
    if (p_id.length() < 1)
    {
        p_id = "no_plugin";
    }
    if (ProtocolIAPResultListener::std_map[p_id] != NULL)
    {
        ProtocolIAPResultListener* listener = ProtocolIAPResultListener::std_map[p_id];
        listener->purge(p_id);
    }
    if(argc != 0)
    	CCLOG("ProtocolIAP_removeListener has wrong number of arguments.");
	return true;
}

JSBool jsb_anysdk_framework_ProtocolIAP_payForProduct(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolIAP_payForProduct, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolIAP* cobj = (ProtocolIAP *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 1)
    {
		JS_ReportError(cx, "jsb_anysdk_framework_ProtocolIAP_payForProduct : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return true;
    }
    jsval *argv = JS_ARGV(cx, vp);
    jsval arg0 = argv[0];
	if ( arg0.isObject() ){
		JSObject* tmp = JSVAL_TO_OBJECT(arg0);
	    if (!tmp) {
	        CCLOG("%s", "jsval_to_ccvaluemap: the jsval is not an object.");
	        return true;
	    }
	    
	    JSObject* it = JS_NewPropertyIterator(cx, tmp);

	    TProductInfo arg;
	    
	    while (true)
	    {
	        jsid idp;
	        jsval key;
	        if (! JS_NextProperty(cx, it, &idp) || ! JS_IdToValue(cx, idp, &key)) {
	            return false; // error
	        }
	        
	        if (key == JSVAL_VOID) {
	            break; // end of iteration
	        }
	        
	        if (!JSVAL_IS_STRING(key)) {
	            continue; // ignore integer properties
	        }
	        
	        JSStringWrapper keyWrapper(JSVAL_TO_STRING(key), cx);

			std::string v1;
			std::string v2;

	        v1 = keyWrapper.get();
	        jsval value;
        	JS_GetPropertyById(cx, tmp, idp, &value);
	        if (value.isString())
	        {
	            bool ok = jsval_to_std_string(cx, value, &v2);
	            if (ok){
	            	CCLog("key:%s, value: %s.",v1.c_str(), v2.c_str());
	        		arg.insert( std::map<std::string,std::string>::value_type(v1, v2) );
	            }
	            else{
	            	CCLog("wrong param in stringmap.\n");
	            }
	        }
	    }
	    cobj->payForProduct( arg );
	}
	return true;
}

JSBool jsb_anysdk_framework_ProtocolIAP_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("\n********** \nsetDebugMode was deprecated.\n**********");
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ProtocolIAP* cobj = (ProtocolIAP *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setDebugMode(arg0);
		CCLOG("ProtocolIAP setDebugMode");
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

class ProtocolAdsResultListener : public AdsListener
{
public:
    ProtocolAdsResultListener():m_bNeedUnroot(false), _jsCallback(JSVAL_VOID), _jsThisObj(JSVAL_VOID)
    {
    }
    ~ProtocolAdsResultListener()
    {
    	CCLOG("on ads result ~listener");
    }

    virtual void onAdsResult(AdsResultCode code, const char* msg)
    {
        CCLOG("on ads result: %d, msg: %s.", code, msg);
    	JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    	JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);

	    jsval retval;
	    if (_jsCallback != JSVAL_VOID)
	    {
	        jsval resultCode = INT_TO_JSVAL(code);
	        // JSString* jsstr = JS_NewStringCopyZ(cx, msg);

	        jsval valArr[2];
	        valArr[0] = resultCode;
	        valArr[1] = std_string_to_jsval(cx, msg);

	        JS_AddValueRoot(cx, valArr);
	        JS_CallFunctionValue(cx, thisObj, _jsCallback, 2, valArr, &retval);
	        JS_RemoveValueRoot(cx, valArr);
	    }
    }
    virtual void onPlayerGetPoints(ProtocolAds* pAdsPlugin, int points) 
    {
        CCLOG("on player get points: %d.", points);
    	JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    	JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);

	    jsval retval;
	    if (_jsCallback != JSVAL_VOID)
	    {
	        jsval resultCode = INT_TO_JSVAL(points);

	        jsval valArr[2];
			js_proxy_t *proxy = js_get_or_create_proxy(cx, pAdsPlugin);
	        valArr[0] = OBJECT_TO_JSVAL(proxy->obj);
	        valArr[1] = resultCode;

	        JS_AddValueRoot(cx, valArr);
	        JS_CallFunctionValue(cx, thisObj, _jsCallback, 2, valArr, &retval);
	        JS_RemoveValueRoot(cx, valArr);
	    }
    }

    void setJSCallbackThis(jsval jsThisObj)
    {
        _jsThisObj = jsThisObj;
        
        JSObject *thisObj = JSVAL_TO_OBJECT(jsThisObj);
	    js_proxy *p = jsb_get_js_proxy(thisObj);
	    if (!p)
	    {
	        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
	        m_bNeedUnroot = true;
	        m_bNeedUnroot &= JS_AddValueRoot(cx, &jsThisObj);
	    }
    }
    void setJSCallbackFunc(jsval func) {
    	_jsCallback = func;
    	JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
		// Root the callback function.
    	JS_AddNamedValueRoot(cx, &_jsCallback, "JSCallbackWrapper_callback_func");
	}

    static ProtocolAdsResultListener* _instance;
    static ProtocolAdsResultListener* getInstance()
    {
        if (_instance == NULL)
        {
            _instance = new ProtocolAdsResultListener();
        }
        return _instance;
    }
    static void purge()
    {
        if (_instance != NULL)
        {
            delete _instance;
            _instance = NULL;
        }
    }
private:
    jsval _jsCallback;
    jsval _jsThisObj;
    bool m_bNeedUnroot;
};
ProtocolAdsResultListener* ProtocolAdsResultListener::_instance = NULL;

JSBool jsb_anysdk_framework_ProtocolAds_setAdsListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolAds_setAdsListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolAds* cobj = (ProtocolAds *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 2)
    {
		JS_ReportError(cx, "jsb_anysdk_framework_ProtocolAds_setAdsListener : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return false;
    }

	jsval *argv = JS_ARGV(cx, vp);
    ProtocolAdsResultListener* listener = ProtocolAdsResultListener::getInstance();
    listener->setJSCallbackFunc( argv[0] );
    listener->setJSCallbackThis( argv[1] );
    cobj->setAdsListener(listener);
	return true;
}

JSBool jsb_anysdk_framework_ProtocolAds_removeListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolAds_removeListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolAds* cobj = (ProtocolAds *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (ProtocolAdsResultListener::_instance != NULL)
    {
        ProtocolAdsResultListener::purge();
    }
    if(argc != 0)
    	CCLOG("ProtocolAds_removeListener has wrong number of arguments.");
	return true;
}

 JSBool jsb_anysdk_framework_ProtocolAds_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("\n********** \n setDebugMode was deprecated.\n**********");
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ProtocolAds* cobj = (ProtocolAds *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setDebugMode(arg0);
		CCLOG("ProtocolAds setDebugMode");
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

class ProtocolUserActionListener : public UserActionListener
{
public:
    ProtocolUserActionListener():m_bNeedUnroot(false), _jsCallback(JSVAL_VOID), _jsThisObj(JSVAL_VOID)
    {
    }
    ~ProtocolUserActionListener()
    {
    	CCLOG("on user action result ~listener");
    }

    virtual void onActionResult(ProtocolUser* pPlugin, UserActionResultCode code, const char* msg)
    {
        CCLOG("on user action result: %d, msg: %s.", code, msg);
    	JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
    	JSObject *thisObj = JSVAL_IS_VOID(_jsThisObj) ? NULL : JSVAL_TO_OBJECT(_jsThisObj);

		js_proxy_t *proxy = js_get_or_create_proxy(cx, pPlugin);
	    jsval retval;
	    if (_jsCallback != JSVAL_VOID)
	    {
	        jsval resultCode = INT_TO_JSVAL(code);
	        // JSString* jsstr = JS_NewStringCopyZ(cx, msg);

	        jsval valArr[3];
	        valArr[0] = OBJECT_TO_JSVAL(proxy->obj);
	        valArr[1] = resultCode;
	        valArr[2] = std_string_to_jsval(cx, msg);

	        JS_AddValueRoot(cx, valArr);
	        JS_CallFunctionValue(cx, thisObj, _jsCallback, 3, valArr, &retval);
	        JS_RemoveValueRoot(cx, valArr);
	    }
    }

    void setJSCallbackThis(jsval jsThisObj)
    {
        _jsThisObj = jsThisObj;
        
        JSObject *thisObj = JSVAL_TO_OBJECT(jsThisObj);
	    js_proxy *p = jsb_get_js_proxy(thisObj);
	    if (!p)
	    {
	        JSContext *cx = ScriptingCore::getInstance()->getGlobalContext();
	        m_bNeedUnroot = true;
	        m_bNeedUnroot &= JS_AddValueRoot(cx, &jsThisObj);
	    }
    }
    void setJSCallbackFunc(jsval func) {
    	_jsCallback = func;
    	JSContext* cx = ScriptingCore::getInstance()->getGlobalContext();
		// Root the callback function.
    	JS_AddNamedValueRoot(cx, &_jsCallback, "JSCallbackWrapper_callback_func");
	}

    static ProtocolUserActionListener* _instance;
    static ProtocolUserActionListener* getInstance(){
        if (_instance == NULL){
            _instance = new ProtocolUserActionListener();
        }
        return _instance;
    }
    static void purge(){
        if (_instance)
        {
            delete _instance;
            _instance = NULL;
        }
    }
private:
    jsval _jsCallback;
    jsval _jsThisObj;
    bool m_bNeedUnroot;
};
ProtocolUserActionListener* ProtocolUserActionListener::_instance = NULL;

JSBool jsb_anysdk_framework_ProtocolUser_setActionListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolUser_setActionListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolUser* cobj = (ProtocolUser *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (argc != 2)
    {
		JS_ReportError(cx, "jsb_anysdk_framework_ProtocolUser_setActionListener : wrong number of arguments: %d, was expecting %d", argc, 0);
    	return false;
    }
	jsval *argv = JS_ARGV(cx, vp);
    ProtocolUserActionListener* listener = ProtocolUserActionListener::getInstance();
    listener->setJSCallbackFunc( argv[0] );
    listener->setJSCallbackThis( argv[1] );
    cobj->setActionListener(listener);
	return true;
}
JSBool jsb_anysdk_framework_ProtocolUser_removeListener(JSContext *cx, uint32_t argc, jsval *vp)
{
	CCLOG("in ProtocolUser_removeListener, argc:%d.", argc);
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolUser* cobj = (ProtocolUser *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    if (ProtocolUserActionListener::_instance != NULL)
    {
        ProtocolUserActionListener::purge();
    }
    if(argc != 0)
    	CCLOG("ProtocolUser_removeListener has wrong number of arguments.");
	return true;
}

JSBool jsb_anysdk_framework_ProtocolUser_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("\n********** \nsetDebugMode was deprecated.\n**********");
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ProtocolUser* cobj = (ProtocolUser *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setDebugMode(arg0);
		CCLOG("ProtocolUser setDebugMode");
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool jsb_anysdk_framework_ProtocolAnalytics_setDebugMode(JSContext *cx, uint32_t argc, jsval *vp)
{
    CCLOG("\n********** \nsetDebugMode was deprecated.\n**********");
	jsval *argv = JS_ARGV(cx, vp);
	JSBool ok = JS_TRUE;
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
	js_proxy_t *proxy = jsb_get_js_proxy(obj);
	ProtocolAnalytics* cobj = (ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);
	JSB_PRECONDITION2( cobj, cx, JS_FALSE, "Invalid Native Object");
	if (argc == 1) {
		JSBool arg0;
		ok &= JS_ValueToBoolean(cx, argv[0], &arg0);
		JSB_PRECONDITION2(ok, cx, JS_FALSE, "Error processing arguments");
		cobj->setDebugMode(arg0);
		CCLOG("ProtocolAnalytics setDebugMode");
		JS_SET_RVAL(cx, vp, JSVAL_VOID);
		return JS_TRUE;
	}

	JS_ReportError(cx, "wrong number of arguments: %d, was expecting %d", argc, 1);
	return JS_FALSE;
}

JSBool jsb_anysdk_framework_ProtocolAnalytics_logEvent(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    ProtocolAnalytics* cobj = (ProtocolAnalytics *)(proxy ? proxy->ptr : NULL);

	jsval *argv = JS_ARGV(cx, vp);
	jsval arg0 = argv[0];
	std::string arg;
	bool ok = jsval_to_std_string(cx, arg0, &arg);
	CCLOG("logevent, argc: %d, str: %s.", argc, arg.c_str());
	if (!ok)
	{
		CCLOG("ProtocolAnalytics_logEvent param type is wrong.");
		return false;
	}
    if (argc == 1)
    {
    	cobj->logEvent(arg.c_str());
    	return true;
    }
    else if(argc == 2)
    {
    	JSObject* tmp = JSVAL_TO_OBJECT(argv[1]);
	    if (!tmp) {
	        CCLOG("%s", "jsval_to_stdmap: the jsval is not an object.");
	        return false;
	    }
	    
	    JSObject* it = JS_NewPropertyIterator(cx, tmp);

    	LogEventParamMap params;
	    
	    while (true)
	    {
	        jsid idp;
	        jsval key;
	        if (! JS_NextProperty(cx, it, &idp) || ! JS_IdToValue(cx, idp, &key)) {
	            return false; // error
	        }
	        
	        if (key == JSVAL_VOID) {
	            break; // end of iteration
	        }
	        
	        if (!JSVAL_IS_STRING(key)) {
	            continue; // ignore integer properties
	        }
	        
	        JSStringWrapper keyWrapper(JSVAL_TO_STRING(key), cx);

			std::string v1;
			std::string v2;

	        v1 = keyWrapper.get();
	        jsval value;
        	JS_GetPropertyById(cx, tmp, idp, &value);
	        if (value.isString())
	        {
	            bool ok = jsval_to_std_string(cx, value, &v2);
	            if (ok){
	            	CCLog("key:%s, value: %s.",v1.c_str(), v2.c_str());
	        		params.insert( std::map<std::string,std::string>::value_type(v1, v2) );
	            }
	            else{
	            	CCLog("wrong param in stringmap.\n");
	            }
	        }
	    }
	    cobj->logEvent(arg.c_str(), &params);

    	return true;
    }
	JS_ReportError(cx, "jsb_anysdk_framework_ProtocolAnalytics_logEvent : wrong number of arguments: %d, was expecting %d", argc, 0);
	return true;
}

JSBool jsb_anysdk_framework_AgentManager_getIAPPlugin(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    AgentManager* cobj = (AgentManager *)(proxy ? proxy->ptr : NULL);

    if (argc != 0)
    {
		CCLOG("AgentManager_getIAPPlugin param number is wrong.");
		return false;
    }
    std::map<std::string , ProtocolIAP*>* plugins = cobj->getIAPPlugin();
    JSObject *jsretArr = JS_NewArrayObject(cx, 0, NULL);

    std::map<std::string , ProtocolIAP*>::iterator iter;
    for (iter = plugins->begin(); iter != plugins->end(); ++iter)
    {
    	// JS::RootedValue dictElement(cx);

        std::string key = std::string(iter->first);
        CCLOG("iap key: %s.", key.c_str());
        ProtocolIAP* iap_plugin = (ProtocolIAP*)(iter->second);

        js_proxy_t *jsProxy = js_get_or_create_proxy<ProtocolIAP>(cx, (ProtocolIAP*)iap_plugin);
		jsval dictElement = OBJECT_TO_JSVAL(jsProxy->obj);

		JS_SetProperty(cx, jsretArr, key.c_str(), &dictElement);
    }
    jsval jsret = OBJECT_TO_JSVAL(jsretArr);
    JS_SET_RVAL(cx, vp, jsret);

	return true;
}
JSBool jsb_anysdk_framework_AgentManager_getFrameworkVersion(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    AgentManager* cobj = (AgentManager *)(proxy ? proxy->ptr : NULL);

    if (argc != 0)
    {
		CCLOG("AgentManager_getFrameworkVersion param number is wrong.");
		return false;
    }

    std::string version;
    version = cobj->getFrameworkVersion();
	
	jsval jsret;
	jsret = c_string_to_jsval(cx, version.c_str());
	JS_SET_RVAL(cx, vp, jsret);

	return true;
}

JSBool jsb_anysdk_framework_PluginProtocol_callFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PluginProtocol* cobj = (PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    CCLOG("callFuncWithParam, param count:%d.\n", argc);
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    if(argc == 1){
    	std::string arg0;
    	ok &= jsval_to_std_string(cx, argv[0], &arg0);
    	CCLOG("arg0: %s\n", arg0.c_str());
    	cobj->callFuncWithParam(arg0.c_str(), NULL);
        return JS_TRUE;
    }
    else if (argc == 0) {
    	JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
    else{
    	std::string arg0;
    	ok &= jsval_to_std_string(cx, argv[0], &arg0);
    	CCLOG("arg0: %s\n", arg0.c_str());

		std::vector<PluginParam*> params;
    	JSObject *obj_1 = JSVAL_TO_OBJECT(argv[1]);
		if ( JS_IsArrayObject(cx, obj_1) )
		{
			CCLog("is array object.");
		    JSObject* it = JS_NewPropertyIterator(cx, obj_1);

		    uint32_t len;
			JS_GetArrayLength(cx, obj_1, &len);
			CCLog("len: %d.", len);

			for (int i = 0; i < len; i++)
			{
				jsval va;
				JS_GetElement(cx, obj_1, i, &va);
				JSObject* jsobj = JSVAL_TO_OBJECT(va);
				js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
				PluginParam* param = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
	        	params.push_back(param);
			}
		}
		else{
			CCLog("is not array.");
            for (int i = 1; i < argc; i++)
            {
			    JSObject* jsobj = JSVAL_TO_OBJECT(argv[i]);
			    js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
				PluginParam* param = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
                params.push_back(param);
            }
        }
		CCLog("will call function in c++, %d.", params.size());
		if (!params.size())
		{
			cobj->callFuncWithParam(arg0.c_str(), NULL);
			CCLog("with null param.");
		}
		else{
			cobj->callFuncWithParam(arg0.c_str(), params);
			CCLog("param is not null.");
		}
    	return JS_TRUE;
    }
}

JSBool jsb_anysdk_framework_PluginProtocol_callStringFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PluginProtocol* cobj = (PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    CCLOG("callStringFuncWithParam, param count:%d.\n", argc);
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    if(argc == 1){
    	std::string arg0;
    	ok &= jsval_to_std_string(cx, argv[0], &arg0);
    	CCLOG("arg0: %s\n", arg0.c_str());
    	std::string ret = cobj->callStringFuncWithParam(arg0.c_str(), NULL);
		jsval jsret;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    else if (argc == 0) {
    	JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
    else{
    	std::string arg0;
    	ok &= jsval_to_std_string(cx, argv[0], &arg0);
    	CCLOG("arg0: %s\n", arg0.c_str());

		std::vector<PluginParam*> params;
    	JSObject *obj_1 = JSVAL_TO_OBJECT(argv[1]);
		if ( JS_IsArrayObject(cx, obj_1) )
		{
			CCLog("is array object.");
		    JSObject* it = JS_NewPropertyIterator(cx, obj_1);

		    uint32_t len;
			JS_GetArrayLength(cx, obj_1, &len);
			CCLog("len: %d.", len);

			for (int i = 0; i < len; i++)
			{
				jsval va;
				JS_GetElement(cx, obj_1, i, &va);
				JSObject* jsobj = JSVAL_TO_OBJECT(va);
				js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
				PluginParam* param = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
	        	params.push_back(param);
			}
		}
		else{
			CCLog("is not array.");
            for (int i = 1; i < argc; i++)
            {
			    JSObject* jsobj = JSVAL_TO_OBJECT(argv[i]);
			    js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
				PluginParam* param = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
                params.push_back(param);
            }
        }
		CCLog("will call function in c++, %d.", params.size());
		std::string ret;
		if (!params.size())
		{
			ret = cobj->callStringFuncWithParam(arg0.c_str(), NULL);
			CCLog("with null param.");
		}
		else{
			ret = cobj->callStringFuncWithParam(arg0.c_str(), params);
			CCLog("param is not null.");
		}
		jsval jsret;
		jsret = std_string_to_jsval(cx, ret);
		JS_SET_RVAL(cx, vp, jsret);
    	return JS_TRUE;
    }
}

JSBool jsb_anysdk_framework_PluginProtocol_callIntFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PluginProtocol* cobj = (PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    CCLOG("callFuncWithParam, param count:%d.\n", argc);
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    if(argc == 1){
    	std::string arg0;
    	ok &= jsval_to_std_string(cx, argv[0], &arg0);
    	CCLOG("arg0: %s\n", arg0.c_str());
    	int ret = cobj->callIntFuncWithParam(arg0.c_str(), NULL);
		jsval jsret;
		jsret = INT_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    else if (argc == 0) {
    	JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
    else{
    	std::string arg0;
    	ok &= jsval_to_std_string(cx, argv[0], &arg0);
    	CCLOG("arg0: %s\n", arg0.c_str());

		std::vector<PluginParam*> params;
    	JSObject *obj_1 = JSVAL_TO_OBJECT(argv[1]);
		if ( JS_IsArrayObject(cx, obj_1) )
		{
			CCLog("is array object.");
		    JSObject* it = JS_NewPropertyIterator(cx, obj_1);

		    uint32_t len;
			JS_GetArrayLength(cx, obj_1, &len);
			CCLog("len: %d.", len);

			for (int i = 0; i < len; i++)
			{
				jsval va;
				JS_GetElement(cx, obj_1, i, &va);
				JSObject* jsobj = JSVAL_TO_OBJECT(va);
				js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
				PluginParam* param = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
	        	params.push_back(param);
			}
		}
		else{
			CCLog("is not array.");
            for (int i = 1; i < argc; i++)
            {
			    JSObject* jsobj = JSVAL_TO_OBJECT(argv[i]);
			    js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
				PluginParam* param = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
                params.push_back(param);
            }
        }
		CCLog("will call function in c++, %d.", params.size());
		int ret;
		if (!params.size())
		{
			ret = cobj->callIntFuncWithParam(arg0.c_str(), NULL);
			CCLog("with null param.");
		}
		else{
			ret = cobj->callIntFuncWithParam(arg0.c_str(), params);
			CCLog("param is not null.");
		}
		jsval jsret;
		jsret = INT_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
    	return JS_TRUE;
    }
}

JSBool jsb_anysdk_framework_PluginProtocol_callBoolFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PluginProtocol* cobj = (PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    CCLOG("callFuncWithParam, param count:%d.\n", argc);
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    if(argc == 1){
    	std::string arg0;
    	ok &= jsval_to_std_string(cx, argv[0], &arg0);
    	CCLOG("arg0: %s\n", arg0.c_str());
    	bool ret = cobj->callBoolFuncWithParam(arg0.c_str(), NULL);
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    else if (argc == 0) {
    	JS_ReportError(cx, "Invalid number of arguments");
        return false;
    }
    else{
    	std::string arg0;
    	ok &= jsval_to_std_string(cx, argv[0], &arg0);
    	CCLOG("arg0: %s\n", arg0.c_str());

		std::vector<PluginParam*> params;
    	JSObject *obj_1 = JSVAL_TO_OBJECT(argv[1]);
		if ( JS_IsArrayObject(cx, obj_1) )
		{
			CCLog("is array object.");
		    JSObject* it = JS_NewPropertyIterator(cx, obj_1);

		    uint32_t len;
			JS_GetArrayLength(cx, obj_1, &len);
			CCLog("len: %d.", len);

			for (int i = 0; i < len; i++)
			{
				jsval va;
				JS_GetElement(cx, obj_1, i, &va);
				JSObject* jsobj = JSVAL_TO_OBJECT(va);
				js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
				PluginParam* param = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
	        	params.push_back(param);
			}
		}
		else{
			CCLog("is not array.");
            for (int i = 1; i < argc; i++)
            {
			    JSObject* jsobj = JSVAL_TO_OBJECT(argv[i]);
			    js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
				PluginParam* param = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
                params.push_back(param);
            }
        }
		CCLog("will call function in c++, %d.", params.size());
		bool ret;
		if (!params.size())
		{
			ret = cobj->callBoolFuncWithParam(arg0.c_str(), NULL);
			CCLog("with null param.");
		}
		else{
			ret = cobj->callBoolFuncWithParam(arg0.c_str(), params);
			CCLog("param is not null.");
		}
		jsval jsret;
		jsret = BOOLEAN_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
    	return JS_TRUE;
    }
}

JSBool jsb_anysdk_framework_PluginProtocol_callFloatFuncWithParam(JSContext *cx, uint32_t argc, jsval *vp)
{
    JSObject *obj = JS_THIS_OBJECT(cx, vp);
    js_proxy_t *proxy = jsb_get_js_proxy(obj);
    PluginProtocol* cobj = (PluginProtocol *)(proxy ? proxy->ptr : NULL);
    JSB_PRECONDITION2( cobj, cx, false, "Invalid Native Object");
    CCLOG("callFuncWithParam, param count:%d.\n", argc);
    jsval *argv = JS_ARGV(cx, vp);
    bool ok = true;
    if(argc == 1){
    	std::string arg0;
    	ok &= jsval_to_std_string(cx, argv[0], &arg0);
    	CCLOG("arg0: %s\n", arg0.c_str());
    	double ret = cobj->callFloatFuncWithParam(arg0.c_str(), NULL);
		jsval jsret;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
        return JS_TRUE;
    }
    else if (argc == 0) {
    	JS_ReportError(cx, "Invalid number of arguments");
        return JS_FALSE;
    }
    else{
    	std::string arg0;
    	ok &= jsval_to_std_string(cx, argv[0], &arg0);
    	CCLOG("arg0: %s\n", arg0.c_str());

		std::vector<PluginParam*> params;
    	JSObject *obj_1 = JSVAL_TO_OBJECT(argv[1]);
		if ( JS_IsArrayObject(cx, obj_1) )
		{
			CCLog("is array object.");
		    JSObject* it = JS_NewPropertyIterator(cx, obj_1);

		    uint32_t len;
			JS_GetArrayLength(cx, obj_1, &len);
			CCLog("len: %d.", len);

			for (int i = 0; i < len; i++)
			{
				jsval va;
				JS_GetElement(cx, obj_1, i, &va);
				JSObject* jsobj = JSVAL_TO_OBJECT(va);
				js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
				PluginParam* param = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
	        	params.push_back(param);
			}
		}
		else{
			CCLog("is not array.");
            for (int i = 1; i < argc; i++)
            {
			    JSObject* jsobj = JSVAL_TO_OBJECT(argv[i]);
			    js_proxy_t *proxy_2 = jsb_get_js_proxy(jsobj);
				PluginParam* param = (PluginParam *)(proxy_2 ? proxy_2->ptr : NULL);
                params.push_back(param);
            }
        }
		CCLog("will call function in c++, %d.", params.size());
		double ret;
		if (!params.size())
		{
			ret = cobj->callFloatFuncWithParam(arg0.c_str(), NULL);
			CCLog("with null param.");
		}
		else{
			ret = cobj->callFloatFuncWithParam(arg0.c_str(), params);
			CCLog("param is not null.");
		}
		jsval jsret;
		jsret = DOUBLE_TO_JSVAL(ret);
		JS_SET_RVAL(cx, vp, jsret);
    	return JS_TRUE;
    }
    return JS_FALSE;
}

JSBool jsb_anysdk_framework_PluginParam_create(JSContext *cx, uint32_t argc, jsval *vp)
{
	JSObject *obj = JS_THIS_OBJECT(cx, vp);
    // js_proxy_t *proxy = jsb_get_js_proxy(obj);
    
    CCLog("in PluginParam create, argc: %d.", argc);
    jsval *argv = JS_ARGV(cx, vp);
    PluginParam* ret = NULL;
    bool ok = true;
    if (argc == 0)
    {
    	ret = new PluginParam();
    }
    else if(argc == 1){
    	jsval arg0 = argv[0];
	    if ( arg0.isObject() ){
			JSObject* tmp = JSVAL_TO_OBJECT(arg0);
		    if (!tmp) {
		        CCLOG("%s", "jsval_to_ccvaluemap: the jsval is not an object.");
		        return JS_FALSE;
		    }
		    JSObject* it = JS_NewPropertyIterator(cx, tmp);

		    StringMap arg;
		    while (true)
		    {
		        jsid idp;
		        jsval key;
		        if (! JS_NextProperty(cx, it, &idp) || ! JS_IdToValue(cx, idp, &key)) {
		            return JS_FALSE; // error
		        }
		        
		        if (key == JSVAL_VOID) {
		            break; // end of iteration
		        }
		        
		        if (!JSVAL_IS_STRING(key)) {
		            continue; // ignore integer properties
		        }
		        
		        JSStringWrapper keyWrapper(JSVAL_TO_STRING(key), cx);

				std::string v1;
				std::string v2;

		        v1 = keyWrapper.get();
	        	jsval value;
	    		JS_GetPropertyById(cx, tmp, idp, &value);
		        if (value.isString())
		        {
		            bool ok = jsval_to_std_string(cx, value, &v2);
		            if (ok){
		        		arg.insert( std::map<std::string,std::string>::value_type(v1, v2) );
		            }
		            else{
		            	CCLOG("wrong param in stringmap.\n");
		            	return JS_FALSE;
		            }
		        }
		    }
		    ret = new PluginParam( arg );
		}
		else if(arg0.isBoolean()){
			bool arg = JSVAL_TO_BOOLEAN( arg0 );
			ret = new PluginParam( arg );
		}
		else if(arg0.isInt32()){
			int arg;
			ok = jsval_to_int32(cx, arg0, &arg);
			if (ok){
				ret = new PluginParam( arg );
			}
			else{
				CCLOG("PluginParam param is wrong.");
				return JS_FALSE;
			}
		}
		else if(arg0.isNumber()){
			float arg;
			arg = arg0.toNumber();
			ret = new PluginParam( arg );
		}
		else if(arg0.isString()){
			std::string arg;
			ok = jsval_to_std_string(cx, arg0, &arg);
			if (ok){
				ret = new PluginParam( arg.c_str() );
			}
			else{
				CCLOG("PluginParam param is wrong.");
				return JS_FALSE;
			}
		}
	}

	js_proxy_t *proxy = js_get_or_create_proxy<anysdk::framework::PluginParam>(cx, ret);
	jsval jsret = OBJECT_TO_JSVAL(proxy->obj);
	JS_SET_RVAL(cx, vp, jsret);
	return JS_TRUE;
}

extern JSObject* jsb_PluginProtocol_prototype;
extern JSObject* jsb_ProtocolIAP_prototype;
extern JSObject* jsb_ProtocolAnalytics_prototype;
extern JSObject* jsb_ProtocolAds_prototype;
extern JSObject* jsb_ProtocolSocial_prototype;
extern JSObject* jsb_ProtocolPush_prototype;
extern JSObject* jsb_ProtocolUser_prototype;
extern JSObject* jsb_AgentManager_prototype;
extern JSObject* jsb_PluginParam_prototype;

void register_all_anysdk_manual(JSContext* cx, JSObject* obj) {
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

	// PluginProtocol
	JS_DefineFunction(cx, jsb_PluginProtocol_prototype, "callFuncWithParam", jsb_anysdk_framework_PluginProtocol_callFuncWithParam, 6, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_PluginProtocol_prototype, "callStringFuncWithParam", jsb_anysdk_framework_PluginProtocol_callStringFuncWithParam, 6, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_PluginProtocol_prototype, "callIntFuncWithParam", jsb_anysdk_framework_PluginProtocol_callIntFuncWithParam, 6, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_PluginProtocol_prototype, "callBoolFuncWithParam", jsb_anysdk_framework_PluginProtocol_callBoolFuncWithParam, 6, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_PluginProtocol_prototype, "callFloatFuncWithParam", jsb_anysdk_framework_PluginProtocol_callFloatFuncWithParam, 6, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	
	// ProtocolUser
	JS_DefineFunction(cx, jsb_ProtocolUser_prototype, "setActionListener", jsb_anysdk_framework_ProtocolUser_setActionListener, 2, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_ProtocolUser_prototype, "removeListener", jsb_anysdk_framework_ProtocolUser_removeListener, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_ProtocolUser_prototype, "setDebugMode", jsb_anysdk_framework_ProtocolUser_setDebugMode, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	
	// ProtocolIAP
	JS_DefineFunction(cx, jsb_ProtocolIAP_prototype, "setResultListener", jsb_anysdk_framework_ProtocolIAP_setResultListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_ProtocolIAP_prototype, "removeListener", jsb_anysdk_framework_ProtocolIAP_removeListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_ProtocolIAP_prototype, "payForProduct", jsb_anysdk_framework_ProtocolIAP_payForProduct, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_ProtocolIAP_prototype, "setDebugMode", jsb_anysdk_framework_ProtocolIAP_setDebugMode, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	
	// AgentManager
	JS_DefineFunction(cx, jsb_AgentManager_prototype, "getIAPPlugin", jsb_anysdk_framework_AgentManager_getIAPPlugin, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_AgentManager_prototype, "getFrameworkVersion", jsb_anysdk_framework_AgentManager_getFrameworkVersion, 0, JSPROP_ENUMERATE | JSPROP_PERMANENT);

	// ProtocolSocial
	JS_DefineFunction(cx, jsb_ProtocolSocial_prototype, "setListener", jsb_anysdk_framework_ProtocolSocial_setListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_ProtocolSocial_prototype, "removeListener", jsb_anysdk_framework_ProtocolSocial_removeListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_ProtocolSocial_prototype, "unlockAchievement", jsb_anysdk_framework_ProtocolSocial_unlockAchievement, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_ProtocolSocial_prototype, "setDebugMode", jsb_anysdk_framework_ProtocolSocial_setDebugMode, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	
	// ProtocolAnalytics
	JS_DefineFunction(cx, jsb_ProtocolAnalytics_prototype, "logEvent", jsb_anysdk_framework_ProtocolAnalytics_logEvent, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_ProtocolAnalytics_prototype, "setDebugMode", jsb_anysdk_framework_ProtocolAnalytics_setDebugMode, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	
	// ProtocolAds
	JS_DefineFunction(cx, jsb_ProtocolAds_prototype, "setAdsListener", jsb_anysdk_framework_ProtocolAds_setAdsListener, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_ProtocolAds_prototype, "removeListener", jsb_anysdk_framework_ProtocolAds_removeListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_ProtocolAds_prototype, "setDebugMode", jsb_anysdk_framework_ProtocolAds_setDebugMode, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	
	// ProtocolPush
	JS_DefineFunction(cx, jsb_ProtocolPush_prototype, "setActionListener", jsb_anysdk_framework_ProtocolPush_setActionListener, 2, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_ProtocolPush_prototype, "removeListener", jsb_anysdk_framework_ProtocolPush_removeListener, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_ProtocolPush_prototype, "setTags", jsb_anysdk_framework_ProtocolPush_setTags, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_ProtocolPush_prototype, "delTags", jsb_anysdk_framework_ProtocolPush_delTags, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);
	JS_DefineFunction(cx, jsb_ProtocolPush_prototype, "setDebugMode", jsb_anysdk_framework_ProtocolPush_setDebugMode, 1, JSPROP_READONLY | JSPROP_PERMANENT);
	
	// PluginParam
	JSObject* tmpObj = JSVAL_TO_OBJECT(anonEvaluate(cx, obj, "(function () { return anysdk.PluginParam; })()"));
	JS_DefineFunction(cx, tmpObj, "create", jsb_anysdk_framework_PluginParam_create, 1, JSPROP_ENUMERATE | JSPROP_PERMANENT);

	// ProtocolShare
	js_register_anysdk_ProtocolShare(cx, obj);
	// js_register_anysdk_PluginParam(cx, obj);
}


void anysdk_jsb_cleanAllSingletons() {
    ProtocolShareActionListener::purge();
    ProtocolPushActionListener::purge();
    ProtocolSocialListener::purge();
    ProtocolAdsResultListener::purge();
    ProtocolUserActionListener::purge();
    ProtocolIAPResultListener::purge();
}

