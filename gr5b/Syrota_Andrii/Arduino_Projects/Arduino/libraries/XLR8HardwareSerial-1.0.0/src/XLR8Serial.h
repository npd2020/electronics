// Requires the XLR8AddrPack be installed
#include <XLR8AddrPack.h>
#include <XLR8HardwareSerial.h>

#define OPENXLR8_vect ANALOG_COMP_vect

// Default UART register addresses
#define XB_USART_BAUDCTRLA_ADR 0xE4
#define XB_USART_BAUDCTRLB_ADR 0xE5
#define XB_USART_CTRLA_ADR     0xE1
#define XB_USART_CTRLB_ADR     0xE2
#define XB_USART_CTRLC_ADR     0xE3
#define XB_USART_RXB_TXB_ADR   0xE0

// Set up the XLR8 interrupt control registers
#define XICR_Reg    _SFR_MEM8(XICR_Address)
#define XMSK_Reg    _SFR_MEM8(XMSK_Address)
#define XACK_Reg    _SFR_MEM8(XACK_Address)
#define XIFR_Reg    _SFR_MEM8(XIFR_Address)
#define OX8ICR_Reg  _SFR_MEM8(OX8ICR_Address)
#define OX8MSK_Reg  _SFR_MEM8(OX8MSK_Address)
#define OX8IFR_Reg  _SFR_MEM8(OX8IFR_Address)

// Default XLR8HardwareSerial instance
XLR8HardwareSerial XLR8Serial(
        XB_USART_BAUDCTRLB_ADR,
        XB_USART_BAUDCTRLA_ADR,
        XB_USART_CTRLA_ADR,
        XB_USART_CTRLB_ADR,
        XB_USART_CTRLC_ADR,
        XB_USART_RXB_TXB_ADR);

// Enable the interrupts
void enableSerialInterrupts() {
  XICR_Reg |= 0x02;
  XMSK_Reg |= 0x02;
  OX8ICR_Reg |= 0x07;
  OX8MSK_Reg |= 0x07;
}

// Handle the UART interrupts
ISR (OPENXLR8_vect) {
  uint8_t flags = OX8IFR_Reg;
  if (flags & 0x01) {
    XLR8Serial.rx_complete_irq();
    OX8IFR_Reg = 0x01;
  }
  if (flags & 0x02) {
    XLR8Serial.tx_udr_empty_irq();
    OX8IFR_Reg = 0x02;
  }
  XACK_Reg = 0x02;
  XIFR_Reg = 0x02;
}

