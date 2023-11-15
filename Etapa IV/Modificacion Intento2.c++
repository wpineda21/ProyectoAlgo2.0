#include <iostream>
#include <cstring>
#include <string>
#include <cctype>

struct TreeNode {
    char symbol;
    double probability;
    TreeNode* parent;
    TreeNode* left_son;
    TreeNode* right_son;
};

TreeNode *crearNodo(char symbol, double probability)
{
    TreeNode *newnode = new TreeNode;
    newnode->symbol = symbol;
    newnode->probability = probability;
    newnode->parent = nullptr;
    newnode->left_son = nullptr;
    newnode->right_son = nullptr;
    return newnode;
}

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

TreeNode* buildHuffmanTree(TreeNode* nodes, int numNodes) {
    TreeNode** minHeap = new TreeNode*[numNodes];
    int size = 0; // Comenzamos con un montículo vacío

    for (int i = 0; i < numNodes; i++) {
        MinHeapInsert(minHeap, nodes + i, size);
    }

    while (size > 1) {
        TreeNode* left = minHeap[0];
        std::swap(minHeap[0], minHeap[size - 1]);
        size--;
        MinHeapify(minHeap, size, 0);

        TreeNode* right = minHeap[0];
        std::swap(minHeap[0], minHeap[size - 1]);
        size--;
        MinHeapify(minHeap, size, 0);

        TreeNode* merged = crearNodo('\0', left->probability + right->probability);
        merged->left_son = left;
        merged->right_son = right;
        left->parent = merged;
        right->parent = merged;

        MinHeapInsert(minHeap, merged, size);
    }

    TreeNode* root = minHeap[0];
    root->parent = nullptr;
    delete[] minHeap;
    return root;
}


void generateHuffmanCodes(TreeNode* node, char* code, char** codes) {
    if (!node) return;
    if (node->symbol != '\0') {
        strcpy(codes[node->symbol], code);
    }

    char left_code[32];
    char right_code[32];

    strcpy(left_code, code);
    strcat(left_code, "0");
    strcpy(right_code, code);
    strcat(right_code, "1");

    generateHuffmanCodes(node->left_son, left_code, codes);
    generateHuffmanCodes(node->right_son, right_code, codes);
}

void decodeHuffmanText(TreeNode* root, const char* textoCodificado) {
    TreeNode* current = root;
    for (int i = 0; textoCodificado[i] != '\0'; i++) {
        if (textoCodificado[i] == '0') {
            current = current->left_son;
        } else if (textoCodificado[i] == '1') {
            current = current->right_son;
        }

        if (current->left_son == nullptr && current->right_son == nullptr) {
            std::cout << current->symbol;
            current = root;
        }
    }
}

int main() {
    
    const int numNodes = 3;
    TreeNode nodes[numNodes];
    nodes[0].symbol = 'a';
    nodes[0].probability = 0.3; 
    nodes[0].parent = nullptr;
    nodes[0].left_son = nullptr;
    nodes[0].right_son = nullptr;

    nodes[1].symbol = 'b';
    nodes[1].probability = 0.2;
    nodes[1].parent = nullptr;
    nodes[1].left_son = nullptr;
    nodes[1].right_son = nullptr;

    nodes[2].symbol = 'c';
    nodes[2].probability = 0.1;
    nodes[2].parent = nullptr;
    nodes[2].left_son = nullptr;
    nodes[2].right_son = nullptr;

    TreeNode* root = buildHuffmanTree(nodes, numNodes);

    char* huffmanCodes[256];
    for (int i = 0; i < 256; i++) {
        huffmanCodes[i] = new char[32];
        huffmanCodes[i][0] = '\0';
    }

    char root_code[32] = "";
    generateHuffmanCodes(root, root_code, huffmanCodes);

    std::cout << "Ingrese una palabra para codificar: ";
    std::string inputWord;
    std::cin >> inputWord;

    char textoCodificado[256] = "";
    for (char c : inputWord) {
        c = tolower(c);
        strcat(textoCodificado, huffmanCodes[c]);
    }

    std::cout << "Texto codificado: " << textoCodificado << std::endl;

    for (int i = 0; i < 256; i++) {
        delete[] huffmanCodes[i];
    }

    std::cout << "Texto decodificado: ";
    decodeHuffmanText(root, textoCodificado);
    std::cout << std::endl;

    return 0;
}
