#include <sstream>
#include <iomanip>
#include <iostream>
#include "../include/TcpFrame.hpp"

using namespace std;

void TcpFrame::fromBytes(const char* frameBytes, const unsigned& size)
{
	setSourcePort(frameBytes[0] * 0x100 + (frameBytes[1] & 0xF));
	setDestinationPort(frameBytes[2] * 0x100 + (frameBytes[3] & 0xF));
	setSequenceNumber(frameBytes[4] * 0x1000000 + frameBytes[5] * 0x10000 + frameBytes[6] * 0x100 + frameBytes[7]);
	setAcknowledgementNumber(frameBytes[8] * 0x1000000 + frameBytes[9] * 0x10000 + frameBytes[10] * 0x100 + frameBytes[11]);
	setHeaderLength(frameBytes[12] >> 4);
	setFlags(frameBytes[13] & 0b111111111);
	setWindow(frameBytes[14] * 0x100 + frameBytes[15]);
	setCheckSum(frameBytes[16] * 0x100 + frameBytes[17]);
	setUrgentPointer(frameBytes[18] * 0x100 + frameBytes[19]);
	setPayload(&frameBytes[getHeaderLength() / 8], size - (getHeaderLength()));
}

TcpFrame::TcpFrame() : payload(nullptr) {}
TcpFrame::~TcpFrame() {}

std::string TcpFrame::getFlagsAsString() const
{
	stringstream ss;
	if (flags & 0b100000000)
		ss << "NS ";
	if (flags & 0b010000000)
		ss << "CWR ";
	if (flags & 0b001000000)
		ss << "ECE ";
	if (flags & 0b000100000)
		ss << "URG ";
	if (flags & 0b000010000)
		ss << "ACK ";
	if (flags & 0b000001000)
		ss << "PSH ";
	if (flags & 0b000000100)
		ss << "RST ";
	if (flags & 0b000000010)
		ss << "SYN ";
	if (flags & 0b000000001)
		ss << "FIN";

	return ss.str();
}

void TcpFrame::setSourcePort(const unsigned& s) { sourcePort = s; }
void TcpFrame::setDestinationPort(const unsigned& d) { destinationPort = d; }
void TcpFrame::setSequenceNumber(const unsigned& s) { sequenceNumber = s; }
void TcpFrame::setAcknowledgementNumber(const unsigned& a) { acknowledgementNumber = a; }
void TcpFrame::setHeaderLength(const unsigned& d) { headerLength = d; }
void TcpFrame::setFlags(const unsigned& f) { flags = f; }
void TcpFrame::setWindow(const unsigned& w) { window = w; }
void TcpFrame::setCheckSum(const unsigned& c) { checkSum = c; }
void TcpFrame::setUrgentPointer(const unsigned& u) { urgentPointer = u; }
void TcpFrame::setPayload(const char* p, const unsigned& size)
{
	if (payload != nullptr)
		delete payload;

	payload = (char*)malloc(size);

	for (unsigned i(0); i < size; i++)
		payload[i] = p[i];
}

unsigned TcpFrame::getSourcePort() const { return sourcePort; }
unsigned TcpFrame::getDestinationPort() const { return destinationPort; }
unsigned TcpFrame::getSequenceNumber() const { return sequenceNumber; }
unsigned TcpFrame::getAcknowledgementNumber() const { return acknowledgementNumber; }
unsigned TcpFrame::getHeaderLength() const { return headerLength; }
unsigned TcpFrame::getFlags() const { return flags; }
unsigned TcpFrame::getWindow() const { return window; }
unsigned TcpFrame::getCheckSum() const { return checkSum; }
unsigned TcpFrame::getUrgentPointer() const { return urgentPointer; }
char* TcpFrame::getPayload() const { return payload; }
