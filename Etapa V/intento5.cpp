#include <iostream>
/*Este Codigo Esta Ok funciona, Codifica  y genera los codigos de huffman falta el decodificador*/
const int MAX_NODES = 27; // Tamaño máximo de nodos (puedes ajustarlo según tu necesidad)

struct TreeNode
{
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;
    char symbol;
    double probability;
    std::string huffmanCode;
};

TreeNode *createNode(char symbol, double probability)
{
    TreeNode *node = new TreeNode;
    node->parent = nullptr;
    node->left = nullptr;
    node->right = nullptr;
    node->symbol = symbol;
    node->probability = probability;
    return node;
}

void swap(TreeNode *&a, TreeNode *&b)
{
    TreeNode *temp = a;
    a = b;
    b = temp;
}

void bubbleUp(TreeNode *node)
{
    if (node->parent != nullptr && node->probability < node->parent->probability)
    {
        swap(node, node->parent);
        bubbleUp(node->parent);
    }
}

void insertNode(TreeNode *&root, TreeNode *node)
{
    if (root == nullptr)
    {
        root = node;
    }
    else if (node->probability > root->probability)
    {
        node->left = root;
        root->parent = node;
        root = node;
    }
    else
    {
        insertNode(root->right, node);
        if (root->right != nullptr)
        {
            root->right->parent = root;
        }
    }
}

TreeNode *extractMin(TreeNode *&root)
{
    if (root == nullptr)
        return nullptr;

    TreeNode *minNode = root;
    if (root->left != nullptr)
    {
        root->left->parent = nullptr;
        root = root->left;
    }
    else if (root->right != nullptr)
    {
        root->right->parent = nullptr;
        root = root->right;
    }
    else
    {
        root = nullptr;
    }
    minNode->left = nullptr;
    minNode->right = nullptr;
    return minNode;
}

// Función para generar códigos Huffman a partir de un árbol Huffman
void generateHuffmanCodes(TreeNode *node, const std::string &code)
{
    // Si el nodo es nulo, no hay nada que procesar, por lo que retornamos
    if (node == nullptr)
    {
        return;
    }

    // Imprimimos información sobre el nodo que estamos procesando
    std::cout << "Procesando nodo con simbolo: " << node->symbol << ", Probabilidad: " << node->probability << ", Código actual: " << code << std::endl;

    // Si el nodo es una hoja (no tiene hijos), o si tiene un solo hijo, entonces le asignamos el código Huffman actual
    if (node->left == nullptr || node->right == nullptr)
    {
        node->huffmanCode = code;
        std::cout << "Código asignado para el símbolo '" << node->symbol << "': " << code << std::endl;
    } 
    // Generamos códigos Huffman para el subárbol izquierdo y derecho
    // Nota: Añadimos '1' al código para el subárbol izquierdo y '0' para el subárbol derecho
    generateHuffmanCodes(node->left, code + "0");
    generateHuffmanCodes(node->right, code + "1");
}

void buildHuffmanTree(TreeNode *&root)
{
    // Construir el árbol de Huffman
    while (root->parent != nullptr)
    {
        TreeNode *node1 = extractMin(root);
        TreeNode *node2 = extractMin(root);

        TreeNode *internalNode = createNode('\0', node1->probability + node2->probability);
        internalNode->left = node1;
        internalNode->right = node2;

        insertNode(root, internalNode);
    }
}
void printHuffmanCodes(TreeNode *root)
{
    if (root != nullptr)
    {
        if (root->symbol != '\0')
        {
            std::cout << "Símbolo: " << root->symbol << ", Código Huffman: " << root->huffmanCode << std::endl;
        }
        printHuffmanCodes(root->left);
        printHuffmanCodes(root->right);
    }
}

