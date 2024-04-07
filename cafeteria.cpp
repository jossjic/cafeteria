#include <iostream>
#include <cassert>
#include <vector>
#include <sstream>
#include <string>

using namespace std;

/**
 * Elimina todos los espacios de una cadena dada.
 * 
 * @param str La cadena de la cual eliminar los espacios.
 * @return Una nueva cadena sin espacios.
 */
string eliminarEspacios(const string& str) {
    string resultado;
    for (char c : str) {
        if (c != ' ') {
            resultado += c;
        }
    }
    return resultado;
}


/**
 * Verifica si la cadena contiene solo caracteres alfabéticos y cumple con las condiciones de longitud.
 * 
 * @param str La cadena a verificar.
 * @return Verdadero si la cadena es válida, falso en caso contrario.
 */
bool esNombreValido(const string& str) {
    if (str.empty() || str.size() < 2 || str.size() > 15) {
        return false;
    }
    for (char c : str) {
        if (!isalpha(c)) { // Verifica si el carácter es alfabético
            return false;
        }
    }
    return true;
}

/**
 * Valida la entrada específica para una lista de especificaciones de productos.
 * 
 * La función verifica varias condiciones:
 * - El primer elemento debe ser un nombre de producto válido (alfabético, longitud de 2 a 15 caracteres).
 * - Debe haber entre 1 y 5 tamaños especificados, cada uno debe ser un entero en el rango de 1 a 48.
 * - Los tamaños deben estar en orden ascendente.
 * 
 * @param specs La cadena de entrada que contiene el nombre del producto y los tamaños, separados por comas.
 * @return Verdadero si la entrada cumple con todas las especificaciones, falso en caso contrario.
 */

bool validacionInput(const string& specs) {
    vector<string> result;
    stringstream ss(specs);
    string item;

    // Procesa y divide la entrada por comas, eliminando espacios.
    while (getline(ss, item, ',')) {
        item = eliminarEspacios(item);
        result.push_back(item);
    }

    // Validaciones de la entrada
   if (!esNombreValido(result[0]) || result.size() < 2|| result.size()>6) {
        return false;
    }


    // Verifica cada tamaño especificado
    int prev = 0;
    for (size_t i = 1; i < result.size(); i++) {
        int numero;
        try {
            numero = stoi(result[i]);
        } catch (const invalid_argument& e) {
            return false;
        } catch (const out_of_range& e) {
            return false;
        }

        if (numero < 1 || numero > 48 || numero <= prev) {
            return false;
        }
        prev = numero;
    }

    return true;
}


int main(){
    //Test cases
    vector<string> tests = {
        //Tests positivos
        "ZumoNa,1", //0 El nombre del artículo es alfabético (válido)
        "GolGolGolGolGol,1",    //1 El nombre del artículo tiene de 2 a 15 caracteres de longitud (válido)
        "Botella,1",    //2 El valor del tamaño está en el rango de 1 a 48 (válido)
        "Botella,48",    //3 El valor del tamaño es un número entero (válido)
        "tt,1,2,3,4,5",    //4 Los valores del tamaño se ingresan en orden ascendente (válido)
        "tt, 20,27,30,39",    //5 Se ingresan de uno a cinco valores de tamaño (válido)
        "ZumoNa,1,2,3,4,5",    //6 El nombre del artículo es el primero en la entrada (válido)
        "ZumoNaranja,2,3,4,5,6",    //7 Una sola coma separa cada entrada en la lista (válido)
        "ZumoNa,20,21,33,43,44",    //8 La entrada no contiene espacios en blanco (válido)
        "    Zum                      oNa,   1 ,    2    ,     3 ,   4,5 ",    //9 La entrada contiene espacios en blanco (válido)

        //Tests negativos
        "123124_+),1", //10 El nombre del artículo no es alfabético (inválido)
        "a,1,2,3,4,5",    //11 El nombre del artículo tiene menos de 2 caracteres de longitud (inválido)
        "AutosAutosAutosL,1,2,3,4,5",    //12 El nombre del artículo tiene mas de 15 caracteres de longitud (inválido)
        "ZumoNa,1,2,3,4,49",    //13 El valor del tamaño es mayor a 48 (inválido)
        "ZumoNa,1,2,3,4,2147298371983499832548935435423524854273981",    //14 El valor del tamaño es mayor a los limites de int (2147483647) (inválido)
        "ZumoNa,-1,0,1,2,3",    //15 El valor del tamaño es menor a 1 (inválido)
        "ZumoNa, 20,19,18,17,16",    //16 Los valores del tamaño se ingresan en orden descendente (inválido)
        "ZumoNa,1,2,3,4,5,6",    //17 Se ingresan más de seis valores de tamaño (inválido)
        "1,2,3,4,5,ZumoNa",    //18 El nombre del artículo es el último en la entrada (inválido)
        "ZumoNa.1.2.3.4.5",    //19 Un punto (.) separa cada entrada en la lista (inválido)
        "ZumoNa_!,1,2,3,4,5",         //20 Nombre del artículo con caracteres especiales (inválido)
        "ZumoNa,1,1,2,3,4",           //21 Valores de tamaño duplicados (inválido)
        "ZumoNa123,1,2,3,4,5",        //22 Número al final del nombre del artículo (inválido)
        "Botella,1,2,2,3,4",          //23 Valores de tamaño duplicados en medio (inválido)
    };

    int count=0;
    //Iteración sobre los test cases usando assert

    for (int i = 0; i<24; i++){
        
            assert((validacionInput(tests[i])==(i<10)));
            cout<<"Test "<<i<<" ("<<tests[i]<<")"<<": Passed"<<endl;
        
        
    count=i;
    }
    cout<<"\nAll "<<count+1<<" test cases passed"<<endl<<endl;



    return 0;
}