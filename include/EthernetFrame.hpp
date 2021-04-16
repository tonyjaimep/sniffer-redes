#ifndef ETHERNETFRAME_H_INCLUDED
#define ETHERNETFRAME_H_INCLUDED

#include <string>

#define ETHERNET_ADDRESS_LENGTH 6
#define ETHERNET_TYPE_LENGTH 2

#define ETHERNET_TYPE_ARP	0x0806
#define ETHERNET_TYPE_RARP	0x8035
#define ETHERNET_TYPE_IPV4	0x0800

class EthernetFrame
{
public:
    EthernetFrame();
    ~EthernetFrame();

    unsigned long getSourceAddress() const;
    unsigned long getDestinationAddress() const;
    void setSourceAddress(const unsigned long value);
    void setDestinationAddress(const unsigned long value);
    unsigned long getType() const;
    void setType(const unsigned type);
    char* getData() const;
    void setData(const char* value, size_t dataLength);

    void fromBytes(const char* bytes, const unsigned long& length);

    static std::string addressAsString(const unsigned long bytes);
    static std::string typeAsString(const unsigned type);

private:
    unsigned long sourceAddress;
    unsigned long destinationAddress;
    unsigned long type : ETHERNET_TYPE_LENGTH * 8;
    char *data;
};

#endif // ETHERNETFRAME_H_INCLUDED