std::string encodeHuffman(const char *text, TreeNode *root)
{
    std::string encodedText;
    while (*text != '\0')
    {
        TreeNode *currentNode = root;
        while (currentNode != nullptr)
        {
            if (currentNode->symbol == *text)
            {
                encodedText += currentNode->huffmanCode;
                break;
            }
            else if (*text < currentNode->symbol)
            {
                currentNode = currentNode->left;
            }
            else
            {
                currentNode = currentNode->right;
            }
        }
        if (currentNode == nullptr)
        {
            encodedText += *text;
        }
        ++text;
    }
    return encodedText;
}

void decodeHuffmanText(TreeNode *root, const std::string &encodedText)
{
    TreeNode *current = root;
    for (char c : encodedText)
    {
        if (c == '0')
        {
            current = current->left;
        }
        else if (c == '1')
        {
            current = current->right;
        }

        if (current->left == nullptr && current->right == nullptr)
        {
            std::cout << current->symbol;
            current = root;
        }
    }
}

int main()
{
    TreeNode *root = nullptr;

    TreeNode *nodeA = createNode('a', 0.15);
    TreeNode *nodeB = createNode('b', 0.12);
    TreeNode *nodeC = createNode('c', 0.71);
    TreeNode *nodeD = createNode('d', 0.39);
    TreeNode *nodeE = createNode('e', 0.32);
    TreeNode *nodeF = createNode('f', 0.70);
    TreeNode *nodeG = createNode('g', 0.33);
    TreeNode *nodeH = createNode('h', 0.73);
    TreeNode *nodeI = createNode('i', 0.50);
    TreeNode *nodeJ = createNode('j', 0.10);
    TreeNode *nodeK = createNode('k', 0.90);
    TreeNode *nodeL = createNode('l', 0.72);
    TreeNode *nodeM = createNode('m', 0.73);
    TreeNode *nodeN = createNode('n', 0.94);
    TreeNode *nodeO = createNode('o', 0.94);
    TreeNode *nodeP = createNode('p', 0.07);
    TreeNode *nodeQ = createNode('q', 0.84);
    TreeNode *nodeR = createNode('r', 0.46);
    TreeNode *nodeS = createNode('s', 0.04);
    TreeNode *nodeT = createNode('t', 0.01);
    TreeNode *nodeU = createNode('u', 0.66);
    TreeNode *nodeV = createNode('v', 0.32);
    TreeNode *nodeW = createNode('w', 0.51);
    TreeNode *nodeX = createNode('x', 0.98);
    TreeNode *nodeY = createNode('y', 0.62);
    TreeNode *nodeZ = createNode('z', 0.41);

    insertNode(root, nodeA);
    insertNode(root, nodeB);
    insertNode(root, nodeC);
    insertNode(root, nodeD);
    insertNode(root, nodeE);
    insertNode(root, nodeF);
    insertNode(root, nodeG);
    insertNode(root, nodeH);
    insertNode(root, nodeI);
    insertNode(root, nodeJ);
    insertNode(root, nodeK);
    insertNode(root, nodeL);
    insertNode(root, nodeM);
    insertNode(root, nodeN);
    insertNode(root, nodeO);
    insertNode(root, nodeP);
    insertNode(root, nodeQ);
    insertNode(root, nodeR);
    insertNode(root, nodeS);
    insertNode(root, nodeT);
    insertNode(root, nodeU);
    insertNode(root, nodeV);
    insertNode(root, nodeW);
    insertNode(root, nodeX);
    insertNode(root, nodeY);
    insertNode(root, nodeZ);

    buildHuffmanTree(root);

    // Generar códigos de Huffman
    generateHuffmanCodes(root,"");

    // Imprimir códigos de Huffman
    std::cout << "Códigos de Huffman:" << std::endl;
    printHuffmanCodes(root);

    // Obtener entrada de usuario
    std::cout << "Ingrese el texto a codificar: ";
    std::string textoOriginal;
    std::getline(std::cin, textoOriginal);

    std::string textoCodificado = encodeHuffman(textoOriginal.c_str(), root);
    std::cout << "Texto cifrado: " << textoCodificado << std::endl;

    std::cout << "Texto decodificado: ";
    decodeHuffmanText(root, textoCodificado);

    return 0;
}
