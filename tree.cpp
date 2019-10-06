#include <iostream>
#include <memory>
#include <vector>
#include <iterator>
#include <algorithm>
using namespace std;

struct node 
{
    int info;
    std::shared_ptr<node> left, right;
};

struct tree
{
    shared_ptr<node> root;
};

void add_to_tree(tree& tr, int info)
{
    node n;
    n.info = info;
    n.left = nullptr;
    n.right = nullptr;

    if (tr.root == nullptr)
    {
        tr.root = make_shared<node>(n);
        return;
    }
    shared_ptr<node> top = tr.root;
    shared_ptr<node> temp = nullptr, prev = nullptr;;
    while (1)
    {
        while (top != nullptr && top->info > info)
        {
            temp = top;
            top = top->left;
        }
        if (top == nullptr)
        {
            top = make_shared<node>(n);
            
            if (temp != nullptr)
            {
                temp->left = top;
            }
            else
            {
                prev->right = top;
            }
            break;
        }
        else
        {
            prev = top;
            top = top->right;
            temp = nullptr;
        }
    }
}

void print(shared_ptr<node> n)
{
    if (n != nullptr)
    {
        print(n->left);
        cout << n->info << "\t";
        print(n->right);
    }
}

ostream& operator<<(ostream& out, const shared_ptr<node>& n)
{
    out << n->info <<"\t";
    return out;
}

void print_all_paths(const tree& tr)
{
    shared_ptr<node> iter = tr.root;
    shared_ptr<node> temp;
    vector<shared_ptr<node>> path;
    while (1)
    {
        while (iter != nullptr)
        {
            temp = iter;
            path.push_back(temp);
            iter = iter->left;
        }

        if (iter == nullptr)
        {
            if (path.back()->right != nullptr)
            {
                iter = path.back()->right;
            }
            else
            {
                copy(path.begin(), path.end(), ostream_iterator<shared_ptr<node>>(cout, " "));
                cout << endl;
                shared_ptr<node> n1 = path.back();
                if (path.empty())
                {
                    break;
                }
                path.pop_back();
                shared_ptr<node> n2 = path.back();

                while (n2->right == n1 || n2->right == nullptr && n2->left == n1)
                {
                    n1 = n2;
                    path.pop_back();
                    if (path.empty())
                    {
                        break;
                    }
                    n2 = path.back();
                }
            }
        }
        if (path.empty())
        {
            break;
        }
    }
}

int main(int, char**) {
    tree tr;
    tr.root = nullptr;
    auto add = [&tr](const int& n) {add_to_tree(tr, n);};
    vector<int> nodes = {25, 20, 10, 15, 36, 32, 34, 17, 12, 13, 22, 21, 29, 27, 28, 31, 33, 35, 7};

    for_each(nodes.begin(), nodes.end(), add);
    print(tr.root);
    cout << endl;
    print_all_paths(tr);
}
