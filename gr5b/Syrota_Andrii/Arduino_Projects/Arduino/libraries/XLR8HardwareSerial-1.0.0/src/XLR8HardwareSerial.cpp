/*
  XLR8HardwareSerial.cpp - Hardware serial library for Wiring
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
  
  Modified 23 November 2006 by David A. Mellis
  Modified 28 September 2010 by Mark Sproul
  Modified 14 August 2012 by Alarus
  Modified 3 December 2013 by Matthijs Kooijman
  Modified 8 May 2018 by Bryan Craker of Alorium Technology
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include "Arduino.h"

#include "XLR8HardwareSerial.h"

/*
// SerialEvent functions are weak, so when the user doesn't define them,
// the linker just sets their address to 0 (which is checked below).
// The Serialx_available is just a wrapper around Serialx.available(),
// but we can refer to it weakly so we don't pull in the entire
// HardwareSerial instance if the user doesn't also refer to it.
*/
void XLR8serialEvent() __attribute__((weak));
bool XLR8Serial_available() __attribute__((weak));

void XLR8serialEventRun(void)
{
  if (XLR8Serial_available && XLR8serialEvent && XLR8Serial_available()) XLR8serialEvent();
}

// Actual interrupt handlers //////////////////////////////////////////////////////////////

void XLR8HardwareSerial::tx_udr_empty_irq(void)
{
  // If interrupts are enabled, there must be more data in the output
  // buffer. Send the next byte
  unsigned char c = _tx_buffer[_tx_buffer_tail];
  _tx_buffer_tail = (_tx_buffer_tail + 1) % SERIAL_TX_BUFFER_SIZE;

  *_udr = c;

  // clear the TXC bit -- "can be cleared by writing a one to its bit
  // location". This makes sure flush() won't return until the bytes
  // actually got written
  *_ucsra |= (1<<TXC0);

  if (_tx_buffer_head == _tx_buffer_tail) {
    // Buffer empty, so disable interrupts
    *_ucsrb &= ~(1<<(UDRIE0));
  }
}

void XLR8HardwareSerial::rx_complete_irq(void)
{
  if (bit_is_clear(*_ucsra, UPE0)) {
    // No Parity error, read byte and store it in the buffer if there is
    // room
    unsigned char c = *_udr;
    rx_buffer_index_t i = (unsigned int)(_rx_buffer_head + 1) % SERIAL_RX_BUFFER_SIZE;

    // if we should be storing the received character into the location
    // just before the tail (meaning that the head would advance to the
    // current location of the tail), we're about to overflow the buffer
    // and so we don't write the character or advance the head.
    if (i != _rx_buffer_tail) {
      _rx_buffer[_rx_buffer_head] = c;
      _rx_buffer_head = i;
    }
  } else {
    // Parity error, read byte but discard it
    *_udr;
  };
}

// Public Methods //////////////////////////////////////////////////////////////

void XLR8HardwareSerial::begin(unsigned long baud, byte config)
{

  // Try u2x mode first
  uint16_t baud_setting = (F_CPU / 4 / baud - 1) / 2;
  *_ucsra = 1 << U2X0;

  // hardcoded exception for 57600 for compatibility with the bootloader
  // shipped with the Duemilanove and previous boards and the firmware
  // on the 8U2 on the Uno and Mega 2560. Also, The baud_setting cannot
  // be > 4095, so switch back to non-u2x mode if the baud rate is too
  // low.
  if (((F_CPU == 16000000UL) && (baud == 57600)) || (baud_setting >4095))
  {
    *_ucsra = 0;
    baud_setting = (F_CPU / 8 / baud - 1) / 2;
  }

  // assign the baud_setting, a.k.a. ubrr (USART Baud Rate Register)
  *_ubrrh = baud_setting >> 8;
  *_ubrrl = baud_setting;

  _written = false;

  //set the data bits, parity, and stop bits
#if defined(__AVR_ATmega8__)
  config |= 0x80; // select UCSRC register (shared with UBRRH)
#endif
  *_ucsrc = config;
  
  *_ucsrb |= (1<<RXEN0);
  *_ucsrb |= (1<<TXEN0);
  *_ucsrb |= (1<<RXCIE0);
  *_ucsrb &= ~(1<<(UDRIE0));
}

