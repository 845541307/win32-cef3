// WebProcess.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "SubProcessApp.h"


int main(int argc, char *argv[])
{
	// Structure for passing command-line arguments.
// The definition of this structure is platform-specific.
// 传递命令行参数的结构体。
// 这个结构体的定义与平台相关。
	CefMainArgs main_args(GetModuleHandle(NULL));
	void* sandbox_info = NULL; 
	// Optional implementation of the CefApp interface.
	// 可选择性地实现CefApp接口
	CefRefPtr<SubProcessApp> app(new SubProcessApp);

	// Execute the sub-process logic. This will block until the sub-process should exit.
	// 执行子进程逻辑，此时会堵塞直到子进程退出。
	return CefExecuteProcess(main_args, app.get(), sandbox_info);
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
