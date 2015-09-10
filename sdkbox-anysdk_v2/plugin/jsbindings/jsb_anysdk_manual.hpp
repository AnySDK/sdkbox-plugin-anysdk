#ifndef __anysdk_manual_h__
#define __anysdk_manual_h__

#include "jsapi.h"
#include "jsfriendapi.h"

extern JSClass  *jsb_ProtocolShare_class;
extern JSObject *jsb_ProtocolShare_prototype;

extern JSClass  *jsb_PluginParam_class;
extern JSObject *jsb_PluginParam_prototype;

void register_all_anysdk_manual(JSContext* cx, JSObject* obj);

#endif

