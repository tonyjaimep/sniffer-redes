#include "../../include/dns/DnsQuery.hpp"
#include <sstream>

using std::stringstream;

DnsQuery::DnsQuery(const char* bytes)
{
	unsigned cursor(0);
	stringstream ss;
	unsigned fractionLength = bytes[cursor++];

	// read domain name
	while (fractionLength > 0) {
		for (unsigned i(fractionLength); i > 0; i--) {
			ss << (char)bytes[cursor++];
		}

		fractionLength = bytes[cursor++];

		if (fractionLength > 0)
			ss << ".";
	}
	setDomainName(ss.str());
	// read type
	setType(0x100 * bytes[cursor] + bytes[cursor + 1]);
	cursor += 2;
	// read class
	setClass(0x100 * bytes[cursor] + bytes[cursor + 1]);

	setSize(cursor + 2);
}

DnsQuery::~DnsQuery() {}

string DnsQuery::getDomainName() const { return domainName; }
void DnsQuery::setDomainName(string value) { domainName = value; }

unsigned DnsQuery::getSize() const { return size; }
void DnsQuery::setSize(unsigned value) { size = value; }

uint16_t DnsQuery::getType() const { return type; }
void DnsQuery::setType(uint16_t value) { type = value; }
string DnsQuery::typeToString(uint16_t type)
{
	switch (type)
	{
		case 1: return "A";
		case 5: return "CNAME";
		case 13: return "HINFO";
		case 15: return "MX";
		case 22: case 23: return "NS";
		default: return "Desconocido";
	}
}

uint16_t DnsQuery::getClass() const { return dnsClass; }
void DnsQuery::setClass(uint16_t value) { dnsClass = value; }
string DnsQuery::classToString(uint16_t dnsClass)
{
	switch (dnsClass)
	{
		case 1: return "IN";
		case 3: return "CH";
		default: return "Desconocido";
	}
}
