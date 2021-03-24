#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <exception>

#include "../include/EthernetFrame.hpp"
#include "../include/Ipv4Frame.hpp"

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
	if (ef.getType() == ETHERNET_TYPE_IPV4) {
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
	} else {

	}

	free(buffer);
	binFile.close();

	return EXIT_SUCCESS;
}
