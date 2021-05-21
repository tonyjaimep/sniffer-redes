#include "../include/DnsFrame.hpp"

DnsFrame::DnsFrame(const char* bytes)
{
	setId(bytes[0] * 0x100 + bytes[1]);
	setQr(bytes[2] >> 7);
	setOpCode((bytes[2] >> 3) & 0b1111);
	setFlags(((bytes[2] & 0b111) << 1) + (bytes[3] & 0b10000000));
	setRcode(bytes[3] & 0b1111);
	setQdCount(bytes[4] * 0x100 + bytes[5]);
	setAnCount(bytes[6] * 0x100 + bytes[7]);
	setNsCount(bytes[8] * 0x100 + bytes[9]);
	setArCount(bytes[10] * 0x100 + bytes[11]);
}

DnsFrame::~DnsFrame() {}

uint16_t DnsFrame::getId() const { return id; }
void DnsFrame::setId(uint16_t value) { id = value; }

void DnsFrame::setQr(bool value) { qr = value; }
bool DnsFrame::isQuery() const { return !qr; }
bool DnsFrame::isResponse() const { return  qr; }

short unsigned DnsFrame::getOpCode() const { return opCode; }
void DnsFrame::setOpCode(short unsigned value) { opCode = value; }

short unsigned DnsFrame::getRcode() const { return rcode; }
void DnsFrame::setRcode(short unsigned value) { rcode = value; }

uint16_t DnsFrame::getQdCount() const { return qdCount; }
void DnsFrame::setQdCount(uint16_t value) { qdCount = value; }

uint16_t DnsFrame::getAnCount() const { return anCount; }
void DnsFrame::setAnCount(uint16_t value) { anCount = value; }

uint16_t DnsFrame::getNsCount() const { return nsCount; }
void DnsFrame::setNsCount(uint16_t value) { nsCount = value; }

uint16_t DnsFrame::getArCount() const { return arCount; }
void DnsFrame::setArCount(uint16_t value) { arCount = value; }

short unsigned DnsFrame::getFlags() const { return flags; }
void DnsFrame::setFlags(short unsigned value) { flags = value; }

string DnsFrame::opCodeAsString(short unsigned code)
{
	switch (code) {
		case 0:
			return "QUERY";
		case 1:
			return "IQUERY";
		case 2:
			return "STATUS";
		default:
			return "Desconocido";
	}
}

string DnsFrame::rCodeAsString(short unsigned code)
{
	switch (code) {
		case 0:
			return "NOERROR";
		case 1:
			return "FORMERR";
		case 2:
			return "SERVFAIL";
		case 3:
			return "NXDOMAIN";
		default:
			return "Desconocido";
	}
}
