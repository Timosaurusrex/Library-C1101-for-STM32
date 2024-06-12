/******************************************************************************
  * @copyright HTL - HOLLABRUNN  2023-2024 All rights reserved
  * @file    funkmodul_header.h 
  * @author  Perzi Timo, Germin Timon
  * @version V1.0.0
  * @date    11-06-2024
  * @brief   Header File for prototypes and bitbanding for CC1101
  *****************************************************************************/

#ifndef CC1101_H
#define CC1101_H

#include "stm32f10x.h"

/*---------------------------- Prototypes ----------------------------------*/
void uart3_init(void);
void uart_put_char(char zeichen);
void uart_put_string(char * string);
void waitloop_10us(int us);

void SPI1_Init(void);
void CC1101_init(void);
void reset_CC1101(void);
uint8_t SPI1_Transfer(uint8_t data);
uint8_t SpiReadStatus(uint8_t addr);
void SpiWriteReg(uint8_t addr, uint8_t value);
void SpiWriteBurstReg(uint8_t addr, uint8_t *buffer, uint8_t num);
void SpiStrobe(uint8_t strobe);
uint8_t SpiReadReg(uint8_t addr);
void SpiReadBurstReg(uint8_t addr, uint8_t *buffer, uint8_t num);

void SendData(uint8_t *txBuffer,uint8_t size);
void SetReceive(void);
uint8_t ReceiveData(uint8_t *rxBuffer);
uint8_t CheckReceiveFlag(void);
void RegConfigSettings(char f);

void ClockConfig(void);
void TIM3_Config(void);
void NVIC_init(char position, char priority);

/*---------------------------- General Definitions ----------------------------------*/
// Calc Bit Band Adress from peripheral address: 
// a = peripheral address, b = Bit number
#define BITBAND_PERI(a,b) ((PERIPH_BB_BASE + (a - PERIPH_BASE) * 32 + (b * 4)))

// Bit Band Alias Adresse for port PA0
#define GPIOA_ODR GPIOA_BASE + 3 * sizeof(uint32_t)  // Calc peripheral address GPIOA ODR
#define GPIOA_IDR GPIOA_BASE + 2 * sizeof(uint32_t)  // Calc peripheral address GPIOA IDR

#define CSN_PIN *((volatile unsigned long *)(BITBAND_PERI(GPIOA_ODR, 4))) // PA4
#define SCK_PIN *((volatile unsigned long *)(BITBAND_PERI(GPIOA_ODR, 5))) // PA5
#define MISO_PIN *((volatile unsigned long *)(BITBAND_PERI(GPIOA_IDR, 6))) // PA6 
#define MOSI_PIN *((volatile unsigned long *)(BITBAND_PERI(GPIOA_ODR, 7))) // PA7
#define GDO0 *((volatile unsigned long *)(BITBAND_PERI(GPIOA_IDR, 0))) // PA0
#define GDO2 *((volatile unsigned long *)(BITBAND_PERI(GPIOA_IDR, 1))) // PA1

// Initialisierungskonstanten
#define F_915       0x00
#define F_433       0x01
#define F_868       0x02

// Registerwerte f�r verschiedene Frequenzen
// Tr�gerfrequenz = 868 MHz
#define F2_868  0x21        
#define F1_868  0x62        
#define F0_868  0x76       
// Tr�gerfrequenz = 902 MHz
#define F2_915  0x22        
#define F1_915  0xB1        
#define F0_915  0x3B       
// Tr�gerfrequenz = 433 MHz
#define F2_433  0x10       
#define F1_433  0xA7        
#define F0_433  0x62

#define 	WRITE_BURST     	0x40					// Schreib-Burst
#define 	READ_SINGLE     	0x80					// Einzelnes Lesen
#define 	READ_BURST      	0xC0					// Lese-Burst
#define 	BYTES_IN_RXFIFO   0x7F  				// Anzahl der Bytes im RXFIFO

