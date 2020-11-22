#pragma once

#include <stdlib.h>
#include "os_hal_adc.h"

class AnalogIn
{
private:
	const adc_channel _Pin;
	u32* _RxBuf;

public:
	AnalogIn(int pin);
	~AnalogIn();

	AnalogIn(const AnalogIn&) = delete;
	AnalogIn& operator=(const AnalogIn) = delete;

	u32 Read()
	{
		if (mtk_os_hal_adc_trigger_one_shot_once() != 0) abort();

		return _RxBuf[0];
	}

};
