#include "stdafx.h"
#include "browser_helper.h"

WNDPROC browser_helper::m_edit_old_proc = NULL;
browser_helper::browser_helper() :m_hwnd_edit(NULL), m_hInstance(NULL)
{
}


browser_helper::~browser_helper()
{
	m_hwnd_edit = NULL;
	m_hInstance = NULL;
}

int browser_helper::InitCef3(HINSTANCE hInstance, int& exit_code)
{
	// Enable High-DPI support on Windows 7 or newer.
	CefEnableHighDPISupport();

	void* sandbox_info = NULL;
	// Provide CEF with command-line arguments.
	m_hInstance = hInstance;
	CefMainArgs main_args(m_hInstance);

	// SimpleApp implements application-level callbacks for the browser process.
	// It will create the first browser instance in OnContextInitialized() after
	// CEF has initialized.
	CefRefPtr<SimpleApp> app(new SimpleApp);

	// CEF applications have multiple sub-processes (render, plugin, GPU, etc)
	// that share the same executable. This function checks the command-line and,
	// if this is a sub-process, executes the appropriate logic.
	exit_code = CefExecuteProcess(main_args, app.get(), sandbox_info);
	if (exit_code >= 0) {
		// The sub-process has completed so return here.
		return exit_code;
	}
	// Specify CEF global settings here.

	CefSettings settings;
	CefString(&settings.log_file).FromWString(L"why.log");
	settings.no_sandbox = true;
	settings.multi_threaded_message_loop = true;
#ifdef _DEBUG
	
#endif // _DEBUG



	// Initialize CEF.
	CefInitialize(main_args, settings, app.get(), sandbox_info);
	return 0;
}

void browser_helper::CloseCef3()
{
	CefShutdown();
}

void browser_helper::CloseBrowser()
{
	SimpleHandler::GetInstance()->GetBrowserPtr()->GetHost()->CloseBrowser(true);
}

void browser_helper::CloseAllBrowser()
{
	SimpleHandler::GetInstance()->CloseAllBrowsers(true);
}

bool browser_helper::IsLastClosing()
{
	if (SimpleHandler::GetInstance() && !SimpleHandler::GetInstance()->IsClosing())
	{
		if (SimpleHandler::GetInstance()->GetBrowserPtr().get())
		{
			return true;
		}
	}
	return false;
}

void browser_helper::BrowserBack()
{
	
	SimpleHandler::GetInstance()->GetBrowserPtr()->GoBack();
}

void browser_helper::BrowserReload()
{
	SimpleHandler::GetInstance()->GetBrowserPtr()->Reload();
}

void browser_helper::BrowserForward()
{
	SimpleHandler::GetInstance()->GetBrowserPtr()->GoForward();
}

void browser_helper::BrowserRunJs()
{
	CefRefPtr<CefBrowser> browser = SimpleHandler::GetInstance()->GetBrowserPtr();
	if (browser)
	{
		CefRefPtr<CefFrame> frame = browser->GetMainFrame();
		if (frame)
		{
			wchar_t strPtr[MAX_URL_LENGTH + 1] = { 0 };
			*((LPWORD)strPtr) = MAX_URL_LENGTH;
			LRESULT strLen = SendMessage(m_hwnd_edit, EM_GETLINE, 0, (LPARAM)strPtr);
			if (strLen > 0)
			{
				strPtr[strLen] = 0;
				frame->ExecuteJavaScript(strPtr, "", 0);
			}
		}		
	}
}

