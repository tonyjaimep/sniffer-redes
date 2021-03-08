#include <string.h>
#include <iostream>

#include <EthernetFrame.hpp>

EthernetFrame::EthernetFrame() {}
EthernetFrame::~EthernetFrame() {}

void EthernetFrame::fromBytes(const char* bytes, const unsigned long& length)
{
	// cada char es un byte
	// las direcciones cuentan con 6 bytes
	setDestinationAddress(
		// cada 00 en hexadecimal significa un byte
		bytes[0]	* 0x10000000000 // resulta en bytes[0] 00 00 00 00 00
		+ bytes[1]	* 0x100000000 // resulta en bytes[0] bytes[1] 00 00 00 00
		+ bytes[2]	* 0x1000000 // y así
		+ bytes[3]	* 0x10000
		+ bytes[4]	* 0x100
		+ bytes[5]
		// hasta que tenemos un campo de 6 bytes guardado en un unsigned long
	);

	setSourceAddress(
		// cada 00 en hexadecimal significa un byte
		bytes[6] 	* 0x10000000000 // resulta en bytes[0] 00 00 00 00 00
		+ bytes[7] 	* 0x100000000 // resulta en bytes[0] bytes[1] 00 00 00 00
		+ bytes[8] 	* 0x1000000 // y así
		+ bytes[9] 	* 0x10000
		+ bytes[10] 	* 0x100
		+ bytes[11]
		// hasta que tenemos un campo de 6 bytes guardado en un unsigned long
	);

	// son dos bytes
	setType(
		bytes[12] * 0x100
		+ bytes[13]
	);

	// los primeros 14 bytes no son "data"
	long unsigned dataLength = length - 14;

	char data[dataLength];

	memcpy(data, bytes + 14, dataLength);

	setData(data);
}

char* EthernetFrame::getData() const
{ 
	return this->data;
}

void EthernetFrame::setData(char* data)
{
	this->data = data;
}

unsigned long EthernetFrame::getType() const
{
	return this->type;
}

void EthernetFrame::setType(const unsigned long type)
{
	this->type = type;
}
	
unsigned long EthernetFrame::getDestinationAddress() const
{
	return this->destinationAddress;
}

void EthernetFrame::setDestinationAddress(const unsigned long destinationAddress)
{
	this->destinationAddress = destinationAddress;
}

unsigned long EthernetFrame::getSourceAddress() const
{
	return this->sourceAddress;
}

void EthernetFrame::setSourceAddress(const unsigned long sourceAddress)
{
	this->sourceAddress = sourceAddress;
}



