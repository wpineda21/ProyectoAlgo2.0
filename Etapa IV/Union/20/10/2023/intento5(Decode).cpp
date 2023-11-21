#include <iostream>

using namespace std;

struct TreeNode
{
    char symbol;
    double probability;
    TreeNode *parent;
    TreeNode *left_son;
    TreeNode *right_son;
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

void MinHeapify(TreeNode *root)
{
    if (root == nullptr)
        return;

    TreeNode *smallest = root;
    if (root->left_son != nullptr && root->left_son->probability < smallest->probability)
        smallest = root->left_son;
    if (root->right_son != nullptr && root->right_son->probability < smallest->probability)
        smallest = root->right_son;

    if (smallest != root)
    {
        std::swap(root->probability, smallest->probability);
        std::swap(root->symbol, smallest->symbol);
        MinHeapify(smallest);
    }
}

void buildMinHeap(TreeNode *root)
{
    if (root == nullptr)
        return;

    buildMinHeap(root->left_son);
    buildMinHeap(root->right_son);
    MinHeapify(root);
}

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

void generateHuffmanCodes(TreeNode *node, const char *code, char **codes)
{
    if (!node)
        return;

    if (node->symbol != '\0')
    {
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

void encodeHuffmanText(TreeNode *root, const char *texto, char **codes)
{
    cout << "Texto original: " << texto << endl;
    cout << "Texto codificado: ";

    for (int i = 0; texto[i] != '\0'; i++)
    {
        cout << codes[static_cast<unsigned char>(texto[i])];
    }

    cout << endl;
}
void decodeHuffmanText(TreeNode *root, const char *encodedText)
{
    cout << "Texto cifrado: " << encodedText << endl;
    cout << "Texto descifrado: ";

    TreeNode *currentNode = root;

    for (int i = 0; encodedText[i] != '\0'; i++)
    {
        if (encodedText[i] == '0')
        {
            currentNode = currentNode->left_son;
        }
        else if (encodedText[i] == '1')
        {
            currentNode = currentNode->right_son;
        }

        // Si alcanzamos una hoja, imprime el símbolo y reinicia desde la raíz
        if (currentNode->left_son == nullptr && currentNode->right_son == nullptr)
        {
            cout << currentNode->symbol;
            currentNode = root;
        }
    }

    cout << endl;
}

int main()
{
    // Símbolos y probabilidades
    char symbols[] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z'};
    double probabilities[] = {0.15, 0.28, 0.71, 0.39, 0.32, 0.7, 0.33, 0.73, 0.5, 0.1, 0.9, 0.72, 0.73, 0.94, 0.94, 0.07, 0.84, 0.46, 0.4, 0.01, 0.66, 0.32, 0.51, 0.98, 0.62, 0.41};

    // Crear nodos para cada símbolo (uno más)
    int numNodes = sizeof(symbols) / sizeof(symbols[0]) + 1;
    TreeNode *nodes = new TreeNode[numNodes];

    // Crear nodos para los primeros numNodes - 1 símbolos
    for (int i = 0; i < numNodes - 1; i++)
    {
        nodes[i] = *crearNodo(symbols[i], probabilities[i]);
    }

    // Crear un nodo adicional (sin asignar un símbolo específico)
    nodes[numNodes - 1] = *crearNodo('\0', 0.0);

    // Construir el árbol de Huffman
    TreeNode *huffmanTreeRoot = buildHuffmanTree(nodes, numNodes);

    // Generar códigos Huffman
    char **huffmanCodes = new char *[256]; // Suponiendo que estás trabajando con caracteres ASCII
    for (int i = 0; i < 256; i++)
    {
        huffmanCodes[i] = new char[32];
        huffmanCodes[i][0] = '\0';
    }
    generateHuffmanCodes(huffmanTreeRoot, "", huffmanCodes);

    // Imprimir códigos Huffman
    for (int i = 0; i < numNodes - 1; i++)
    {
        cout << "Símbolo: " << nodes[i].symbol << ", Código: " << huffmanCodes[nodes[i].symbol] << endl;
    }
    cout << "Ingrese el texto cifrado: ";
    string encoded_text;
    getline(cin, encoded_text);

    // Codificar el texto usando los códigos Huffman generados
    //cout << "Aplicando el algoritmo de Huffman al texto:" << endl;
    encodeHuffmanText(huffmanTreeRoot, encoded_text.c_str(), huffmanCodes);

        // Decodificar el texto cifrado usando el árbol de Huffman inverso
    //cout << "Decodificando el texto cifrado:" << endl;
    decodeHuffmanText(huffmanTreeRoot, encoded_text.c_str());
       
    // Liberar memoria
    delete[] nodes;
    for (int i = 0; i < 256; i++)
    {
        delete[] huffmanCodes[i];
    }
    delete[] huffmanCodes;

    return 0;
}
