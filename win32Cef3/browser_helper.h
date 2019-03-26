#pragma once
#include "simple_app.h"
#include "simple_handler.h"
class browser_helper
{
public:
	browser_helper();
	~browser_helper();
public:
	int InitCef3(HINSTANCE hInstance, int& exit_code);
	void CloseCef3();
	void CloseBrowser();
	void CloseAllBrowser();
	bool IsLastClosing();
	bool CreateBrowserAndUI(HWND hWnd, std::wstring& strUrl);
	void SizeMesgHandler(HWND hWnd);
	void BrowserBack();
	void BrowserReload();
	void BrowserForward();
	void BrowserRunJs();
private:
	// Window procedure for the edit field.
	static LRESULT CALLBACK EditWndProc(HWND hWnd,
		UINT message,
		WPARAM wParam,
		LPARAM lParam);

	WNDPROC SetWndProcPtr(HWND hWnd, WNDPROC wndProc);
private:
	HWND m_hwnd_edit;
	HWND m_hwnd_back;
	HWND m_hwnd_reload;
	HWND m_hwnd_forward;
	HWND m_hwnd_runjs;
	HINSTANCE m_hInstance;
	static WNDPROC m_edit_old_proc;
};

