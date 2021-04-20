#include "../include/ArpFrame.hpp"
#include <sstream>

ArpFrame::ArpFrame() {}
ArpFrame::~ArpFrame() {}

void ArpFrame::fromBytes(const char* bytes)
{
	setHardwareType(bytes[0] * 0x100 + bytes[1]);
	setProtocolType(bytes[2] * 0x100 + bytes[3]);
	setHardwareAddressLength(bytes[4]);
	setProtocolAddressLength(bytes[5]);

	setOperation(bytes[6] * 0x100 + bytes[7]);

	setSenderHardwareAddress(
		(((unsigned long)bytes[8] & 0xFF)	<< (5 * 8))
		+ (((unsigned long)bytes[9] & 0xFF)	<< (4 * 8))
		+ ((bytes[10] & 0xFF)			<< (3 * 8))
		+ ((bytes[11] & 0xFF)			<< (2 * 8))
		+ ((bytes[12] & 0xFF)			<< 8)
		+ ((bytes[13] & 0xFF))
	);

	setSenderProtocolAddress(
		((bytes[14] & 0xFF)			<< (3 * 8))
		+ ((bytes[15] & 0xFF)			<< (2 * 8))
		+ ((bytes[16] & 0xFF)			<< 8)
		+ ((bytes[17] & 0xFF))
	);

	setTargetHardwareAddress(
		(((unsigned long)bytes[18] & 0xFF)	<< (5 * 8))
		+ (((unsigned long)bytes[19] & 0xFF)	<< (4 * 8))
		+ ((bytes[20] & 0xFF)			<< (3 * 8))
		+ ((bytes[21] & 0xFF)			<< (2 * 8))
		+ ((bytes[22] & 0xFF)			<< 8)
		+ ((bytes[23] & 0xFF))
	);

	setSenderProtocolAddress(
		((bytes[24] & 0xFF)			<< (3 * 8))
		+ ((bytes[25] & 0xFF)			<< (2 * 8))
		+ ((bytes[26] & 0xFF)			<< 8)
		+ ((bytes[27] & 0xFF))
	);
}

void ArpFrame::setHardwareType(unsigned long value)
{
	hardwareType = value;
}

void ArpFrame::setProtocolType(unsigned long value)
{
	protocolType = value;
}

void ArpFrame::setHardwareAddressLength(unsigned long value)
{
	hardwareAddressLength = value;
}

void ArpFrame::setProtocolAddressLength(unsigned long value)
{
	protocolAddressLength = value;
}

void ArpFrame::setOperation(unsigned long value)
{
	operation = value;
}

void ArpFrame::setSenderHardwareAddress(unsigned long value)
{
	senderHardwareAddress = value;
}

void ArpFrame::setSenderProtocolAddress(unsigned long value)
{
	senderProtocolAddress = value;
}

void ArpFrame::setTargetHardwareAddress(unsigned long value)
{
	targetHardwareAddress = value;
}

void ArpFrame::setTargetProtocolAddress(unsigned long value)
{
	targetProtocolAddress = value;
}

unsigned long ArpFrame::getHardwareType() const { return hardwareType; }
unsigned long ArpFrame::getProtocolType() const { return protocolType; }
unsigned long ArpFrame::getHardwareAddressLength() const { return hardwareAddressLength; }
unsigned long ArpFrame::getProtocolAddressLength() const { return protocolAddressLength; }
unsigned long ArpFrame::getOperation() const { return operation; }
unsigned long ArpFrame::getSenderHardwareAddress() const { return senderHardwareAddress; }
unsigned long ArpFrame::getSenderProtocolAddress() const { return senderProtocolAddress; }
unsigned long ArpFrame::getTargetHardwareAddress() const { return targetHardwareAddress; }
unsigned long ArpFrame::getTargetProtocolAddress() const { return targetProtocolAddress; }

std::string ArpFrame::hardwareTypeAsString(unsigned long hardwareType)
{
	switch (hardwareType)
	{
		case ARP_HTYPE_ETHERNET:
			return "Ethernet";
		default:
			return "Desconocido";
	}
}

std::string ArpFrame::protocolTypeAsString(unsigned long protocolType)
{
	switch (protocolType)
	{
		case ARP_PTYPE_IPV4:
			return "IPv4";
		default:
			return "Desconocido";
	}
}

std::string ArpFrame::addressToString(const unsigned& address)
{
	std::stringstream ss;
	ss << (address / 0x1000000);
	ss << '.';
	ss << (address / 0x10000 & 0x0000FF);
	ss << '.';
	ss << (address / 0x100 & 0x00FF);
	ss << '.';
	ss << (address & 0xFF);
	return ss.str();
}

std::string ArpFrame::operationAsString(const unsigned& op)
{
	switch (op) {
	case 0:
		return "Reservado";
	case 1:
		return "Solicitud";
	case 2:
		return "Respuesta";
	case 3:
		return "Solicitud RARP";
	case 4:
		return "Respuesta RARP";
	case 5:
		return "Solicitud DRARP";
	case 6:
		return "Respuesta DRARP";
	case 7:
		return "Error DRARP";
	case 8:
		return "Solicitud InARP";
	case 9:
		return "Respuesta InARP";
	// ...
	default:
		return "Desconocido";
	}
}
