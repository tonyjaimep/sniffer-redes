#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>

#include <EthernetFrame.hpp>

EthernetFrame::EthernetFrame() {}
EthernetFrame::~EthernetFrame() {}

void EthernetFrame::fromBytes(const char* bytes, const unsigned long& length)
{
	// cada char es un byte
	// las direcciones cuentan con 6 bytes

	setDestinationAddress(
		// cada 00 en hexadecimal significa un byte
		(bytes[0] & 0xFF)	* 0x10000000000 // resulta en bytes[0] 00 00 00 00 00
		| (bytes[1] & 0xFF)	* 0x100000000 // resulta en bytes[0] bytes[1] 00 00 00 00
		| (bytes[2] & 0xFF)	* 0x1000000 // y así
		| (bytes[3] & 0xFF)	* 0x10000
		| (bytes[4] & 0xFF)	* 0x100
		| (bytes[5] & 0xFF)
		// hasta que tenemos un campo de 6 bytes guardado en un unsigned long
	);

	setSourceAddress(
		// cada 00 en hexadecimal significa un byte
		(bytes[6] & 0xFF)	* 0x10000000000 // resulta en bytes[6] 00 00 00 00 00
		| (bytes[7] & 0xFF)	* 0x100000000 // resulta en bytes[6] bytes[7] 00 00 00 00
		| (bytes[8] & 0xFF)	* 0x1000000 // y así
		| (bytes[9] & 0xFF)	* 0x10000
		| (bytes[10] & 0xFF)	* 0x100
		| (bytes[11] & 0xFF)
		// hasta que tenemos un campo de 6 bytes guardado en un unsigned long
	);

	// son dos bytes
	setType(
		(bytes[12] & 0xFF) * 0x100
		| (bytes[13] & 0xFF)
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

void EthernetFrame::setType(const unsigned type)
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

std::string EthernetFrame::addressAsString(const unsigned long address)
{
	// unsigned numBytes = sizeof(bytes);
	std::stringstream resultStream;

	for (unsigned i(1); i <= ETHERNET_ADDRESS_LENGTH; i++) {
		resultStream
			<< std::setfill('0')
			<< std::setw(2)
			<< std::hex
			<< ((address >> ((ETHERNET_ADDRESS_LENGTH - i) * 8)) & 0xFF);

		if (i < ETHERNET_ADDRESS_LENGTH)
			resultStream << ":" ;
	}

	return resultStream.str();
}

std::string EthernetFrame::typeAsString(const unsigned type)
{
	std::string result;
	switch (type) {
	case ETHERNET_TYPE_ARP:
		result = "ARP";
		break;
	case ETHERNET_TYPE_IPV4:
		result = "IPV4";
		break;
	default:
		result = "Desconocido";
		break;
	}

	return result;
}
