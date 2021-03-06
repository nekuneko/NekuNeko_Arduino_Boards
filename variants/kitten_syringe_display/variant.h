/*
  Copyright (c) 2014-2015 Arduino LLC.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef _VARIANT_KITTEN_SYRINGE_DISPLAY_
#define _VARIANT_KITTEN_SYRINGE_DISPLAY_

// The definitions here needs a SAMD core >=1.6.10
#define ARDUINO_SAMD_VARIANT_COMPLIANCE 10610

/*----------------------------------------------------------------------------
 *        Definitions
 *----------------------------------------------------------------------------*/

/** Frequency of the board main oscillator */
#define VARIANT_MAINOSC		(32768ul)

/** Master clock frequency */
#define VARIANT_MCK	(F_CPU)

/*----------------------------------------------------------------------------
 *        Headers
 *----------------------------------------------------------------------------*/

#include "WVariant.h"

#ifdef __cplusplus
#include "SERCOM.h"
#include "Uart.h"
#endif // __cplusplus

#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/*----------------------------------------------------------------------------
 *        Pins
 *----------------------------------------------------------------------------*/

// Number of pins defined in PinDescription array
#define PINS_COUNT           (24u)
#define NUM_DIGITAL_PINS     (14u)
#define NUM_ANALOG_INPUTS    (10u)
#define NUM_ANALOG_OUTPUTS   (1u)
#define analogInputToDigitalPin(p)  ((p < NUM_ANALOG_INPUTS) ? PIN_A0 + (p) : -1)

#define digitalPinToPort(P)        ( &(PORT->Group[g_APinDescription[P].ulPort]) )
#define digitalPinToBitMask(P)     ( 1 << g_APinDescription[P].ulPin )
//#define analogInPinToBit(P)        ( )
#define portOutputRegister(port)   ( &(port->OUT.reg) )
#define portInputRegister(port)    ( &(port->IN.reg) )
#define portModeRegister(port)     ( &(port->DIR.reg) )
#define digitalPinHasPWM(P)        ( g_APinDescription[P].ulPWMChannel != NOT_ON_PWM || g_APinDescription[P].ulTCChannel != NOT_ON_TIMER )

/*
 * digitalPinToTimer(..) is AVR-specific and is not defined for SAMD
 * architecture. If you need to check if a pin supports PWM you must
 * use digitalPinHasPWM(..).
 *
 * https://github.com/arduino/Arduino/issues/1833
 */
// #define digitalPinToTimer(P)


// Pin not defined
#define NOT_CONNECTED_PIN   (37u)

// LEDs
#define PIN_LED_13           (6u)
#define PIN_LED              PIN_LED_13
#define LED_BUILTIN          PIN_LED_13
#define NEOPIXEL_BUILTIN     (8u)
#define PIN_NEOPIXEL         NEOPIXEL_BUILTIN

/*
 * Digital pins
 */
static const uint8_t D0   = 0;
static const uint8_t D1   = 1;
static const uint8_t D2   = 2;
static const uint8_t D3   = 3;
static const uint8_t D4   = 4;
static const uint8_t D5   = 5;
static const uint8_t D6   = 6;  // LED_BUILTIN
static const uint8_t D7   = 7;
static const uint8_t D8   = 8;  // NEOPIXEL_BUILTIN
static const uint8_t D9   = 9;
static const uint8_t D10  = 10; // PA00 (XIN32)
static const uint8_t D11  = 11; // PA01 (XOUT32)
static const uint8_t D12  = 12;
static const uint8_t D13  = 13;

/*
 * Analog pins
 */
#define PIN_A0               (14ul)
#define PIN_A1               (PIN_A0 + 1)
#define PIN_A2               (PIN_A0 + 2)
#define PIN_A3               (PIN_A0 + 3)
#define PIN_A4               (PIN_A0 + 4)   
#define PIN_A5               (PIN_A0 + 5)   
#define PIN_A6               (PIN_A0 + 6)
#define PIN_A7               (PIN_A0 + 7)
#define PIN_A8               (PIN_A0 + 8)
#define PIN_A9               (PIN_A0 + 9)

#define PIN_DAC0             PIN_A8

static const uint8_t A0  = PIN_A0;
static const uint8_t A1  = PIN_A1;
static const uint8_t A2  = PIN_A2;
static const uint8_t A3  = PIN_A3;
static const uint8_t A4  = PIN_A4;
static const uint8_t A5  = PIN_A5;
static const uint8_t A6  = PIN_A6;
static const uint8_t A7  = PIN_A7;
static const uint8_t A8  = PIN_A8;
static const uint8_t A9  = PIN_A9;
static const uint8_t SOK = PIN_A9; // SOK SELECTOR / AREF

static const uint8_t DAC0 = PIN_DAC0;

#define ADC_RESOLUTION		12


// Other pins
#define PIN_ATN NOT_CONNECTED_PIN   // -- unsed, arduino zero default is on 38ul, PA13
static const uint8_t ATN =  PIN_ATN;

