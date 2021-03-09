#ifndef _DEFINES_H_
#define _DEFINES_H_

#pragma once

/////////////////////////////
///*   MACRO CONSTANTS   *///
/////////////////////////////

#define IMGUIHK_VERSION							"v1.0"
#define IMGUIHK_NAME							"Counter-Strike 1.6 ImGUI Hook"
#define IMGUIHK_AUTHOR							"__oxk"
#define IMGUIHK_TIME_LAST_MODIFIED				__TIMESTAMP__
#define IMGUIHK_TIME_FIRST_MODIFIED				"Tue Feb 9 4:38:42 2021"

// Settings
#define IMGUIHK_CONSOLE_LOG						1
#define IMGUIHK_USE_FN_ANNOTATIONS				0

#define NORETVOID							[[noreturn]] VOID

EXTERN_C IMAGE_DOS_HEADER					__ImageBase;

////////////////////////////
///*   UTILITY MACROS   *///
////////////////////////////

// Bit shift
#define BIT(x)								(1 << x)
// Error handler
#define throwFatalError(x, ...)				ThrowProcedure(eThrowFatalError, GetCurrentThread(), __LINE__, __builtin_COLUMN(), __TIMESTAMP__, __func__, x, __VA_ARGS__)
#define throwError(x, ...)					ThrowProcedure(eThrowError, GetCurrentThread(), __LINE__, __builtin_COLUMN(), __TIMESTAMP__, __func__, x, __VA_ARGS__)
#define throwMessage(x, ...)				ThrowProcedure(eThrowMessage, GetCurrentThread(), __LINE__, __builtin_COLUMN(), __TIMESTAMP__, __func__, x, __VA_ARGS__)
// Custom assertion method
#define Assert(x)													\
	if (x) 															\
		ThrowProcedure(eThrowAssert, GetCurrentThread(), __LINE__, __builtin_COLUMN(), __TIMESTAMP__, __func__, #x)

// Variadic function arguments
#define SETUP_VA_ARGS(szBuffer, Params)								\
	ZeroMemory(szBuffer, ARRAYSIZE(szBuffer));						\
	va_list va_alist;												\
	va_start(va_alist, Params);										\
	Assert(															\
		sizeof(szBuffer) == 4 &&									\
		"The buffer size is 4, is it a pointer, or a regular array?"\
	);																\
	_vsnprintf_s(szBuffer, sizeof(szBuffer), Params, va_alist);		\
	va_end(va_alist)

#define SEPARATE							"-----------------------------------------------\n"

////////////////////////////////////
/*   FUNCTION PARAMETER HELPERS   */
////////////////////////////////////

/* If a function has no parameters */
#ifdef NOPARAMS 
#	undef NOPARAMS
#endif // #ifdef NOPARAMS
#	define NOPARAMS
/* If a function has a parameter that goes in */
#ifdef IN 
#	undef IN
#endif // #ifdef IN
#if OJ_USE_FN_ANNOTATIONS
#	ifdef _In_
#		define IN							_In_
#	else
#		define IN
#	endif // #ifdef _In_
#else
#	define IN
#endif // #if OJ_USE_FN_ANNOTATIONS
/* If a function has a parameter that goes out */
#ifdef OUT 
#	undef OUT
#endif // #ifdef OUT
#if OJ_USE_FN_ANNOTATIONS
#	ifdef _Out_
#		define OUT							_Out_
#	else
#		define OUT
#	endif // #ifdef _In_
#else
#	define OUT
#endif // #if OJ_USE_FN_ANNOTATIONS

enum eThrowMethod 
{
	eThrowFatalError = BIT(0),
	eThrowError = BIT(1),
	eThrowAssert = BIT(2),
	eThrowMessage = BIT(3),
};

enum eKeyFlags
{
	eKF_None,

	eKF_KeyDown,
	eKF_KeyUp,
	eKF_SysKeyDown,
	eKF_SysKeyUp,
};

enum eKeyboardInput
{
	eKeyNone = 0x0,

	/*	Characters	*/
	eKeyA = 0x41, eKeyB, eKeyC, eKeyD, eKeyE, eKeyF, eKeyG,
	eKeyH, eKeyI, eKeyJ, eKeyK, eKeyL, eKeyM, eKeyN, eKeyO, eKeyP,
	eKeyQ, eKeyR, eKeyS, eKeyT, eKeyU, eKeyV, eKeyW, eKeyX, eKeyY,
	eKeyZ,

	/*	0-9 keys	*/
	eKey0 = 0x30, eKey1, eKey2, eKey3, eKey4,
	eKey5, eKey6, eKey7, eKey8, eKey9,

	/*	Numpad keys	*/
	eKeyNum0 = 0x60, eKeyNum1, eKeyNum2, eKeyNum3, eKeyNum4,
	eKeyNum5, eKeyNum6, eKeyNum7, eKeyNum8, eKeyNum9,

	/*	Arrow keys	*/
	eKeyLeftArrow = 0x25,
	eKeyUpArrow,
	eKeyRightArrow,
	eKeyDownArrow,

	/*	Functional keys	*/
	eKeyF1 = 0x70, eKeyF2, eKeyF3, eKeyF4,
	eKeyF5, eKeyF6, eKeyF7, eKeyF8, eKeyF9,
	eKeyF10, eKeyF11, eKeyF12,

	/*	Locks	*/
	eKeyCapsLock = 0x14,
	eKeyNumLock = 0x90,
	eKeyScrollLock = 0x91,

	/*	Other keys	*/
	eKeyBackspace = 0x8,
	eKeyTab = 0x9,
	eKeyEnter = 0xD,
	eKeyEscape = 0x1B,

	eKeySpace = 0x20,
	eKeyPgUp = 0x21,
	eKeyPgDown = 0x22,
	eKeyEnd = 0x23,
	eKeyHome = 0x24,
	eKeyInsert = 0x2D,
	eKeyDelete = 0x2E,

	eKeyCount = 256,
};

NORETVOID extern ThrowProcedure(IN const eThrowMethod& ThrowMethod, IN const HANDLE thread, IN const INT line, IN const INT column, IN const CHAR* timestamp, IN const CHAR* funcName, IN const CHAR* msg, ...);
template <std::size_t T> const CHAR* const vargs(
	IN const CHAR* const fmt, ...
)
{
	CHAR buf[T];
	SETUP_VA_ARGS(buf, fmt);
	return buf;
}

#endif