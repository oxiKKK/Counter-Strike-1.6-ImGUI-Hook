#include "Includes.h"

CGlobals cGlobals;

using pfnwglSwapBuffers_t = BOOL(APIENTRY*)(HDC hdc);
pfnwglSwapBuffers_t pfnwglSwapBuffers;

const char* SystimeToStr(
	NOPARAMS
)
{
	SYSTEMTIME SysTime;
	GetSystemTime(&SysTime);

	return vargs<512>("[%02d-%02d-%d %02d-%02d-%02d.%03d]",
					  SysTime.wDay,
					  SysTime.wMonth,
					  SysTime.wYear,

					  SysTime.wHour,
					  SysTime.wMinute,
					  SysTime.wSecond,
					  SysTime.wMilliseconds
					  );
}

NORETVOID ThrowProcedure(
	IN const eThrowMethod& ThrowMethod,
	IN const HANDLE thread,
	IN const INT line,
	IN const INT column,
	IN const CHAR* timestamp,
	IN const CHAR* funcName,
	IN const CHAR* msg, ...
)
{
	CHAR szLoadType[512], buf[1024];
	if (ThrowMethod & eThrowFatalError)
		sprintf_s(szLoadType, "%s %s" " | " "Fatal Error" " | " "(%d:%d): %s", IMGUIHK_NAME, IMGUIHK_VERSION, line, column, funcName);
	else if (ThrowMethod & eThrowError)
		sprintf_s(szLoadType, "%s %s" " | " "Error"       " | " "(%d:%d): %s", IMGUIHK_NAME, IMGUIHK_VERSION, line, column, funcName);
	else if (ThrowMethod & eThrowMessage)
		sprintf_s(szLoadType, "%s %s" " | " "Message"     " | " "(%d:%d): %s", IMGUIHK_NAME, IMGUIHK_VERSION, line, column, funcName);
	else if (ThrowMethod & eThrowAssert)
		sprintf_s(szLoadType, "%s %s" " | " "Assertion"   " | " "(%d:%d): %s", IMGUIHK_NAME, IMGUIHK_VERSION, line, column, funcName);
	else sprintf_s(szLoadType, "Not valid");

	SETUP_VA_ARGS(buf, msg);

	MessageBox(
		NULL,
		buf,
		szLoadType,
		MB_OK | (ThrowMethod & eThrowMessage ? MB_ICONINFORMATION : MB_ICONERROR)
	);

	if (ThrowMethod & eThrowFatalError)
	{
		Beep(500, 200); // Error 'sound'
		std::exit(EXIT_FAILURE);
	}
}

NORETVOID CheckForDetourErrorCode(
	IN const LONG errcode,
	IN const char* name
)
{
	if (errcode != NO_ERROR)
		throwError("%s: Failure detouring. %d\n", name, errcode);
}

BOOL APIENTRY Hooked_wglSwapBuffers(
	IN HDC hdc
)
{
	cKeyboardEvent.Initialize(hdc);
	cImGui.Process(cGlobals.hWND);

	return (pfnwglSwapBuffers)(hdc);
}

NORETVOID PrintInjectMessage(
	NOPARAMS
)
{
	PrintCodeMeasurements();
}

NORETVOID MainProcedure(
	NOPARAMS
)
{
	CODE_MEASUREMENT_START(MainProcedure);

	DetourTransactionBegin();
	DetourUpdateThread(GetCurrentThread());

	pfnwglSwapBuffers = (pfnwglSwapBuffers_t)GetProcAddress(GetModuleHandle("opengl32.dll"), "wglSwapBuffers");

	// Attach our function to the original one stored in the process memory.
	DetourAttach(&(PVOID&)pfnwglSwapBuffers, Hooked_wglSwapBuffers);

	LONG errcode = DetourTransactionCommit();

	// We check if the detour fails or not.
	CheckForDetourErrorCode(errcode, "pfnwglSwapBuffers");

	CODE_MEASUREMENT_END(MainProcedure);

	PrintInjectMessage();
}

BOOL WINAPI DllMain(
	_In_ HINSTANCE hInstance,
	_In_ DWORD dwReason,
	_In_ LPVOID lpvReserved
)
{
	cGlobals.hInstance = hInstance;

	switch (dwReason)
	{
		case DLL_PROCESS_ATTACH:
		{
			CreateThread(
				0,
				0,
				(LPTHREAD_START_ROUTINE)MainProcedure,
				0,
				0,
				0
			);

			break;
		}
		case DLL_PROCESS_DETACH:
		{
			// To make sure this case happened. Optional.
			Beep(1000, 100);

			break;
		}
	}

	return TRUE;
}

NORETVOID TerminateSelf(
	NOPARAMS
)
{
	// It is safer to call it there, instead of DLL_PROCESS_DETACH in DllMain.
	// Seems like... While in some cases, DLL_PROCESS_DETACH case isnt even called.
	UnloadCheat();

	CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)FreeLibraryAndExitThread, &__ImageBase, 0, NULL);
}

NORETVOID UnloadCheat(
	NOPARAMS
)
{
	LONG errcode;
	errcode = DetourTransactionBegin();
	CheckForDetourErrorCode(errcode, "pfnwglSwapBuffers");
	errcode = DetourUpdateThread(GetCurrentThread());
	CheckForDetourErrorCode(errcode, "pfnwglSwapBuffers");

	// Detach our function from the original one stored in the process memory.
	errcode = DetourDetach(&(PVOID&)pfnwglSwapBuffers, Hooked_wglSwapBuffers);
	CheckForDetourErrorCode(errcode, "pfnwglSwapBuffers");

	errcode = DetourTransactionCommit();

	// We check if the detour fails or not.
	CheckForDetourErrorCode(errcode, "pfnwglSwapBuffers");
}