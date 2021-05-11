#pragma once

#include <string>

// measured in bytes
#define TCP_MIN_HEADER_LENGTH 20

// measured in bits
#define TCP_PORT_SIZE 16
#define TCP_SEQUENCE_NUMBER_SIZE 32
#define TCP_ACKNOWLEDGEMENT_NUMBER_SIZE 32
#define TCP_HEADER_LENGTH_SIZE 4
#define TCP_RESERVED_FIELD_SIZE 3
#define TCP_FLAGS_SIZE 9
#define TCP_WINDOW_SIZE 16
#define TCP_CHECKSUM_SIZE 16
#define TCP_URGENT_POINTER_SIZE 16

class TcpFrame
{
private:
	unsigned sourcePort : TCP_PORT_SIZE;
	unsigned destinationPort : TCP_PORT_SIZE;
	unsigned sequenceNumber : TCP_SEQUENCE_NUMBER_SIZE;
	unsigned acknowledgementNumber : TCP_ACKNOWLEDGEMENT_NUMBER_SIZE;
	unsigned headerLength : TCP_HEADER_LENGTH_SIZE;
	unsigned flags : TCP_FLAGS_SIZE;
	unsigned window : TCP_WINDOW_SIZE;
	unsigned checkSum : TCP_CHECKSUM_SIZE;
	unsigned urgentPointer : TCP_URGENT_POINTER_SIZE;
	char* payload;
public:
	TcpFrame();
	~TcpFrame();

	void fromBytes(const char*, const unsigned&);

	std::string getFlagsAsString() const;

	void setSourcePort(const unsigned&);
	void setDestinationPort(const unsigned&);
	void setSequenceNumber(const unsigned&);
	void setAcknowledgementNumber(const unsigned&);
	void setHeaderLength(const unsigned&);
	void setFlags(const unsigned&);
	void setWindow(const unsigned&);
	void setCheckSum(const unsigned&);
	void setUrgentPointer(const unsigned&);
	void setPayload(const char*, const unsigned&);

	unsigned getSourcePort() const;
	unsigned getDestinationPort() const;
	unsigned getSequenceNumber() const;
	unsigned getAcknowledgementNumber() const;
	unsigned getHeaderLength() const;
	unsigned getFlags() const;
	unsigned getWindow() const;
	unsigned getCheckSum() const;
	unsigned getUrgentPointer() const;
	char* getPayload() const;
};
