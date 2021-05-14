#pragma once

#define UDP_PORT_SIZE 16
#define UDP_LENGTH_SIZE 16
#define UDP_CHECKSUM_SIZE 16

class UdpFrame
{
private:
	unsigned sourcePort : UDP_PORT_SIZE;
	unsigned destinationPort : UDP_PORT_SIZE;
	unsigned length: UDP_LENGTH_SIZE;
	unsigned checksum: UDP_CHECKSUM_SIZE;
	char* payload;
public:
	UdpFrame();
	~UdpFrame();

	void fromBytes(const char*);

	void setSourcePort(const unsigned&);
	void setDestinationPort(const unsigned&);
	void setLength(const unsigned&);
	void setCheckSum(const unsigned&);
	void setPayload(const char*);

	unsigned getSourcePort() const;
	unsigned getDestinationPort() const;
	unsigned getLength() const;
	unsigned getCheckSum() const;
	char* getPayload() const;
};
