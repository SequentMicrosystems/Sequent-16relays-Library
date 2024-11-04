# Sequent-16relays-Library
Arduino library for Sequent Microsystems [Sixteen Relays 2A/24V 8-Layer Stackable HAT for Raspberry Pi](https://sequentmicrosystems.com/collections/all-io-cards/products/sixteen-relays-8-layer-stackable-hat-for-raspberry-pi)
## Install
### Library manager
Go to **Tools**>>**Manage Libraries..** menu and search for *SM_16RELAYS* and click install 
### Manual install
To download click <>Code > [Download ZIP](https://github.com/SequentMicrosystems/Sequent-16relays-Library/archive/refs/heads/main.zip) button from the main [page](https://github.com/SequentMicrosystems/Sequent-16relays-Library), rename the uncompressed folder to "SM_16relays" 
and copy to the libraries subdirectory of your sketchbook directory ("This PC > Documents > Arduino > libraries" for a Windows PC
 or "Home > arduino > libraries" on a Linux PC). Now launch the Arduino environment. If you open the Sketch > Include Library menu, you should see Sequent 16relays inside. 
 The library will be compiled with sketches that use it. Open an Arduino sketch, go to File > Examples > Seqquent 16relays >, and choose your example to run.

## Usage
There are three ways to control the Sexteen Universal Inputs Card from the Arduino environment.

### Method 1: Using any Arduino controller
You can use this method with any Arduino card with an I2C port by connecting I2C-SDA, I2C-SCL, +5V and GND, as shown in the following table.
      
| SIGNAL | PIN# |CONN| PIN# | SIGNAL|
|---|---|---|---|---|
| | --1 | O - O | 2-- |  +5V | 
| I2C-SDA | --3| O - O | 4-- |  +5V |
| I2C-SCL |-- 5|O - O| 6--|  GND |
|  |-- 7|O - O| 8--||
| GND |-- 9|O - O|10--||
| |--11|O - O|12--||
| |--13|O - O|14--| GND|
| |--15|O - O|16--||
||--17|O - O|18--||
||--19|O - O|20--|  GND|
||--21|O - O|22--||
||--23|O - O|24--||
|GND |--25|O - O|26--||
||--27|O - O|28--||
||--29|O - O|30--|  GND|
||--31|O - O|32--||
||--33|O - O|34--|  GND|
||--35|O - O|36--||
||--37|O - O|38--||
|GND |--39|O - O|40--||
 
### Method 2: Using the SM Arduino Raspberry Pi Replacement Kit
Sequent Microsystems [Arduino Uno, Nano, Teensy, Feather or ESP32 Raspberry Pi Replacement Kit](https://sequentmicrosystems.com/products/raspberry-pi-replacement-card) is an inexpensive adapter which can be used to control any of our HATs using Uno, Nano, Teensy, Feather or ESP32. Plug the Home Automation HAT into the 40 pin connector of the adapter and write your Arduino software.

### Method 3: Using the SM ESP32-Pi Raspberry Pi Alternative Card
ESP32-Pi is a Raspberry Pi alternate solution that can control directly the Sexteen Relays HAT.
In your sketchbook set the board type to DOIT ESP32 DEVKIT V1: Tool >> Board >> ESP32 Arduino >> DOIT ESP32 DEVKIT V1

## Functions prototypes
	
	/*!
	 * @brief Class constructor
	 * @param stack - stack level set from the dip switches on the card
	 */
	SM_16_RELAYS(uint8_t stack = 0);
	
	/*!
	 * @brief Check card presence
	 * @return Returns true is successful
	 */
	bool begin();

	/*!
	 * @brief Return card existence status
	 * @return Returns true if the card is present
	 */
	bool isAlive();

	/*!
	 * @brief Turn on or Off one relay
	 * @param relay The led number 1..16
	 * @param val The new state true = on, false = off
	 * @return true if succeed, false else
	 */
	bool relay(uint8_t relay, bool val);

	/*!
	 * @brief Turn on or Off all relays
	 * @param val All 16 relays state as a bitmap
	 * @return true if succeed, false else
	 */
	bool relay(uint16_t val);
