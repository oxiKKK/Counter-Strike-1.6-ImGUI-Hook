#ifndef _C_IMGUI_H_
#define _C_IMGUI_H_

#pragma once

class CImGUI
{
public:
	bool bImGuiDrawing = false;
	bool m_bImGuiInsideRenderingCycle = false;
public:
	CSingleKey* ImGuiActivateKey;
	ImFont* HackFont01;
public:
	VOID Initialize(IN const HWND hwnd);
	NORETVOID Process(IN const HWND hwnd);
	VOID HandleDrawingEvent(NOPARAMS);
	NORETVOID HandleKeyboardEvent(NOPARAMS);
};

extern CImGUI cImGui;

#endif