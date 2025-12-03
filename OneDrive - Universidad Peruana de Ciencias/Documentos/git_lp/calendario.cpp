#include <iostream>
#include <locale>
#include <string>
#include <iomanip>
#include <fstream>   
#include <cstdlib> 


using namespace std;


const int DIAS = 6;
const int HORAS = 6;


string nombresDias[DIAS] = { "Lunes", "Martes", "Miercoles", "Jueves", "Viernes", "Sabado" };
string horas[HORAS] = { "08:00-09:00", "09:00-10:00", "10:00-11:00", "11:00-12:00", "14:00-15:00", "15:00-16:00" };


struct Curso
{

    string nombre;
    string aula;
    string docente;

};


void Presentacion()
{

    cout << "=========================================\n";
    cout << "      BIENVENIDO AL GESTOR DE HORARIOS   \n";
    cout << "              CALEB CALENDER             \n";
    cout << "=========================================\n\n";
    cout << "Presione Enter para continuar...";
    cin.get();
    system("cls");

}


void Despedida()
{

    system("cls");
    cout << "\n=========================================\n";
    cout << "      GRACIAS POR USAR EL SISTEMA        \n";
    cout << "=========================================\n";
    cout << "Presione Enter para cerrar...";
    cin.ignore();
    cin.get();

}


void BuscarCurso(Curso horario[DIAS][HORAS])
{

    string buscar;
    bool encontrado;
    int totalHoras = 0;

    encontrado = false;

    system("cls");

    cout << "\n=== BUSQUEDA DE CURSO ===\n";

    cout << "Ingrese el nombre exacto del curso a buscar: ";

    cin.ignore();
    getline(cin, buscar);

    cout << "\nResultados para '" << buscar << "':\n";
    cout << "--------------------------------------------------\n";

    for (int d = 0; d < DIAS; d++)
    {

        for (int h = 0; h < HORAS; h++)
        {

            if (horario[d][h].nombre == buscar) {
                cout << "-> DIA: " << nombresDias[d]
                    << " | HORA: " << horas[h]
                    << " | AULA: " << horario[d][h].aula
                    << " | DOCENTE: " << horario[d][h].docente << endl;

                encontrado = true;
                totalHoras++;

            }

        }

    }

    if (!encontrado)
    {

        cout << "\n[INFO] No se encontro ningun curso con ese nombre.\n";

    }

    else
    {

        cout << "--------------------------------------------------\n";
        cout << "TOTAL DE HORAS SEMANALES: " << totalHoras << " horas.\n";

    }

    cout << "--------------------------------------------------\n";

}


void ExportarExcel(Curso horario[DIAS][HORAS])
{

    ofstream archivo("Horario_Excel.csv");

    if (archivo.is_open()) {

        archivo << "DIA / HORA";

        for (int h = 0; h < HORAS; h++)
        {

            archivo << ";" << horas[h];

        }


        archivo << "\n";

        for (int d = 0; d < DIAS; d++) {

            archivo << nombresDias[d];

            for (int h = 0; h < HORAS; h++)
            {

                archivo << ";";

                if (horario[d][h].nombre != "")
                {

                    archivo << horario[d][h].nombre << " (" << horario[d][h].aula << ")";

                }

                else
                {

                    archivo << "-";

                }

            }

            archivo << "\n";

        }

        archivo.close();

        cout << "\nArchivo 'Horario_Excel.csv' creado.\n";

    }

    else
    {

        cout << "Error al crear archivo Excel.\n";

    }

}


