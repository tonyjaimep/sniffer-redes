#include "../include/Icmpv6Frame.hpp"
#include <iostream>

void Icmpv6Frame::setType(const unsigned& value)
{
	type = value;
}

void Icmpv6Frame::setCode(const unsigned& value)
{
	code = value;
}

void Icmpv6Frame::setCheckSum(const unsigned& value)
{
	checkSum = value;
}

void Icmpv6Frame::setContent(const char* value)
{
	content[0] = value[0];
	content[1] = value[1];
	content[2] = value[2];
	content[3] = value[3];
}

unsigned Icmpv6Frame::getType() const
{
	return type;
}

unsigned Icmpv6Frame::getCode() const
{
	return code;
}

unsigned Icmpv6Frame::getCheckSum() const
{
	return checkSum;
}

unsigned const char* Icmpv6Frame::getContent() const
{
	return content;
}

std::string Icmpv6Frame::getTypeAsAstring() const
{
	switch (getType()) {
	case ICMPV6_TYPE_DESTINATION_UNREACHABLE:
		return "Destination unreachable";
    case ICMPV6_TYPE_PACKET_TOO_BIG:
        return "Packet too big";
    case ICMPV6_TYPE_TIME_EXCEEDED:
        return "Time exceeded";
    case ICMPV6_TYPE_PARAMETER_PROBLEM:
        return "Parameter problem";
    case ICMPV6_TYPE_ECHO_REQUEST:
        return "Echo request";
    case ICMPV6_TYPE_ECHO_REPLY:
        return "Echo reply";
    case ICMPV6_TYPE_ROUTER_SOLICITATION:
        return "Router solicitation";
    case ICMPV6_TYPE_ROUTER_ADVERTISEMENT:
        return "Router advertisement";
    case ICMPV6_TYPE_NEIGHBOR_SOLICITATION:
        return "Neighbor solicitation";
    case ICMPV6_TYPE_NEIGHBOR_ADVERTISEMENT:
        return "Neighbor advertisement";
    case ICMPV6_TYPE_REDIRECT_MESSAGE:
        return "Redirect message";
	default:
		return "Unknown";
	}
}

std::string Icmpv6Frame::getCodeAsAstring() const
{
	switch (getType()) {
	case ICMPV6_TYPE_DESTINATION_UNREACHABLE:
		switch (getCode()) {
		case ICMPV6_CODE_NO_ROUTE_DESTINATION:
			return "No route to destination ";
        case ICMPV6_CODE_COMMUNICATION_ADMINISTRATIVELY_PROHIBITED:
            return "Communication with destination administratively prohibited";
        case ICMPV6_CODE_BEYOND_SCOPE_OF_SOURCE:
            return "Beyond scope of source address ";
        case ICMPV6_CODE_ADDRESS_UNREACHABLE:
            return "Address unreachable";
		default:
			return "Unknown";
		}
	case ICMPV6_TYPE_TIME_EXCEEDED:
		switch (getCode()) {
		case ICMPV6_CODE_HOP_LIMIT_EXCEEDED:
		    return "Hop limit exceeded in transit";
        case ICMPV6_CODE_FRAGMENT_REASSEMBLY_TIME_EXCEEDED:
            return "Fragment reassembly time exceeded";
		default:
			return "Unknown";
		}
	case ICMPV6_TYPE_PARAMETER_PROBLEM:
		switch (getCode()) {
		case ICMPV6_CODE_ERRONEUS_HEADER_FIELD:
		    return "Erroneous header field encountered ";
        case ICMPV6_CODE_UNRECOGNIZED_NEXT_HEADER:
            return "Unrecognized Next Header type encountered ";
        case ICMPV6_CODE_UNRECOGNIZED_IPV6_OPTION:
            return "Unrecognized IPv6 option encountered ";
		default:
			return "Unknown";
		}

	default:
		return "Unknown";
	}
}

void Icmpv6Frame::fromBytes(const char* bytes)
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
