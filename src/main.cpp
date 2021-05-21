#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <exception>

#include "../include/EthernetFrame.hpp"
#include "../include/Ipv4Frame.hpp"
#include "../include/Ipv6Frame.hpp"
#include "../include/Icmpv4Frame.hpp"
#include "../include/Icmpv6Frame.hpp"
#include "../include/ArpFrame.hpp"
#include "../include/TcpFrame.hpp"
#include "../include/UdpFrame.hpp"
#include "../include/DnsFrame.hpp"

using namespace std;

void showEthernetInfo(const char* bytes, unsigned length);
void showArpInfo(const char* bytes);
void showIpv4Info(const char* bytes);
void showIpv6Info(const char* bytes);
void showTcpInfo(const char* bytes, unsigned length);
void showUdpInfo(const char* bytes);
void showIcmpv4Info(const char* bytes);
void showIcmpv6Info(const char* bytes);
void showDnsInfo(const char* bytes);

string knownPortAsString(unsigned port);

int main()
{
	string filename;
	ifstream binFile;
	char* buffer;

	cout << "Analizador de Paquetes Ethernet" << endl;
	cout << "Equipo 5 de la sección D03" << endl << endl;

	while (!binFile.is_open()) {
		cout << "Introduzca la localización del paquete (vacío para cancelar): ";
		cin >> filename;

		if (filename.size() < 2)
			return EXIT_SUCCESS;

		binFile.open(filename, ifstream::in | ifstream::binary);

		if (!binFile.is_open())
			cout << "Error abriendo el archivo." << endl;
	}

	// va hasta el final
	binFile.seekg (0, binFile.end);
	// obtiene la posición del final
	unsigned length = binFile.tellg();
	// regresa al inicio
	binFile.seekg (0, binFile.beg);

	// buffer contiene todo el contenido del archivo
	buffer = static_cast<char*>(malloc(length));

	binFile.read(buffer, length);

	showEthernetInfo(buffer, length);

	free(buffer);
	binFile.close();

	return EXIT_SUCCESS;
}

void showEthernetInfo(const char* bytes, unsigned length)
{
	EthernetFrame ef;
	ef.fromBytes(bytes, length);

	cout << "Ethernet" << endl;

	cout << "\tDirección de destino: " << ef.addressAsString(ef.getDestinationAddress()) << endl;
	cout << "\tDirección de origen: " << ef.addressAsString(ef.getSourceAddress()) << endl;
	cout << "\tTipo: " << ef.typeAsString(ef.getType())
		<< " (0x" << setfill('0') << setw(4) << hex << ef.getType() << ")" << endl;

	switch (ef.getType()) {
		case ETHERNET_TYPE_IPV4:
			showIpv4Info(ef.getData());
			break;
		case ETHERNET_TYPE_IPV6:
			showIpv6Info(ef.getData());
			break;
		case ETHERNET_TYPE_ARP:
			showArpInfo(ef.getData());
			break;
		default:
			break;
	}
}

void showIpv4Info(const char* bytes)
{
	Ipv4Frame ipv4F;
	ipv4F.fromBytes(bytes);
	cout << "IPV4" << endl;
	cout << "\tVersión: " << dec <<ipv4F.getVersion()<< endl;
	cout << "\tIHL: " << ipv4F.getIhl() << " palabras"<< endl;

	cout << "\tServicios Diferenciados: " << ipv4F.getService() << endl;
	cout << "\t\tDCSP: " << ipv4F.getDscpAsString() << endl;
	cout << "\t\tECN: " << ipv4F.getEcnAsString() << endl;


	cout << "\tLongitud total: " << dec << ipv4F.getTotalLength() << endl; cout << "\tID: 0x" << hex << ipv4F.getId() << " (" << dec << ipv4F.getId() <<")"<< endl;
	cout << "\tFlags: " << 0 << ipv4F.getDf() << ipv4F.getMf();

	if (ipv4F.getDf())
		cout << " (Don't Fragment)";
	else
		cout << " (Fragment)";

	if (ipv4F.getMf())
		cout << " (More Fragments)";
	else
		cout << " (No More Fragments)";

	cout << endl;

	cout << "\tDesplazamiento: " << ipv4F.getOffset() << endl;
	cout << "\tTTL: "  << ipv4F.getTtl() << endl;
	cout << "\tProtocolo: " << ipv4F.getProtocolAsString() << " (" << ipv4F.getProtocol() << ")" << endl;
	cout << "\tCheckSum: 0x" << hex << ipv4F.getCheckSum() <<endl;
	cout << "\tDirección de origen: " << ipv4F.getSourceAddressAsString() << endl;
	cout << "\tDirección de destino: " << ipv4F.getDestinationAddressAsString() << endl;

	switch (ipv4F.getProtocol()) {
		case IP_PROTOCOL_ICMP:
			showIcmpv4Info(ipv4F.getPayload());
			break;
		case IP_PROTOCOL_TCP:
			showTcpInfo(ipv4F.getPayload(), ipv4F.getPayloadLength());
			break;
		case IP_PROTOCOL_UDP:
			showUdpInfo(ipv4F.getPayload());
			break;
		default:
			break;
	}
}

