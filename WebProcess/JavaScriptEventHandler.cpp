#include "pch.h"
#include "include/cef_v8.h"
#include "JavaScriptEventHandler.h"


JavaScriptEventHandler::JavaScriptEventHandler()
{
}


JavaScriptEventHandler::~JavaScriptEventHandler()
{
}

bool JavaScriptEventHandler::Execute(const CefString& name,
	CefRefPtr<CefV8Value> object,
	const CefV8ValueList& arguments,
	CefRefPtr<CefV8Value>& retval,
	CefString& exception)
{
	if (name != "HandleEventFunc" || arguments.size() == 0)
	{
		return true;//Return true if execution was handled.
	}

	CefRefPtr<CefBrowser> browser = CefV8Context::GetCurrentContext()->GetBrowser();
	if (browser)
	{
		CefRefPtr<CefProcessMessage> message = CefProcessMessage::Create(arguments[0]->GetStringValue());
		message->GetArgumentList()->SetSize(arguments.size() - 1);
		for (size_t i = 1; i < arguments.size(); i++)
		{
			message->GetArgumentList()->SetString(i - 1, arguments[i]->GetStringValue());
		}
		browser->SendProcessMessage(PID_BROWSER, message);
	}
	return false;
}
