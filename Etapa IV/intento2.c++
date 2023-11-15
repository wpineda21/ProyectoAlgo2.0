#include <iostream>
#include <cstring>

// Estructura para representar un nodo del árbol de Huffman
struct TreeNode {
    char symbol;
    double probability;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char sym, double prob) : symbol(sym), probability(prob), left(nullptr), right(nullptr) {}
};

// Estructura para representar una cola de prioridad personalizada (Montículo de Mínimos)
class MinHeap {
private:
    TreeNode** heap;
    int capacity;
    int size;

    void heapify(int index) {
        int smallest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;

        if (left < size && heap[left]->probability < heap[smallest]->probability) {
            smallest = left;
        }

        if (right < size && heap[right]->probability < heap[smallest]->probability) {
            smallest = right;
        }

        if (smallest != index) {
            std::swap(heap[index], heap[smallest]);
            heapify(smallest);
        }
    }

public:
    MinHeap(int capacity) : capacity(capacity), size(0) {
        heap = new TreeNode*[capacity];
    }

    ~MinHeap() {
        delete[] heap;
    }

    void push(TreeNode* node) {
        if (size == capacity) {
            return; // No se puede insertar más elementos
        }

        int index = size;
        int parent = (index - 1) / 2;
        heap[size++] = node;

        while (index > 0 && heap[parent]->probability > heap[index]->probability) {
            std::swap(heap[index], heap[parent]);
            index = parent;
            parent = (index - 1) / 2;
        }
    }

    TreeNode* pop() {
        if (size == 0) {
            return nullptr; // No hay elementos para sacar
        }

        TreeNode* root = heap[0];
        heap[0] = heap[--size];
        heapify(0);
        return root;
    }

    bool empty() {
        return size == 0;
    }
};

// Función para construir el árbol de Huffman
TreeNode* buildHuffmanTree(TreeNode* nodes, int numNodes) {
    MinHeap minHeap(numNodes);

    for (int i = 0; i < numNodes; i++) {
        minHeap.push(&nodes[i]);
    }

    while (!minHeap.empty()) {
        TreeNode* left = minHeap.pop();
        TreeNode* right = minHeap.pop();

        TreeNode* merged = new TreeNode('\0', left->probability + right->probability);
        merged->left = left;
        merged->right = right;

        if (!minHeap.empty()) {
            minHeap.push(merged);
        } else {
            return merged; // Este es el nodo raíz del árbol de Huffman
        }
    }

    return nullptr;
}

// Función para generar códigos de Huffman recursivamente
void generateHuffmanCodes(TreeNode* node, char* code, char** codes) {
    if (!node) return;
    if (node->symbol != '\0') {
        for (int i = 0; code[i] != '\0'; i++) {
            codes[node->symbol][i] = code[i];
        }
        codes[node->symbol][strlen(code)] = '\0';
    }

    char left_code[32]; // Suponemos un máximo de 32 bits
    char right_code[32]; // Suponemos un máximo de 32 bits

    for (int i = 0; code[i] != '\0'; i++) {
        left_code[i] = code[i];
        right_code[i] = code[i];
    }

    left_code[strlen(code)] = '0';
    left_code[strlen(code) + 1] = '\0';

    right_code[strlen(code)] = '1';
    right_code[strlen(code) + 1] = '\0';

    generateHuffmanCodes(node->left, left_code, codes);
    generateHuffmanCodes(node->right, right_code, codes);
}
// Función para decodificar el texto utilizando el árbol de Huffman
void decodeHuffmanText(TreeNode* root, const char* textoCodificado) {
    TreeNode* current = root;
    for (int i = 0; textoCodificado[i] != '\0'; i++) {
        if (textoCodificado[i] == '0') {
            current = current->left;
        } else if (textoCodificado[i] == '1') {
            current = current->right;
        }

        if (current->left == nullptr && current->right == nullptr) {
            std::cout << current->symbol;
            current = root;
        }
    }
}

int main() {
    const int numNodes = 3;
    TreeNode nodes[numNodes] = { TreeNode('A', 0.3), TreeNode('B', 0.2), TreeNode('C', 0.1) };

    TreeNode* root = buildHuffmanTree(nodes, numNodes);

    char* huffmanCodes[256]; // Suponemos un máximo de 256 símbolos
    for (int i = 0; i < 256; i++) {
        huffmanCodes[i] = new char[32];
        huffmanCodes[i][0] = '\0';
    }

    char root_code[32] = "";
    generateHuffmanCodes(root, root_code, huffmanCodes);

    // Construir un texto de 5 palabras utilizando los códigos de Huffman
    char textoCodificado[256] = "";
    strcat(textoCodificado, huffmanCodes['A']); // Codificar la primera palabra
    strcat(textoCodificado, huffmanCodes['B']); // Codificar la segunda palabra
    strcat(textoCodificado, huffmanCodes['C']); // Codificar la tercera palabra
    strcat(textoCodificado, huffmanCodes['A']); // Codificar la cuarta palabra
    strcat(textoCodificado, huffmanCodes['B']); // Codificar la quinta palabra

    std::cout << "Texto codificado: " << textoCodificado << std::endl;

    // Liberar la memoria utilizada para los códigos
    for (int i = 0; i < 256; i++) {
        delete[] huffmanCodes[i];
    }

    std::cout << "Texto codificado: " << textoCodificado << std::endl;

    // Decodificar el texto codificado utilizando el árbol de Huffman
    std::cout << "Texto decodificado: ";
    decodeHuffmanText(root, textoCodificado);
    std::cout << std::endl;

    // Liberar la memoria utilizada para los códigos
    for (int i = 0; i < 256; i++) {
        delete[] huffmanCodes[i];
    }

    return 0;
}