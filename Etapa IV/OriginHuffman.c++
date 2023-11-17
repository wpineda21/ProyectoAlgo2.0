#include <iostream>
#include <string>
#include <queue>
#include <unordered_map>
using namespace std;

#define EMPTY_STRING ""

// Un nodo de árbol
struct Node
{
    char ch;
    int freq;
    Node *left, *right;
};

// Función para asignar un nuevo nodo de árbol
Node *getNode(char ch, int freq, Node *left, Node *right)
{
    Node *node = new Node();

    node->ch = ch;
    node->freq = freq;
    node->left = left;
    node->right = right;

    return node;
}

// Objeto de comparación que se usará para ordenar el heap
struct comp
{
    bool operator()(const Node *l, const Node *r) const
    {
        // el elemento de mayor prioridad tiene la menor frecuencia
        return l->freq > r->freq;
    }
};

// Función de utilidad para verificar si Huffman Tree contiene solo un solo nodo
bool isLeaf(Node *root)
{
    return root->left == nullptr && root->right == nullptr;
}

// Atraviesa el árbol de Huffman y almacena los códigos de Huffman en un mapa.
void encode(Node *root, string str, unordered_map<char, string> &huffmanCode)
{
    if (root == nullptr)
    {
        return;
    }

    // encontrado un nodo hoja
    if (isLeaf(root))
    {
        huffmanCode[root->ch] = (str != EMPTY_STRING) ? str : "1";
    }

    encode(root->left, str + "0", huffmanCode);
    encode(root->right, str + "1", huffmanCode);
}

// Atraviesa el árbol de Huffman y decodifica la string codificada
void decode(Node *root, int &index, string str)
{
    if (root == nullptr)
    {
        return;
    }

    // encontrado un nodo hoja
    if (isLeaf(root))
    {
        cout << root->ch;
        return;
    }

    index++;

    if (str[index] == '0')
    {
        decode(root->left, index, str);
    }
    else
    {
        decode(root->right, index, str);
    }
}

// Construye Huffman Tree y decodifica el texto de entrada dado
void buildHuffmanTree(string text)
{
    // caso base: string vacía
    if (text == EMPTY_STRING)
    {
        return;
    }

    // cuenta la frecuencia de aparición de cada personaje
    // y almacenarlo en un mapa
    unordered_map<char, int> freq;
    for (char ch : text)
    {
        freq[ch]++;
    }

    // Crear una cola de prioridad para almacenar nodos en vivo del árbol de Huffman
    priority_queue<Node *, vector<Node *>, comp> pq;

    // Crea un nodo hoja para cada carácter y añádelo
    // a la cola de prioridad.
    for (auto pair : freq)
    {
        pq.push(getNode(pair.first, pair.second, nullptr, nullptr));
    }

    // hacer hasta que haya más de un nodo en la queue
    while (pq.size() != 1)
    {
        // Elimina los dos nodos de mayor prioridad
        // (la frecuencia más baja) de la queue

        Node *left = pq.top();
        pq.pop();
        Node *right = pq.top();
        pq.pop();

        // crea un nuevo nodo interno con estos dos nodos como hijos y
        // con una frecuencia igual a la suma de las frecuencias de los dos nodos.
        // Agregar el nuevo nodo a la cola de prioridad.

        int sum = left->freq + right->freq;
        pq.push(getNode('\0', sum, left, right));
    }

    // `root` almacena el puntero a la raíz de Huffman Tree
    Node *root = pq.top();

    // Atraviesa el árbol Huffman y almacena códigos Huffman
    // en un mapa. Además imprímelos
    unordered_map<char, string> huffmanCode;
    encode(root, EMPTY_STRING, huffmanCode);

    cout << "Huffman Codes are:\n"
         << endl;
    for (auto pair : huffmanCode)
    {
        cout << pair.first << " " << pair.second << endl;
    }

    cout << "\nThe original string is:\n"
         << text << endl;

    // Imprimir string codificada
    string str;
    for (char ch : text)
    {
        str += huffmanCode[ch];
    }

    cout << "\nThe encoded string is:\n"
         << str << endl;
    cout << "\nThe decoded string is:\n";

    if (isLeaf(root))
    {
        // Caso especial: Para entradas como a, aa, aaa, etc.
        while (root->freq--)
        {
            cout << root->ch;
        }
    }
    else
    {
        // Atraviesa el árbol Huffman de nuevo y esta vez,
        // decodifica la string codificada
        int index = -1;
        while (index < (int)str.size() - 1)
        {
            decode(root, index, str);
        }
    }
}

// Implementación del algoritmo de codificación de Huffman en C++
int main()
{
    string text = "El veloz murciélago hindu comía feliz cardillo y kiwi";
    buildHuffmanTree(text);

    return 0;
}