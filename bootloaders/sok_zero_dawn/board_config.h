#ifndef BOARD_CONFIG_H
#define BOARD_CONFIG_H

#define VENDOR_NAME "NeKuNeKo Inc."
#define PRODUCT_NAME "SoK Zero Dawn (SAMD21)"
#define VOLUME_LABEL "SOK-M0-BOOT"
#define INDEX_URL "https://github.com/nekuneko/"
#define BOARD_ID "SAMD21J18A-SoK-Zero-Dawn"

#define USB_VID 0x1993
#define USB_PID 0x0119

#define LED_PIN PIN_PA16


#define BOOT_USART_MODULE SERCOM0
#define BOOT_USART_MASK APBAMASK
#define BOOT_USART_BUS_CLOCK_INDEX MCLK_APBAMASK_SERCOM0
#define BOOT_USART_PAD_SETTINGS UART_RX_PAD1_TX_PAD0
#define BOOT_USART_PAD3 PINMUX_UNUSED
#define BOOT_USART_PAD2 PINMUX_UNUSED
#define BOOT_USART_PAD1 PINMUX_PA05D_SERCOM0_PAD1
#define BOOT_USART_PAD0 PINMUX_PA04D_SERCOM0_PAD0
#define BOOT_GCLK_ID_CORE SERCOM0_GCLK_ID_CORE
#define BOOT_GCLK_ID_SLOW SERCOM0_GCLK_ID_SLOW

#endif
