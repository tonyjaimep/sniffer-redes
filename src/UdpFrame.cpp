#include <sstream>
#include <iomanip>
#include <iostream>
#include "../include/UdpFrame.hpp"

UdpFrame::UdpFrame() : payload(nullptr) {};
UdpFrame::~UdpFrame() {};

void UdpFrame::fromBytes(const char* frameBytes)
{
	setSourcePort((frameBytes[0] & 0xFF) * 0x100 + (frameBytes[1] & 0xFF));
	setDestinationPort((frameBytes[2] & 0xFF) * 0x100 + (frameBytes[3] & 0xFF));
	setLength((frameBytes[4] & 0xFF) * 0x100 + (frameBytes[5] & 0xFF));
	setCheckSum((frameBytes[6] & 0xFF) * 0x100 + (frameBytes[7] & 0xFF));
	setPayload(frameBytes);
}

void UdpFrame::setSourcePort(const unsigned& value) { sourcePort = value; }
void UdpFrame::setDestinationPort(const unsigned& value) { destinationPort = value; }
void UdpFrame::setLength(const unsigned& value) { length = value; }
void UdpFrame::setCheckSum(const unsigned& value) { checksum = value; }
void UdpFrame::setPayload(const char* p)
{
	if (payload != nullptr)
		delete payload;

	payload = (char*)malloc(getLength() - 8);

	for (unsigned i(0); i < getLength(); i++)
		payload[i] = p[i + 8];
}

unsigned UdpFrame::getSourcePort() const { return sourcePort; }
unsigned UdpFrame::getDestinationPort() const { return destinationPort; }
unsigned UdpFrame::getLength() const { return length; }
unsigned UdpFrame::getCheckSum() const { return checksum; }
char* UdpFrame::getPayload() const { return payload; }
