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

using namespace std;

int main()
{
	EthernetFrame ef;
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

	// ********************************
	//           ETHERNET
	// ********************************
	ef.fromBytes(buffer, length);

	cout << "Ethernet" << endl;

	cout << "\tDirección de destino: " << ef.addressAsString(ef.getDestinationAddress()) << endl;
	cout << "\tDirección de origen: " << ef.addressAsString(ef.getSourceAddress()) << endl;
	cout << "\tTipo: " << ef.typeAsString(ef.getType())
		<< " (0x" << setfill('0') << setw(4) << hex << ef.getType() << ")" << endl;

	switch (ef.getType()) {
		case ETHERNET_TYPE_IPV4: {
			Ipv4Frame ipv4F;
			ipv4F.fromBytes(ef.getData());
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
				case IP_PROTOCOL_ICMP: {
					Icmpv4Frame icmpv4F = Icmpv4Frame();
					icmpv4F.fromBytes(ipv4F.getPayload());
					cout << "ICMP" << endl;
					cout << "\tTipo: " << dec << icmpv4F.getType() << " (" << icmpv4F.getTypeAsAstring() << ")"<< endl;
					cout << "\tCódigo: " << dec << icmpv4F.getCode() << " (" << icmpv4F.getCodeAsAstring() << ")"<< endl;
					cout << "\tChecksum: 0x" << hex << icmpv4F.getCheckSum() << endl;
					cout << "\tContenido: "
						<< hex << (unsigned)icmpv4F.getContent()[0] << " "
						<< (unsigned)icmpv4F.getContent()[1] << " "
						<< (unsigned)icmpv4F.getContent()[2] << " "
						<< (unsigned)icmpv4F.getContent()[3] << endl;
					break;
				}
				case IP_PROTOCOL_TCP: {
					TcpFrame tcpF;
					tcpF.fromBytes(ipv4F.getPayload(), ipv4F.getPayloadLength());
					cout << "TCP" << endl;
					cout << "\tPuerto de origen: " << dec << tcpF.getSourcePort() << endl;
					cout << "\tPuerto de destino: " << dec << tcpF.getDestinationPort() << endl;
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
					// mostrar datos
					cout << "\tContenido: " << endl;
					cout << "\t\tContenido: " << endl;
					for (unsigned i(0); i < (ipv4F.getPayloadLength() - tcpF.getHeaderLength() * 4); i++)
						cout << hex << ((unsigned)tcpF.getPayload()[i] & 0xFF) << " ";
					cout << endl;

					for (unsigned i(0); i < (ipv4F.getPayloadLength() - tcpF.getHeaderLength() * 4); i++)
						cout << tcpF.getPayload()[i] << " ";
					cout << endl;
				}
			}

			break;
		}
		case ETHERNET_TYPE_IPV6: {
			Ipv6Frame ipv6F;
			ipv6F.fromBytes((const unsigned char*)ef.getData());

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
			case IP_PROTOCOL_ICMPV6: {
				Icmpv6Frame icmpv6F;
				icmpv6F.fromBytes(ipv6F.getPayload());

				std::cout << "ICMPv6" << std::endl;
				std::cout << "\tTipo: "
					<< Icmpv6Frame::typeToString(icmpv6F.getType())
					<< " (" << dec <<  icmpv6F.getType() << ")" << std::endl;
				std::cout << "\tCódigo: "
					<< Icmpv6Frame::codeToString(icmpv6F.getType(), icmpv6F.getCode())
					<< " (" << dec <<  icmpv6F.getCode() << ")" << std::endl;
				std::cout << "\tContenido: "
					<< hex
					<< (unsigned)icmpv6F.getContent()[0]
					<< " " << (unsigned)icmpv6F.getContent()[1]
					<< " " << (unsigned)icmpv6F.getContent()[2]
					<< " " << (unsigned)icmpv6F.getContent()[3]
					<< std::endl;
				break;
			}
			default:
				break;
			}

			break;
		}
		case ETHERNET_TYPE_ARP: {
			ArpFrame arpf;
			arpf.fromBytes(ef.getData());

			cout << "ARP" << endl;

			cout << "\tTipo de Hardware: " << ArpFrame::hardwareTypeAsString(arpf.getHardwareType())
				<< "(" << hex << "0x" << arpf.getHardwareType() << ")" << endl;
			cout << "\tTipo de Protocolo: " << ArpFrame::protocolTypeAsString(arpf.getProtocolType())
				<< "(" << hex << "0x" << arpf.getProtocolType() << ")" << endl;
			cout << "\tLongitud de dirección de hardware: " << dec << arpf.getHardwareAddressLength() << " bytes" << endl;
			cout << "\tLongitud de dirección de protocolo: " << dec << arpf.getProtocolAddressLength() << " bytes" << endl;
			cout << "\tOperación: " << arpf.operationAsString(arpf.getOperation()) << " (" << dec << arpf.getOperation() << ")" << endl;
			cout << "\tDirección de hardware origen: " << hex << ef.addressAsString(arpf.getSenderHardwareAddress()) << endl;
			cout << "\tDirección de protocolo origen: " << arpf.addressToString(arpf.getSenderProtocolAddress()) << endl;

			cout << "\tDirección de hardware destino: " << hex << ef.addressAsString(arpf.getTargetHardwareAddress()) << endl;
			cout << "\tDirección de protocolo destino: " << arpf.addressToString(arpf.getTargetProtocolAddress()) << endl;

			break;
		}
	}

	free(buffer);
	binFile.close();

	return EXIT_SUCCESS;
}
