#include "Includes.h"

CKeyboardEvent cKeyboardEvent;

CSingleKey::CSingleKey(
	IN const DWORD vkCode,
	IN const DWORD uMsg
)
{
	this->vkCode = vkCode;
	this->uMsg = uMsg;
	bInitialized = true;
}

CSingleKey::CSingleKey(
	IN const CSingleKey& key)
{
	this->vkCode = key.vkCode;
	this->uMsg = key.uMsg;
	bInitialized = true;
}

VOID CSingleKey::Press(
	NOPARAMS
)
{
	PressN(1);
}

VOID CSingleKey::PressN(
	IN const DWORD times
)
{
	if (!isInitialized())
	{
		throwFatalError("Cannot use key %d until its initialized!\n", this->vkCode);
		return;
	}

	KEYBDINPUT kb{ 0 };
	INPUT Input{ 0 };

	// generate down 
	kb.wVk = this->vkCode;
	Input.type = INPUT_KEYBOARD;

	Input.ki = kb;

	for(DWORD i = 0; i < times; i++)
		SendInput(1, &Input, sizeof(Input));
}

NORETVOID CKeyboardEvent::Initialize(
	IN const HDC hdc
)
{
	static bool once = false;
	if (!once)
	{
		DWORD i = 0;
		while (i++ < 256)
			KeyMap[i] = { i, 0x0 };

		cGlobals.hWND = WindowFromDC(hdc);

		hGameWndProc = (WNDPROC)SetWindowLongPtr(cGlobals.hWND, GWLP_WNDPROC, (LONG)WindowProc);

		once = true;
	}
}

const bool CKeyboardEvent::isCtrlPressed(
	NOPARAMS
) const
{
	return (::GetKeyState(VK_CONTROL) & 0x8000) != false;
}

NORETVOID CKeyboardEvent::Unload(
	NOPARAMS
)
{
	if (hGameWndProc)
		SetWindowLongPtr(cGlobals.hWND, GWLP_WNDPROC, (LONG)hGameWndProc);
	hGameWndProc = 0;
}

LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);
LRESULT CALLBACK WindowProc(
	_In_ HWND hwnd,
	_In_ UINT uMsg,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{	
	if (wParam < 256)
		cKeyboardEvent.KeyMap[wParam].uMsg = uMsg;
	
	if (cImGui.bImGuiDrawing)
	{
		if (ImGui_ImplWin32_WndProcHandler(hwnd, uMsg, wParam, lParam))
		{
			if ((uMsg == WM_KEYUP || uMsg == WM_SYSKEYUP) && (wParam < 256))
				return CallWindowProc(cKeyboardEvent.hGameWndProc, hwnd, uMsg, wParam, lParam);
			return TRUE;
		}
	}
	return CallWindowProc(cKeyboardEvent.hGameWndProc, hwnd, uMsg, wParam, lParam);
}

LRESULT CALLBACK LowLevelKeyboardProc(
	_In_ int nCode,
	_In_ WPARAM wParam,
	_In_ LPARAM lParam
)
{
	KBDLLHOOKSTRUCT* pKeyBoard = (KBDLLHOOKSTRUCT*)lParam;

	if (nCode >= 0)
	{
		DWORD vkCode = pKeyBoard->vkCode;
		
		// code

		return FALSE;
	}
	return CallNextHookEx(cKeyboardEvent.hLowLevelKeyboardProcHook, nCode, wParam, lParam);
}
