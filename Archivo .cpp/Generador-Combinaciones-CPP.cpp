#include <iostream>
#include <limits>
#include <fstream>
#include <string>
#include <filesystem>

using namespace std;

template <typename T>
void CapturarNumero(T &num, const char solicitud[]);

long double NumComb(int n,int r);
long double Factorial(int n );
long double Combinaciones(int n, int r);

#define MAX 22

int main()
{
    cout << "Programa que genera en orden lexicogr\240fico creciente las combinaciones de n,r ,";
    cout << " con 1 =< n <= " << MAX << " y 0 =< r <= n" << endl;

    int n, r;

    cout << "n es el tama\244o del conjunto base" << endl;
    cout << "r es el tama\244o de combinaciones" << endl;

    // Captura de forma segura la n y la r, para evitar el ingreso de datos inválidos
    do{
        CapturarNumero(n, "Ingresar n: ");
        if(n > MAX) cout << "ERROR, recordatorio que n debe ser menor o igual a " << MAX << ", int\202ntelo otra vez" << endl;
        if(n < 1)   cout << "ERROR, recordatorio que n deber ser mayor o igual que 1, int\202ntelo otra vez" << endl;
    }while(n > MAX || n < 1);

    do{
        CapturarNumero(r, "Ingresar r: ");
        if(r < 0) cout << "ERROR, recordatorio que r debe ser mayor o igual a 0, int\202ntelo otra vez" << endl;
        if(r > n) cout << "ERROR, recordatorio que r debe ser menor o igual a n, int\202ntelo otra vez" << endl;
    }while(r < 0 || r > n); // no permite que la r sea mayor que la n

    if(r == 0){
        // Esto generaría un listado vació por lo que se decidió no mandar un archivo.csv en blanco
        cout << "La cantidad de combinaciones de " << n << " en " << r << " es 1" << endl;
        cout << "La cual es { }" << endl;
        cout << "Por lo que no se generar\240 un archivo .csv" << endl;
    }else{
        long double total = Combinaciones(n,r);

        cout << "Se generaron " << total << " combinaciones" << endl;
        cout << "El valor te\242rico de combinaciones es: " << NumComb(n,r) << endl;

        // Verifica que el método experimetal se haya llevado a cabo de forma correcta
        if(total == NumComb(n,r)){
            cout << "Por lo que el conteo experimental y te\242rico coincide" << endl;
        }

        cout << "\nEstas combinaciones fueron guardadas en el archivo combinaciones_n" << n << "_r" << r << ".csv" << endl;
    }

    system("pause");
    return 0;
}

//Genera y guarda en un archivo .csv todas las combinaciones posibles si r > 0
long double Combinaciones(int n, int r){

    string nombreArchivo = "combinaciones_n" + to_string(n) + "_r" + to_string(r) + ".csv";
    ofstream archivo(nombreArchivo);
    if (!archivo.is_open()) {
        cerr << "Error al abrir el archivo para escritura.\n";
        return -1;
    }

    long double total = 0; //Va guardando cuantas combinaciones se van generando

    int s[r];
    for(int i = 0; i < r; ++i){
        s[i] = i + 1;
    }

    archivo << "\"";
    // Imprime la primera combinación
    for(int i = 0; i < r; ++i){
      archivo << s[i];
        if(i != r - 1){
            archivo << "," ;
        } 
    }
    archivo << "\"\n";

    archivo << "\n";
    ++total;

    // Se encarga de iterar hasta que todas las combinaciones posibles se hayan generado
    while(true){

        int m = r - 1;

        // Busca el primer índice que aún puede incrementarse para generar la siguiente combinación
        while(m >= 0 && s[m] == n - r + m + 1){
            m = m - 1;
        }

        if(m < 0 ) break; // Se corta el ciclo y con eso la función porque ya no habrá mas combinaciones que generar

        s[m] = s[m] + 1;

        // Rellena los siguientes valores en orden creciente después de incrementar s[m]
        for(int j = m + 1 ; j < r; ++j){
            s[j] = s[j-1] + 1;
        }

        archivo << "\"";
        //Imprime la siguiente combinación de manera lexicográfica creciente
        for(int i = 0; i < r; ++i){
            archivo << s[i];
            if(i != r - 1){
                archivo << ",";
            }
        }
   
        archivo << "\"\n";
        ++total;
    }

    archivo.close();
    std::filesystem::path rutaCompleta = std::filesystem::absolute("combinaciones_n" + to_string(n) + "_r" + to_string(r) + ".csv");
    cout << "\nArchivo guardado en: " << rutaCompleta << "\n\n";
    
    return total;
}

// Captura segura de datos ingresados por el usuario
template <typename T>
void CapturarNumero(T &num, const char solicitud[])
{
    cout << solicitud;
    cin >> num;
    while(cin.fail()){
        cout << "Error: no es un n\243mero\n";
        cin.clear();
        cin.ignore(std::numeric_limits<int>::max(),'\n');
        cout << solicitud;
        cin >> num;
    }
}

//Funciones utilizadas para calcular teoricamente el número de combinaciones
long double NumComb(int n,int r)
{
    long double comb;
    return comb = Factorial(n)/(Factorial(r)*Factorial(n-r));
}

long double Factorial(int n)
{
    long double fact = 1;
    for(int i = 1; i <= n ; ++i){
        fact *= i;
    }
    return fact;
}