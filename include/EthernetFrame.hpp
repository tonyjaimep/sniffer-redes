#ifndef ETHERNETFRAME_H_INCLUDED
#define ETHERNETFRAME_H_INCLUDED

#include <string>

#define ETHERNET_ADDRESS_LENGTH 6
#define ETHERNET_TYPE_LENGTH 2

#define ETHERNET_TYPE_ARP	0x0806
#define ETHERNET_TYPE_IPV4	0x0800

class EthernetFrame
{
public:
    EthernetFrame();
    ~EthernetFrame();

    unsigned long getSourceAddress() const;
    void setSourceAddress(const unsigned long value);
    unsigned long getDestinationAddress() const;
    void setDestinationAddress(const unsigned long value);
    unsigned long getType() const;
    void setType(const unsigned type);
    char* getData() const;
    void setData(char* value);

    void fromBytes(const char* bytes, const unsigned long& length);

    static std::string addressAsString(const unsigned long address);
    static std::string typeAsString(const unsigned type);

private:
    unsigned long sourceAddress : ETHERNET_ADDRESS_LENGTH * 8;
    unsigned long destinationAddress : ETHERNET_ADDRESS_LENGTH * 8;
    unsigned long type : ETHERNET_TYPE_LENGTH * 8;
    char *data;
};

#endif // ETHERNETFRAME_H_INCLUDED
