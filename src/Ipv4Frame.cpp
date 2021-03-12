#include <Ipv4Frame.hpp>

unsigned Ipv4Frame::getPayloadLength() const
{

}

unsigned Ipv4Frame::getOptionsLength() const
{

}

string Ipv4Frame::addressToString(const unsigned&) const
{

}

void Ipv4Frame::calculateCheckSum()
{

}

void Ipv4Frame::constructPayload()
{

}

~ Ipv4Frame::IpFrame()
{

}

void Ipv4Frame::fromBytes(const char*)
{

}

string Ipv4Frame::getSourceAddressAsString() const
{

}

string Ipv4Frame::getDestinationAddressAsString() const
{

}

string Ipv4Frame::getPrecedenceAsString() const
{

}

string Ipv4Frame::getDelayAsString() const
{

}

string Ipv4Frame::getThroughputAsString() const
{

}

string Ipv4Frame::getReliabilityAsString() const
{

}

string Ipv4Frame::getProtocolAsString() const
{

}

void Ipv4Frame::setVersion(const unsigned&)
{
    version=value;
}

void Ipv4Frame::setIhl(const unsigned&)
{
    ihl=value;
}

void Ipv4Frame::setService(const unsigned&)
{
    service=value;
}

void Ipv4Frame::setTotalLength(const unsigned&)
{
    totalLength=value;
}

void Ipv4Frame::setId(const unsigned&)
{
    id=value;
}

void Ipv4Frame::setDf(const bool&)
{
    df=value;
}

void Ipv4Frame::setMf(const bool&)
{
    mf=value;
}

void Ipv4Frame::setOffset(const unsigned&)
{
    offset=value;
}

void Ipv4Frame::setTtl(const unsigned&)
{
    ttl=value;
}

void Ipv4Frame::setProtocol(const unsigned&)
{
    protocol=value;
}

void Ipv4Frame::setCheckSum(const unsigned&)
{
    checkSum=value;
}

void Ipv4Frame::setSourceAddress(const unsigned&)
{
    sourceAddress=value;
}

void Ipv4Frame::setDestinationAddress(const unsigned&)
{
    destinationAddress=value;
}

void Ipv4Frame::setOptions(const char*)
{
    options=value;
}

void Ipv4Frame::setPayload(const char*)
{
    payload=value;
}


unsigned Ipv4Frame::getVersion() const
{
    return version;
}

unsigned Ipv4Frame::getIhl() const
{
    return ihl;
}

unsigned Ipv4Frame::getService() const
{
    return service;
}

unsigned Ipv4Frame::getTotalLength() const
{
    return totalLength;
}

unsigned Ipv4Frame::getId() const
{
    return id;
}

bool Ipv4Frame::getDf() const
{
    return df;
}

bool Ipv4Frame::getMf() const
{
    return mf;
}

unsigned Ipv4Frame::getOffset() const
{
    return offset;
}

unsigned Ipv4Frame::getTtl() const
{
    return ttl;
}

unsigned Ipv4Frame::getProtocol() const
{
    return protocol;
}

unsigned Ipv4Frame::getCheckSum() const
{
    return checkSum;
}

unsigned Ipv4Frame::getCalculatedCheckSum() const
{
    return calculatedCheckSum;
}

const unsigned Ipv4Frame::getSourceAddress() const
{
    return sourceAddress;
}

const unsigned Ipv4Frame::getDestinationAddress() const
{
    return destinationAddress;
}

/*unsigned Ipv4Frame::getPrecedence() const
{

}

unsigned Ipv4Frame::getDelay() const
{

}

unsigned Ipv4Frame::getThroughput() const
{

}

unsigned Ipv4Frame::getReliability() const
{

}

unsigned Ipv4Frame::getReservedTosBits() const
{

}*/


//debemos conservarlos?
const char* Ipv4Frame::getOptions(void) const
{
    return options;
}

const char* Ipv4Frame::getPayload(void) const
{
    return payload;
}
