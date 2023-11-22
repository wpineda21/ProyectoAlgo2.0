#include <iostream>

struct TreeNode
{
    TreeNode *parent;
    TreeNode *left;
    std::string code;
    TreeNode *right;
    char symbol;
    double probability;
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

void insertNode(TreeNode *&root, TreeNode *node, TreeNode *parent = nullptr)
{
    if (root == nullptr)
    {
        root = node;
        root->parent = parent;
    }
    else if (node->probability < root->probability)
    {
        node->left = root->left;
        node->right = root;
        if (node->left != nullptr)
            node->left->parent = node;
        root->left = nullptr;
        root->parent = node;
        root = node;
    }
    else
    {
        insertNode(root->left, node, root);
    }
    bubbleUp(node);
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

TreeNode *buildHuffmanTree(TreeNode *nodes, int numNodes)
{
    TreeNode *root = nullptr;

    for (int i = 0; i < numNodes; i++)
    {
        insertNode(root, createNode(nodes[i].symbol, nodes[i].probability));
    }

    while (root->left != nullptr)
    {
        TreeNode *left = extractMin(root);
        TreeNode *right = extractMin(root);

        TreeNode *merged = createNode('\0', left->probability + right->probability);
        merged->left = left;
        merged->right = right;
        left->parent = merged;
        right->parent = merged;

        insertNode(root, merged);
    }

    return root;
}
void generateHuffmanCodes(TreeNode *root, const std::string &code)
{
    if (root == nullptr)
        return;

    root->code = code;

    generateHuffmanCodes(root->left, code + "0");
    generateHuffmanCodes(root->right, code + "1");
}

void printHuffmanCodes(TreeNode *root)
{
    if (root == nullptr)
        return;

    if (root->symbol != '\0')
        std::cout << "Symbol: " << root->symbol << ", Code: " << root->code << std::endl;

    printHuffmanCodes(root->left);
    printHuffmanCodes(root->right);
}

void encodeHuffman(const char *text, TreeNode *root)
{
    while (*text != '\0')
    {
        // Buscar el carácter en los códigos de Huffman usando el árbol
        TreeNode *currentNode = root;

        while (currentNode != nullptr)
        {
            if (currentNode->symbol == *text)
            {
                // Imprimir el código Huffman correspondiente al carácter
                std::cout << currentNode->code;
                break;
            }
            else
            {
                currentNode = (currentNode->left != nullptr && currentNode->left->symbol <= *text) ? currentNode->left : currentNode->right;
            }
        }

        if (currentNode == nullptr)
        {
            // Si el carácter no tiene un código Huffman, simplemente imprimir el carácter
            std::cout << *text;
        }

        ++text;
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
    TreeNode *nodeI = createNode('i', 0.5);
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

    TreeNode *minNode = extractMin(root);
    if (minNode != nullptr)
    {
        std::cout << "Simbolo: " << minNode->symbol << ", Probabilidad: " << minNode->probability << std::endl;
    }

    // codigos de huffman
    generateHuffmanCodes(root, "");
    printHuffmanCodes(root);
    
    const char *text = "Hola papasito rico";
    encodeHuffman(text, root);

    return 0;
}