void GuardarTXT(Curso horario[DIAS][HORAS])
{

    ofstream archivo("Horario_Visual.txt");

    if (archivo.is_open()) {

        archivo << "====================================================================================================================\n";
        archivo << "                                              CALEB CALENDAR - HORARIO SEMANAL                                      \n";
        archivo << "====================================================================================================================\n";

        archivo << setw(12) << left << " DIA/HORA " << "|";

        for (int h = 0; h < HORAS; h++)
        {

            archivo << setw(20) << horas[h] << "|";

        }

        archivo << "\n------------|--------------------|--------------------|--------------------|--------------------|--------------------|--------------------|\n";

        for (int d = 0; d < DIAS; d++)
        {

            archivo << setw(12) << left << nombresDias[d] << "|";

            for (int h = 0; h < HORAS; h++)
            {

                if (horario[d][h].nombre == "")
                {

                    archivo << setw(20) << " - " << "|";

                }
                else {

                    string texto = horario[d][h].nombre + " (" + horario[d][h].aula + ")";

                    if (texto.length() > 19)
                    {

                        texto = texto.substr(0, 19);

                    }

                    archivo << setw(20) << texto << "|";

                }

            }

            archivo << "\n------------|--------------------|--------------------|--------------------|--------------------|--------------------|--------------------|\n";

        }

        archivo.close();

        cout << "Archivo 'Horario_Visual.txt' generado correctamente.\n";

    }

    else
    {

        cout << "Error al generar archivo visual.\n";

    }

}


void RegistrarCurso(Curso horario[DIAS][HORAS])
{

    int diaSel;
    int horaSel;
    char continuar;

    continuar = 's';

    do
    {

        system("cls");

        cout << "\n=== MODIFICAR HORARIO ===\n";

        cout << "Selecciona el dia:\n";

        for (int i = 0; i < DIAS; i++)
        {

            cout << i + 1 << ". " << nombresDias[i] << endl;

        }

        cout << "7. [CANCELAR]\n";

        cout << "Opcion: ";
        cin >> diaSel;

        if (diaSel != 7)
        {

            if (diaSel >= 1 && diaSel <= DIAS)
            {

                int dia;

                dia = diaSel - 1;

                cout << "\n--- Horario del " << nombresDias[dia] << " ---\n";

                for (int hora = 0; hora < HORAS; hora++)
                {

                    cout << hora + 1 << ". " << horas[hora] << " -> ";

                    if (horario[dia][hora].nombre == "")
                    {

                        cout << "[ Vacio ]";

                    }

                    else
                    {

                        cout << horario[dia][hora].nombre << " (" << horario[dia][hora].aula << ")";

                    }

                    cout << endl;

                }

                cout << "\nElige el numero de hora a modificar (1-6): ";
                cin >> horaSel;

                if (horaSel < 1 || horaSel > HORAS)
                {

                    cout << "Hora invalida.\n";

                }

                else
                {

                    int hora;
                    hora = horaSel - 1;

                    cin.ignore();

                    cout << "\n>> Editando: " << nombresDias[dia] << " - " << horas[hora] << endl;

                    cout << "Nombre del Curso (Escribe 'BORRAR' para eliminar): ";

                    getline(cin, horario[dia][hora].nombre);

                    if (horario[dia][hora].nombre == "BORRAR" || horario[dia][hora].nombre == "borrar")
                    {

                        horario[dia][hora].nombre = "";
                        horario[dia][hora].aula = "";
                        horario[dia][hora].docente = "";

                        cout << "-> Turno eliminado/limpiado.\n";

                    }

                    else
                    {

                        cout << "Aula: ";
                        getline(cin, horario[dia][hora].aula);

                        cout << "Docente: ";
                        getline(cin, horario[dia][hora].docente);

                        cout << "-> Curso registrado correctamente.\n";

                    }

                }

                cout << "\n¿Quieres editar otra hora? (s/n): ";
                cin >> continuar;

            }

            else
            {

                cout << "Dia invalido.\n";
                system("PAUSE");
                continuar = 's';

            }

        }

    } while (diaSel != 7 && (continuar == 's' || continuar == 'S'));

}


