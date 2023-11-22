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

void generateHuffmanCodes(TreeNode *root, std::string currentCode = "")
{
    if (root != nullptr)
    {
        if (root->symbol != '\0')
        {
            root->huffmanCode = currentCode;
        }
        generateHuffmanCodes(root->left, currentCode + "0"); // Invertir 0 y 1 aquí
        generateHuffmanCodes(root->right, currentCode + "1");
    }
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

void encodeHuffman(const char *text, TreeNode *root, std::string &encodedText)
{
    while (*text != '\0')
    {
        // Buscar el carácter en los códigos de Huffman usando el árbol
        TreeNode *currentNode = root;

        while (currentNode != nullptr)
        {
            if (currentNode->symbol == *text)
            {
                // Almacenar el código Huffman correspondiente al carácter
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
            // Si el carácter no tiene un código Huffman, simplemente almacenar el carácter
            encodedText += *text;
        }

        ++text;
    }
}

char decodeSymbol(const std::string &code, TreeNode *root)
{
    TreeNode *currentNode = root;

    for (char bit : code)
    {
        if (bit == '0' && currentNode->left != nullptr)
        {
            currentNode = currentNode->left;
        }
        else if (bit == '1' && currentNode->right != nullptr)
        {
            currentNode = currentNode->right;
        }
        else
        {
            // En caso de un código inválido, puedes manejarlo según tus necesidades
            std::cerr << "Código Huffman inválido encontrado durante la decodificación.\n";
            return '\0'; // Puedes cambiar esto según tus necesidades
        }
    }

    return currentNode->symbol;
}

// Función para decodificar una cadena Huffman completa
std::string decodeHuffman(const std::string &encodedText, TreeNode *root)
{
    std::string decodedText;
    std::string currentCode;

    for (char bit : encodedText)
    {
        currentCode += bit;

        char symbol = decodeSymbol(currentCode, root);
        if (symbol != '\0')
        {
            decodedText += symbol;
            currentCode = ""; // Reiniciar el código actual después de decodificar un carácter
        }
    }

    return decodedText;
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
    generateHuffmanCodes(root);

    // Imprimir códigos de Huffman
    std::cout << "Códigos de Huffman:" << std::endl;
    printHuffmanCodes(root);

std::cout << "Ingrese el texto a codificar: ";
    std::string textoOriginal;
    std::getline(std::cin, textoOriginal);

    // Cifrar el texto usando los códigos de Huffman
    std::string encodedText;
    encodeHuffman(textoOriginal.c_str(), root, encodedText);
    std::cout << "Texto cifrado: " << encodedText << std::endl;

    // Decodificar el texto usando los códigos de Huffman
    std::string textoDecodificado = decodeHuffman(encodedText, root);
    std::cout << "Texto decodificado: " << textoDecodificado << std::endl;

    return 0;
}
