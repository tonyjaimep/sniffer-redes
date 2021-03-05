#ifndef ETHERNETFRAME_H_INCLUDED
#define ETHERNETFRAME_H_INCLUDED

class EthernetFrame
{
public:
    EthernetFrame();
    ~EthernetFrame();

    unsigned long getSourceAddress() const;
    void setSourceAddress(unsigned long value);
    unsigned long getDestinationAddress() const;
    void setDestinationAddress(unsigned long value);
    unsigned long getType() const;
    void setType(unsigned long value);
    char* getData() const;
    void setData(char* value);

    void fromBytes(const char* bytes);

private:
    unsigned long sourceAddress : 6*8;
    unsigned long destinationAddress : 6*8;
    unsigned long type : 2*8;
    char *data;
};

#endif // ETHERNETFRAME_H_INCLUDED
