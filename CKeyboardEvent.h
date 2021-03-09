#ifndef _C_KEYBOARD_EVENT_H_
#define _C_KEYBOARD_EVENT_H_

#pragma once

class CSingleKey
{
public:
	DWORD vkCode = 0x0;
	DWORD uMsg = 0x0;
private:
	bool bInitialized = false;
public:
	VOID Press(NOPARAMS);
	VOID PressN(IN const DWORD times);

	const bool isPressed(NOPARAMS) const
	{
		return uMsg == WM_KEYDOWN;
	}

	const bool isUnPressed(NOPARAMS) const
	{
		return uMsg == WM_KEYUP;
	}

	const bool isInitialized(NOPARAMS)
	{
		return vkCode && bInitialized;
	}
public:
	CSingleKey() : vkCode(0x0), uMsg(0x0)
	{	}
	CSingleKey(IN const DWORD vkCode, IN const DWORD uMsg);
	CSingleKey(IN const CSingleKey& key);
};

class CKeyboardEvent
{
public:
	CSingleKey KeyMap[256];
	WNDPROC hGameWndProc;
	HHOOK hLowLevelKeyboardProcHook;
public:
	NORETVOID Initialize(IN const HDC hdc);
	NORETVOID Unload(NOPARAMS);

	// Alt and Shift keys doesnt work in cs
	const bool isCtrlPressed(NOPARAMS) const;
};

extern CKeyboardEvent cKeyboardEvent;

extern LRESULT CALLBACK WindowProc(_In_ HWND hwnd, _In_ UINT uMsg, _In_ WPARAM wParam, _In_ LPARAM lParam);
extern LRESULT CALLBACK LowLevelKeyboardProc(_In_ int nCode, _In_ WPARAM wParam, _In_ LPARAM lParam);

#endif