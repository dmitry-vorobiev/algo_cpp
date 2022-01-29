/* 
 *https://habr.com/ru/post/150732/ 
 */
#include <cassert>
#include <stdint.h>
#include <type_traits>
#include <iostream>

template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
struct Node
{
	T key;
	uint8_t height;
	Node<T>* left;
	Node<T>* right;

	Node(T k) : 
        key(k)
    {
        left = nullptr;
        right = nullptr; 
        height = 1;
    }
};

template <typename T>
uint8_t height(Node<T>* p)
{
	return p ? p->height : 0;
}

template <typename T>
void fix_height(Node<T>* p)
{
	auto h_l = height(p->left);
	auto h_r = height(p->right);
	p->height = (h_l > h_r ? h_l : h_r) + 1;
}

template <typename T>
Node<T>* rotate_right(Node<T>* p)
{
	Node<T>* q = p->left;
	p->left = q->right;
	q->right = p;
	fix_height(p);
	fix_height(q);
	return q;
}

template <typename T>
Node<T>* rotate_left(Node<T>* q)
{
	Node<T>* p = q->right;
	q->right = p->left;
	p->left = q;
	fix_height(q);
	fix_height(p);
	return p;
}

template <typename T>
int8_t bfactor(Node<T>* p)
{
	return height(p->right) - height(p->left);
}

template <typename T>
Node<T>* balance(Node<T>* p)
{
	fix_height(p);

    auto bf_p = bfactor(p);
    assert(-3 < bf_p && bf_p < 3);

	if (bf_p == 2)
	{
		if (bfactor(p->right) < 0)
        {
            p->right = rotate_right(p->right);
        } 
		return rotate_left(p);
	}
	if (bf_p == -2)
	{
		if (bfactor(p->left) > 0)
        {
			p->left = rotate_left(p->left);
        }
		return rotate_right(p);
	}
	return p;
}

template <typename T>
Node<T>* insert_new_node(Node<T>* p, T k)
{
	if (!p) 
        return new Node<T>(k);

	if (k < p->key)
		p->left = insert_new_node(p->left, k);
	else
		p->right = insert_new_node(p->right, k);
    
	return balance(p);
}

template <typename T, typename std::enable_if<std::is_arithmetic<T>::value>::type* = nullptr>
class AVLTree
{
private:
    Node<T>* m_root;
    
public:
    AVLTree() { m_root = nullptr; };
    ~AVLTree() {};

    uint8_t height() { return m_root->height; }

    void insert(T k) { m_root = insert_new_node<T>(m_root, k); }
};

bool test_avl_tree()
{
    int test_values[] {
        2, 3, 10, 1, -12, -5, 0, 24, 13, 9, 
        15, 25, 5, 20, 27, 18, 6, -1, 8, 11,
        31, 16, 14, 7, -2, -4, -11, -9, -13, 4,
        28, -72, 21, 17, 12, -15, 52, 42,
        29, -35, 45, 19, -8, 22, 33, 50
    };

    AVLTree<int> tree;

    for (auto value : test_values)
    {
        tree.insert(value);
    }

    std::cout << "Height: " << static_cast<int>(tree.height()) << std::endl;
    return true;
}
