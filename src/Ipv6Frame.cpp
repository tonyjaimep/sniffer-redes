#include "../include/Ipv6Frame.hpp"

#include <string>
#include <sstream>
#include <iomanip>
#include <iostream>

Ipv6Frame::Ipv6Frame() {}
Ipv6Frame::~Ipv6Frame() {}

void Ipv6Frame::fromBytes(const unsigned char* bytes)
{
	unsigned char addressBuffer[IPV6_STD_ADDRESS_LENGTH];
	unsigned payloadLengthBuffer = bytes[4] * 0x100 + bytes[5];

	setVersion(bytes[0] >> 4);
	setTrafficClass(((bytes[0] & 0xF) << 4) + (bytes[1] >> 4));
	setFlowLabel((bytes[1] >> 4) * 0x10000 + (bytes[2] * 0x100) + bytes[3]);
	setPayloadLength(payloadLengthBuffer);
	setNextHeader(bytes[6]);
	setHopLimit(bytes[7]);

	char* payloadBuffer = (char*)malloc(payloadLengthBuffer);

	for (unsigned i(0); i < IPV6_STD_ADDRESS_LENGTH; i++) {
		addressBuffer[i] = bytes[8 + i];
	}

	setSourceAddress(addressBuffer);

	for (unsigned i(0); i < IPV6_STD_ADDRESS_LENGTH; i++) {
		addressBuffer[i] = bytes[24 + i];
	}

	setDestinationAddress(addressBuffer);

	for (unsigned i(0); i < payloadLengthBuffer; i++) {
		payloadBuffer[i] = bytes[40 + i];
	}

	setPayload(payloadBuffer, payloadLengthBuffer);
	delete payloadBuffer;
}

std::string Ipv6Frame::addressToString(const unsigned char* address)
{
	std::stringstream ss;

	for (unsigned i(0); i < IPV6_STD_ADDRESS_LENGTH; i++) {
		if (i != 0 && i % 2 == 0)
			ss << ':';
		ss << std::hex << std::setw(2) << std::setfill('0') << (unsigned)address[i];
	}

	return ss.str();
}

std::string Ipv6Frame::getTrafficClassAsString() const
{
	return "Traffic class";
}

const char* Ipv6Frame::getPayload() const { return payload; }

unsigned Ipv6Frame::getVersion() const
{
	return version;
}

unsigned Ipv6Frame::getTrafficClass() const
{
	return trafficClass;
}

unsigned Ipv6Frame::getFlowLabel() const
{
	return flowLabel;
}

unsigned Ipv6Frame::getPayloadLength() const
{
	return payloadLength;
}

unsigned Ipv6Frame::getNextHeader() const {
	return nextHeader;
}

unsigned Ipv6Frame::getHopLimit() const
{
	return hopLimit;
}

unsigned char* Ipv6Frame::getSourceAddress()
{
	return sourceAddress;
}

unsigned char* Ipv6Frame::getDestinationAddress()
{
	return destinationAddress;
}

void Ipv6Frame::setVersion(const unsigned& val)
{
	version = val;
}

void Ipv6Frame::setTrafficClass(const unsigned& val)
{
	trafficClass = val;
}

void Ipv6Frame::setFlowLabel(const unsigned& val)
{
	flowLabel = val;
}

void Ipv6Frame::setPayloadLength(const unsigned& val)
{
	payloadLength = val;
}

void Ipv6Frame::setNextHeader(const unsigned& val)
{
	nextHeader = val;
}

void Ipv6Frame::setHopLimit(const unsigned& val)
{
	hopLimit = val;
}

void Ipv6Frame::setSourceAddress(const unsigned char* val)
{
	for (unsigned i(0); i < IPV6_STD_ADDRESS_LENGTH; i++) {
		sourceAddress[i] = val[i];
	}
}

void Ipv6Frame::setDestinationAddress(const unsigned char* val)
{
	for (unsigned i(0); i < IPV6_STD_ADDRESS_LENGTH; i++) {
		destinationAddress[i] = val[i];
	}
}

void Ipv6Frame::setPayload(const char* bytes, const unsigned& size)
{
	payload = (char*)malloc(size);

	for (unsigned i(0); i < size; i++) {
		payload[i] = bytes[i];
	}
}