bool browser_helper::CreateBrowserAndUI(HWND hWnd, std::wstring& strUrl)
{
	RECT rect;
	::GetClientRect(hWnd, &rect);
	//create ui
	int x_offset = 0;
	int window_width = rect.right - rect.left;
	int window_beight = rect.bottom - rect.top;
	int button_width = 40;
	int button_beight = 40;
	m_hwnd_back = CreateWindow(L"BUTTON", L"back",
	WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		x_offset, 0, button_width, button_beight, hWnd, 
		reinterpret_cast<HMENU>(IDC_NAV_BACK), m_hInstance, 0); 
	MYCHECK(m_hwnd_back);

	x_offset += button_width;
	m_hwnd_forward = CreateWindow(L"BUTTON", L"forward",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		x_offset, 0, button_width * 2, button_beight, hWnd,
		reinterpret_cast<HMENU>(IDC_NAV_FORWARD), m_hInstance, 0);
	MYCHECK(m_hwnd_forward);

	x_offset += button_width * 2;
	m_hwnd_reload = CreateWindow(L"BUTTON", L"reload",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		x_offset, 0, button_width * 2, button_beight, hWnd,
		reinterpret_cast<HMENU>(IDC_NAV_RELOAD), m_hInstance, 0);
	MYCHECK(m_hwnd_reload);

	x_offset += button_width * 2;
	m_hwnd_runjs = CreateWindow(L"BUTTON", L"runJs",
		WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON,
		x_offset, 0, button_width, button_beight, hWnd,
		reinterpret_cast<HMENU>(IDC_NAV_RUNJS), m_hInstance, 0);
	MYCHECK(m_hwnd_runjs);

	x_offset += button_width * 2;
	m_hwnd_edit = CreateWindow(L"EDIT", 0,
		WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT | ES_AUTOHSCROLL,
		x_offset, 0, window_width / 4,
		window_beight / 20, hWnd, 0, m_hInstance, 0);
	MYCHECK(m_hwnd_edit);
	//set editwindow windowprocess
	m_edit_old_proc = SetWndProcPtr(m_hwnd_edit, EditWndProc);

	// SimpleHandler implements browser-level callbacks.
	CefRefPtr<SimpleHandler> handler(new SimpleHandler(false));
	// Specify CEF browser settings here.
	CefBrowserSettings browser_settings;
	CefWindowInfo window_info;
	rect.top = rect.top + window_beight / 20;
	window_info.SetAsChild(hWnd, rect);
	return CefBrowserHost::CreateBrowser(window_info, handler, strUrl, browser_settings, NULL);
}

WNDPROC browser_helper::SetWndProcPtr(HWND hWnd, WNDPROC wndProc)
{
	WNDPROC old =
		reinterpret_cast<WNDPROC>(::GetWindowLongPtr(hWnd, GWLP_WNDPROC));
	CHECK(old != NULL);
	LONG_PTR result = ::SetWindowLongPtr(hWnd, GWLP_WNDPROC,
		reinterpret_cast<LONG_PTR>(wndProc));
	CHECK(result != 0 || GetLastError() == ERROR_SUCCESS);
	return old;
}

//static
LRESULT CALLBACK browser_helper::EditWndProc(HWND hWnd,
	UINT message,
	WPARAM wParam,
	LPARAM lParam)
{
	switch (message) {
	case WM_CHAR:
		if (wParam == VK_RETURN) {
			// When the user hits the enter key load the URL.
			CefRefPtr<CefBrowser> browser = SimpleHandler::GetInstance()->GetBrowserPtr();
			if (browser)
			{
				wchar_t strPtr[MAX_URL_LENGTH + 1] = { 0 };
				*((LPWORD)strPtr) = MAX_URL_LENGTH;
				LRESULT strLen = SendMessage(hWnd, EM_GETLINE, 0, (LPARAM)strPtr);
				if (strLen > 0)
				{
					strPtr[strLen] = 0;
					browser->GetMainFrame()->LoadURL(strPtr);
				}				
			}
			return 0;
		}
		break;
	case WM_NCDESTROY:
		{
			// Clear the reference to |self|.
			void *userdataptr = NULL;
			LONG_PTR result = ::SetWindowLongPtr(hWnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(userdataptr));
			return 0;
		}
		break;		
	}
	return CallWindowProc(m_edit_old_proc, hWnd, message, wParam, lParam);
}

void browser_helper::SizeMesgHandler(HWND hWnd)
{
	RECT rect;
	GetClientRect(hWnd, &rect);
	CefWindowHandle hWndBrowser = NULL;
	int window_width = rect.right - rect.left;
	int window_beight = rect.bottom - rect.top;
	std::list<CefRefPtr<CefBrowser>> browser_list = SimpleHandler::GetInstance()->GetBrowserPtrList();
	if (!browser_list.empty())
	{
		for (auto ite : browser_list)
		{
			hWndBrowser = ite->GetHost()->GetWindowHandle();
			if (hWndBrowser)
				MoveWindow(hWndBrowser, rect.left, rect.top + window_beight / 20,
					window_width,
					window_beight,
					false);
		}
	}
}