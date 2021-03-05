#include <iostream>
#include <fstream>
#include <string>
#include <exception>

#include <EthernetFrame.hpp>

using namespace std;

int main()
{
	EthernetFrame ef;
	string filename;
	ifstream binFile;
	char* buffer;

	cout << "Analizador de Paquetes Ethernet" << endl;
	cout << "Equipo 5 de la sección D03" << endl << endl;

	while (!binFile) {
		cout << "Introduzca la localización del paquete (vacío para cancelar): ";
		cin >> filename;

		if (filename.size() == 0)
			return EXIT_SUCCESS;

		binFile.open(filename, ifstream::in | ifstream::binary);

		if (!binFile)
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

	/* TODO: imprimir datos de ef
	// falta implementar setters/getters
	//
	// ef.setData(binFile.read(buffer, length));
	//
	// cout << "Dirección de destino: " << hex << ef.getDestinationAddress() << endl;
	// cout << "Dirección de origen: " << hex << ef.getSourceAddress() << endl;
	// cout << "Tipo: " << hex << ef.getType() << endl;
	// cout << "Contenido: " << ef.getData() << endl;
	*/

	binFile.close();

	return EXIT_SUCCESS;
}