// FingerSoK Interfaces custom pins
#define FSP_IRQ (11u) // SCK
#define FSP_RST NOT_CONNECTED_PIN

#define FSC_IRQ (13u)
#define FSC_RST (9u)

#define FSS_IRQ NOT_CONNECTED_PIN
#define FSS_IRQ NOT_CONNECTED_PIN

// Custom pins for Kitten Syringe
#if defined(NEKUNEKO_KITTEN_SYRINGE)
  static uint8_t BTTN_INJECT = PIN_A1;
#endif

// Custom pins for Kitten Display
#if defined(NEKUNEKO_KITTEN_DISPLAY)
  static uint8_t BTTN_T     = PIN_A6;
  static uint8_t BTTN_1     = PIN_A7;
  static uint8_t BTTN_2     = 4u;
  static uint8_t BTTN_A     = 12u;
  static uint8_t BTTN_B     = 10u;
  static uint8_t TFT_LITE   = PIN_A8; // (DAC)
  static uint8_t TFT_NRESET = PIN_A9; // (SOK)
  static uint8_t TFT_CMD    = PIN_A0;  
  static uint8_t TFT_SCK    = PIN_A1; // SCK1
  static uint8_t TFT_MISO   = PIN_A2; // MISO1
  static uint8_t TFT_MOSI   = PIN_A3; // MOSI1
#endif



/*
 * Serial interfaces
 */

  // Serial (USB) - HID

#define SERIAL_INTERFACES_COUNT 2

  // Serial1 (D0/D1 - SPI) - SERCOM1 (Alternate use of SERCOM1-SPI, TX1-MISO, RX1-MOSI) (SERIAL_OVER_SPI)
  #define PIN_SERIAL1_TX        (0ul)
  #define PIN_SERIAL1_RX        (1ul)
  #define PAD_SERIAL1_TX        (UART_TX_PAD_2)
  #define PAD_SERIAL1_RX        (SERCOM_RX_PAD_3)

#if defined (NEKUNEKO_KITTEN_SYRINGE)
  // SerialSOK (D2/D3 - Wire) - SERCOM3 (Alternate use of SERCOM3-I2C, TX-SDA, RX-SCL) (SERIAL_OVER_I2C)
  #define PIN_SERIALSOK_TX      (2ul)
  #define PIN_SERIALSOK_RX      (3ul)
  #define PAD_SERIALSOK_TX      (UART_TX_PAD_0)
  #define PAD_SERIALSOK_RX      (SERCOM_RX_PAD_1)

#elif defined (NEKUNEKO_KITTEN_DISPLAY)
  // SerialSOK (A4/A5 - Wire) - SERCOM2 (Alternate use of SERCOM2-I2C, TX-SDA, RX-SCL) (SERIAL_OVER_I2C)
  #define PIN_SERIALSOK_TX      (18ul)
  #define PIN_SERIALSOK_RX      (19ul)
  #define PAD_SERIALSOK_TX      (UART_TX_PAD_0)
  #define PAD_SERIALSOK_RX      (SERCOM_RX_PAD_1)
#endif



/*
 * Wire Interfaces
 */
#define WIRE_INTERFACES_COUNT 2

#if defined (NEKUNEKO_KITTEN_SYRINGE)
  // Primary I2C pins (I2C) - SERCOM3
  #define PIN_WIRE_SDA        (26u)  // D2
  #define PIN_WIRE_SCL        (27u)  // D3
  #define PERIPH_WIRE         sercom3
  #define WIRE1_IT_HANDLER    SERCOM3_Handler 

  static const uint8_t SDA = PIN_WIRE_SDA;
  static const uint8_t SCL = PIN_WIRE_SCL;

  // Secondary I2C pins (I2C1) - SERCOM2
  #define PIN_WIRE1_SDA       (24u)  // A4
  #define PIN_WIRE1_SCL       (25u)  // A5
  #define PERIPH_WIRE1        sercom2
  #define WIRE_IT_HANDLER     SERCOM2_Handler 

  static const uint8_t SDA1 = PIN_WIRE1_SDA;
  static const uint8_t SCL1 = PIN_WIRE1_SCL;

#elif defined (NEKUNEKO_KITTEN_DISPLAY)
  // Primary I2C pins (I2C) - SERCOM2
  #define PIN_WIRE_SDA        (24u)  // A4
  #define PIN_WIRE_SCL        (25u)  // A5
  #define PERIPH_WIRE         sercom2
  #define WIRE_IT_HANDLER     SERCOM2_Handler 

  static const uint8_t SDA = PIN_WIRE_SDA;
  static const uint8_t SCL = PIN_WIRE_SCL;

  // Secondary I2C pins (I2C1) - SERCOM3
  #define PIN_WIRE1_SDA       (26u)  // D2
  #define PIN_WIRE1_SCL       (27u)  // D3
  #define PERIPH_WIRE1        sercom3
  #define WIRE1_IT_HANDLER    SERCOM3_Handler 

  static const uint8_t SDA1 = PIN_WIRE1_SDA;
  static const uint8_t SCL1 = PIN_WIRE1_SCL;
