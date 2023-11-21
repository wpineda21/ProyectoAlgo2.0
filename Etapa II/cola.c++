#include <iostream>

/*Definimos la Estructura de los Nodos establecidos en el proyecto*/
struct TreeNode
{
    TreeNode *parent;
    TreeNode *left_son;
    TreeNode *right_son;
    char symbol;        /* Decidimos Utilizar la variable de tipo Char para el simbolo de la letra del alfabeto */
    double probability; /* Este valor de probabilidad variara conforme el dado segun la tabla de probabilidad de cada Elemento */
};

TreeNode *crearNodo(char symbol, double probability)
{
    TreeNode *newnode = new TreeNode;
    newnode->parent = nullptr;
    newnode->left_son = nullptr;
    newnode->right_son = nullptr;
    newnode->symbol = symbol;
    newnode->probability = probability;
    return newnode;
}

// Función para MinHeapInsertar un nodo en el montículo de mínimos
void MinHeapInsert(TreeNode **heap, TreeNode *newNode, int &heapSize)
{
    // Agrega el nuevo nodo al final del montículo
    heap[heapSize] = newNode;
    int currentIdx = heapSize;

    // Realiza el proceso de "burbujeo" hacia arriba para mantener la propiedad del montículo
    while (currentIdx > 0 && heap[currentIdx]->probability < heap[(currentIdx - 1) / 2]->probability)
    {
        std::swap(heap[currentIdx], heap[(currentIdx - 1) / 2]);
        currentIdx = (currentIdx - 1) / 2;
    }

    heapSize++;
}

// Función para realizar el proceso de "burbujeo" hacia abajo en el montículo
void MinHeapify(TreeNode **heap, int heapSize, int currentIdx)
{
    while (true)
    {
        int leftChildIdx = 2 * currentIdx + 1;
        int rightChildIdx = 2 * currentIdx + 2;
        int smallestIdx = currentIdx;

        if (leftChildIdx < heapSize && heap[leftChildIdx]->probability < heap[smallestIdx]->probability)
        {
            smallestIdx = leftChildIdx;
        }
        if (rightChildIdx < heapSize && heap[rightChildIdx]->probability < heap[smallestIdx]->probability)
        {
            smallestIdx = rightChildIdx;
        }

        if (smallestIdx != currentIdx)
        {
            std::swap(heap[currentIdx], heap[smallestIdx]);
            currentIdx = smallestIdx;
        }
        else
        {
            break;
        }
    }
}

// Función para extraer el nodo con el valor mínimo del montículo
TreeNode *MinHeapExtractMin(TreeNode **heap, int &heapSize)
{
    if (heapSize == 0)
    {
        return nullptr;
    }

    TreeNode *minNode = heap[0];

    // Mueve el último nodo al principio del montículo
    heap[0] = heap[heapSize - 1];
    heapSize--;

    // Llama a la función MinHeapify para mantener la propiedad del montículo
    MinHeapify(heap, heapSize, 0);

    return minNode;
}

int BussinesLogic()
{
    const int maxHeapSize = 100;
    TreeNode *minHeap[maxHeapSize]; // Cambiar el tipo del montículo a puntero a puntero

    int heapSize = 0;

    // Crear los nodos
    TreeNode nodo_A;
    nodo_A.symbol = 'A';
    nodo_A.probability = 0.15;

    TreeNode nodo_B;
    nodo_B.symbol = 'B';
    nodo_B.probability = 0.12;

    TreeNode nodo_C;
    nodo_C.symbol = 'C';
    nodo_C.probability = 0.71;

    TreeNode nodo_D;
    nodo_D.symbol = 'D';
    nodo_D.probability = 0.39;

    TreeNode nodo_E;
    nodo_E.symbol = 'E';
    nodo_E.probability = 0.32;

    TreeNode nodo_F;
    nodo_F.symbol = 'F';
    nodo_F.probability = 0.70;

    TreeNode nodo_G;
    nodo_G.symbol = 'G';
    nodo_G.probability = 0.33;

    TreeNode nodo_H;
    nodo_H.symbol = 'H';
    nodo_H.probability = 0.73;

    TreeNode nodo_I;
    nodo_I.symbol = 'I';
    nodo_I.probability = 0.50;

    TreeNode nodo_J;
    nodo_J.symbol = 'J';
    nodo_J.probability = 0.10;

    TreeNode nodo_K;
    nodo_K.symbol = 'K';
    nodo_K.probability = 0.9;

    TreeNode nodo_L;
    nodo_L.symbol = 'L';
    nodo_L.probability = 0.72;

    // Agregar nodos al montículo
    MinHeapInsert(minHeap, &nodo_A, heapSize);
    MinHeapInsert(minHeap, &nodo_B, heapSize);
    MinHeapInsert(minHeap, &nodo_C, heapSize);
    MinHeapInsert(minHeap, &nodo_D, heapSize);
    MinHeapInsert(minHeap, &nodo_E, heapSize);
    MinHeapInsert(minHeap, &nodo_F, heapSize);
    MinHeapInsert(minHeap, &nodo_G, heapSize);
    MinHeapInsert(minHeap, &nodo_H, heapSize);
    MinHeapInsert(minHeap, &nodo_I, heapSize);
    MinHeapInsert(minHeap, &nodo_J, heapSize);
    MinHeapInsert(minHeap, &nodo_K, heapSize);
    MinHeapInsert(minHeap, &nodo_L, heapSize);

    // Resto de la inserción de nodos (continuar con los otros nodos)

    // Extraemos y mostramos el nodo con el valor mínimo
    TreeNode *minNode = MinHeapExtractMin(minHeap, heapSize);
    if (minNode)
    {
        std::cout << "Simbolo: " << minNode->symbol << ", Probabilidad: " << minNode->probability << std::endl;
    }

    return 0;
}

int main()
{
    BussinesLogic();
}