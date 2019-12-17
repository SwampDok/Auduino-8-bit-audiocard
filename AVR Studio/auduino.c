#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define uchar unsigned char

#define F_CPU 16000000L
#define BAUDRATE 9600L
#define MY_UBRR (F_CPU / (16 * BAUDRATE) - 1)

signed long int arr[100];

void InitUART () {
	UBRR0H = 0;
	UBRR0L = 8;

	// Авыаыва
	UCSR0B = (1 << TXEN0);
	// Привет Вася
	
	UCSR0C = (3 << UCSZ00);
}

void Send (unsigned char data) {
	while ( !(UCSR0A & (1 << UDRE0)) );
	UDR0 = data;
}

void SendString (uchar *data, uchar length) {
	for (uchar i = 0; i < length; ++i) {
		while ( !(UCSR0A & (1 << UDRE0)) );
		UDR0 = data[i];
	}
}

void SendError (signed long int error) {
	while ( !(UCSR0A & (1 << UDRE0)) );
	UDR0 = (unsigned char) error;

	while ( !(UCSR0A & (1 << UDRE0)) );
	UDR0 = (unsigned char) error >> 8;
	
	while ( !(UCSR0A & (1 << UDRE0)) );
	UDR0 = (unsigned char) error >> 16;

	while ( !(UCSR0A & (1 << UDRE0)) );
	UDR0 = (unsigned char) error >> 24;
	
}

void SendError2 (unsigned char index) {
	while ( !(UCSR0A & (1 << UDRE0)) );
	UDR0 = (unsigned char) arr[index];

	while ( !(UCSR0A & (1 << UDRE0)) );
	UDR0 = (unsigned char) arr[index] >> 8;
	
	while ( !(UCSR0A & (1 << UDRE0)) );
	UDR0 = (unsigned char) arr[index] >> 16;

	while ( !(UCSR0A & (1 << UDRE0)) );
	UDR0 = (unsigned char) arr[index] >> 24;
}

void SendFlag () {
	while ( !(UCSR0A & (1 << UDRE0)) );
	UDR0 = 0xFF;

	while ( !(UCSR0A & (1 << UDRE0)) );
	UDR0 = 0xFF;
	
	while ( !(UCSR0A & (1 << UDRE0)) );
	UDR0 = 0xFF;

	while ( !(UCSR0A & (1 << UDRE0)) );
	UDR0 = 0xFF;
}

int main () {

	

	return 0;
}

