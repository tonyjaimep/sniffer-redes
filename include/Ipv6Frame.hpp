#pragma once

#include "Ipv4Frame.hpp"

#define IP_STD_TRAFFIC_CLASS_LENGTH 16
#define IP_STD_FLOW_LABEL_LENGTH 20
#define IP_STD_PAYLOAD_LENGTH_LENGTH 16
#define IP_STD_NEXT_HEADER_LENGTH 8
#define IP_STD_HOP_LIMIT_LENGTH 8

// en bytes, porque no cabe en campo de bits
#define IPV6_STD_ADDRESS_LENGTH 16

class Ipv6Frame
{
private:
	unsigned version: IP_STD_VERSION_LENGTH;
	unsigned trafficClass: IP_STD_TRAFFIC_CLASS_LENGTH;
	unsigned flowLabel: IP_STD_FLOW_LABEL_LENGTH;
	unsigned payloadLength: IP_STD_PAYLOAD_LENGTH_LENGTH;
	unsigned nextHeader: IP_STD_NEXT_HEADER_LENGTH;
	unsigned hopLimit: IP_STD_HOP_LIMIT_LENGTH;

	unsigned char sourceAddress[IPV6_STD_ADDRESS_LENGTH];
	unsigned char destinationAddress[IPV6_STD_ADDRESS_LENGTH];
public:
	Ipv6Frame();
	~Ipv6Frame();

	void fromBytes(const unsigned char*);

	static std::string addressToString(const unsigned char* address);

	std::string getTrafficClassAsString() const;

	unsigned getVersion() const;
	unsigned getTrafficClass() const;
	unsigned getFlowLabel() const;
	unsigned getPayloadLength() const;
	unsigned getNextHeader() const;
	unsigned getHopLimit() const;

	unsigned char* getSourceAddress();
	unsigned char* getDestinationAddress();

	void setVersion(const unsigned&);
	void setTrafficClass(const unsigned&);
	void setFlowLabel(const unsigned&);
	void setPayloadLength(const unsigned&);
	void setNextHeader(const unsigned&);
	void setHopLimit(const unsigned&);

	void setSourceAddress(const unsigned char*);
	void setDestinationAddress(const unsigned char*);
};
