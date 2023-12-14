#include <iostream>
#include <vector>
using namespace std;

template <typename T1, typename T2>
class ordered_map
{
private:
    struct Node
    {
        T1 key;
        T2 value;
        Node *left;
        Node *right;
        int h;
    };

    Node *root;
    int size_;

    Node *rightRotate(Node *node2)
    {
        Node *node1 = node2->left;
        Node *temp = node1->right;

        node1->right = node2;
        node2->left = temp;

        node2->h = 1 + max((node2->left ? node2->left->h : 0), (node2->right ? node2->right->h : 0));
        node1->h = 1 + max((node1->left ? node1->left->h : 0), (node1->right ? node1->right->h : 0));

        return node1;
    }

    Node *leftRotate(Node *node1)
    {
        Node *node2 = node1->right;
        Node *temp = node2->left;

        node2->left = node1;
        node1->right = temp;

        node1->h = 1 + max((node1->left ? node1->left->h : 0), (node1->right ? node1->right->h : 0));
        node2->h = 1 + max((node2->left ? node2->left->h : 0), (node2->right ? node2->right->h : 0));

        return node2;
    }

    Node *balance(Node *node)
    {
        if (node == NULL)
            return node;

        int balance = getBalance(node);

        if (balance > 1)
        {
            if (getBalance(node->left) >= 0)
            {
                return rightRotate(node);
            }
            else
            {
                node->left = leftRotate(node->left);
                return rightRotate(node);
            }
        }

        if (balance < -1)
        {
            if (getBalance(node->right) <= 0)
            {
                return leftRotate(node);
            }
            else
            {
                node->right = rightRotate(node->right);
                return leftRotate(node);
            }
        }

        return node;
    }

    int getBalance(Node *node)
    {
        if (node == NULL)
            return 0;
        return (node->left ? node->left->h : 0) - (node->right ? node->right->h : 0);
    }

    Node *insert(Node *node, T1 key, T2 value)
    {
        if (node == NULL)
        {
            Node *newNode = new Node;
            newNode->key = key;
            newNode->value = value;
            newNode->left = NULL;
            newNode->right = NULL;
            newNode->h = 1;
            size_++;
            return newNode;
        }

        if (key < node->key)
        {
            node->left = insert(node->left, key, value);
        }
        else if (key > node->key)
        {
            node->right = insert(node->right, key, value);
        }
        else
        {
            node->value = value;
            return node;
        }

        node->h = 1 + max((node->left ? node->left->h : 0), (node->right ? node->right->h : 0));

        return balance(node);
    }

    Node *findMin(Node *node)
    {
        while (node->left != NULL)
        {
            node = node->left;
        }
        return node;
    }

    Node *remove(Node *node, T1 key)
    {
        if (node == NULL)
            return node;

        if (key < node->key)
        {
            node->left = remove(node->left, key);
        }
        else if (key > node->key)
        {
            node->right = remove(node->right, key);
        }
        else
        {
            if (node->left == NULL || node->right == NULL)
            {
                Node *temp = node->left ? node->left : node->right;

                // No child case
                if (temp == NULL)
                {
                    temp = node;
                    node = NULL;
                }
                else
                { // One child case
                    *node = *temp;
                }

                delete temp;
                size_--; // Decrement size here
            }
            else
            {
                // Node with two children, get the inorder successor (smallest in the right subtree)
                Node *temp = findMin(node->right);

                // Copy the inorder successor's data to this node
                node->key = temp->key;
                node->value = temp->value;

                // Delete the inorder successor
                node->right = remove(node->right, temp->key);
            }
        }

        if (node == NULL)
            return node;

        node->h = 1 + max((node->left ? node->left->h : 0), (node->right ? node->right->h : 0));

        return balance(node);
    }

    bool contains(Node *node, T1 key)
    {
        if (node == NULL)
            return false;

        if (key < node->key)
        {
            return contains(node->left, key);
        }
        else if (key > node->key)
        {
            return contains(node->right, key);
        }
        else
        {
            return true;
        }
    }

    T2 &get(Node *node, T1 key)
    {
        if (node == NULL)
        {
            root = insert(root, key, T2());
            return find(root, key)->value;
        }

        if (key < node->key)
        {
            return get(node->left, key);
        }
        else if (key > node->key)
        {
            return get(node->right, key);
        }
        else
        {
            return node->value;
        }
    }

