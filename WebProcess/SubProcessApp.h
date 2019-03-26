#pragma once
class SubProcessApp : public CefApp, public CefRenderProcessHandler
{
public:
	SubProcessApp();
	~SubProcessApp();
public:
	//CefApp methods:
	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler()
		OVERRIDE {
		return this;
	}

	//CefRenderProcessHandler methods:
	virtual void OnContextCreated(CefRefPtr<CefBrowser> browser,
		CefRefPtr<CefFrame> frame,
		CefRefPtr<CefV8Context> context) OVERRIDE;

private:
	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(SubProcessApp);
};

