#include <iostream>

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
    if (!root )
        return;

    TreeNode *smallest = root;
    TreeNode *left = root->left_son;
    TreeNode *right = root->right_son;

    if (left && left->probability < smallest->probability)
    {
        smallest = left;
    }
    if (right && right->probability < smallest->probability)
    {
        smallest = right;
    }

    if (smallest != root)
    {
        std::swap(root->probability, smallest->probability);
        MinHeapify(smallest);
    }
}

void buildMinHeap(TreeNode *nodes, int numNodes)
{
    for (int i = numNodes / 2 - 1; i >= 0; i--)
    {
        MinHeapify(&nodes[i]);
    }
}

void MinHeapInsert(TreeNode *root, TreeNode *newNode)
{
if (!root || !newNode)
    return;

    if (!root->left_son)
    {
        root->left_son = newNode;
        newNode->parent = root;
    }
    else if (!root->right_son)
    {
        root->right_son = newNode;
        newNode->parent = root;
    }
    else
    {
        // Insert in the subtree with lower probability
        if (root->left_son->probability < root->right_son->probability)
        {
            MinHeapInsert(root->left_son, newNode);
        }
        else
        {
            MinHeapInsert(root->right_son, newNode);
        }
    }

    // Adjust the tree after insertion
    MinHeapify(root);
}

TreeNode *buildHuffmanTree(TreeNode *nodes, int numNodes)
{
    buildMinHeap(nodes, numNodes);

    while (numNodes > 1)
    {
        TreeNode *left = nodes;
        MinHeapify(left);

        TreeNode *right = nodes + 1;
        MinHeapify(right);

        TreeNode *merged = crearNodo('\0', left->probability + right->probability);
        merged->left_son = left;
        merged->right_son = right;
        left->parent = merged;
        right->parent = merged;

        nodes = merged;
        numNodes--;

        MinHeapInsert(nodes, merged);
        buildMinHeap(nodes, numNodes);
    }

    return nodes;
}

void generateHuffmanCodes(TreeNode *node, std::string code, std::string *codes)
{
    if (!node)
        return;

    if (node->symbol != '\0')
    {
        codes[node->symbol] = code;
    }

    generateHuffmanCodes(node->left_son, code + "0", codes);
    generateHuffmanCodes(node->right_son, code + "1", codes);
}

void decodeHuffmanText(TreeNode *root, const std::string &textoCodificado)
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
            std::cout << current->symbol;
            current = root; // Reset the current node to the root after decoding a symbol
        }
    }
}

