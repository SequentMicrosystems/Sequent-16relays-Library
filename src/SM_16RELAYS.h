/*!
 * @file SM_16RELAYS.h
 * 
 * Designed specifically to work with the Sequent Microsysatems 
 * Sixteen Relays 2A/24V 8-Layer Stackable HAT for Raspberry Pi
 * 
 * ----> https://sequentmicrosystems.com/collections/all-io-cards/products/sixteen-relays-8-layer-stackable-hat-for-raspberry-pi
 * 
 *   This card use I2C to communicate.
 *   
 *   Written by Alexandru Burcea for Sequent Microsystems
 * 
 *   Software License Agreement (BSD License)
 *
 *  Copyright (c) 2024, Sequent Microsystems 
 *  
 */
#ifndef __SM_16RELAYS__
#define __SM_16RELAYS__

#define SM_16R_RELAY_CH_NO 16


#define SM_16R_SLAVE_OWN_ADDRESS_BASE 0x20

enum
{
	SM_16R_INPORT_REG_ADD,
	SM_16R_OUTPORT_REG_ADD = 2,
	SM_16R_POLINV_REG_ADD = 4,
	SM_16R_CFG_REG_ADD = 6,
	SM_16R_SW_MOM_ADD = 8,
	SM_16R_SW_INT_ADD,
	SM_16R_SW_INT_EN_ADD,
	SM_16R_MEM_DIAG_3V3_MV_ADD,
	SM_16R_MEM_DIAG_TEMPERATURE_ADD = SM_16R_MEM_DIAG_3V3_MV_ADD +2,
	SM_16R_MEM_DIAG_5V_ADD,
	SM_16R_MEM_WDT_RESET_ADD = SM_16R_MEM_DIAG_5V_ADD + 2,
	SM_16R_MEM_WDT_INTERVAL_SET_ADD,
	SM_16R_MEM_WDT_INTERVAL_GET_ADD = SM_16R_MEM_WDT_INTERVAL_SET_ADD + 2,
	SM_16R_MEM_WDT_INIT_INTERVAL_SET_ADD = SM_16R_MEM_WDT_INTERVAL_GET_ADD + 2,
	SM_16R_MEM_WDT_INIT_INTERVAL_GET_ADD = SM_16R_MEM_WDT_INIT_INTERVAL_SET_ADD + 2,
	SM_16R_MEM_WDT_RESET_COUNT_ADD = SM_16R_MEM_WDT_INIT_INTERVAL_GET_ADD + 2,
	SM_16R_MEM_WDT_CLEAR_RESET_COUNT_ADD = SM_16R_MEM_WDT_RESET_COUNT_ADD + 2,
	SM_16R_MEM_WDT_POWER_OFF_INTERVAL_SET_ADD,
	SM_16R_MEM_WDT_POWER_OFF_INTERVAL_GET_ADD = SM_16R_MEM_WDT_POWER_OFF_INTERVAL_SET_ADD + 4,
	SM_16R_MODBUS_SETINGS_ADD  = SM_16R_MEM_WDT_POWER_OFF_INTERVAL_GET_ADD + 4,//5 bytes

	SM_16R_MEM_CPU_RESET = 0xaa,
	SM_16R_MEM_REVISION_HW_MAJOR_ADD ,
	SM_16R_MEM_REVISION_HW_MINOR_ADD,
	SM_16R_MEM_REVISION_MAJOR_ADD,
	SM_16R_MEM_REVISION_MINOR_ADD,
	SM_16R_MEM_LED_MODE = 254,
	SLAVE_BUFF_SIZE = 255
};


/*!
 * @brief SM_16RELAYS class
 */
class SM_16RELAYS
{
public:

    /*!
	 * @brief Class constructor.
	 */
	SM_16RELAYS(uint8_t stack = 0);
	
	/*!
	 * @brief Check card presence
	 * @return Returns true is successful
	 */
	bool begin();

	/*!
	 * @brief Return card existance status
	 * @return Returns true if card is present
	 */
	bool isAlive();

	/*!
	 * @brief Set one relay state
	 * @param relay -  Relay number 1..4 as are printed on the card
	 * @param val The new state of the relay, true: energised
	 * @return Returns true if successful
	 */
	bool writeRelay(uint8_t relay, bool val);

	/*!
	 * @brief Write all relays state as a 4 bits bitmap
	 * @param val The bitmap of the relays states
	 * @return Returns true if successful
	 */
	bool writeRelay(uint16_t val); 

private:
	uint8_t _hwAdd;
	bool _detected;
	int writeByte(uint8_t add, uint8_t value);
	int writeWord(uint8_t add, uint16_t value);
	int writeDWord(uint8_t add, uint32_t value);
	int readByte(uint8_t add, uint8_t* value);
	int readWord(uint8_t add, uint16_t* value);
	int readDWord(uint8_t add, uint32_t* value);
};

#endif //__SM_16RELAYS__
