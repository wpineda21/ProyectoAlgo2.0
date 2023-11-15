#include <iostream>

struct Nodo{
    Nodo *padre;
    Nodo *hijo_izquierdo;
    Nodo *hijo_derecho;
    char simbolo;
    double probabilidad;};

// Estructura de montículo de mínimos
struct MonticuloMinimos
{
    Nodo *raiz; // Raíz del montículo

    // Constructor
    MonticuloMinimos()
    {
        raiz = nullptr;
    }

    // Función auxiliar para intercambiar dos nodos
    void intercambiar(Nodo *a, Nodo *b)
    {
        Nodo *temp = a;
        a = b;
        b = temp;
    }

    // Insertar un nodo en el montículo
    void insertar(Nodo *nodo)
    {
        if (raiz == nullptr)
        {
            raiz = nodo;
        }
        else
        {
            // Encuentra el primer lugar disponible en el nivel más a la izquierda
            Nodo *temp = raiz;
            while (temp->hijo_izquierdo != nullptr)
            {
                temp = temp->hijo_izquierdo;
            }

            if (temp->hijo_izquierdo == nullptr)
            {
                temp->hijo_izquierdo = nodo;
                nodo->padre = temp;
            }

            // Realiza un ajuste hacia arriba para mantener la propiedad del montículo de mínimos
            ajustarHaciaArriba(nodo);
        }
    }

    // Función para ajustar el montículo hacia arriba
    void ajustarHaciaArriba(Nodo *nodo)
    {
        while (nodo->padre != nullptr && nodo->probabilidad < nodo->padre->probabilidad)
        {
            intercambiar(nodo, nodo->padre);
            nodo = nodo->padre;
        }
    }

    // Función para extraer el nodo con probabilidad mínima
    Nodo *extraerMinimo()
    {
        if (raiz == nullptr)
        {
            return nullptr;
        }

        Nodo *minimo = raiz;

        // Encuentra el último nodo y colócalo como raíz
        Nodo *ultimo = raiz;
        while (ultimo->hijo_izquierdo != nullptr)
        {
            ultimo = ultimo->hijo_izquierdo;
        }

        raiz = ultimo;

        // Realiza un ajuste hacia abajo para mantener la propiedad del montículo de mínimos
        ajustarHaciaAbajo(raiz);

        minimo->padre = nullptr;
        minimo->hijo_izquierdo = nullptr;
        minimo->hijo_derecho = nullptr;

        return minimo;
    }

    // Función para ajustar el montículo hacia abajo
    void ajustarHaciaAbajo(Nodo *nodo)
    {
        while (nodo->hijo_izquierdo != nullptr)
        {
            Nodo *hijoMenor = nodo->hijo_izquierdo;

            if (nodo->hijo_derecho != nullptr && nodo->hijo_derecho->probabilidad < hijoMenor->probabilidad)
            {
                hijoMenor = nodo->hijo_derecho;
            }

            if (nodo->probabilidad < hijoMenor->probabilidad)
            {
                return;
            }

            intercambiar(nodo, hijoMenor);
        }
    }
};

int main()
{
    MonticuloMinimos monticulo;

    Nodo *nodoA = new Nodo;
    nodoA->simbolo = 'A';
    nodoA->probabilidad = 0.1;
    monticulo.insertar(nodoA);

    Nodo *nodoB = new Nodo;
    nodoB->simbolo = 'B';
    nodoB->probabilidad = 0.2;
    monticulo.insertar(nodoB);

    Nodo *nodoC = new Nodo;
    nodoC->simbolo = 'C';
    nodoC->probabilidad = 0.3;
    monticulo.insertar(nodoC);

    while (monticulo.raiz != nullptr)
    {
        Nodo *minimo = monticulo.extraerMinimo();
        std::cout << "Nodo con probabilidad mínima: " << minimo->simbolo << " (" << minimo->probabilidad << ")\n";
    }

    return 0;
}
