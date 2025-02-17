/**
* Copyright (c) Pervasive Displays Inc. All rights reserved.
*
* \asf_license_start
*
* \page License
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*
* 1. Redistributions of source code must retain the above copyright notice,
*    this list of conditions and the following disclaimer.
*
* 2. Redistributions in binary form must reproduce the above copyright notice,
*    this list of conditions and the following disclaimer in the documentation
*    and/or other materials provided with the distribution.
*
* \asf_license_stop
**/

#include "timer_if.h"
#include "Board_HW_Driver.h"

static  volatile uint32_t EPD_Counter;
#define CS_H_L_Delay()		MAP_UtilsDelay(1000);
void TimerBaseIntHandler(void);
/**
 * \brief Set up EPD Timer for 1 mSec interrupts
 *
 * \note
 * desired value: 1mSec
 * actual value:  1.000mSec
 */
 void initialize_EPD_timer(void) {
	 Timer_IF_Init(PRCM_TIMERA0, TIMERA0_BASE, TIMER_CFG_PERIODIC, TIMER_A, 0);
	  Timer_IF_IntSetup(TIMERA0_BASE, TIMER_A, TimerBaseIntHandler);
}
uint32_t getnowtime(void)
{
	return 0;
}
/**
 * \brief Start Timer
 * \note
 * desired value: 1mSec
 * actual value:  1.00mSec
 */
void Systick_Configuration(void)
{
	initialize_EPD_timer();
}
void SysTickIntHandler(void)
{

}
void systick_Stop(void)
{

}
void systick_Start(void)
{

}

/**
 * \brief Start Timer
 * \note
 * desired value: 1mSec
 * actual value:  1.000mSec
 */
void start_EPD_timer(void) {

		Timer_IF_Start(TIMERA0_BASE, TIMER_A,
					  PERIODIC_TEST_CYCLES / 1000);
		EPD_Counter = 0;
}

/**
 * \brief Stop Timer
 */
void stop_EPD_timer(void) {
	Timer_IF_Stop(TIMERA0_BASE, TIMER_A);
}
/**
 * \brief Get current Timer after starting a new one
 */
uint32_t get_EPD_time_tick(void) {

	return EPD_Counter;
}

void TimerBaseIntHandler(void)
{
    Timer_IF_InterruptClear(TIMERA0_BASE);
    EPD_Counter++;
}
/**
 * \brief Delay mini-seconds
 * \param ms The number of mini-seconds
 */
void EPD_delay_ms(unsigned int ms) {
	start_EPD_timer();
	while(get_EPD_time_tick()<=ms)
	{

	}
}

void delay_btwn_CS_H_L(void) {
	//delay > 80ns
}
/**
 * \brief PWM toggling.
 *
 * \param ms The interval of PWM toggling (mini seconds)
 */
void PWM_run(uint16_t ms) {
    start_EPD_timer();
	do {

		EPD_pwm_high();
		MAP_UtilsDelay(20);
		EPD_pwm_low();
		MAP_UtilsDelay(20);
	} while (get_EPD_time_tick() < ms); //wait Delay Time

	stop_EPD_timer();

}
//******************************************************************
//* SPI  Configuration
//******************************************************************
bool spi_state=false;

/**
 * \brief Configure SPI
 */
void epd_spi_init(uint32_t spi_baudrate) {


}
/**
 * \brief Initialize SPI
 */
