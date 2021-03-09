#include "Includes.h"

std::deque<CCodeMeasurement> CodeMeasurements;

CCodeMeasurement::CCodeMeasurement(
	IN const CCodeMeasurement& other
) noexcept
{
	szName = other.szName;
	fDeltaTime = other.fDeltaTime;
}

CCodeMeasurement::CCodeMeasurement(
	IN const char* name
) noexcept
{
	szName = std::string(name);
}

NORETVOID CCodeMeasurement::End(
	NOPARAMS
) noexcept
{
	fDeltaTime = std::chrono::duration_cast<std::chrono::duration<double>>(
		std::chrono::high_resolution_clock::now() - MeasureStart).count();
}

inline const double CCodeMeasurement::GetDeltaTime(
	NOPARAMS
) const noexcept
{
	return fDeltaTime;
}

const char* const CCodeMeasurement::GetName(
	NOPARAMS
) const noexcept
{
	return szName.c_str();
}

NORETVOID PrintCodeMeasurements(
	NOPARAMS
)
{
	cGlobals.InjectionTime.End();
	throwMessage("Took total of %.*f seconds.\n", 10, cGlobals.InjectionTime.GetDeltaTime());
}