int main()
{
    const int numNodes = 27; // Modified to exclude ' '
    TreeNode nodes[numNodes];
    nodes[0].symbol = 'a';
    nodes[0].probability = 0.15;
    nodes[0].parent = nullptr;
    nodes[0].left_son = nullptr;
    nodes[0].right_son = nullptr;

    nodes[1].symbol = 'b';
    nodes[1].probability = 0.28;
    nodes[1].parent = nullptr;
    nodes[1].left_son = nullptr;
    nodes[1].right_son = nullptr;

    nodes[2].symbol = 'c';
    nodes[2].probability = 0.71;
    nodes[2].parent = nullptr;
    nodes[2].left_son = nullptr;
    nodes[2].right_son = nullptr;

    nodes[3].symbol = 'd';
    nodes[3].probability = 0.39;
    nodes[3].parent = nullptr;
    nodes[3].left_son = nullptr;
    nodes[3].right_son = nullptr;

    nodes[4].symbol = 'e';
    nodes[4].probability = 0.32;
    nodes[4].parent = nullptr;
    nodes[4].left_son = nullptr;
    nodes[4].right_son = nullptr;

    nodes[5].symbol = 'f';
    nodes[5].probability = 0.7;
    nodes[5].parent = nullptr;
    nodes[5].left_son = nullptr;
    nodes[5].right_son = nullptr;

    nodes[6].symbol = 'g';
    nodes[6].probability = 0.33;
    nodes[6].parent = nullptr;
    nodes[6].left_son = nullptr;
    nodes[6].right_son = nullptr;

    nodes[7].symbol = 'h';
    nodes[7].probability = 0.73;
    nodes[7].parent = nullptr;
    nodes[7].left_son = nullptr;
    nodes[7].right_son = nullptr;

    nodes[8].symbol = 'i';
    nodes[8].probability = 0.5;
    nodes[8].parent = nullptr;
    nodes[8].left_son = nullptr;
    nodes[8].right_son = nullptr;

    nodes[9].symbol = 'j';
    nodes[9].probability = 0.1;
    nodes[9].parent = nullptr;
    nodes[9].left_son = nullptr;
    nodes[9].right_son = nullptr;

    nodes[10].symbol = 'k';
    nodes[10].probability = 0.9;
    nodes[10].parent = nullptr;
    nodes[10].left_son = nullptr;
    nodes[10].right_son = nullptr;

    nodes[11].symbol = 'l';
    nodes[11].probability = 0.72;
    nodes[11].parent = nullptr;
    nodes[11].left_son = nullptr;
    nodes[11].right_son = nullptr;

    nodes[12].symbol = 'm';
    nodes[12].probability = 0.73;
    nodes[12].parent = nullptr;
    nodes[12].left_son = nullptr;
    nodes[12].right_son = nullptr;

    nodes[13].symbol = 'n';
    nodes[13].probability = 0.94;
    nodes[13].parent = nullptr;
    nodes[13].left_son = nullptr;
    nodes[13].right_son = nullptr;

    nodes[14].symbol = 'p';
    nodes[14].probability = 0.11;
    nodes[14].parent = nullptr;
    nodes[14].left_son = nullptr;
    nodes[14].right_son = nullptr;

    nodes[15].symbol = 'o';
    nodes[15].probability = 0.94;
    nodes[15].parent = nullptr;
    nodes[15].left_son = nullptr;
    nodes[15].right_son = nullptr;

    nodes[16].symbol = 'p';
    nodes[16].probability = 0.07;
    nodes[16].parent = nullptr;
    nodes[16].left_son = nullptr;
    nodes[16].right_son = nullptr;

    nodes[17].symbol = 'q';
    nodes[17].probability = 0.84;
    nodes[17].parent = nullptr;
    nodes[17].left_son = nullptr;
    nodes[17].right_son = nullptr;

    nodes[18].symbol = 'r';
    nodes[18].probability = 0.46;
    nodes[18].parent = nullptr;
    nodes[18].left_son = nullptr;
    nodes[18].right_son = nullptr;

    nodes[19].symbol = 's';
    nodes[19].probability = 0.4;
    nodes[19].parent = nullptr;
    nodes[19].left_son = nullptr;
    nodes[19].right_son = nullptr;

    nodes[20].symbol = 't';
    nodes[20].probability = 0.01;
    nodes[20].parent = nullptr;
    nodes[20].left_son = nullptr;
    nodes[20].right_son = nullptr;

    nodes[21].symbol = 'u';
    nodes[21].probability = 0.66;
    nodes[21].parent = nullptr;
    nodes[21].left_son = nullptr;
    nodes[21].right_son = nullptr;

    nodes[22].symbol = 'v';
    nodes[22].probability = 0.32;
    nodes[22].parent = nullptr;
    nodes[22].left_son = nullptr;
    nodes[22].right_son = nullptr;

    nodes[23].symbol = 'w';
    nodes[23].probability = 0.51;
    nodes[23].parent = nullptr;
    nodes[23].left_son = nullptr;
    nodes[23].right_son = nullptr;

    nodes[24].symbol = 'x';
    nodes[24].probability = 0.98;
    nodes[24].parent = nullptr;
    nodes[24].left_son = nullptr;
    nodes[24].right_son = nullptr;

    nodes[25].symbol = 'y';
    nodes[25].probability = 0.62;
    nodes[25].parent = nullptr;
    nodes[25].left_son = nullptr;
    nodes[25].right_son = nullptr;

    nodes[26].symbol = 'z';
    nodes[26].probability = 0.41;
    nodes[26].parent = nullptr;
    nodes[26].left_son = nullptr;
    nodes[26].right_son = nullptr;

    nodes[27].symbol = ' ';       // Usamos ' ' para representar un espacio en blanco
    nodes[27].probability = 0.90; // La probabilidad de que ocurra un espacio en blanco
    nodes[27].parent = nullptr;
    nodes[27].left_son = nullptr;
    nodes[27].right_son = nullptr;

    TreeNode *root = buildHuffmanTree(nodes, numNodes);

    std::string huffmanCodes[256];
    generateHuffmanCodes(root, "", huffmanCodes);

    std::string inputText;
    std::string textoCodificado;

    int index = 0;

    int option;
    bool textoAlmacenado = false;
    bool huffmanAplicado = false;
    int contador = 0;

    do
    {
        std::cout << "1. Ingresar texto a modificar\n"
                  << "2. Consultar texto a modificar almacenado\n"
                  << "3. Aplicar Algoritmo de Huffman\n"
                  << "4. Consultar texto modificado almacenado\n"
                  << "5. Salir del programa\n"
                  << "Ingrese la opcion: ";
        while (!(std::cin >> option))
        {
            std::cout << "Error: Por favor, ingrese un número válido.\n";
            std::cout << "Por favor ingrese una Opcion válida: ";
            std::cin.clear();            // Limpiar el estado de error
            std::cin.ignore(1000, '\n'); // Descartar la entrada no válida
        }
        std::cout << "\n"
                  << std::endl;
        std::cin.ignore(); // Limpiar el buffer de entrada

        switch (option)
        {
        case 1:
        {
            // Reset variables
            std::string inputText;
            std::string textoCodificado;
            index = 0;
            textoAlmacenado = false;
            huffmanAplicado = false;

            std::cout << "Ingrese una cadena para codificar: ";
            std::getline(std::cin, inputText);

            textoAlmacenado = true;

            // Reconstruye el árbol de Huffman y regenera los códigos de Huffman
            root = buildHuffmanTree(nodes, numNodes);
            for (int i = 0; i < 256; i++)
            {
                huffmanCodes[i] = new char[32];
                huffmanCodes[i][0] = '\0';
            }
            char root_code[32] = "";
            generateHuffmanCodes(root, root_code, huffmanCodes);
            break;
        }
        case 2:
        {
            std::cout << "Texto a modificar almacenado: ";
            bool isEmpty = true; // Inicializar la variable

            for (int i = 0; inputText[i] != '\0'; i++)
            {
                std::cout << inputText[i];

                isEmpty = false;
            }

            if (isEmpty)
            {
                std::cout << "No hay Ningun Texto Almacenado";
            }

            std::cout << std::endl;
            break;
        }

        case 3:
        {
            if (!textoAlmacenado)
            {
                std::cout << "Error: No hay texto almacenado. Ingrese un texto primero." << std::endl;
            }
            else if (huffmanAplicado)
            {
                std::cout << "Error: El algoritmo de Huffman ya se aplicó a este texto." << std::endl;
            }
            else
            {
                for (int i = 0; inputText[i] != '\0'; i++)
                {
                    // char c = tolower(inputText[i]);
                    std::string huffmanCode = huffmanCodes[static_cast<unsigned char>(inputText[i])];

                    int j = 0;
                    while (huffmanCode[j] != '\0')
                    {
                        textoCodificado[index++] = huffmanCode[j++];
                    }
                }
                // Asegúrate de agregar el carácter nulo al final de la cadena.
                textoCodificado[index] = '\0';
                std::cout << "Texto codificado: " << textoCodificado << std::endl;
                huffmanAplicado = true;
            }
            break;
        }
        case 4:
        {
            if (!textoAlmacenado)
            {
                std::cout << "Error: No hay texto almacenado. Ingrese un texto primero." << std::endl;
            }
            else
            {
                std::cout << "Resultados Del Algoritmo: " << std::endl;
                std::cout << "Texto Cifrado por Huffman: " << textoCodificado << std::endl;
                std::cout << "Texto Decifrado: ";
                decodeHuffmanText(root, textoCodificado);
                std::cout << std::endl;
            }
            break;
        }
        case 5:
        {
            std::cout << "Saliendo del programa.\n";
            break;
        }
        default:
        {
            std::cout << "Opcion no válida. Inténtelo de nuevo.\n";
            break;
        }
        }

    } while (option != 5);

    return 0;
}
