/*
struct Node {
    int data;
    Node *left;
    Node *right;

    Node(int val) {
        data = val;
        left = right = NULL;
    }
}; */

class Solution {
    public: vector < int > inOrder(Node * root) {
        vector < int > result;
        inOrderTraversal(root, result);
        return result;
    }
    private: void inOrderTraversal(Node * root, vector <int> & result) {
        if (!root) return;
        inOrderTraversal(root -> left, result);
        result.push_back(root -> data);
        inOrderTraversal(root -> right, result);

    }


};