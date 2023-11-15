#include <iostream>

#define EMPTY_STRING ""

// Estructura de nodo
struct Node
{
    char ch;
    int freq;
    Node* left;
    Node* right;
};

// Función para asignar un nuevo nodo de árbol
Node* getNode(char ch, int freq, Node* left, Node* right)
{
    Node* node = new Node;

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

// Función para verificar si un nodo es una hoja
bool isLeaf(Node* root)
{
    return root->left == nullptr && root->right == nullptr;
}

// Función para atravesar el árbol de Huffman y almacenar los códigos en un arreglo
void encode(Node* root, char huffmanCode[256][256], char* str, int codeLength)
{
    if (root == nullptr)
    {
        return;
    }

    if (isLeaf(root))
    {
        for (int i = 0; i < codeLength; i++)
        {
            huffmanCode[root->ch][i] = str[i];
        }
        huffmanCode[root->ch][codeLength] = '\0';
        codeLength++;
    }

    str[codeLength] = '0';
    encode(root->left, huffmanCode, str, codeLength);
    str[codeLength] = '1';
    encode(root->right, huffmanCode, str, codeLength);
}

// Función para atravesar el árbol de Huffman y decodificar la cadena codificada
void decode(Node* root, int& index, const char* str, char* result)
{
    if (root == nullptr)
    {
        return;
    }

    if (isLeaf(root))
    {
        result[index] = root->ch;
        index++;
        return;
    }

    index++;

    if (str[index] == '0')
    {
        decode(root->left, index, str, result);
    }
    else
    {
        decode(root->right, index, str, result);
    }
}
// ...

// Función para construir el árbol de Huffman y decodificar la cadena de entrada
void buildHuffmanTree(const char* text)
{
    if (text[0] == '\0')
    {
        return;
    }

    int freq[256] = {0};
    int n = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        freq[text[i]]++;
        n++;
    }

    Node* pq[256];
    int pqSize = 0;

    for (int i = 0; i < 256; i++)
    {
        if (freq[i] > 0)
        {
            pq[pqSize] = getNode(static_cast<char>(i), freq[i], nullptr, nullptr);
            pqSize++;
        }
    }

    while (pqSize != 1)
    {
        int min1 = 0, min2 = 1;
        if (pq[min1]->freq > pq[min2]->freq)
        {
            std::swap(min1, min2);
        }

        for (int i = 2; i < pqSize; i++)
        {
            if (pq[i]->freq < pq[min1]->freq)
            {
                min2 = min1;
                min1 = i;
            }
            else if (pq[i]->freq < pq[min2]->freq)
            {
                min2 = i;
            }
        }

        int sum = pq[min1]->freq + pq[min2]->freq;
        pq[pqSize] = getNode('\0', sum, pq[min1], pq[min2]);
        pqSize++;

        std::swap(pq[min1], pq[pqSize - 1]);
        std::swap(pq[min2], pq[pqSize - 2]);
        pqSize -= 2;
    }

    Node* root = pq[0];

    char huffmanCode[256][256];
    char str[256] = {0};
    int codeLength = 0;

    encode(root, huffmanCode, str, codeLength);

    std::cout << "Huffman Codes are:\n" << std::endl;
    for (int i = 0; i < 256; i++)
    {
        if (huffmanCode[i][0] != '\0')
        {
            std::cout << static_cast<char>(i) << " " << huffmanCode[i] << std::endl;
        }
    }

    std::cout << "\nThe original string is:\n" << text << std::endl;

    char result[256];
    int index = -1;

    if (isLeaf(root))
    {
        while (root->freq--)
        {
            result[++index] = root->ch;
        }
    }
    else
    {
        while (index < n - 1)
        {
            decode(root, index, text, result);
        }
    }

    result[n] = '\0';

    std::cout << "\nThe encoded string is:\n" << text << std::endl;
    std::cout << "\nThe decoded string is:\n" << result << std::endl;
}

int main()
{
    const char* text = "Barcelona el Mejor Equipo del Mundo";
    buildHuffmanTree(text);

    return 0;
}