void showIpv6Info(const char* bytes)
{
	Ipv6Frame ipv6F;
	ipv6F.fromBytes((const unsigned char*)bytes);

	cout << "IPV6" << endl;
	cout << "\tVersión: " << dec << ipv6F.getVersion()<< endl;

	cout << "\tServicios diferenciados: " << ipv6F.getTrafficClass() << endl;
	cout << "\t\tDCSP: " << Ipv4Frame::dscpToString(ipv6F.getTrafficClass() >> 2) << endl;
	cout << "\t\tECN: " << Ipv4Frame::ecnToString(ipv6F.getTrafficClass() & 0b11) << endl;

	cout << "\tLongitud de contenido: " << dec << ipv6F.getPayloadLength() << " bytes" << endl;

	cout << "\tSiguiente encabezado: " << ipv6F.getNextHeader() << " (" << Ipv4Frame::protocolToString(ipv6F.getNextHeader()) << ")" << endl;
	cout << "\tLímite de saltos: "  << ipv6F.getHopLimit() << endl;

	cout << "\tDirección de origen: " << Ipv6Frame::addressToString(ipv6F.getSourceAddress()) << endl;
	cout << "\tDirección de destino: " << Ipv6Frame::addressToString(ipv6F.getDestinationAddress()) << endl;

	switch (ipv6F.getNextHeader()) {
		case IP_PROTOCOL_TCP:
			showTcpInfo(ipv6F.getPayload(), ipv6F.getPayloadLength());
			break;
		case IP_PROTOCOL_UDP:
			showUdpInfo(ipv6F.getPayload());
			break;
		case IP_PROTOCOL_ICMPV6:
			showIcmpv6Info(ipv6F.getPayload());
			break;
		default:
			break;
	}
}

void showArpInfo(const char* bytes)
{
	ArpFrame arpf;
	arpf.fromBytes(bytes);

	cout << "ARP" << endl;

	cout << "\tTipo de Hardware: " << ArpFrame::hardwareTypeAsString(arpf.getHardwareType())
		<< "(" << hex << "0x" << arpf.getHardwareType() << ")" << endl;
	cout << "\tTipo de Protocolo: " << ArpFrame::protocolTypeAsString(arpf.getProtocolType())
		<< "(" << hex << "0x" << arpf.getProtocolType() << ")" << endl;
	cout << "\tLongitud de dirección de hardware: " << dec << arpf.getHardwareAddressLength() << " bytes" << endl;
	cout << "\tLongitud de dirección de protocolo: " << dec << arpf.getProtocolAddressLength() << " bytes" << endl;
	cout << "\tOperación: " << arpf.operationAsString(arpf.getOperation()) << " (" << dec << arpf.getOperation() << ")" << endl;
	cout << "\tDirección de hardware origen: " << hex << EthernetFrame::addressAsString(arpf.getSenderHardwareAddress()) << endl;
	cout << "\tDirección de protocolo origen: " << arpf.addressToString(arpf.getSenderProtocolAddress()) << endl;

	cout << "\tDirección de hardware destino: " << hex << EthernetFrame::addressAsString(arpf.getTargetHardwareAddress()) << endl;
	cout << "\tDirección de protocolo destino: " << arpf.addressToString(arpf.getTargetProtocolAddress()) << endl;
}

void showTcpInfo(const char* bytes, unsigned length)
{
	TcpFrame tcpF;
	tcpF.fromBytes(bytes, length);
	cout << "TCP" << endl;
	cout << "\tPuerto de origen: " << dec << tcpF.getSourcePort()
		<< " (" << knownPortAsString(tcpF.getSourcePort()) << ")" << endl;
	cout << "\tPuerto de destino: " << dec << tcpF.getDestinationPort()
		<< " (" << knownPortAsString(tcpF.getDestinationPort()) << ")" << endl;
	cout << "\tNúmero de secuencia: " << dec << tcpF.getSequenceNumber() << endl;
	cout << "\tNúmero de acuse de recibo: " << dec << tcpF.getAcknowledgementNumber() << endl;
	cout << "\tLongitud de cabecera: " << dec << (tcpF.getHeaderLength() * 4) << " bytes" << endl;
	cout << "\tBanderas: " << endl;
	cout << "\t\t" << tcpF.getFlagsAsString() << endl;
	cout << "\tTamaño de ventana: " << tcpF.getWindow() << endl;
	cout << "\tChecksum: 0x" << hex << tcpF.getCheckSum() << endl;
	// solo muestra puntero urgente si está la bandera URG
	if (tcpF.getFlags() & 0b000100000)
		cout << "\tPuntero urgente: " << dec << tcpF.getUrgentPointer() << endl;

	if (tcpF.getDestinationPort() == 53 || tcpF.getSourcePort() == 53) {
		showDnsInfo(tcpF.getPayload());
	} else {
		cout << "\tContenido: " << endl;
		for (unsigned i(0); i < (length - tcpF.getHeaderLength() * 4); i++)
			cout << hex << ((unsigned)tcpF.getPayload()[i] & 0xFF) << " ";
		cout << endl;
	}
}

