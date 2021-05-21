#pragma once

#include <cinttypes>
#include <string>
using std::uint16_t;
using std::string;

#define DNS_OPCODE_SIZE 4
#define DNS_RCODE_SIZE 4

class DnsFrame
{
public:
	DnsFrame(const char*);
	~DnsFrame();

	// Getters and setters for header fields
	uint16_t getId() const;
	void setId(uint16_t);

	void setQr(bool);
	bool isQuery() const;
	bool isResponse() const;

	short unsigned getOpCode() const;
	void setOpCode(short unsigned);

	short unsigned getRcode() const;
	void setRcode(short unsigned);

	uint16_t getQdCount() const;
	void setQdCount(uint16_t);

	uint16_t getAnCount() const;
	void setAnCount(uint16_t);

	uint16_t getNsCount() const;
	void setNsCount(uint16_t);

	uint16_t getArCount() const;
	void setArCount(uint16_t);

	short unsigned getFlags() const;
	void setFlags(short unsigned);

	static string opCodeAsString(short unsigned);
	static string rCodeAsString(short unsigned);
private:
	uint16_t id;
	bool qr;
	short unsigned opCode : DNS_OPCODE_SIZE;
	short unsigned flags : 4;
	short unsigned rcode : DNS_RCODE_SIZE;
	uint16_t qdCount;
	uint16_t anCount;
	uint16_t nsCount;
	uint16_t arCount;
};
