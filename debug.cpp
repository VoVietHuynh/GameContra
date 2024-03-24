#include <Windows.h>
#include "debug.h"

HWND _hwnd = NULL;

void DebugOut(const wchar_t* fmt, ...)
{
	va_list argp;
	va_start(argp, fmt);
	wchar_t dbg_out[4096];
	vswprintf_s(dbg_out, fmt, argp);
	va_end(argp);
	OutputDebugStringW(dbg_out);
}

void SetDebugWindow(HWND hwnd)
{
	_hwnd = hwnd;
}