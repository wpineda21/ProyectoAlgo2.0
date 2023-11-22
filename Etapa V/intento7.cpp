#include <iostream>

struct TreeNode
{
    char symbol;
    double probability;
    TreeNode *parent;
    TreeNode *left_son;
    TreeNode *right_son;
};
TreeNode* createNode(char symbol, double probability)
{ 
    TreeNode* node = new TreeNode;
    node->parent = nullptr; 
    node->left_son = nullptr;
    node->right_son = nullptr;
    node->symbol = symbol;
    node->probability = probability; 
    return node;
}

void insertNode(TreeNode* &root, TreeNode* node)
{
    if (root == nullptr)
    { 
        root = node; 
    }
    else if (node->probability < root->probability)
    {
        node->left_son = root;
        root = node;
    }
    else
    {
        insertNode(root->left_son, node); 
    }
}

TreeNode* extractMin(TreeNode* &root)
{
    if (root == nullptr)
        return nullptr;

    TreeNode* minNode = root;
    root = root->left_son;
    minNode->left_son = nullptr;
    return minNode;
}

// Funciones que quieres acoplar
TreeNode *buildHuffmanTree(TreeNode *nodes, int numNodes)
{
    TreeNode *root = nullptr;
    for (int i = 0; i < numNodes; i++)
    {
        insertNode(root, nodes + i);
    }
    while (root->left_son != nullptr)
    { 
        TreeNode *left = extractMin(root);
        TreeNode *right = extractMin(root);
        TreeNode *merged = createNode('\0', left->probability + right->probability); 
        merged->left_son = left; 
        merged->right_son = right;
        left->parent = merged;
        right->parent = merged;
        insertNode(root, merged);
    }
    return root;
}

void generateHuffmanCodes(TreeNode *node, char *code, char **codes)
{
    if (!node)
        return;

    if (node->symbol != '\0')
    {
        std::cout << "Simbolo: " << node->symbol << ", Codigo: " << code << std::endl;
        int i = 0;
        while (code[i] != '\0')
        {
            codes[node->symbol][i] = code[i];
            i++;
        }
        codes[node->symbol][i] = '\0';
    }
    char *left_code = new char[32];
    char *right_code = new char[32];
    int i = 0;
    while (code[i] != '\0')
    {
        left_code[i] = code[i];
        right_code[i] = code[i];
        i++;
    }
    left_code[i] = '0';
    left_code[i + 1] = '\0';
    right_code[i] = '1';
    right_code[i + 1] = '\0';
    generateHuffmanCodes(node->left_son, left_code, codes);
    generateHuffmanCodes(node->right_son, right_code, codes);
    delete[] left_code;
    delete[] right_code;
}

void decodeHuffmanText(TreeNode *root, const char *textoCodificado)
{
    TreeNode *current = root;
    for (int i = 0; textoCodificado[i] != '\0'; i++)
    {
        if (textoCodificado[i] == '0')
        {
            current = current->left_son;
        }
        else if (textoCodificado[i] == '1')
        {
            current = current->right_son;
        }

        if (current->left_son == nullptr && current->right_son == nullptr)
        {
            if (current->symbol == ' ')
            {
                std::cout << " ";
            }
            else
            {
                std::cout << current->symbol;
            }
            current = root;
        }
    }
}

int main() {
    // Crear nodos
    TreeNode* nodes = new TreeNode[5];
    nodes[0] = *createNode('a', 0.1);
    nodes[1] = *createNode('b', 0.2);
    nodes[2] = *createNode('c', 0.3);
    nodes[3] = *createNode('d', 0.4);

    // Construir el árbol de Huffman
    TreeNode* root = buildHuffmanTree(nodes, 4);

    // Generar códigos de Huffman
    char* code = new char[32];
    code[0] = '\0';
    char** codes = new char*[256];
    for (int i = 0; i < 256; i++) {
        codes[i] = new char[32];
    }
    generateHuffmanCodes(root, code, codes);

    // Decodificar texto codificado
    const char* textoCodificado = "01010101";  // Este es un ejemplo, debes reemplazarlo con tu texto codificado
    decodeHuffmanText(root, textoCodificado);

    // Liberar memoria
    delete[] nodes;
    delete[] code;
    for (int i = 0; i < 256; i++) {
        delete[] codes[i];
    }
    delete[] codes;

    return 0;
}