#endif



/*
 * SPI Interfaces
 */
#define SPI_INTERFACES_COUNT 2

  // Primary SPI pins (SPI) - SERCOM1
  #define PIN_SPI_MOSI         (28u)  // D1
  #define PIN_SPI_SCK          (29u)  // D11
  #define PIN_SPI_MISO         (30)   // D2
  #define PIN_SPI_SS           (17u)  // A3
  #define PERIPH_SPI           sercom1
  #define PAD_SPI_TX           SPI_PAD_3_SCK_1 // MOSI - SCK
  #define PAD_SPI_RX           SERCOM_RX_PAD_2 // MISO

  static const uint8_t MOSI = PIN_SPI_MOSI ;
  static const uint8_t SCK  = PIN_SPI_SCK  ;
  static const uint8_t MISO = PIN_SPI_MISO ;
  static const uint8_t SS   = PIN_SPI_SS   ;  

  // Secondary SPI pins (SPI1) - SERCOM0
  #define PIN_SPI1_MOSI        (31u) // A3
  #define PIN_SPI1_SCK         (32u) // A1
  #define PIN_SPI1_MISO        (33u) // A2
  #define PIN_SPI1_SS          NOT_CONNECTED_PIN // NC, UNDEFINED
  #define PERIPH_SPI1          sercom0
  #define PAD_SPI1_TX          SPI_PAD_3_SCK_1 // MOSI1 - SCK1
  #define PAD_SPI1_RX          SERCOM_RX_PAD_2 // MISO1

  static const uint8_t MOSI1 = PIN_SPI1_MOSI ;
  static const uint8_t SCK1  = PIN_SPI1_SCK  ;
  static const uint8_t MISO1 = PIN_SPI1_MISO ;
  static const uint8_t SS1   = PIN_SPI1_SS   ;  // HW SS isn't used. Set here only for reference.


// Needed for SD library, taken from MKRZero variant.h file
// Primary SPI as SDCARD
#define SDCARD_SPI      SPI
#define SDCARD_MOSI_PIN PIN_SPI_MOSI
#define SDCARD_SCK_PIN  PIN_SPI_SCK
#define SDCARD_MISO_PIN PIN_SPI_MISO
#define SDCARD_SS_PIN   PIN_SPI_SS

// On-board SPI Flash
#define EXTERNAL_FLASH_DEVICES  IS25LP016D// GD25Q16C
#define EXTERNAL_FLASH_USE_SPI  SPI
#define EXTERNAL_FLASH_USE_CS   SS



/*
 * USB
 */
#define PIN_USB_HOST_ENABLE   NOT_CONNECTED_PIN
#define PIN_USB_DM            (34ul)
#define PIN_USB_DP            (35ul)



/*
 * I2S Interfaces
 */
#define I2S_INTERFACES_COUNT 1

#define I2S_DEVICE          0
#define I2S_CLOCK_GENERATOR 3
#define PIN_I2S_SD          (17u)  // A3
#define PIN_I2S_SCK         (20u)  // A6
#define PIN_I2S_FS          (21u)  // A7 



#ifdef __cplusplus
}
#endif



/*----------------------------------------------------------------------------
 *        Arduino objects - C++ only
 *----------------------------------------------------------------------------*/

#ifdef __cplusplus

/*	=========================
 *	===== SERCOM DEFINITION
 *	=========================
*/
extern SERCOM sercom0;
extern SERCOM sercom1;
extern SERCOM sercom2;
extern SERCOM sercom3;

extern Uart Serial1;
extern Uart SerialSOK;

#endif

// These serial port names are intended to allow libraries and architecture-neutral
// sketches to automatically default to the correct port name for a particular type
// of use.  For example, a GPS module would normally connect to SERIAL_PORT_HARDWARE_OPEN,
// the first hardware serial port whose RX/TX pins are not dedicated to another use.
//
// SERIAL_PORT_MONITOR        Port which normally prints to the Arduino Serial Monitor
//
// SERIAL_PORT_USBVIRTUAL     Port which is USB virtual serial
//
// SERIAL_PORT_LINUXBRIDGE    Port which connects to a Linux system via Bridge library
//
// SERIAL_PORT_HARDWARE       Hardware serial port, physical RX & TX pins.
//
// SERIAL_PORT_HARDWARE_OPEN  Hardware serial ports which are open for use.  Their RX & TX
//                            pins are NOT connected to anything by default.
#define SERIAL_PORT_MONITOR         Serial
#define SERIAL_PORT_USBVIRTUAL      Serial
#define SERIAL_PORT_HARDWARE_OPEN   Serial1 // & SerialSOK

#endif /* _VARIANT_KITTEN_SYRINGE_DISPLAY_ */

