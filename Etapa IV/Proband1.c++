#include <iostream>

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
void generateHuffmanCodes(TreeNode* node, std::string code) {
    if (!node) return;
    if (node->symbol != '\0') {
        std::cout << node->symbol << ": " << code << std::endl;
    }
    generateHuffmanCodes(node->left, code + "0");
    generateHuffmanCodes(node->right, code + "1");
}

int main() {
    const int numNodes = 6;
    TreeNode nodes[numNodes] = { TreeNode('A', 0.3), TreeNode('B', 0.2), TreeNode('C', 0.5) , TreeNode('D', 0.7) , TreeNode('E', 0.2) , TreeNode('F', 0.1) };
    
    TreeNode* root = buildHuffmanTree(nodes, numNodes);

    generateHuffmanCodes(root, "");

    return 0;
}
