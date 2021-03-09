#ifndef _C_CODE_MEASUREMENT_H_
#define _C_CODE_MEASUREMENT_H_

#pragma once

class CCodeMeasurement
{
public:

	CCodeMeasurement(IN const CCodeMeasurement& other) noexcept;
	CCodeMeasurement(IN const char* name) noexcept;
	CCodeMeasurement(NOPARAMS) noexcept
	{	}

	NORETVOID End(NOPARAMS) noexcept;

	inline const double GetDeltaTime(NOPARAMS) const noexcept;
	inline const char* const GetName(NOPARAMS) const noexcept;
private:
	std::string szName = std::string("<unknown>");
	double fDeltaTime = 0.0f;

	// We've started measuring after the object has been constructed
	std::chrono::high_resolution_clock::time_point MeasureStart = std::chrono::high_resolution_clock::now();
};

extern std::deque<CCodeMeasurement> CodeMeasurements;

#define CODE_MEASUREMENT_START(name) 					\
	CCodeMeasurement code_measure_##name = { #name };

#define CODE_MEASUREMENT_END(name)						\
	code_measure_##name.End();							\
	CodeMeasurements.push_back(code_measure_##name);

NORETVOID PrintCodeMeasurements(NOPARAMS);

#endif
