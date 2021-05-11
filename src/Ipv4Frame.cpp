#include "../include/Ipv4Frame.hpp"
#include <sstream>
#include <iostream>

using namespace std;

Ipv4Frame::Ipv4Frame() : payload(nullptr) { }

Ipv4Frame::~Ipv4Frame() { }

unsigned Ipv4Frame::getPayloadLength() const
{
	if (getTotalLength() == 0)
		return 0;

	return getTotalLength() - getIhl() * getVersion();
}

void Ipv4Frame::fromBytes(const char* frameBytes)
{
	setVersion(frameBytes[0] >> 4);
	setIhl(frameBytes[0] & 0xF);
	setService(frameBytes[1]);
	setTotalLength((frameBytes[2] << 8) + frameBytes[3]);
	setId(frameBytes[4] * 0x100 + frameBytes[5]);
	setDf((frameBytes[6] >> 6) & 1);
	setMf((frameBytes[6] >> 7) & 1);
	setOffset((frameBytes[6] & 0b11111) * 0x10 + frameBytes[7]);
	setTtl(frameBytes[8]);
	setProtocol(frameBytes[9]);
	setCheckSum(frameBytes[10] * 0x100 + static_cast<uint8_t>(frameBytes[11]));
	setSourceAddress((frameBytes[12] << 24) + (frameBytes[13] << 16) + (frameBytes[14] << 8) + (frameBytes[15]));
	setDestinationAddress((frameBytes[16] << 24) + (frameBytes[17] << 16) + (frameBytes[18] << 8) + (frameBytes[19]));

	// si el paquete tiene opciones
	if (getIhl() * getVersion() > 20) {
		unsigned optionsSize(getIhl() * getVersion() - 20);
		char optionsOnBytes[optionsSize];

		for (unsigned i(0); i < optionsSize; i++) {
			optionsOnBytes[i] = frameBytes[i + 19];
		}
		setOptions(optionsOnBytes);
	}

	if ((getIhl() * getVersion()) < getTotalLength()) {
		const unsigned payloadStartByte = getIhl() * getVersion();
		char payloadOnBytes[getPayloadLength()];

		for (unsigned i(0); i < getPayloadLength(); i++) {
			payloadOnBytes[i] = frameBytes[i + payloadStartByte];
		}

		setPayload(payloadOnBytes);
	}
}

string Ipv4Frame::addressToString(const unsigned& address)
{
	stringstream ss;
	ss << (address / 0x1000000);
	ss << '.';
	ss << (address / 0x10000 & 0x0000FF);
	ss << '.';
	ss << (address / 0x100 & 0x00FF);
	ss << '.';
	ss << (address & 0xFF);
	return ss.str();
}

string Ipv4Frame::getSourceAddressAsString() const
{
	return addressToString(getSourceAddress());
}

string Ipv4Frame::getDestinationAddressAsString() const
{
	return addressToString(getDestinationAddress());
}

void Ipv4Frame::setVersion(const unsigned& value)
{
	version = value;
}

void Ipv4Frame::setIhl(const unsigned& value)
{
	ihl = value;
}

void Ipv4Frame::setService(const unsigned& value)
{
	service = value;
}

void Ipv4Frame::setTotalLength(const unsigned& value)
{
	totalLength = value;
}

void Ipv4Frame::setId(const unsigned& value)
{
	id = value;
}

void Ipv4Frame::setDf(const bool& value)
{
	df=value;
}

void Ipv4Frame::setMf(const bool& value)
{
	mf = value;
}

void Ipv4Frame::setOffset(const unsigned& value)
{
	offset = value;
}

void Ipv4Frame::setTtl(const unsigned& value)
{
	ttl = value;
}

void Ipv4Frame::setProtocol(const unsigned& value)
{
	protocol = value;
}

void Ipv4Frame::setSourceAddress(const unsigned& value)
{
	sourceAddress = value;
}

void Ipv4Frame::setDestinationAddress(const unsigned& value)
{
	destinationAddress = value;
}

void Ipv4Frame::setOptions(const char* value)
{
	options = value;
}

void Ipv4Frame::setPayload(const char* value)
{
	if (payload != nullptr)
		delete payload;

	payload = static_cast<char*>(malloc(getPayloadLength()));

	for (unsigned i=0; i < getPayloadLength(); i++) {
		payload[i] = value[i];
	}
}

unsigned Ipv4Frame::getVersion() const
{
	return version;
}

