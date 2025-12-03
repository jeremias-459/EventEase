#include <iostream>
#include<locale>
#include <string>
#include <iomanip>
#include <fstream>   

using namespace std;

const int DIAS = 6;
const int HORAS = 6;

string nombresDias[DIAS] = { "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado" };
string horas[HORAS] = { "08:00-09:00", "09:00-10:00", "10:00-11:00", "11:00-12:00", "14:00-15:00", "15:00-16:00" };

struct Curso {
    string nombre;
    string aula;
    string docente;
};

void Mostrar_calendario(Curso horario[DIAS][HORAS]) {

    cout << "\n========= CALEB CALENDAR =========\n\n";

    cout << setw(10) << left << "Dia/Hora";

    for (int h = 0; h < HORAS; h++) {
    
        cout << setw(20) << horas[h];
    }
    
    cout << "\n";

    for (int d = 0; d < DIAS; d++) {
    
        cout << setw(10) << left << nombresDias[d];
        
        for (int h = 0; h < HORAS; h++) {
        
            if (horario[d][h].nombre == "")
            
                cout << setw(20) << "-";
            
            else {
                cout << setw(20) << horario[d][h].nombre;
            }
        }

        cout << "\n";
    }
}


void GuardarArchivo(Curso horario[DIAS][HORAS]) {

    ofstream archivo("CaletCalender.txt");

    if (!archivo.is_open()) {
        cout << "Error al abrir archivo para guardar.\n";
        return;
    }

    for (int d = 0; d < DIAS; d++) {
        for (int h = 0; h < HORAS; h++) {
            archivo << d << "|"
                << h << "|"

                << horario[d][h].nombre << "|"
                
                << horario[d][h].aula << "|"
                
                << horario[d][h].docente << "\n";
        }
    }

    archivo.close();

    cout << "\n*** Archivo guardado correctamente ***\n";

}


void CargarArchivo(Curso horario[DIAS][HORAS]) {

    ifstream archivo("CaletCalender.txt");

    if (!archivo.is_open()) {

        cout << "No existe archivo previo. Se inicia vacío.\n";
        
        return;
    }

    string linea;

    while (getline(archivo, linea)) {

        int pos = 0;
        
        int campo = 0;
        
        string temp[5];

        string dato = "";


        for (int i = 0; i <= linea.length(); i++) {
          
            if (i == linea.length() || linea[i] == '|') {
            
                temp[campo] = dato;
                
                dato = "";
                
                campo++;
            }
            
            else {
            
                dato += linea[i];
            }
        }

        int d = stoi(temp[0]);

        int h = stoi(temp[1]);

        horario[d][h].nombre = temp[2];
        
        horario[d][h].aula = temp[3];
        
        horario[d][h].docente = temp[4];
    }

    archivo.close();

    cout << "--- Archivo cargado correctamente ---\n";
}


void MostrarMenu() {

    cout << "\n================";
    cout << "\n      MENU   ";
    cout << "\n================\n";

    cout << "1. Registrar cursos\n";

    cout << "2. Lista de horario completo\n";
    
    cout << "3. Mostrar clases de un dia\n";
    
    cout << "4. Contar horas de un curso\n";
    
    cout << "5. Mostrar calendario\n";
    
    cout << "6. Guardar en archivo\n";
    
    cout << "7. Salir\n\n";

    cout << "Seleccionar una opcion: ";
}


void RegistrarCurso(Curso horario[DIAS][HORAS]) {

    cin.ignore();

    for (int d = 0; d < DIAS; d++) {

        cout << "\n--- " << nombresDias[d] << " ---\n";

        for (int h = 0; h < HORAS; h++) {

            cout << horas[h] << " -> Nombre del curso: ";
            getline(cin, horario[d][h].nombre);

            cout << "Aula: ";
            getline(cin, horario[d][h].aula);

            cout << "Docente: ";
            getline(cin, horario[d][h].docente);

            cout << endl;
        }
    }
}

void ListarHorario(Curso horario[DIAS][HORAS]) {

    for (int d = 0; d < DIAS; d++) {

        cout << "\n" << nombresDias[d] << ":\n";

        for (int h = 0; h < HORAS; h++) {

            cout << horas[h] << " -> ";

            if (horario[d][h].nombre == "") {
             
                cout << "(vacío)\n";
            }
            else {
                cout << horario[d][h].nombre << " | Aula: " << horario[d][h].aula << " | Docente: " << horario[d][h].docente << endl;
            }
        }
    }
}


void MostrarDia(Curso horario[DIAS][HORAS], int dia) {

    if (dia < 0 || dia >= DIAS) {

        cout << "Dia invalido\n";
        
        return;
    }

    cout << "\nHorario de " << nombresDias[dia] << ":\n";

    for (int h = 0; h < HORAS; h++) {

        cout << horas[h] << " -> ";

        if (horario[dia][h].nombre == "") {

            cout << "(vacío)\n";
        }
        else {
            cout << horario[dia][h].nombre << " | Aula: " << horario[dia][h].aula << " | Docente: " << horario[dia][h].docente << endl;
        }
    }
}


int ContarCurso(Curso horario[DIAS][HORAS], string curso) {

    int contador = 0;

    for (int d = 0; d < DIAS; d++) {

        for (int h = 0; h < HORAS; h++) {
        
            if (horario[d][h].nombre == curso) {
            
                contador++;
            
            }
        }
    }

    return contador;
}



int main() {
    setlocale(LC_ALL, "spanish");

    Curso horario[DIAS][HORAS];

    int  opcion;
   
    int dia;
    
    string curso;
    
    int horasCurso;

    // Inicializar vacío
    for (int d = 0; d < DIAS; d++)
    
        for (int h = 0; h < HORAS; h++)
        
            horario[d][h].nombre = "";
    
    Mostrar_calendario(horario);
    
    system("PAUSE");

    
    do {

        MostrarMenu();
        cin >> opcion;

        switch (opcion) {

        case 1:
            RegistrarCurso(horario);
        case 2:

            ListarHorario(horario);


        case 3:
            cout << "\nIngrese el número del día (1-6): ";
            cin >> dia;
            MostrarDia(horario, dia - 1);
            break;
        case 4:
            cout << "\n Ingrese el nombre del curso: ";
            cin >> curso;
            horasCurso = ContarCurso(horario, curso);

            cout << "El curso " << curso << " tiene " << horasCurso << " horas en la semana.\n";
            break;

        case 5:
            Mostrar_calendario(horario);

            break;
        case 6:
            GuardarArchivo(horario);
            break;
        case 7:
            cout << "Saliendo ...";

            break;
        default:

            cout << "Opcion invalida!\n";
        }

    } while (opcion != 7);

    return 0;
}