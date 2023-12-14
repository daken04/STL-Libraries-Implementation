#include <iostream>
#include <vector>
using namespace std;

size_t custom_hash(const float &key)
{
    int int_value = *reinterpret_cast<const int *>(&key);
    return static_cast<size_t>(int_value);
}

size_t custom_hash(const double &key)
{
    long long int_value = *reinterpret_cast<const long long *>(&key);
    return static_cast<size_t>(int_value);
}

size_t custom_hash(const char &key)
{
    return static_cast<size_t>(key);
}

size_t custom_hash(const string &key)
{
    size_t hash = 0;
    for (char c : key)
    {
        hash = (hash * 43) + static_cast<size_t>(c);
    }
    return hash;
}

template <typename T>
size_t custom_hash(const T &key)
{
    return static_cast<size_t>(key);
}

template <typename T1, typename T2>
class unordered_map
{
private:
    struct Node
    {
        T1 key;
        T2 value;
        Node *next;
    };

    Node *arr[10000] = {}; // Initialize all elements to NULL
    int map_size = 0;

    // Custom hash function specialization
    size_t hash(const T1 &key) const
    {
        return custom_hash(key) % 10000;
    }

public:
    bool insert(const T1 &key, const T2 &value)
    {
        size_t index = hash(key);

        Node *n = new Node();
        n->key = key;
        n->value = value;
        n->next = nullptr;

        Node *t = arr[index];

        if (t == nullptr)
        {
            arr[index] = n;
        }
        else
        {
            if (t->key == key)
            {
                delete n;
                return false;
            }

            while (t->next != nullptr)
            {
                t = t->next;
                if (t->key == key)
                {
                    delete n;
                    return false;
                }
            }
            t->next = n;
        }

        map_size++;
        return true;
    }

    bool erase(const T1 &key)
    {
        size_t index = hash(key);

        Node *t = arr[index];
        Node *prev = nullptr;

        while (t != nullptr)
        {
            if (t->key == key)
            {
                if (prev == nullptr)
                {
                    arr[index] = t->next;
                }
                else
                {
                    prev->next = t->next;
                }
                delete t;
                map_size--;
                return true;
            }
            prev = t;
            t = t->next;
        }

        return false;
    }

    bool contains(const T1 &key) const
    {
        size_t index = hash(key);

        Node *t = arr[index];

        while (t != nullptr)
        {
            if (t->key == key)
            {
                return true;
            }
            t = t->next;
        }

        return false;
    }

    T2 &operator[](const T1 &key)
    {
        size_t index = hash(key);

        Node *t = arr[index];

        while (t != nullptr)
        {
            if (t->key == key)
            {
                return t->value;
            }
            t = t->next;
        }

        // If key is not found, insert with a default value and return it
        T2 default_value = T2();
        insert(key, default_value);
        return arr[index]->value;
    }

    vector<T1> keys() const
    {
        vector<T1> key_vector;

        for (size_t i = 0; i < 10000; ++i)
        {
            Node *t = arr[i];
            while (t != nullptr)
            {
                key_vector.push_back(t->key);
                t = t->next;
            }
        }

        return key_vector;
    }

    int size() const
    {
        return map_size;
    }

    bool empty() const
    {
        return size() == 0;
    }

    void clear()
    {
        for (size_t i = 0; i < 10000; ++i)
        {
            Node *t = arr[i];
            while (t != nullptr)
            {
                Node *temp = t;
                t = t->next;
                delete temp;
            }
            arr[i] = nullptr;
        }

        map_size = 0;
    }
};

int main()
{
    unordered_map<double, int> my_map; // here

    int q;
    cin >> q;

    while (q--)
    {
        int type;
        cin >> type;

        if (type == 1)
        {
            double key; // here
            int value;  // here
            cin >> key >> value;
            cout << boolalpha << my_map.insert(key, value) << endl;
        }
        else if (type == 2)
        {
            double key; // here
            cin >> key;
            cout << boolalpha << my_map.erase(key) << endl;
        }
        else if (type == 3)
        {
            double key; // here
            cin >> key;
            cout << boolalpha << my_map.contains(key) << endl;
        }
        else if (type == 4)
        {
            double key; // here
            cin >> key;
            cout << my_map[key] << endl;
        }
        else if (type == 5)
        {
            my_map.clear();
        }
        else if (type == 6)
        {
            cout << my_map.size() << endl;
        }
        else if (type == 7)
        {
            cout << my_map.empty() << endl;
        }
        else if (type == 8)
        {
            if (my_map.keys().size() == 0)
            {
                cout << endl;
            }

            for (auto z : my_map.keys())
            {
                cout << z << endl;
            }
        }
    }

    return 0;
}
