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
    std::swap(a, b);
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

void encodeHuffman(char text, TreeNode *root, std::string &encodedText)
{
    // Search for the character in the Huffman codes using the tree
    TreeNode *currentNode = root;

    while (currentNode != nullptr)
    {
        if (currentNode->symbol == text)
        {
            // Add the Huffman code corresponding to the character to the encoded text
            encodedText += currentNode->huffmanCode;
            break;
        }
        else if (text < currentNode->symbol)
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
        // If the character does not have a Huffman code, simply add the character to the encoded text
        encodedText += text;
    }
}

void decodeHuffman(char bit, TreeNode *&currentNode, TreeNode *root)
{
    if (bit == '0')
    {
        currentNode = currentNode->left;
    }
    else // bit is '1'
    {
        currentNode = currentNode->right;
    }

    // If a leaf node is reached
    if (currentNode->left == nullptr && currentNode->right == nullptr)
    {
        std::cout << currentNode->symbol;
        currentNode = root; // Go back to the root node for the next character
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
    generateHuffmanCodes(root);

    // Imprimir códigos de Huffman
    std::cout << "Códigos de Huffman:" << std::endl;
    printHuffmanCodes(root);

// Get user input
    std::cout << "Ingrese el texto a codificar: ";
    std::string textoOriginal;
    std::getline(std::cin, textoOriginal);

    // Encrypt the text using Huffman codes
    std::string encodedText;
    for (char c : textoOriginal)
    {
        encodeHuffman(c, root, encodedText);
    }
    std::cout << "Texto cifrado: " << encodedText;

    // Decrypt the text using Huffman codes
    std::cout << "\nTexto descifrado: ";
    TreeNode *currentNode = root;
    for (char bit : encodedText)
    {
        decodeHuffman(bit, currentNode, root);
    }

    return 0;
}