void ListarHorario(Curso horario[DIAS][HORAS])
{

    system("cls");

    for (int d = 0; d < DIAS; d++)

    {

        cout << "\n" << nombresDias[d] << ":\n";

        for (int h = 0; h < HORAS; h++)
        {

            if (horario[d][h].nombre != "")
            {

                cout << "  " << horas[h] << " -> " << horario[d][h].nombre
                    << " | Aula: " << horario[d][h].aula << endl;

            }

        }

        cout << endl;
        cout << endl;
        cout << endl;

    }

}


void MostrarDia(Curso horario[DIAS][HORAS], int dia)
{

    system("cls");

    if (dia < 0 || dia >= DIAS)
    {

        cout << "Dia invalido\n";

        return;

    }

    cout << "\nHorario de " << nombresDias[dia] << ":\n";

    for (int h = 0; h < HORAS; h++)
    {

        cout << horas[h] << " -> ";

        if (horario[dia][h].nombre == "")
        {

            cout << "-- Libre --\n";

        }

        else
        {

            cout << horario[dia][h].nombre << " (" << horario[dia][h].aula << ")\n";

        }

    }

}


void Mostrar_calendario(Curso horario[DIAS][HORAS])
{
    string nom;

    system("cls");

    cout << "\n========= CALEB CALENDAR =========\n\n";

    cout << setw(10) << left << "Dia/Hora";

    for (int h = 0; h < HORAS; h++)
    {

        cout << setw(20) << horas[h];

    }

    cout << "\n";

    for (int d = 0; d < DIAS; d++)
    {

        cout << setw(10) << left << nombresDias[d];

        for (int h = 0; h < HORAS; h++)
        {

            if (horario[d][h].nombre == "")
            {

                cout << setw(20) << "-";

            }

            else
            {

                nom = horario[d][h].nombre;

                if (nom.length() > 18)
                {

                    nom = nom.substr(0, 18);

                }

                cout << setw(20) << nom;

            }

        }

        cout << "\n";

    }

}


void MostrarMenu()
{

    system("cls");

    cout << "\n================================\n";
    cout << "        MENU PRINCIPAL   \n";
    cout << "================================\n";
    cout << "1. EDITAR / REGISTRAR CURSOS\n";
    cout << "2. LISTA DE HORARIO COMPLETO\n";
    cout << "3. VER CLASES DE UN DIA ESPECIFICO\n";
    cout << "4. BUSCAR CURSO\n";
    cout << "5. MOSTRAR CALENDARIO\n";
    cout << "6. GUARDAR CALENDARIO EN TXT\n";
    cout << "7. EXPORTAR A EXCEL\n";
    cout << "8. Salir\n\n";
    cout << "Seleccionar opcion: ";

}


int main()
{

    setlocale(LC_ALL, "spanish");

    Curso horario[DIAS][HORAS];

    int opcion;
    int dia;

    for (int d = 0; d < DIAS; d++)
    {

        for (int h = 0; h < HORAS; h++)
        {

            horario[d][h].nombre = "";
            horario[d][h].aula = "";
            horario[d][h].docente = "";

        }

    }

    Presentacion();

    do
    {

        MostrarMenu();

        if (!(cin >> opcion))
        {

            cin.clear(); cin.ignore(10000, '\n'); opcion = 0;

        }

        switch (opcion)
        {

        case 1:

            RegistrarCurso(horario);

            break;

        case 2:

            ListarHorario(horario);

            break;

        case 3:

            cout << "Dia (1=Lun ... 6=Sab): ";
            cin >> dia;

            MostrarDia(horario, dia - 1);

            break;

        case 4:

            BuscarCurso(horario);

            break;

        case 5:

            Mostrar_calendario(horario);

            break;

        case 6:

            GuardarTXT(horario);

            break;

        case 7:

            ExportarExcel(horario);

            break;


        case 8:

            Despedida();

            break;

        default:

            cout << "Opcion no valida.\n";

        }

        if (opcion != 8)
        {

            system("PAUSE");

        }

    } while (opcion != 8);

    return 0;

}