#include <iostream>
#include <conio.h>
#include <string>
#include <fstream>

using namespace std;

int SeleccionarOpcion();
int UpsertSSHKey(string);
int RunSonar(string, string);
string path = "C:\\sonar-scanner-4.6.2.2472-windows\\bin\\key.h";

int main(int argc, char** argv)
{
    if(argc > 1){
        RunSonar(argv[1], argv[2]);
    }else{
        SeleccionarOpcion();
    }
    return 0;
}

int SeleccionarOpcion(){
    int opcion;
    string sshkey, project, projectKey;
    cout << "----------------SonarQube----------------" << endl;
    cout << "1 - Agregar/Cambiar clave ssh" << endl << "2 - Correr el sonar" << endl << "9 - Salir" << endl << "Ingrese la opcion: ";
    cin >> opcion;
    if(opcion == 1){
        cout << "Ingrese su clave: ";
        cin >> sshkey;
        UpsertSSHKey(sshkey);
        getch();
        system("cls");
        SeleccionarOpcion();
    }else if(opcion == 2){
        cout << "Ingrese la ruta del proyecto: ";
        cin >> project;
        cout << "Ingrese el projectKey: ";
        cin >> project;
        return RunSonar(project, projectKey);
    }else if(opcion == 9){
        return 0;
    }else{
        cout<<"Opcion no valida"<<endl<<"Precione una tecla para continuar...";
        getch();
        system("cls");
        SeleccionarOpcion();
    }
}

int UpsertSSHKey(string sshkey){
    ofstream myfile;
    myfile.open (path);
    myfile << sshkey;
    myfile.close();
    cout << "Clave guardada";
    return 0;
}

int RunSonar(string project, string projectKey){
    string sshkey;
    string cmd;
    ifstream myfile;
    myfile.open(path);
    if(myfile){
        getline (myfile, sshkey);
        cmd = "sonar-scanner.bat -X -D sonar.login=\""+sshkey+"\" -D sonar.host.url=https://sq.edge.com.py/ -D sonar.projectKey="+projectKey+" -D sonar.sources=apiproxy -D sonar.projectBaseDir="+project;
        system(cmd.c_str());
        return 0;
    }else{
        cout << "Aun no se ha registrado ninguna clave ssh";
        getch();
        system("cls");
        SeleccionarOpcion();
    }    
}