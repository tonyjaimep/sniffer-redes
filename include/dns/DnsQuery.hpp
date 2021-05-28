#pragma once
#include <string>

using std::string;

class DnsQuery
{
public:
	string getDomainName() const;
	void setDomainName(string);

	uint16_t getType() const;
	void setType(uint16_t);
	static string typeToString(uint16_t);

	uint16_t getClass() const;
	void setClass(uint16_t);
	static string classToString(uint16_t);

	unsigned getSize() const;

	DnsQuery(const char*);
	~DnsQuery();
private:
	string domainName;
	uint16_t type;
	uint16_t dnsClass;
	unsigned size;

	void setSize(unsigned);
};
