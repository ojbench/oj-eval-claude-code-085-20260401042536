#include <iostream>
#include <vector>
using namespace std;

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

// Build tree from extended preorder traversal
TreeNode* buildTree(vector<int>& preorder, int& index) {
    if (index >= preorder.size() || preorder[index] == -1) {
        index++;
        return nullptr;
    }

    TreeNode* root = new TreeNode(preorder[index]);
    index++;
    root->left = buildTree(preorder, index);
    root->right = buildTree(preorder, index);
    return root;
}

// Prune tree: remove subtrees where all nodes are 0
TreeNode* pruneTree(TreeNode* root) {
    if (root == nullptr) {
        return nullptr;
    }

    // Recursively prune left and right subtrees
    root->left = pruneTree(root->left);
    root->right = pruneTree(root->right);

    // If current node is 0 and has no children, prune it
    if (root->val == 0 && root->left == nullptr && root->right == nullptr) {
        delete root;
        return nullptr;
    }

    return root;
}

// Print preorder traversal with null nodes
void printPreorder(TreeNode* root, vector<int>& result) {
    if (root == nullptr) {
        result.push_back(-1);
        return;
    }

    result.push_back(root->val);
    printPreorder(root->left, result);
    printPreorder(root->right, result);
}

// Delete tree to prevent memory leak
void deleteTree(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    vector<int> input;
    int num;

    // Read input until -2
    while (cin >> num) {
        if (num == -2) {
            break;
        }
        input.push_back(num);
    }

    // Build tree
    int index = 0;
    TreeNode* root = buildTree(input, index);

    // Prune tree
    root = pruneTree(root);

    // Get preorder traversal
    vector<int> result;
    printPreorder(root, result);

    // Output result
    for (int i = 0; i < result.size(); i++) {
        if (i > 0) cout << " ";
        cout << result[i];
    }
    cout << endl;

    // Clean up memory
    deleteTree(root);

    return 0;
}
