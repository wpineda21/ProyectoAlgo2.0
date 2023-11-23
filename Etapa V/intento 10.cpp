#include <iostream>

struct TreeNode
{
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;
    char symbol;
    double probability;
    std::string huffmanCode;
};

TreeNode* createNode(char symbol, double probability)
{
    TreeNode* node = new TreeNode;
    node->parent = nullptr;
    node->left = nullptr;
    node->right = nullptr;
    node->symbol = symbol;
    node->probability = probability;
    return node;
}

void swap(TreeNode* &a, TreeNode* &b)
{
    TreeNode* temp = a;
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



void buildHuffmanTree(TreeNode *&root)
{
    while (root != nullptr && root->parent != nullptr)
    {
        TreeNode *node1 = extractMin(root);
        TreeNode *node2 = extractMin(root);

        if (node1 == nullptr || node2 == nullptr)
            break;

        TreeNode *internalNode = createNode('\0', node1->probability + node2->probability);
        internalNode->left = node1;
        internalNode->right = node2;

        insertNode(root, internalNode);
    }
}

void generateHuffmanCodes(TreeNode *root, std::string currentCode = "")
{
    if (root != nullptr)
    {
        if (root->symbol != '\0')
        {
            root->huffmanCode = currentCode;
            //std::cout << "Symbol: " << root->symbol << ", Huffman Code: " << currentCode << std::endl;
        }
        generateHuffmanCodes(root->left, currentCode + "1"); // Invertir 0 y 1 aquí
        generateHuffmanCodes(root->right, currentCode + "0");
    }
}

std::string getHuffmanString(TreeNode *root, char c)
{
    if (root != nullptr)
    {
        if (root->symbol == c)
        {
            if (c == ' ')
                return "\n";  // Return newline for space
            else
                return root->huffmanCode;
        }
        std::string left = getHuffmanString(root->left, c);
        if (!left.empty())
        {
            return left;
        }
        std::string right = getHuffmanString(root->right, c);
        if (!right.empty())
        {
            return right;
        }
    }
    return "";
}
std::string decodeHuffmanString(TreeNode *root, const std::string &huffmanString)
{
    std::string decodedString;
    TreeNode *currentNode = root;
    for (char bit : huffmanString)
    {
        if (bit == '0')
            currentNode = currentNode->left;
        else // bit == '1'
            currentNode = currentNode->right;

        // If it's a leaf node
        if (currentNode->left == nullptr && currentNode->right == nullptr)
        {
            decodedString += currentNode->symbol;
            currentNode = root; // Go back to the root for the next character
        }
    }
    return decodedString;
}

void insertNodes(TreeNode *&root)
{
    TreeNode* nodeA = createNode('a', 0.15);
    TreeNode* nodeB = createNode('b', 0.12);
    TreeNode* nodeC = createNode('c', 0.71);
    TreeNode* nodeD = createNode('d', 0.39);
    TreeNode* nodeE = createNode('e', 0.32);
    TreeNode* nodeF = createNode('f', 0.70);
    TreeNode* nodeG = createNode('g', 0.33);
    TreeNode* nodeH = createNode('h', 0.73);
    TreeNode* nodeI = createNode('i', 0.5);
    TreeNode* nodeJ = createNode('j', 0.10);
    TreeNode* nodeK = createNode('k', 0.90);
    TreeNode* nodeL = createNode('l', 0.72);
    TreeNode* nodeM = createNode('m', 0.73);
    TreeNode* nodeN = createNode('n', 0.94);
    TreeNode* nodeO = createNode('o', 0.94);
    TreeNode* nodeP = createNode('p', 0.07);
    TreeNode* nodeQ = createNode('q', 0.84);
    TreeNode* nodeR = createNode('r', 0.46);
    TreeNode* nodeS = createNode('s', 0.04);
    TreeNode* nodeT = createNode('t', 0.01);
    TreeNode* nodeU = createNode('u', 0.66);
    TreeNode* nodeV = createNode('v', 0.32);
    TreeNode* nodeW = createNode('w', 0.51);
    TreeNode* nodeX = createNode('x', 0.98);
    TreeNode* nodeY = createNode('y', 0.62);
    TreeNode* nodeZ = createNode('z', 0.41);
    TreeNode* nodeBlank = createNode(' ', 0.99);

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
    insertNode(root, nodeBlank);
}

/*int BussinesLogic()
{

    TreeNode* root = nullptr;

    insertNodes(root);

    buildHuffmanTree(root);

    // Generar códigos de Huffman
    generateHuffmanCodes(root);

    // Get user input
    std::string userInput;
    std::cout << "Enter a string: ";
    std::getline(std::cin, userInput);

    // Print Huffman string for each character in the input
    std::cout << "Huffman strings:" << std::endl;

    for (char c : userInput)
    {
        std::cout << "Symbol: " << c << ", Huffman String: " << getHuffmanString(root, c) << std::endl;
    }

        std::string huffmanString;
    for (char c : userInput)
    {
        huffmanString += getHuffmanString(root, c);
    }

    // Print the concatenated Huffman string
    std::cout << "Concatenated Huffman string: "<< "\n" << huffmanString << std::endl;

    for (char c : userInput)
    {
        huffmanString += getHuffmanString(root, c);
    }

    std::cout << "Decoded string:" << userInput.c_str() << std::endl;
    

    return 0;
}*/

int BussinesLogic()
{

    TreeNode* root = nullptr;
    insertNodes(root);
    buildHuffmanTree(root);
    generateHuffmanCodes(root);

    // Get user input
    std::string userInput;
    std::cout << "Enter a string: ";
    std::getline(std::cin, userInput);

    // Print Huffman string for each character in the input
    std::cout << "Huffman strings:" << std::endl;

    for (char c : userInput)
    {
        std::cout << "Symbol: " << c << ", Huffman String: " << getHuffmanString(root, c) << std::endl;
    }

        std::string huffmanString;
    for (char c : userInput)
    {
        huffmanString += getHuffmanString(root, c);
    }

    // Print the concatenated Huffman string
    std::cout << "Concatenated Huffman string: "<< "\n" << huffmanString << std::endl;

    for (char c : userInput)
    {
        huffmanString += getHuffmanString(root, c);
    }

    std::cout << "Decoded string:" << userInput.c_str() << std::endl;
    

    return 0;
}

int Menu(){
    TreeNode* root = nullptr;
    insertNodes(root);
    buildHuffmanTree(root);
    generateHuffmanCodes(root);
    std::string userInput = "";
    bool textoIngresado = false;
    std::string huffmanString = "";
    bool algoritmoHuffmanAplicado = false;

    while (true)
    {
        std::cout << "1. Ingresar texto\n"
                  << "2. Consultar texto\n"
                  << "3. Aplicar Algoritmo de Huffman\n"
                  << "4. Consultar texto modificado\n"
                  << "5. Salir\n"
                  << "Seleccione una opción: ";

        int opcion;
        std::cin >> opcion;
        std::cin.ignore(); // Limpiar el buffer de entrada

        switch (opcion)
        {
        case 1:
                if (textoIngresado) {
                 std::cout << "Ya hay un texto almacenado, Tome en Cuenta que Esta Sobreescribiendo el Texto: " << std::endl;
                    textoIngresado = false;  // Reiniciar el indicador
                    algoritmoHuffmanAplicado = false;
                    huffmanString = "";  // Reiniciar el indicador
                }
                std::cout << "Por Favor Ingresa Un texto: ";
                std::getline(std::cin, userInput);
                textoIngresado = true; // Actualizar el indicador
                algoritmoHuffmanAplicado = false;
                break;
            break;
        case 2:
                if (textoIngresado) {
                    std::cout << "Texto almacenado: " << userInput << std::endl;
                } else {
                    std::cout << "No hay un texto almacenado aún. Por favor, ingresa un texto primero." << std::endl;
                }
            break;
        case 3:
                if (textoIngresado && !algoritmoHuffmanAplicado) {
                    // Print Huffman string for each character in the input
                    std::cout << "Huffman strings:" << std::endl;

                    for (char c : userInput)
                    {
                        std::cout << "Symbol: " << c << ", Huffman String: " << getHuffmanString(root, c) << std::endl;
                    }
                    for (char c : userInput)
                    {
                        huffmanString += getHuffmanString(root, c);
                    }

                    // Print the concatenated Huffman string
                    std::cout << "Concatenated Huffman string: "<< "\n" << huffmanString << std::endl;
                    algoritmoHuffmanAplicado = true;
                } else if (!textoIngresado) {
                    std::cout << "No hay un texto almacenado aún. ingresa un texto primero para poder aplicar el Algoritmo de Huffman" << std::endl;
                } else {
                    std::cout << "El algoritmo de Huffman ya se aplicó al texto, Si desea Visualizarlo Seleccione la Opcion 4" << std::endl;
                }
            break;
        case 4: 
                
                if (textoIngresado) {
                        if(algoritmoHuffmanAplicado == true){
                            std::cout << "Concatenated Huffman string: "<< huffmanString << std::endl;
                            std::cout << "Texto Decifrado: " << userInput.c_str() << std::endl;
                        } else {
                            std::cout << "Es Necesario Aplicar el Algoritmo de Huffman al Texto para acceder a esta opcion "<<std::endl;
                        }
                } else {
                    std::cout << "No hay un texto almacenado aún. Por favor, ingresa un texto primero." << std::endl;
                }
            break;
        case 5:
            std::cout<<"Saliendo del programa"<<std::endl;
            return 0; // Salir del programa
        default:
            std::cout << "Opcion no valida. Intente de nuevo." << std::endl;
            break;
        }
    }
}

int main(){
    //BussinesLogic();
    Menu();
}