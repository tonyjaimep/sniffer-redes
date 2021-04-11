#pragma once

#include <string>

#define ICMPV4_TYPE_LENGTH 8
#define ICMPV4_CODE_LENGTH 8
#define ICMPV4_CHECK_SUM_LENGTH 16

#define ICMPV4_TYPE_ECHO_REPLY 0
#define ICMPV4_TYPE_DESTINATION_UNREACHABLE 3
#define ICMPV4_TYPE_REDIRECT_MESSAGE 5
#define ICMPV4_TYPE_ECHO_REQUEST 8
#define ICMPV4_TYPE_ROUTER_ADVERTISEMENT 9
#define ICMPV4_TYPE_ROUTER_SOLICITATION 10
#define ICMPV4_TYPE_TIME_EXCEEDED 11
#define ICMPV4_TYPE_PARAMETER_PROBLEM 12
#define ICMPV4_TYPE_TIMESTAMP 13
#define ICMPV4_TYPE_TIMESTAMP_REPLY 14

class Icmpv4Frame
{
private:
	unsigned type :		ICMPV4_TYPE_LENGTH;
	unsigned code :		ICMPV4_CODE_LENGTH;
	unsigned checkSum :	ICMPV4_CHECK_SUM_LENGTH;
	unsigned char content[4];
public:
	void setType(const unsigned &);
	void setCode(const unsigned &);
	void setCheckSum(const unsigned&);
	void setContent(const char*);

	unsigned getType() const;
	unsigned getCode() const;
	unsigned getCheckSum() const;
	unsigned const char* getContent() const;

	std::string getTypeAsAstring() const;
	std::string getCodeAsAstring() const;

	void fromBytes(const char*);
};