void XLR8HardwareSerial::end()
{
  // wait for transmission of outgoing data
  flush();

  *_ucsrb &= ~(1<<(RXEN0));
  *_ucsrb &= ~(1<<(TXEN0));
  *_ucsrb &= ~(1<<(RXCIE0));
  *_ucsrb &= ~(1<<(UDRIE0));
  
  // clear any received data
  _rx_buffer_head = _rx_buffer_tail;
}

int XLR8HardwareSerial::available(void)
{
  return ((unsigned int)(XLR8_SERIAL_RX_BUFFER_SIZE + _rx_buffer_head - _rx_buffer_tail)) % XLR8_SERIAL_RX_BUFFER_SIZE;
}

int XLR8HardwareSerial::peek(void)
{
  if (_rx_buffer_head == _rx_buffer_tail) {
    return -1;
  } else {
    return _rx_buffer[_rx_buffer_tail];
  }
}

int XLR8HardwareSerial::read(void)
{
  // if the head isn't ahead of the tail, we don't have any characters
  if (_rx_buffer_head == _rx_buffer_tail) {
    return -1;
  } else {
    unsigned char c = _rx_buffer[_rx_buffer_tail];
    _rx_buffer_tail = (rx_buffer_index_t)(_rx_buffer_tail + 1) % XLR8_SERIAL_RX_BUFFER_SIZE;
    return c;
  }
}

int XLR8HardwareSerial::availableForWrite(void)
{
#if (XLR8_SERIAL_TX_BUFFER_SIZE>256)
  uint8_t oldSREG = SREG;
  cli();
#endif
  tx_buffer_index_t head = _tx_buffer_head;
  tx_buffer_index_t tail = _tx_buffer_tail;
#if (XLR8_SERIAL_TX_BUFFER_SIZE>256)
  SREG = oldSREG;
#endif
  if (head >= tail) return XLR8_SERIAL_TX_BUFFER_SIZE - 1 - head + tail;
  return tail - head - 1;
}

void XLR8HardwareSerial::flush()
{
  // If we have never written a byte, no need to flush. This special
  // case is needed since there is no way to force the TXC (transmit
  // complete) bit to 1 during initialization
  if (!_written)
    return;

  while (bit_is_set(*_ucsrb, UDRIE0) || bit_is_clear(*_ucsra, TXC0)) {
    if (bit_is_clear(SREG, SREG_I) && bit_is_set(*_ucsrb, UDRIE0))
	// Interrupts are globally disabled, but the DR empty
	// interrupt should be enabled, so poll the DR empty flag to
	// prevent deadlock
	if (bit_is_set(*_ucsra, UDRE0))
	  tx_udr_empty_irq();
  }
  // If we get here, nothing is queued anymore (DRIE is disabled) and
  // the hardware finished tranmission (TXC is set).
}

size_t XLR8HardwareSerial::write(uint8_t c)
{
  _written = true;
  // If the buffer and the data register is empty, just write the byte
  // to the data register and be done. This shortcut helps
  // significantly improve the effective datarate at high (>
  // 500kbit/s) bitrates, where interrupt overhead becomes a slowdown.
  if (_tx_buffer_head == _tx_buffer_tail && bit_is_set(*_ucsra, UDRE0)) {
    *_udr = c;
    *_ucsra |= (1<<TXC0);
    return 1;
  }
  tx_buffer_index_t i = (_tx_buffer_head + 1) % SERIAL_TX_BUFFER_SIZE;
	
  // If the output buffer is full, there's nothing for it other than to 
  // wait for the interrupt handler to empty it a bit
  while (i == _tx_buffer_tail) {
    if (bit_is_clear(SREG, SREG_I)) {
      // Interrupts are disabled, so we'll have to poll the data
      // register empty flag ourselves. If it is set, pretend an
      // interrupt has happened and call the handler to free up
      // space for us.
      if(bit_is_set(*_ucsra, UDRE0))
	tx_udr_empty_irq();
    } else {
      // nop, the interrupt handler will free up space for us
    }
  }

  _tx_buffer[_tx_buffer_head] = c;
  _tx_buffer_head = i;
	
  *_ucsrb |= (1<<UDRIE0);
  
  return 1;
}

