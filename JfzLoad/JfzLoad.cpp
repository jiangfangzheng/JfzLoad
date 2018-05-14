//JfzLoad.cpp: 定义应用程序的入口点。

// 为了使用wcstok
#define _CRT_NON_CONFORMING_WCSTOK
#define _CRT_SECURE_NO_WARNINGS

#include "resource.h"
#include <windows.h>
#include <cstdio>
#include <string>

void Wchar_tToString(std::string& szDst, wchar_t *wchar);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	//获取exe执行文件名字(去掉后缀".exe")
	wchar_t filepath[1024] = {0};
	GetModuleFileName(NULL, filepath, MAX_PATH);
	// 从最左边开始最后一次出现"."的位置(注：strchr/strrchr函数使用)
	*wcsrchr(filepath, '.') = '\0';
	// 获取本启动器的文件名
	wchar_t const* delimiter = L"\\";
	wchar_t* tokenPre = NULL;
	wchar_t* token = wcstok(filepath, delimiter);
	while (token != NULL)
	{
		tokenPre = token;
		token = wcstok(NULL, delimiter);
	}
	// printf("%ls ", tokenPre);
	std::string fileNameStr = "fff";
	Wchar_tToString(fileNameStr, tokenPre);
	std::string cmdSys = "javaw -jar " + fileNameStr + ".jar";
	std::string cmdLib = "./lib/bin/javaw.exe -jar " + fileNameStr + ".jar";
	LPCSTR cmdSysLPCSTR = cmdSys.c_str();
	LPCSTR cmdLibLPCSTR = cmdLib.c_str();

	LoadIconW(hInstance, MAKEINTRESOURCE(IDC_ICON));
	UINT result = WinExec(cmdSysLPCSTR, SW_SHOW);
	// 一调用就立刻返回一个值，返回值大于31，则表示运行成功
	if (result < 31)
	{
		result = WinExec(cmdLibLPCSTR, SW_SHOW);
		if (result < 31)
		{
			MessageBox(NULL, TEXT("未找到Java运行时！"), TEXT("失败"), MB_OK | MB_ICONINFORMATION);
		}
	}
	return 0;
}

// wchar_t to string
void Wchar_tToString(std::string& szDst, wchar_t *wchar)
{
	wchar_t * wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);// WideCharToMultiByte的运用
	char *psText;  // psText为char*的临时数组，作为赋值给std::string的中间变量
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);// WideCharToMultiByte的再次运用
	szDst = psText;// std::string赋值
	delete[]psText;// psText的清除
}
