#include "../include/Icmpv4Frame.hpp"
#include <iostream>

void Icmpv4Frame::setType(const unsigned& value)
{
	type = value;
}

void Icmpv4Frame::setCode(const unsigned& value)
{
	code = value;
}

void Icmpv4Frame::setCheckSum(const unsigned& value)
{
	checkSum = value;
}

void Icmpv4Frame::setContent(const char* value)
{
	content[0] = value[0];
	content[1] = value[1];
	content[2] = value[2];
	content[3] = value[3];
}

unsigned Icmpv4Frame::getType() const
{
	return type;
}

unsigned Icmpv4Frame::getCode() const
{
	return code;
}

unsigned Icmpv4Frame::getCheckSum() const
{
	return checkSum;
}

unsigned const char* Icmpv4Frame::getContent() const
{
	return content;
}

std::string Icmpv4Frame::getTypeAsAstring() const
{
	switch (getType()) {
	case ICMPV4_TYPE_ECHO_REPLY:
		return "Echo Reply";
	case ICMPV4_TYPE_DESTINATION_UNREACHABLE:
		return "Destination Unreachable";
	case ICMPV4_TYPE_REDIRECT_MESSAGE:
		return "Redirect Message";
	case ICMPV4_TYPE_ECHO_REQUEST:
		return "Echo Request";
	case ICMPV4_TYPE_ROUTER_ADVERTISEMENT:
		return "Router Advertisement";
	case ICMPV4_TYPE_TIME_EXCEEDED:
		return "Time Exceeded";
	case ICMPV4_TYPE_PARAMETER_PROBLEM:
		return "Parameter Problem";
	case ICMPV4_TYPE_TIMESTAMP:
		return "Timestamp";
	case ICMPV4_TYPE_TIMESTAMP_REPLY:
		return "Timestamp Reply";
	default:
		return "Desconocido";
	}
}

std::string Icmpv4Frame::getCodeAsAstring() const
{
	switch (getType()) {
	case ICMPV4_TYPE_ECHO_REPLY:
		switch (getCode()) {
		case 0:
			return "Echo reply";
		default:
			return "Desconocido";
		}
	case ICMPV4_TYPE_DESTINATION_UNREACHABLE:
		switch (getCode()) {
		case 0:
			return "Destination Network Unreachable";
		case 1:
			return "Destination Host Unreachable";
		case 2:
			return "Destination Protocol Unreachable";
		case 3:
			return "Destination Port Unreachable";
		case 4:
			return "Fragmentation Needed and DF Flag Set";
		case 5:
			return "Source Route Failed";
		default:
			return "Desconocido";
		}
	case ICMPV4_TYPE_REDIRECT_MESSAGE:
		switch (getCode()) {
		case 0:
			return "Redirect Datagram for the Network";
		case 1:
			return "Redirecct Datagram for the Host";
		case 2:
			return "Redirecct Datagram for the ToS and Network";
		case 3:
			return "Redirecct Datagram for the Service and Host";
		default:
			return "Desconocido";
		}
	case ICMPV4_TYPE_ECHO_REQUEST:
		switch (getCode()) {
		case 0:
			return "Echo request";
		default:
			return "Desconocido";
		}
	case ICMPV4_TYPE_ROUTER_ADVERTISEMENT:
	case ICMPV4_TYPE_ROUTER_SOLICITATION:
		switch (getCode()) {
		case 0:
			return "Use to discover the addresses of operational routers";
		default:
			return "Desconocido";
		}
	case ICMPV4_TYPE_TIME_EXCEEDED:
		switch (getCode()) {
		case 0:
			return "TTL Exceeded in Transit";
		case 1:
			return "Fragment Reassembly Time Exceeded";
		default:
			return "Desconocido";
		}
	case ICMPV4_TYPE_PARAMETER_PROBLEM:
		switch (getCode()) {
		case 0:
			return "Pointer Indicates Error";
		case 1:
			return "Missing Required Option";
		default:
			return "Bad Length";
		}
	case ICMPV4_TYPE_TIMESTAMP:
		switch (getCode()) {
		case 0:
			return "Time Synchronization";
		default:
			return "Desconocido";
		}
	case ICMPV4_TYPE_TIMESTAMP_REPLY:
		switch (getCode()) {
		case 0:
			return "Reply to Timestamp Message";
		default:
			return "Desconocido";
		}
	default:
		return "Desconocido";
	}
}

void Icmpv4Frame::fromBytes(const char* bytes)
{
	setType(bytes[0]);
	setCode(bytes[1]);

	setCheckSum(((unsigned)bytes[2] * 0x100) + (unsigned)bytes[3]);

	char newContent[4];

	newContent[0] = bytes[4];
	newContent[1] = bytes[5];
	newContent[2] = bytes[6];
	newContent[3] = bytes[8];

	setContent(newContent);
}