    Node *find(Node *node, T1 key)
    {
        if (node == NULL)
            return NULL;

        if (key < node->key)
        {
            return find(node->left, key);
        }
        else if (key > node->key)
        {
            return find(node->right, key);
        }
        else
        {
            return node;
        }
    }

    void clear(Node *node)
    {
        if (size_ > 0)
        {
            size_ = 0;
        }

        if (node == NULL)
        {
            return;
        }

        clear(node->left);
        clear(node->right);

        delete node;
    }

    void collectKeys(Node *node, vector<T1> &keys)
    {
        if (node == NULL)
            return;

        collectKeys(node->left, keys);
        keys.push_back(node->key);
        collectKeys(node->right, keys);
    }

public:
    ordered_map() : root(NULL), size_(0) {}

    ~ordered_map()
    {
        clear(root);
    }

    bool empty()
    {
        return root == NULL;
    }

    int size()
    {
        return size_;
    }

    bool contains(T1 key)
    {
        return contains(root, key);
    }

    bool insert(T1 key, T2 value)
    {
        int oldSize = size_;
        root = insert(root, key, value);
        return size_ > oldSize;
    }

    bool erase(T1 key)
    {
        int oldSize = size_;
        root = remove(root, key);
        return size_ < oldSize;
    }

    T2 &operator[](T1 key)
    {
        return get(root, key);
    }

    void clear()
    {
        clear(root);
        root = NULL;
    }

    vector<T1> keys()
    {
        vector<T1> result;
        if (!empty())
        {
            collectKeys(root, result);
        }
        return result;
    }

    pair<bool, T1> lower_bound(T1 key)
    {
        Node *current = root;
        Node *lbNode = NULL;

        while (current != NULL)
        {
            if (key < current->key)
            {
                lbNode = current;
                current = current->left;
            }
            else if (key > current->key)
            {
                current = current->right;
            }
            else
            {
                // If the exact key is found, return it as the lower bound
                return make_pair(true, current->key);
            }
        }

        if (lbNode)
        {
            return make_pair(true, lbNode->key);
        }
        else
        {

            return make_pair(false, T1());
        }
    }

    pair<bool, T1> upper_bound(T1 key)
    {
        Node *current = root;
        Node *ubNode = NULL;

        while (current != NULL)
        {
            if (key < current->key)
            {
                ubNode = current;
                current = current->left;
            }
            else if (key >= current->key)
            {
                current = current->right;
            }
        }

        if (ubNode)
        {
            return make_pair(true, ubNode->key);
        }
        else
        {
            return make_pair(false, T1());
        }
    }
};

int main()
{
    ordered_map<int, string> omap; // here

    while (1)
    {
        int input;
        cin >> input;

        if (input == 1)
        {
            cout << boolalpha << omap.empty()<<endl;
        }
        else if (input == 2)
        {
            cout << omap.size()<<endl;
        }
        else if (input == 3)
        {
            int key; // here;
            cin >> key;
            cout << boolalpha << omap.contains(key)<<endl;
        }
        else if (input == 4)
        {
            int key;
            string value;
            cin >> key;
            cin >> value;
            cout << boolalpha << omap.insert(key, value)<<endl;
        }
        else if (input == 5)
        {
            int key;
            cin >> key;
            cout << boolalpha << omap.erase(key)<<endl;
        }
        else if (input == 6)
        {
            int key;
            cin >> key;
            cout << omap[key]<<endl;
        }
        else if (input == 7)
        {
            omap.clear();
        }
        else if (input == 8)
        {
            if(omap.keys().size()==0)
            {
                cout<<endl;
            }

            for (auto z : omap.keys())
            {
                cout << z << endl;
            }
        }
        else if (input == 9)
        {
            int key;
            cin >> key;
            pair<bool, int> result = omap.lower_bound(key);
            if (result.first)
            {
                cout << "true" <<endl<< result.second << endl;
            }
            else
            {
                cout << "false" << endl;
            }
        }
        else if (input == 10)
        {
            int key;
            cin >> key;
            pair<bool, int> result = omap.upper_bound(key);
            if (result.first)
            {
                cout << "true" <<endl<< result.second << endl;
            }
            else
            {
                cout << "false" << endl;
            }
        }
        else if (input == 0)
        {
            break;
        }
    }

    return 0;
}
