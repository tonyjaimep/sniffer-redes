#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <exception>

#include <EthernetFrame.hpp>
#include <Ipv4Frame.hpp>

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

	cout << "Dirección de destino: " << ef.addressAsString(ef.getDestinationAddress()) << endl;
	cout << "Dirección de origen: " << ef.addressAsString(ef.getSourceAddress()) << endl;
	cout << "Tipo: " << setfill('0') << setw(4) << hex << ef.getType()
		<< " (" << ef.typeAsString(ef.getType()) << ")"
		<< endl;
	//ipv4
	
	ipv4F.fromBytes(ef.getData());
	cout<<"versión: "<< dec <<ipv4F.getVersion()<<endl;
	cout<<"IHL: "<<ipv4F.getIhl()<<endl;
	cout<<"Servicios diferenciados: "<<ipv4F.getService()<<endl;
	cout<<"Longitud total: "<<ipv4F.getTotalLength()<<endl;
	cout<<"Id: "<<ipv4F.getId()<<endl;
	cout<<"Flags: "<<0<<ipv4F.getDf()<<ipv4F.getMf()<<endl;
	cout<<"Desplazamiento: "<<ipv4F.getOffset()<<endl;
	cout<<"TTL: "<<ipv4F.getTtl()<<endl;
	cout<<"Protocolo: "<<ipv4F.getProtocol()<<endl;
	//cout<<"CheckSum: "<<ipv4F.get<<endl;
	free(buffer);
	binFile.close();

	return EXIT_SUCCESS;
}
