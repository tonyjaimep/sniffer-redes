#pragma once

#include <string>

#define ARP_HTYPE_LENGTH	16
#define ARP_PTYPE_LENGTH	16
#define ARP_HLEN_LENGTH		8
#define ARP_PLEN_LENGTH		8
#define ARP_OPERATION_LENGTH	16
#define ARP_SHA_LENGTH		6 * 8
#define ARP_SPA_LENGTH		4 * 8
#define ARP_THA_LENGTH		6 * 8
#define ARP_TPA_LENGTH		4 * 8

#define ARP_HTYPE_ETHERNET 1

// ARP protocol types
#define ARP_PTYPE_IPV4 0x0800

class ArpFrame
{
private:
	unsigned long hardwareType		: ARP_HTYPE_LENGTH;
	unsigned long protocolType		: ARP_PTYPE_LENGTH;
	unsigned long hardwareAddressLength	: ARP_HLEN_LENGTH;
	unsigned long protocolAddressLength	: ARP_PLEN_LENGTH;
	unsigned long operation			: ARP_OPERATION_LENGTH;
	unsigned long senderHardwareAddress	: ARP_SHA_LENGTH;
	unsigned long senderProtocolAddress	: ARP_SPA_LENGTH;
	unsigned long targetHardwareAddress	: ARP_THA_LENGTH;
	unsigned long targetProtocolAddress	: ARP_TPA_LENGTH;
public:
	ArpFrame();
	~ArpFrame();

	void fromBytes(const char*);

	void setHardwareType(unsigned long);
	void setProtocolType(unsigned long);
	void setHardwareAddressLength(unsigned long);
	void setProtocolAddressLength(unsigned long);
	void setOperation(unsigned long);
	void setSenderHardwareAddress(unsigned long);
	void setSenderProtocolAddress(unsigned long);
	void setTargetHardwareAddress(unsigned long);
	void setTargetProtocolAddress(unsigned long);

	unsigned long getHardwareType() const;
	unsigned long getProtocolType() const;
	unsigned long getHardwareAddressLength() const;
	unsigned long getProtocolAddressLength() const;
	unsigned long getOperation() const;
	unsigned long getSenderHardwareAddress() const;
	unsigned long getSenderProtocolAddress() const;
	unsigned long getTargetHardwareAddress() const;
	unsigned long getTargetProtocolAddress() const;

	static std::string hardwareTypeAsString(unsigned long);
	static std::string protocolTypeAsString(unsigned long);
	static std::string operationAsString(const unsigned& op);

	static std::string addressToString(const unsigned& address);
};
