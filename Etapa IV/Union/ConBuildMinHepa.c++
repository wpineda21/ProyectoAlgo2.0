#include <iostream>

/* Definimos la Estructura de los Nodos establecidos en el proyecto */
struct TreeNode {
    char symbol;
    double probability;
    TreeNode* parent;
    TreeNode* left_son;
    TreeNode* right_son;
};

TreeNode* crearNodo(char symbol, double probability) {
    TreeNode* newnode = new TreeNode;
    newnode->parent = nullptr;
    newnode->left_son = nullptr;
    newnode->right_son = nullptr;
    newnode->symbol = symbol;
    newnode->probability = probability;
    return newnode;
}



// Función para realizar el proceso de "burbujeo" hacia abajo en el montículo
void MinHeapify(TreeNode** heap, int heapSize, int currentIdx) {
    while (true) {
        int leftChildIdx = 2 * currentIdx + 1;
        int rightChildIdx = 2 * currentIdx + 2;
        int smallestIdx = currentIdx;

        if (leftChildIdx < heapSize && heap[leftChildIdx]->probability < heap[smallestIdx]->probability) {
            smallestIdx = leftChildIdx;
        }
        if (rightChildIdx < heapSize && heap[rightChildIdx]->probability < heap[smallestIdx]->probability) {
            smallestIdx = rightChildIdx;
        }

        if (smallestIdx != currentIdx) {
            std::swap(heap[currentIdx], heap[smallestIdx]);
            currentIdx = smallestIdx;
        } else {
            break;
        }
    }
}

void buildMinHeap(TreeNode** heap, int size) {
    for (int i = size / 2 - 1; i >= 0; i--) {
        MinHeapify(heap, size, i);
    }
}

void MinHeapInsert(TreeNode **heap, TreeNode *newNode, int &heapSize) {
    // Agrega el nuevo nodo al final del montículo
    heap[heapSize] = newNode;
    int currentIdx = heapSize;

    // Realiza el proceso de "burbujeo" hacia arriba para mantener la propiedad del montículo
    while (currentIdx > 0 && heap[currentIdx]->probability < heap[(currentIdx - 1) / 2]->probability) {
        std::swap(heap[currentIdx], heap[(currentIdx - 1) / 2]);
        currentIdx = (currentIdx - 1) / 2;
    }

    heapSize++;
}

int BussinesLogic() {
    const int maxHeapSize = 100;
    TreeNode* minHeap[maxHeapSize];
    int heapSize = 0;

    // Crear una lista de nodos
    TreeNode nodes[] = {
        {'A', 0.15, nullptr, nullptr, nullptr},
        {'B', 0.12, nullptr, nullptr, nullptr},
        {'C', 0.71, nullptr, nullptr, nullptr},
        {'D', 0.39, nullptr, nullptr, nullptr},
        {'E', 0.32, nullptr, nullptr, nullptr},
        {'F', 0.70, nullptr, nullptr, nullptr},
        {'G', 0.33, nullptr, nullptr, nullptr},
        {'H', 0.73, nullptr, nullptr, nullptr},
        {'I', 0.50, nullptr, nullptr, nullptr},
        {'J', 0.10, nullptr, nullptr, nullptr},
        {'K', 0.90, nullptr, nullptr, nullptr},
        {'L', 0.72, nullptr, nullptr, nullptr}
        // Continuar con los otros nodos...
    };

    // Agregar nodos al montículo
    for (int i = 0; i < sizeof(nodes) / sizeof(nodes[0]); i++) {
        minHeap[heapSize] = new TreeNode(nodes[i]);
        heapSize++;
    }

    // Construir el montículo mínimo
    buildMinHeap(minHeap, heapSize);

    // Mostrar el nodo mínimo sin extraerlo
    TreeNode* minNode = minHeap[0];
    if (minNode) {
        std::cout << "Simbolo: " << minNode->symbol << ", Probabilidad: " << minNode->probability << std::endl;
    }

    // Liberar la memoria utilizada por los nodos
    for (int i = 0; i < heapSize; i++) {
        delete minHeap[i];
    }

    return 0;
}

int main() {
    BussinesLogic();
}