void EPD_spi_attach() {
		MAP_PRCMPeripheralClkEnable(PRCM_GSPI, PRCM_RUN_MODE_CLK);
		if(spi_state) return;
		EPD_flash_cs_high();
		EPD_cs_high();
		// MAP_PRCMPeripheralReset(PRCM_SSPI);
		// Configure PIN_05 for SPI0 GSPI_CLK
		MAP_PinTypeSPI(PIN_05, PIN_MODE_7);
		// Configure PIN_06 for SPI0 GSPI_MISO
		MAP_PinTypeSPI(PIN_06, PIN_MODE_7);
		// Configure PIN_07 for SPI0 GSPI_MOSI
		MAP_PinTypeSPI(PIN_07, PIN_MODE_7);
		// Reset SPI
		MAP_SPIReset(GSPI_BASE);
		// Configure SPI interface
		MAP_SPIConfigSetExpClk(GSPI_BASE,MAP_PRCMPeripheralClockGet(PRCM_GSPI),
						 COG_SPI_baudrate,SPI_MODE_MASTER,SPI_SUB_MODE_0,
						 (SPI_SW_CTRL_CS |
						 SPI_4PIN_MODE |
						 SPI_TURBO_OFF  |
						 SPI_CS_ACTIVELOW  |
						 SPI_WL_8));
		// Enable SPI for communication
		MAP_SPIEnable(GSPI_BASE);
		MAP_SPICSEnable(GSPI_BASE);
		spi_state=true;
}
/**
 * \brief Disable SPI and change to GPIO
 */
void EPD_spi_detach(void) {
		if(!spi_state) return;
		EPD_cs_high();
		MAP_SPICSDisable(GSPI_BASE);
		MAP_SPIDisable(GSPI_BASE);
		config_gpio_dir_o(SPICLK_PinIO,SPICLK_PORT,SPICLK_PIN);
		config_gpio_dir_o(SPIMISO_PinIO,SPIMISO_PORT,SPIMISO_PIN);
		config_gpio_dir_o(SPIMOSI_PinIO,SPIMOSI_PORT,SPIMOSI_PIN);
		SPIMISO_low();
		SPIMOSI_low();
		SPICLK_low();
		spi_state=false;
}
bool check_flash_spi(void)
{
	if(!spi_state) EPD_spi_attach();
	return spi_state;
}
/**
 * \brief SPI synchronous read
 */
uint8_t EPD_spi_read(unsigned char data) {
		unsigned char rxData;
		MAP_SPITransfer(GSPI_BASE, &data, &rxData, 1, 0);
		return rxData;
}

/**
 * \brief SPI synchronous write
 */
void EPD_spi_write(unsigned char data) {
	EPD_spi_read(data);
}
void iTC_spi_sendReg(uint8_t register_index)
{
	EPD_cs_low();
	EPD_DC_low();
	CS_H_L_Delay();
	EPD_spi_write(register_index);
	EPD_cs_high();
	CS_H_L_Delay();
	EPD_DC_high();
	EPD_cs_low();
	CS_H_L_Delay();
}
void iTC_spi_sendRegData(uint8_t register_data)
{
	EPD_spi_write(register_data);
}

void iTC_spi_send(uint8_t register_index,uint8_t *register_data,uint8_t len)
{

	EPD_cs_low();
	EPD_DC_low();
	CS_H_L_Delay();
	EPD_spi_write(register_index);
	//EPD_cs_high();
	//CS_H_L_Delay();
	EPD_DC_high();
	//EPD_cs_low();
	CS_H_L_Delay();
	while(len--)
	{
		EPD_spi_write(*register_data++);
	}

	EPD_cs_high();
}
void iTC_spi_send_array(Em_register_array_t *register_array,uint8_t len)
{
	uint8_t i;
	for(i=0;i<len;i++)
	{
		iTC_spi_send(register_array[i].register_index,register_array[i].register_data,register_array[i].len);
	}
}
/**
* \brief SPI command
*
* \param register_index The Register Index as SPI Data to COG
* \param register_data The Register Data for sending command data to COG
* \return the SPI read value
*/
uint8_t EPD_Gx_spi_r(uint8_t register_index, uint8_t register_data) {
	uint8_t result;
	EPD_cs_low ();
	EPD_spi_write (0x70); // header of Register Index
	EPD_spi_write (register_index);
	EPD_cs_high ();
	delay_btwn_CS_H_L ();
	EPD_cs_low ();

	EPD_spi_write (0x73); // header of Register Data of read command
	result=EPD_spi_read (register_data);

	EPD_cs_high ();

	return result;
}
uint8_t EPD_Gx_spi_rid(void)
{
	uint8_t result;
	EPD_cs_low ();
	EPD_spi_write (0x71);
	result=EPD_spi_read (0x00);
	EPD_cs_high ();
	return result;
}