#define CC1101_IOCFG2       0x00        // GDO2 output pin configuration
#define CC1101_IOCFG1       0x01        // GDO1 output pin configuration
#define CC1101_IOCFG0       0x02        // GDO0 output pin configuration
#define CC1101_FIFOTHR      0x03        // RX FIFO and TX FIFO thresholds
#define CC1101_SYNC1        0x04        // Sync word, high INT8U
#define CC1101_SYNC0        0x05        // Sync word, low INT8U
#define CC1101_PKTLEN       0x06        // Packet length
#define CC1101_PKTCTRL1     0x07        // Packet automation control
#define CC1101_PKTCTRL0     0x08        // Packet automation control
#define CC1101_ADDR         0x09        // Device address
#define CC1101_CHANNR       0x0A        // Channel number
#define CC1101_FSCTRL1      0x0B        // Frequency synthesizer control
#define CC1101_FSCTRL0      0x0C        // Frequency synthesizer control
#define CC1101_FREQ2        0x0D        // Frequency control word, high INT8U
#define CC1101_FREQ1        0x0E        // Frequency control word, middle INT8U
#define CC1101_FREQ0        0x0F        // Frequency control word, low INT8U
#define CC1101_MDMCFG4      0x10        // Modem configuration
#define CC1101_MDMCFG3      0x11        // Modem configuration
#define CC1101_MDMCFG2      0x12        // Modem configuration
#define CC1101_MDMCFG1      0x13        // Modem configuration
#define CC1101_MDMCFG0      0x14        // Modem configuration
#define CC1101_DEVIATN      0x15        // Modem deviation setting
#define CC1101_MCSM2        0x16        // Main Radio Control State Machine configuration
#define CC1101_MCSM1        0x17        // Main Radio Control State Machine configuration
#define CC1101_MCSM0        0x18        // Main Radio Control State Machine configuration
#define CC1101_FOCCFG       0x19        // Frequency Offset Compensation configuration
#define CC1101_BSCFG        0x1A        // Bit Synchronization configuration
#define CC1101_AGCCTRL2     0x1B        // AGC control
#define CC1101_AGCCTRL1     0x1C        // AGC control
#define CC1101_AGCCTRL0     0x1D        // AGC control
#define CC1101_WOREVT1      0x1E        // High INT8U Event 0 timeout
#define CC1101_WOREVT0      0x1F        // Low INT8U Event 0 timeout
#define CC1101_WORCTRL      0x20        // Wake On Radio control
#define CC1101_FREND1       0x21        // Front end RX configuration
#define CC1101_FREND0       0x22        // Front end TX configuration
#define CC1101_FSCAL3       0x23        // Frequency synthesizer calibration
#define CC1101_FSCAL2       0x24        // Frequency synthesizer calibration
#define CC1101_FSCAL1       0x25        // Frequency synthesizer calibration
#define CC1101_FSCAL0       0x26        // Frequency synthesizer calibration
#define CC1101_RCCTRL1      0x27        // RC oscillator configuration
#define CC1101_RCCTRL0      0x28        // RC oscillator configuration
#define CC1101_FSTEST       0x29        // Frequency synthesizer calibration control
#define CC1101_PTEST        0x2A        // Production test
#define CC1101_AGCTEST      0x2B        // AGC test
#define CC1101_TEST2        0x2C        // Various test settings
#define CC1101_TEST1        0x2D        // Various test settings
#define CC1101_TEST0        0x2E        // Various test settings

//CC1101 Strobe commands
#define CC1101_SRES         0x30        // Reset chip.
#define CC1101_SFSTXON      0x31        // Enable and calibrate frequency synthesizer (if MCSM0.FS_AUTOCAL=1).
                                        // If in RX/TX: Go to a wait state where only the synthesizer is
                                        // running (for quick RX / TX turnaround).
#define CC1101_SXOFF        0x32        // Turn off crystal oscillator.
#define CC1101_SCAL         0x33        // Calibrate frequency synthesizer and turn it off
                                        // (enables quick start).
#define CC1101_SRX          0x34        // Enable RX. Perform calibration first if coming from IDLE and
                                        // MCSM0.FS_AUTOCAL=1.
#define CC1101_STX          0x35        // In IDLE state: Enable TX. Perform calibration first if
                                        // MCSM0.FS_AUTOCAL=1. If in RX state and CCA is enabled:
                                        // Only go to TX if channel is clear.
#define CC1101_SIDLE        0x36        // Exit RX / TX, turn off frequency synthesizer and exit
                                        // Wake-On-Radio mode if applicable.
#define CC1101_SAFC         0x37        // Perform AFC adjustment of the frequency synthesizer
#define CC1101_SWOR         0x38        // Start automatic RX polling sequence (Wake-on-Radio)
#define CC1101_SPWD         0x39        // Enter power down mode when CSn goes high.
#define CC1101_SFRX         0x3A        // Flush the RX FIFO buffer.
#define CC1101_SFTX         0x3B        // Flush the TX FIFO buffer.
#define CC1101_SWORRST      0x3C        // Reset real time clock.
#define CC1101_SNOP         0x3D        // No operation. May be used to pad strobe commands to two
                                        // INT8Us for simpler software.
//CC1101 STATUS REGSITER
#define CC1101_PARTNUM      0x30
#define CC1101_VERSION      0x31
#define CC1101_FREQEST      0x32
#define CC1101_LQI          0x33
#define CC1101_RSSI         0x34
#define CC1101_MARCSTATE    0x35
#define CC1101_WORTIME1     0x36
#define CC1101_WORTIME0     0x37
#define CC1101_PKTSTATUS    0x38
#define CC1101_VCO_VC_DAC   0x39
#define CC1101_TXBYTES      0x3A
#define CC1101_RXBYTES      0x3B

// CC1101 PATABLE, TXFIFO, RXFIFO Registeradressen
#define CC1101_PATABLE      0x3E
#define CC1101_TXFIFO       0x3F
#define CC1101_RXFIFO       0x3F

#endif /* CC1101_H */
