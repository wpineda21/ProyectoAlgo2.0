#include <iostream>

/*Definimos la Estructura de los Nodos establecidos en el proyecto*/ 
struct Nodo
{
    Nodo *padre;
    Nodo *hijo_izquierdo;
    Nodo *hijo_derecho;
    char simbolo;        /* Decidimos Utilizar la variable de tipo Char para el simbolo de la letra del alfabeto */ 
    double probabilidad; /* Este valor de probabilidad variara conforme el dado segun la tabla de probabilidad de cada Elemento */ 
};

/*Para la Creacion de Cada uno de los nodos nos auxiliamos de esta funcion que declara la estructura anterior*/ 
/*Y asigna valores Nulos a las ramas y al nodo padre ya que en esta Etapa no vamos a Estar Utilizando Un arbol Binario como tal*/
Nodo *crearNodo(char simbolo, double probabilidad)
{
    Nodo *nuevoNodo = new Nodo;
    nuevoNodo->padre = NULL;
    nuevoNodo->hijo_izquierdo = NULL;
    nuevoNodo->hijo_derecho = NULL;
    nuevoNodo->simbolo = simbolo;
    nuevoNodo->probabilidad = probabilidad;
    return nuevoNodo;
}

int main()
{
    Nodo *abecedario_latino[12]; /*Un arreglo para almacenar los nodos*/

    /*Creamos Cada Noodo y le asignamos su valor de probabilidad*/
    abecedario_latino[0] = crearNodo('A', 0.15);
    abecedario_latino[1] = crearNodo('B', 0.28);
    abecedario_latino[2] = crearNodo('C', 0.71);
    abecedario_latino[3] = crearNodo('D', 0.39);
    abecedario_latino[4] = crearNodo('E', 0.32);
    abecedario_latino[5] = crearNodo('F', 0.7);
    abecedario_latino[6] = crearNodo('G', 0.33);
    abecedario_latino[7] = crearNodo('H', 0.73);
    abecedario_latino[8] = crearNodo('I', 0.50);
    abecedario_latino[9] = crearNodo('J', 0.10);
    abecedario_latino[10] = crearNodo('K', 0.90);
    abecedario_latino[11] = crearNodo('L', 0.72);

    /*Imprimir los valores de todos los nodos*/
    for (int i = 0; i < 12; i++)
    {
        std::cout << "Nodo Padre: " << abecedario_latino[i]->padre << std::endl;
        std::cout << "Nodo Derecho: " << abecedario_latino[i]->hijo_derecho << std::endl;
        std::cout << "Nodo Izquierod: " << abecedario_latino[i]->hijo_izquierdo << std::endl;
        std::cout << "Simbolo: " << abecedario_latino[i]->simbolo << std::endl;
        std::cout << "Probabilidad: " << abecedario_latino[i]->probabilidad << std::endl;
    }

    return 0;
}

/*
// Creamos Los nodos Para Cada Letra del Abaecedario con su respectiva proabilidad
Nodo* nodo_A = crearNodo('A', 0.15);
Nodo* nodo_B = crearNodo('B', 0.28);
Nodo* nodo_C = crearNodo('C', 0.71);
Nodo* nodo_D = crearNodo('D', 0.39);
Nodo* nodo_E = crearNodo('E', 0.32);
Nodo* nodo_F = crearNodo('F', 0.7);
Nodo* nodo_G = crearNodo('G', 0.33);
Nodo* nodo_H = crearNodo('H', 0.73);
Nodo* nodo_I = crearNodo('I', 0.50);
Nodo* nodo_J = crearNodo('J', 0.10);
Nodo* nodo_K = crearNodo('K', 0.90);
Nodo* nodo_L = crearNodo('L', 0.72);
// Imprimir los valores del nodo
std::cout << "Simbolo: " << nodo_A->simbolo << std::endl;
std::cout << "Probabilidad: " << nodo_A->probabilidad << std::endl;
    // Imprimir los valores del nodo
std::cout << "Simbolo: " << nodo_B->simbolo << std::endl;
std::cout << "Probabilidad: " << nodo_B->probabilidad << std::endl;

// Crear un nodo para el símbolo A con probabilidad 0.2
Nodo* nodo_A = new Nodo;
nodo_A->padre = NULL;
nodo_A->izquierda = NULL;
nodo_A->derecha = NULL;
nodo_A->simbolo = 'A';
nodo_A->probabilidad = 0.2;
*/