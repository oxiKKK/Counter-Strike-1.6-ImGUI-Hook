#include "Includes.h"

CImGUI cImGui;

VOID CImGUI::HandleDrawingEvent(
	NOPARAMS
)
{
	// There draw things like esp, some generic screen text information, etc...

	if (!bImGuiDrawing)
		return;

	ImGui::ShowDemoWindow();

	// There draw your menu....
}

NORETVOID CImGUI::HandleKeyboardEvent(
	NOPARAMS
)
{
	static int state = 0;
	if (ImGuiActivateKey->isPressed())
		state = 1;
	if (ImGuiActivateKey->isUnPressed() && state == 1)
		state = 0, bImGuiDrawing = !bImGuiDrawing;
}

VOID CImGUI::Initialize(
	IN const HWND hwnd
)
{
	static bool once = true;

	if (!once)
		return;

	ImGui::CreateContext();

	ImGui_ImplWin32_Init(hwnd);
	ImGui_ImplOpenGL2_Init();

	ImGuiActivateKey = &cKeyboardEvent.KeyMap[eKeyInsert];

	once = false;
}

NORETVOID CImGUI::Process(
	IN const HWND hwnd
)
{
	Initialize(hwnd);

	ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplWin32_NewFrame();

	ImGui::NewFrame();

	// Idk what this actually does, but i've red that it's usefull
	ImGui::GetIO().DeltaTime = 0;

	// YOUR code start
	m_bImGuiInsideRenderingCycle = true;

	HandleKeyboardEvent();
	HandleDrawingEvent();

	m_bImGuiInsideRenderingCycle = false;
	// YOUR code end

	ImGui::Render();

	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());

	///////////////////////////////////////////////////////////////////////////////////////
	//		Use this to prevent mouse issues when in game while opening imgui.
	///////////////////////////////////////////////////////////////////////////////////////
	//
	//	if (bImGuiDrawing)
	//	{
	//		pGetClientFuncs()->IN_DeactivateMouse();
	//	}
	//	else
	//	{
	//		pGetClientFuncs()->IN_ActivateMouse();
	//	}
	//
	///////////////////////////////////////////////////////////////////////////////////////
	//		Also, hook HUD_Key_Event from cl_enginefuncs_t and do following.
	///////////////////////////////////////////////////////////////////////////////////////
	//
	//	int ret = GetOrigClientFuncs()->HUD_Key_Event(down, keynum, pszCurrentBinding);
	//	
	//	// Otherwise you would start shooting when clicking in the menu
	//	if (cImGui.bImGuiDrawing)
	//		return false;
	//	
	//	if (cImGui.ImGuiActivateKey)
	//		if (cImGui.ImGuiActivateKey->isPressed())
	//			return false;
	//	
	//	return ret;
}
