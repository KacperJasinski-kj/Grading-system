#include <algorithm>
#include <fstream>
#include <iostream>
#include <vector>
#include <string>

double notas;
std::string nombre;
int cantidadAlumnos;
int cantidadNotas;
double media = 0.0;
std::vector<std::string> alumnos;
std::vector<double> mediaAlumnos;

void menu() {
    std::cout << "\n1. Introducir nombre y notas\n";
    std::cout << "2. Mostrar resumen de alumnos\n";
    std::cout << "3. Mostrar estadisticas de la clase\n";
    std::cout << "4. Buscar alumno por nombre\n";
    std::cout << "5. Salir\n";
    std::cout << "Ingrese opcion: ";
}


void agregarAlumnosYNotas() {

    std::cout << "Ingrese la cantidad de alumnos:";
    std::cin >> cantidadAlumnos;

    if (cantidadAlumnos < 0) {
        std::cout << "La cantidad de alumnos debe ser mayor que 0";
    }

    std::cout << "Ingrese la cantidad de notas:";
    std::cin >> cantidadNotas;

    if (cantidadNotas < 0) {
        std::cout << "La cantidad de notas debe ser mayor que 0";
    }


    for (int i = 0; i < alumnos.size(); i++) {
        double sumaNotas = 0.0;

        std::cout << "Ingrese nombre del alumno: ";
        std::cin >> nombre;

        //añade nombre al array
        alumnos.push_back(nombre);

        for (int j = 0; j < cantidadNotas; j++) {
            notas = -1;

            while (notas < 0 || notas > 10) {
                std::cout << "Ingrese la nota del alumno/a: ";
                std::cin >> notas;
            }
            sumaNotas += notas;
        }

        media = sumaNotas / cantidadNotas;
        mediaAlumnos.push_back(media);
    }
}

std::string estado(double media) {
    if (media >= 5) {
        return "Estado: Aprobado\n";
    } else {
        return "Estado: Suspendido\n";
    }
}

void resumenAlumnosYNotas() {
    std::cout << "Cantidad de alumnos: " << cantidadAlumnos << std::endl;

    for (int i = 0; i < alumnos.size(); i++) {
        std::cout << "\n----------------------------------------\n";
        std::cout << "Alumno : " << alumnos[i] << "\n";


        std::cout << "Media: " << mediaAlumnos[i] << "\n";

        std::cout << estado(mediaAlumnos[i]);

    }
}


void estadisticas() {
}

//boolean para hacer funcion equalsIgnoreCase de java

bool equalsIgnoreCase(std::string texto1, std::string texto2) {
    std::transform(texto1.begin(), texto1.end(), texto1.begin(), ::tolower);
    std::transform(texto2.begin(), texto2.end(), texto2.begin(), ::tolower);

    return texto1 == texto2;
}

void buscarAlumnosYNotas() {
    std::cout << "Ingrese el nombre del alumno:";
    std::cin >> nombre;

    if (nombre.empty()) {
        std::cout << "Este campo no puede estar vacío";
    } else {
        for (int i = 0; i < alumnos.size(); i++) {
            if (equalsIgnoreCase(nombre, alumnos[i])) {
                std::cout << "Alumno: " << alumnos[i]
                        << "; Media: " << mediaAlumnos[i]
                        << "; " << estado(mediaAlumnos[i])
                        << std::endl;
            }
        }
    }
}

void guardarAlumnos() {
    std::ofstream archivo("alumnos.txt");

    if (!archivo.is_open()) {
        std::cout << "Error: no se pudo crear o abrir el archivo alumnos.txt\n";
        return;
    }

    for (int i = 0; i < alumnos.size(); i++) {
        archivo << alumnos[i] << " " << mediaAlumnos[i] << std::endl;
    }

    archivo.close();

    std::cout << "Alumnos guardados correctamente en alumnos.txt\n";
}

void cargarAlumnos() {
    std::ifstream archivo("alumnos.txt");

    if (!archivo.is_open()) {
        std::cout << "No hay archivo alumnos.txt todavía.\n";
        return;
    }

    std::string nombreArchivo;
    double mediaArchivo;

    while (archivo >> nombreArchivo >> mediaArchivo) {
        alumnos.push_back(nombreArchivo);
        mediaAlumnos.push_back(mediaArchivo);
    }

    archivo.close();

    cantidadAlumnos = alumnos.size();
}

int main() {
    cargarAlumnos();
    int opcional = 0;

    while (opcional != 5) {
        menu();
        std::cin >> opcional;

        switch (opcional) {
            case 1:
                agregarAlumnosYNotas();
                guardarAlumnos();
                break;
            case 2:
                resumenAlumnosYNotas();
                break;
            case 3:
                estadisticas();
                break;
            case 4:
                buscarAlumnosYNotas();
                break;
            case 5:
                std::cout << "Hasta la proxima!";
                break;
            default:
                std::cout << "Ingrese una opcion valida";
        }
    }
    return 0;
}