/**
* \brief SPI command if register data is larger than two bytes
*
* \param register_index The Register Index as SPI command to COG
* \param register_data The Register Data for sending command data to COG
* \param length The number of bytes of Register Data which depends on which
* Register Index is selected.
*/
void EPD_Gx_spi_send (unsigned char register_index, unsigned char *register_data,
               unsigned length) {
	EPD_cs_low ();
	EPD_spi_write (0x70); // header of Register Index
	EPD_spi_write (register_index);
	EPD_cs_high ();
	delay_btwn_CS_H_L ();
	EPD_cs_low ();

	EPD_spi_write (0x72); // header of Register Data of write command
	while(length--) {
		EPD_spi_write (*register_data++);
	}
	EPD_cs_high ();
}

/**
* \brief SPI command
*
* \param register_index The Register Index as SPI command to COG
* \param register_data The Register Data for sending command data to COG
*/
void EPD_Gx_spi_send_byte (uint8_t register_index, uint8_t register_data) {
	EPD_cs_low ();
	EPD_spi_write (0x70); // header of Register Index
	EPD_spi_write (register_index);
	EPD_cs_high ();
	delay_btwn_CS_H_L ();
	EPD_cs_low ();
	EPD_spi_write (0x72); // header of Register Data
	EPD_spi_write (register_data);
	EPD_cs_high ();
}
#if defined(ccs)
extern void (* const g_pfnVectors[])(void);
#endif
#if defined(ewarm)
extern uVectorEntry __vector_table;
#endif
void system_init(void)
{
	/* In case of TI-RTOS vector table is initialize by OS itself */
	#ifndef USE_TIRTOS
	    //
	    // Set vector table base
	    //
	#if defined(ccs)
	    MAP_IntVTableBaseSet((unsigned long)&g_pfnVectors[0]);
	#endif
	#if defined(ewarm)
	    MAP_IntVTableBaseSet((unsigned long)&__vector_table);
	#endif
	#endif

	    //
	    // Enable Processor
	    //
	    MAP_IntMasterEnable();
	    MAP_IntEnable(FAULT_SYSTICK);

	    PRCMCC3200MCUInit();
}
/**
* \brief Configure GPIO
*/
void EPD_initialize_gpio(void) {
    MAP_PRCMPeripheralClkEnable(PRCM_GPIOA0, PRCM_RUN_MODE_CLK);
    MAP_PRCMPeripheralClkEnable(PRCM_GPIOA1, PRCM_RUN_MODE_CLK);
    MAP_PRCMPeripheralClkEnable(PRCM_GPIOA2, PRCM_RUN_MODE_CLK);
    MAP_PRCMPeripheralClkEnable(PRCM_GPIOA3, PRCM_RUN_MODE_CLK);
	Config_Busy_Pin();
	Config_EPD_cs_Pin();
	Config_EPD_rst_Pin();
	Config_EPD_panelon_Pin();
	Config_EPD_discharge_Pin();
	Config_EPD_border_Pin();
    Config_EPD_flash_cs_Pin();
	Config_EPD_pwm_Pin();
    Config_LED1_Pin();
    Config_BS1_Pin();
    BS1_low();//Must be LOW

	EPD_pwm_low();
	EPD_flash_cs_high();
	EPD_border_low();
	EPD_Vcc_turn_off();
}
/**
 * \brief Initialize the EPD hardware setting
 */
void EPD_display_hardware_init(void) {
	EPD_initialize_gpio();
	EPD_Vcc_turn_off();
	EPD_cs_low();
	EPD_rst_low();
	EPD_discharge_low();
#if isDebug
	ConfigureUART(115200);
#endif
}

