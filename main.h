#ifndef _MAIN_H_
#define _MAIN_H_

#pragma once

struct CGlobals
{
	HWND hWND;
	HINSTANCE hInstance;
	bool HudFrameLoaded;
	CCodeMeasurement InjectionTime;
	DWORD dwHudRedraw;

	char szModulePath[MAX_PATH];
};
extern CGlobals cGlobals;

NORETVOID TerminateSelf(NOPARAMS);
NORETVOID UnloadCheat(NOPARAMS);

#endif