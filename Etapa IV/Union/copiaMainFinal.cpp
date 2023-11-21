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

TreeNode *buildHuffmanTree(TreeNode *root, TreeNode *left, TreeNode *right)
{
    TreeNode *merged = crearNodo('\0', left->probability + right->probability);
    merged->left_son = left;
    merged->right_son = right;
    left->parent = merged;
    right->parent = merged;

    MinHeapInsert(root, merged);

    return root;
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
    return 0;
}
