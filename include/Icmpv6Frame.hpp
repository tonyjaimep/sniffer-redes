#include <string>

#define ICMPV6_TYPE_LENGTH 8
#define ICMPV6_CODE_LENGTH 8
#define ICMPV6_CHECK_SUM_LENGTH 16

#define ICMPV6_TYPE_DESTINATION_UNREACHABLE 1
#define ICMPV6_TYPE_PACKET_TOO_BIG 2
#define ICMPV6_TYPE_TIME_EXCEEDED 3
#define ICMPV6_TYPE_PARAMETER_PROBLEM 4
#define ICMPV6_TYPE_ECHO_REQUEST 128
#define ICMPV6_TYPE_ECHO_REPLY 129
#define ICMPV6_TYPE_ROUTER_SOLICITATION 133
#define ICMPV6_TYPE_ROUTER_ADVERTISEMENT 134
#define ICMPV6_TYPE_NEIGHBOR_SOLICITATION 135
#define ICMPV6_TYPE_NEIGHBOR_ADVERTISEMENT 136
#define ICMPV6_TYPE_REDIRECT_MESSAGE 137

#define ICMPV6_CODE_NO_ROUTE_DESTINATION 0
#define ICMPV6_CODE_COMMUNICATION_ADMINISTRATIVELY_PROHIBITED 1
#define ICMPV6_CODE_BEYOND_SCOPE_OF_SOURCE 2
#define ICMPV6_CODE_ADDRESS_UNREACHABLE 3

#define ICMPV6_CODE_HOP_LIMIT_EXCEEDED 0
#define ICMPV6_CODE_FRAGMENT_REASSEMBLY_TIME_EXCEEDED 1

#define ICMPV6_CODE_ERRONEUS_HEADER_FIELD 0
#define ICMPV6_CODE_UNRECOGNIZED_NEXT_HEADER 1
#define ICMPV6_CODE_UNRECOGNIZED_IPV6_OPTION 2

class Icmpv6Frame
{
private:
	unsigned type :		ICMPV6_TYPE_LENGTH;
	unsigned code :		ICMPV6_CODE_LENGTH;
	unsigned checkSum :	ICMPV6_CHECK_SUM_LENGTH;
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

	static std::string typeToString(const unsigned&);
	static std::string codeToString(const unsigned&, const unsigned&);

	void fromBytes(const char*);
};