unsigned Ipv4Frame::getIhl() const
{
	return ihl;
}

unsigned Ipv4Frame::getService() const
{
	return service;
}

unsigned Ipv4Frame::getTotalLength() const
{
	return totalLength;
}

unsigned Ipv4Frame::getId() const
{
	return id;
}

bool Ipv4Frame::getDf() const
{
	return df;
}

bool Ipv4Frame::getMf() const
{
	return mf;
}

unsigned Ipv4Frame::getOffset() const
{
	return offset;
}

unsigned Ipv4Frame::getTtl() const
{
	return ttl;
}

unsigned Ipv4Frame::getProtocol() const
{
	return protocol;
}

const unsigned Ipv4Frame::getSourceAddress() const
{
	return sourceAddress;
}

const unsigned Ipv4Frame::getDestinationAddress() const
{
	return destinationAddress;
}

unsigned Ipv4Frame::getCheckSum() const
{
	return checkSum;
}

/*unsigned Ipv4Frame::getPrecedence() const
{

}

unsigned Ipv4Frame::getDelay() const
{

}

unsigned Ipv4Frame::getThroughput() const
{

}

unsigned Ipv4Frame::getReliability() const
{

}

unsigned Ipv4Frame::getReservedTosBits() const
{

}*/

const char* Ipv4Frame::getOptions(void) const
{
	return options;
}

const char* Ipv4Frame::getPayload(void) const
{
	return payload;
}

void Ipv4Frame::setCheckSum(const unsigned& cs)
{
	checkSum = cs;
}

std::string Ipv4Frame::protocolToString(const unsigned& value)
{
	switch (value) {
	case IP_PROTOCOL_HOPOPT:
		return "HOPOPT";
	case IP_PROTOCOL_ICMP:
		return "ICMP";
	case IP_PROTOCOL_IGMP:
		return "IGMP";
	case IP_PROTOCOL_TCP:
		return "TCP";
	case IP_PROTOCOL_IP_IN_IP:
		return "IP in IP";
	case IP_PROTOCOL_ICMPV6:
		return "ICMPv6";
	case IP_PROTOCOL_NONXT:
		return "No Next Header";
	case IP_PROTOCOL_OPTS:
		return "IPv6 Options";
	default:
		return "Desconocido";
	}
}

std::string Ipv4Frame::dscpToString(const unsigned& dscp)
{
	/*
	*
	* CS0 		0 		0: Best Effort
	* LE 		1 		n/a
	* CS1, AF11-13 	8,10,12,14 	1: Priority
	* CS2, AF21-23 	16,18,20,22 	2: Immediate
	* CS3, AF31-33 	24,26,28,30 	3: Flash - mainly used for voice signaling
	* CS4, AF41-43 	32,34,36,38 	4: Flash Override
	* CS5, EF 	40,46 		5: Critical - mainly used for voice RTP
	* CS6 		48 		6: Internetwork Control
	* CS7 		56 		7: Network Control
	*/

	switch (dscp) {
		case 0:
			return "CS0 (Best Effort)";
		case 1:
			return "LE (N/A)";
		case 8: case 10: case 12: case 14:
			return "CS1 (Priority)";
		case 16: case 18: case 20: case 22:
			return "CS2 (Immediate)";
		case 24: case 26: case 28: case 30:
			return "CS3 (Flash)";
		case 32: case 34: case 36: case 38:
			return "CS4 (Flash Override)";
		case 40: case 46:
			return "CS5 (Critical)";
		case 48:
			return "CS6 (Internetwork Control)";
		case 56:
			return "CS7 (Network Control)";
		default:
			return "Desconocido";
	}
}

std::string Ipv4Frame::ecnToString(const unsigned& ecn) {
	switch (ecn) {
		case 0b00:
			return "Non ECN-Capable Transport, Non-ECT";
		case 0b10:
			return "ECN Capable Transport, ECT(0)";
		case 0b01:
			return "ECN Capable Transport, ECT(1)";
		case 0b11:
			return "Congestion Encountered, CE";
		default:
			return "Desconocido";
	}
}

std::string Ipv4Frame::getProtocolAsString() const
{
	return protocolToString(getProtocol());
}

std::string Ipv4Frame::getDscpAsString() const
{
	return dscpToString(getService() >> 2);
}

std::string Ipv4Frame::getEcnAsString() const
{
	return ecnToString(getService() & 0b11);
}
