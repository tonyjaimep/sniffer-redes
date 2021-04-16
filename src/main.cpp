#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <exception>

#include "../include/EthernetFrame.hpp"
#include "../include/Ipv4Frame.hpp"
#include "../include/Icmpv4Frame.hpp"
#include "../include/ArpFrame.hpp"

using namespace std;

int main()
{
	EthernetFrame ef;
	Ipv4Frame ipv4F;
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
		<< " (" << setfill('0') << setw(4) << hex << ef.getType() << ")" << endl;

	//ipv4
	switch (ef.getType()) {
	case ETHERNET_TYPE_IPV4:
		ipv4F.fromBytes(ef.getData());
		cout << "IPV4" << endl;
		cout << "\tVersión: " << dec <<ipv4F.getVersion()<< endl;
		cout << "\tIHL: " << ipv4F.getIhl() << " palabras"<< endl;

		cout << "\tServicios Diferenciados: " << ipv4F.getService() << endl;
		cout << "\t\tDCSP: " << ipv4F.getDscpAsString() << endl;
		cout << "\t\tECN: " << ipv4F.getEcnAsString() << endl;
		

		cout << "\tLongitud total: " << dec << ipv4F.getTotalLength() << endl;
		cout << "\tID: 0x" << hex << ipv4F.getId() << " (" << dec << ipv4F.getId() <<")"<< endl;
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

		if (ipv4F.getProtocol() == IP_PROTOCOL_ICMP) {
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
		}

		break;
	case ETHERNET_TYPE_ARP:
		ArpFrame arpf;
		arpf.fromBytes(ef.getData());

		cout << "ARP" << endl;
		cout << "\tTipo de Hardware: " << ArpFrame::hardwareTypeAsString(arpf.getHardwareType())
			<< "(" << hex << "0x" << arpf.getHardwareType() << ")" << endl;
		cout << "\tTipo de Protocolo: " << ArpFrame::protocolTypeAsString(arpf.getProtocolType())
			<< "(" << hex << "0x" << arpf.getProtocolType() << ")" << endl;
		cout << "\tLongitud de dirección de hardware: " << dec << arpf.getHardwareAddressLength() << " bytes" << endl;
		cout << "\tLongitud de dirección de protocolo: " << dec << arpf.getProtocolAddressLength() << " bytes" << endl;
		cout << "\tOperación: " << hex << "0x" << arpf.getOperation() << endl;
		cout << "\tDirección de hardware origen: " << hex << arpf.getSenderHardwareAddress() << endl;
		cout << "\tDirección de protocolo origen: " << hex << arpf.getSenderProtocolAddress() << endl;

		cout << "\tDirección de hardware destino: " << hex << arpf.getTargetHardwareAddress() << endl;
		cout << "\tDirección de protocolo destino: " << hex << arpf.getTargetProtocolAddress() << endl;

		break;
	}

	free(buffer);
	binFile.close();

	return EXIT_SUCCESS;
}
