#pragma once
class JavaScriptEventHandler : public CefV8Handler
{
public:
	JavaScriptEventHandler();
	~JavaScriptEventHandler();
public:
	virtual bool Execute(const CefString& name,
		CefRefPtr<CefV8Value> object,
		const CefV8ValueList& arguments,
		CefRefPtr<CefV8Value>& retval,
		CefString& exception) OVERRIDE;
private:
	IMPLEMENT_REFCOUNTING(JavaScriptEventHandler);
};

