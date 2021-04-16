#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>

#include "../include/EthernetFrame.hpp"

EthernetFrame::EthernetFrame() {}
EthernetFrame::~EthernetFrame() {}

void EthernetFrame::fromBytes(const char* bytes, const unsigned long& length)
{
	// cada char es un byte
	// las direcciones cuentan con 6 bytes
	//
	setDestinationAddress(
		(((unsigned long)bytes[0] & 0xFF)	<< (5 * 8))
		+ (((unsigned long)bytes[1] & 0xFF)	<< (4 * 8))
		+ ((bytes[2] & 0xFF)			<< (3 * 8))
		+ ((bytes[3] & 0xFF)			<< (2 * 8))
		+ ((bytes[4] & 0xFF)			<< 8)
		+ ((bytes[5] & 0xFF))
	);

	setSourceAddress(
		(((unsigned long)bytes[6] & 0xFF)	<< (5 * 8))
		+ (((unsigned long)bytes[7] & 0xFF)	<< (4 * 8))
		+ ((bytes[8] & 0xFF)			<< (3 * 8))
		+ ((bytes[9] & 0xFF)			<< (2 * 8))
		+ ((bytes[10] & 0xFF)			<< 8)
		+ ((bytes[11] & 0xFF))
	);

	// son dos bytes
	setType(
		(bytes[12] & 0xFF) * 0x100
		| (bytes[13] & 0xFF)
	);

	// los primeros 14 bytes no son "data"
	size_t dataLength = length - 14;

	char dataBuffer[dataLength];

	for (unsigned i(0); i < dataLength; i++) {
		dataBuffer[i] = bytes[i + 14];
	}

	setData(dataBuffer, dataLength);
}

char* EthernetFrame::getData() const
{
	return this->data;
}

void EthernetFrame::setData(const char* value, size_t dataLength)
{
	data = static_cast<char*>(malloc(dataLength));

	for (unsigned i(0); i < dataLength; i++) {
		data[i] = value[i];
	}
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
	case ETHERNET_TYPE_RARP:
		result = "RARP";
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
