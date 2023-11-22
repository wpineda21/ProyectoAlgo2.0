#include <iostream>

struct TreeNode
{
    TreeNode *parent;
    TreeNode *left;
    TreeNode *right;
    char symbol;
    double probability;
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

void bubbleUp(TreeNode* node)
{
    if (node->parent != nullptr && node->probability < node->parent->probability)
    {
        swap(node, node->parent);
        bubbleUp(node->parent);
    }
}

void insertNode(TreeNode* &root, TreeNode* node, TreeNode* parent = nullptr)
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

TreeNode* extractMin(TreeNode* &root)
{
    if (root == nullptr)
        return nullptr;

    TreeNode* minNode = root;
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

int main()
{
    TreeNode* root = nullptr;

    /*TreeNode* nodeA = createNode('a', 0.15);
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
    TreeNode* nodeZ = createNode('z', 0.41);*/

    insertNode(root, createNode('a', 0.15));
    insertNode(root, createNode('b', 0.12));
    insertNode(root, createNode('c', 0.71));
    insertNode(root, createNode('d', 0.39));
    insertNode(root, createNode('e', 0.32));
    insertNode(root, createNode('f', 0.70));
    insertNode(root, createNode('g', 0.33));
    insertNode(root, createNode('h', 0.73));
    insertNode(root, createNode('i', 0.5));
    insertNode(root, createNode('j', 0.10));
    insertNode(root, createNode('k', 0.90));
    insertNode(root, createNode('l', 0.72));
    insertNode(root, createNode('m', 0.73));
    insertNode(root, createNode('n', 0.94));
    insertNode(root, createNode('o', 0.94));
    insertNode(root, createNode('p', 0.07));
    insertNode(root, createNode('q', 0.84));
    insertNode(root, createNode('r', 0.46));
    insertNode(root, createNode('s', 0.04));
    insertNode(root, createNode('t', 0.01));
    insertNode(root, createNode('u', 0.66));
    insertNode(root, createNode('v', 0.32));
    insertNode(root, createNode('w', 0.51));
    insertNode(root, createNode('x', 0.98));
    insertNode(root, createNode('y', 0.62));
    insertNode(root, createNode('z', 0.41));
    
    TreeNode* minNode = extractMin(root);
    /*if (minNode != nullptr)
    {
        std::cout << "Simbolo: " << minNode->symbol << ", Probabilidad: " << minNode->probability << std::endl;
    }*/

    while (root->left != nullptr)
    {
        TreeNode* left = extractMin(root);
        TreeNode* right = extractMin(root);

        TreeNode* merged = createNode('\0', left->probability + right->probability);
        merged->left = left;
        merged->right = right;
        left->parent = merged;
        right->parent = merged;

        insertNode(root, merged);
    }

    std::cout<<"al menos compila"<<endl;

    return 0;
}
