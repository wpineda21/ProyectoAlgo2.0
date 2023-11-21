#include <iostream>

using namespace std;
//Este Codigo Tiene Potencial ya que podria ser Utilizado Para la Fase 4 tambien ya que solo genera los arboles y su respectivo codigo de huffman
// Define la estructura del nodo del árbol de Huffman
struct TreeNode
{
    char symbol;
    double probability;
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

// Función para generar códigos de Huffman
void generateHuffmanCodes(TreeNode *node, string code, char codes[26][32])
{
    if (!node)
        return;

    if (node->symbol != '\0')
    {
        for (int i = 0; i < code.size(); i++)
        {
            codes[node->symbol - 'A'][i] = code[i];
        }
        codes[node->symbol - 'A'][code.size()] = '\0';
    }

    generateHuffmanCodes(node->left_son, code + '0', codes);
    generateHuffmanCodes(node->right_son, code + '1', codes);
}

int main()
{
    // Datos de entrada
    char symbols[] = {'A', 'B', 'C', 'D', 'E'};
    double probabilities[] = {0.15, 0.28, 0.71, 0.39, 0.32};

    // Crear nodos para cada letra del abecedario
    TreeNode nodes[5];
    for (int i = 0; i < 5; i++)
    {
        nodes[i] = *crearNodo(symbols[i], probabilities[i]);
    }

    // Construir el árbol de Huffman
    TreeNode *huffmanTree = buildHuffmanTree(nodes, 5);

    // Generar códigos de Huffman
    char huffmanCodes[26][32]; // Arreglo para almacenar los códigos
    generateHuffmanCodes(huffmanTree, "", huffmanCodes);

    // Imprimir los códigos de Huffman resultantes
    cout << "Códigos de Huffman para cada letra del abecedario:" << endl;
    for (int i = 0; i < 5; i++)
    {
        cout << symbols[i] << ": " << huffmanCodes[symbols[i] - 'A'] << endl;
    }

    return 0;
}
