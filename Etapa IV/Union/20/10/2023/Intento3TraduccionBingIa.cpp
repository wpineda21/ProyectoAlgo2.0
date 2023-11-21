#include <iostream>

using namespace std;

// Define la estructura del nodo del árbol de Huffman
struct TreeNode
{
    char symbol;
    double probability;
    string code; // Almacena el código de Huffman directamente en el nodo
    TreeNode *parent;
    TreeNode *left_son;
    TreeNode *right_son;
};

// Función para crear un nodo
TreeNode *crearNodo(char symbol, double probability)
{
    TreeNode *newnode = new TreeNode;
    newnode->symbol = symbol;
    newnode->probability = probability;
    newnode->code = "";
    newnode->parent = nullptr;
    newnode->left_son = nullptr;
    newnode->right_son = nullptr;
    return newnode;
}

// Función para insertar en el montículo mínimo
TreeNode *MinHeapInsert(TreeNode *root, TreeNode *newNode)
{
    if (root == nullptr)
        return newNode;

    if (newNode->probability < root->probability)
    {
        newNode->left_son = root;
        return newNode;
    }

    TreeNode *right = MinHeapInsert(root->right_son, newNode);
    root->right_son = right;
    right->parent = root;

    if (root->left_son != nullptr && root->left_son->probability < root->right_son->probability)
    {
        std::swap(root->left_son, root->right_son);
    }

    return root;
}

// Función para construir el árbol de Huffman
TreeNode *buildHuffmanTree(TreeNode *nodes, int numNodes)
{
    TreeNode *root = nullptr;

    for (int i = 0; i < numNodes; i++)
    {
        root = MinHeapInsert(root, nodes + i);
    }

    while (root->left_son != nullptr && root->right_son != nullptr)
    {
        TreeNode *left = root;
        root = root->right_son;
        left->parent = nullptr;
        root->parent = nullptr;

        TreeNode *right = root;
        if (root->left_son != nullptr && root->left_son->probability < root->probability)
        {
            right = root->left_son;
            root->left_son = root->left_son->right_son;
            if (root->left_son != nullptr)
                root->left_son->parent = root;
            right->parent = nullptr;
            right->right_son = nullptr;
        }

        TreeNode *merged = crearNodo('\0', left->probability + right->probability);
        merged->left_son = left;
        merged->right_son = right;
        left->parent = merged;
        right->parent = merged;

        root = MinHeapInsert(root, merged);
    }

    return root;
}

// Función para generar códigos de Huffman// Función para generar códigos de Huffman
void generateHuffmanCodes(TreeNode *node, string code)
{
    if (!node)
        return;

    if (node->symbol != '\0')
    {
        node->code = code;
    }

    // Invierte la asignación de '0' y '1' para asignar códigos más cortos a mayores probabilidades
    generateHuffmanCodes(node->left_son, code + '0');
    generateHuffmanCodes(node->right_son, code + '1');
}

int main()
{
    // Datos de entrada
  char symbols[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
  double probabilities[] = {0.15, 0.28, 0.71, 0.39, 0.32, 0.7, 0.33, 0.73, 0.5, 0.1, 0.9, 0.72, 0.73, 0.94, 0.94, 0.07, 0.84, 0.46, 0.4, 0.01, 0.66, 0.32, 0.51, 0.98, 0.62, 0.41};

    // Crear nodos para cada letra del abecedario
    TreeNode nodes[27];
    for (int i = 0; i < 27; i++)
    {
        nodes[i] = *crearNodo(symbols[i], probabilities[i]);
    }

    TreeNode *huffmanTree = buildHuffmanTree(nodes, 27);
    generateHuffmanCodes(huffmanTree, "");

    cout << "Códigos de Huffman para cada letra del abecedario:" << endl;
    for (int i = 0; i < 26; i++)
    {
        cout << nodes[i].symbol << ": " << nodes[i].code << endl;
    }

    return 0;
}
