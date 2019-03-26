#include "pch.h"
#include "SubProcessApp.h"
#include "JavaScriptEventHandler.h"


SubProcessApp::SubProcessApp()
{
}


SubProcessApp::~SubProcessApp()
{
}

void SubProcessApp::OnContextCreated(CefRefPtr<CefBrowser> browser,
	CefRefPtr<CefFrame> frame,
	CefRefPtr<CefV8Context> context)
{
	CefRefPtr<CefV8Value> object = context->GetGlobal();
	if (object)
	{
		CefRefPtr<CefV8Handler> handler = new JavaScriptEventHandler();
		CefRefPtr<CefV8Value> func = CefV8Value::CreateFunction("HandleEventFunc", handler);
		object->SetValue("HandleEventFunc", func, V8_PROPERTY_ATTRIBUTE_NONE);
	}
}
