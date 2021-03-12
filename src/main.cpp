#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <exception>

#include <EthernetFrame.hpp>

using namespace std;

int main()
{
	EthernetFrame ef;
	Ipv4 ;
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

	cout << "Tamaño del contenido: " << endl;
	cout << sizeof(ef.getData()) << endl;

	cout << endl;

	// ********************************
	//             IPV4
	// ********************************
	// HAY QUE MOSTRAR:
	// Versión
	// IHL
	// Servicios Diferenciados
	// Longitud total
	// Identificación
	// Banderas (3 bits)
	// DF, MF
	// Desplazamiento
	// TTL
	// Protocolo
	// Checksum
	// Dirección origen y destino

	free(buffer);
	binFile.close();

	return EXIT_SUCCESS;
}
