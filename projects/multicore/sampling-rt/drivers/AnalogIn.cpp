#include "AnalogIn.h"
#include "FreeRTOS.h"

AnalogIn::AnalogIn(int pin) :
	_Pin{ static_cast<adc_channel>(pin) }
{
	if (mtk_os_hal_adc_ctlr_init() != 0) abort();

	_RxBuf = (u32*)pvPortMalloc(sizeof(u32) * 1);
	if (_RxBuf == NULL) abort();

	struct adc_fsm_param adc_fsm_parameter;
	adc_fsm_parameter.pmode = ADC_PMODE_ONE_TIME;
	adc_fsm_parameter.channel_map = 1 << pin;
	adc_fsm_parameter.fifo_mode = ADC_FIFO_DIRECT;
	adc_fsm_parameter.ier_mode = ADC_FIFO_IER_RXFULL;
	adc_fsm_parameter.vfifo_addr = _RxBuf;
	adc_fsm_parameter.vfifo_len = 1;
	adc_fsm_parameter.rx_callback_func = NULL;
	adc_fsm_parameter.rx_callback_data = NULL;
	adc_fsm_parameter.rx_period_len = 1;
	if (mtk_os_hal_adc_fsm_param_set(&adc_fsm_parameter) != 0) abort();
}

AnalogIn::~AnalogIn()
{
	if (mtk_os_hal_adc_ctlr_deinit() != 0) abort();
	vPortFree(_RxBuf);
}