void showUdpInfo(const char* bytes)
{
	UdpFrame udpF;
	udpF.fromBytes(bytes);

	cout << "UDP" << endl;
	cout << "\tPuerto de origen: " << dec << udpF.getSourcePort()
		<< " (" << knownPortAsString(udpF.getSourcePort()) << ")" << endl;
	cout << "\tPuerto de destino: " << dec << udpF.getDestinationPort()
		<< " (" << knownPortAsString(udpF.getDestinationPort()) << ")" << endl;
	cout << "\tLongitud: " << dec << udpF.getLength() << " bytes." << endl;
	cout << "\tChecksum: 0x" << hex << udpF.getCheckSum() << endl;

	if (udpF.getDestinationPort() == 53 || udpF.getSourcePort() == 53) {
		showDnsInfo(udpF.getPayload());
	} else {
		cout << "\tContenido: " << endl;
		for (unsigned i(0); i < udpF.getLength(); i++)
			cout << hex << ((unsigned)udpF.getPayload()[i] & 0xFF) << " ";
		cout << endl;
	}
}

void showIcmpv4Info(const char* bytes)
{
	Icmpv4Frame icmpv4F = Icmpv4Frame();
	icmpv4F.fromBytes(bytes);
	cout << "ICMP" << endl;
	cout << "\tTipo: " << dec << icmpv4F.getType() << " (" << icmpv4F.getTypeAsAstring() << ")"<< endl;
	cout << "\tCódigo: " << dec << icmpv4F.getCode() << " (" << icmpv4F.getCodeAsAstring() << ")"<< endl;
	cout << "\tChecksum: 0x" << hex << icmpv4F.getCheckSum() << endl;
	cout << "\tContenido: "
		<< hex << (unsigned)icmpv4F.getContent()[0] << " "
		<< (unsigned)icmpv4F.getContent()[1] << " "
		<< (unsigned)icmpv4F.getContent()[2] << " "
		<< (unsigned)icmpv4F.getContent()[3] << endl;
}

void showIcmpv6Info(const char* bytes)
{
	Icmpv6Frame icmpv6F;
	icmpv6F.fromBytes(bytes);

	cout << "ICMPv6" << endl;
	cout << "\tTipo: "
		<< Icmpv6Frame::typeToString(icmpv6F.getType())
		<< " (" << dec <<  icmpv6F.getType() << ")" << endl;
	cout << "\tCódigo: "
		<< Icmpv6Frame::codeToString(icmpv6F.getType(), icmpv6F.getCode())
		<< " (" << dec <<  icmpv6F.getCode() << ")" << endl;
	cout << "\tContenido: "
		<< hex
		<< (unsigned)icmpv6F.getContent()[0]
		<< " " << (unsigned)icmpv6F.getContent()[1]
		<< " " << (unsigned)icmpv6F.getContent()[2]
		<< " " << (unsigned)icmpv6F.getContent()[3]
		<< endl;
}

void showDnsInfo(const char* bytes)
{
	DnsFrame dnsF(bytes);
	cout << "DNS" << endl;
	cout << "\tID: " << dnsF.getId() << endl;

	if (dnsF.isResponse()) {
		cout << "\tEs respuesta (QR: 1)" << endl;
	} else {
		cout << "\tEs consulta (QR: 0)" << endl;
	}

	cout << "\tCódigo de operación: " << dnsF.getOpCode() << " (" << dnsF.opCodeAsString(dnsF.getOpCode()) << ")" << endl;
	cout << "\tBanderas: " << endl;

	cout << "\t\t";

	if (dnsF.getFlags() & 0b1000) {
		cout << "AA ";
	}

	if (dnsF.getFlags() & 0b0100) {
		cout << "TC ";
	}

	if (dnsF.getFlags() & 0b0010) {
		cout << "RD ";
	}

	if (dnsF.getFlags() & 0b0001) {
		cout << "RA";
	}
	cout << endl;

	cout << "\tRcode: " << dnsF.getRcode() << " (" << dnsF.rCodeAsString(dnsF.getRcode()) << ")" << endl;
	cout << "\tQD count: " << dnsF.getQdCount() << endl;
	cout << "\tAN count: " << dnsF.getAnCount() << endl;
	cout << "\tNS count: " << dnsF.getNsCount() << endl;
	cout << "\tAR count: " << dnsF.getArCount() << endl;
}

string knownPortAsString(unsigned port)
{
	switch (port) {
		case 20: case 21:
			return "FTP";
		case 22:
			return "SSH";
		case 23:
			return "TELNET";
		case 25:
			return "SMTP";
		case 53:
			return "DNS";
		case 67: case 68:
			return "DHCP";
		case 69:
			return "TFTP";
		case 80:
			return "HTTP";
		case 110:
			return "POP3";
		case 143:
			return "IMAP";
		case 443:
			return "HTTPS";
		case 993:
			return "IMAP SSL";
		case 995:
			return "POP SSL";
		default:
			return "Desconocido";
	}
}
