/* 
 *https://habr.com/ru/post/150732/ 
 */
#include <cassert>
#include <cmath>
#include <stdint.h>
#include <type_traits>
#include <iostream>

namespace avl_tree {

template <typename K, typename std::enable_if<std::is_arithmetic<K>::value>::type* = nullptr>
struct Node
{
	K key;
	uint8_t h;
	Node<K>* left;
	Node<K>* right;

    Node(K k) noexcept { key = k; left = right = nullptr; h = 1; }

	static uint8_t height(Node<K>* p) {	return p ? p->h : 0; }

	static int8_t bfactor(Node<K>* p) {	return height(p->right) - height(p->left); }

	static Node<K>* insert_new_node(Node<K>* p, K k)
	{
		if (!p) return new Node<K>(k);

		if (k < p->key)
			p->left = insert_new_node(p->left, k);
		else
			p->right = insert_new_node(p->right, k);
		
		return balance(p);
	}

	static Node<K>* rotate_right(Node<K>* p)
	{
		Node<K>* q = p->left;
		p->left = q->right;
		q->right = p;
		p->fix_height();
		q->fix_height();
		return q;
	}

	static Node<K>* rotate_left(Node<K>* q)
	{
		Node<K>* p = q->right;
		q->right = p->left;
		p->left = q;
		q->fix_height();
		p->fix_height();
		return p;
	}

	static Node<K>* balance(Node<K>* p)
	{
		p->fix_height();

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

	void fix_height()
	{
		uint8_t h_l = height(this->left);
		uint8_t h_r = height(this->right);
		this->h = (h_l > h_r ? h_l : h_r) + 1;
	}
};

template <typename K, typename std::enable_if<std::is_arithmetic<K>::value>::type* = nullptr>
class Tree
{
private:
    Node<K>* m_root;
	uint32_t m_size;
    
public:
    Tree() { m_root = nullptr; m_size = 0; };
    ~Tree() {};

    uint8_t height() const { return Node<K>::height(m_root); }

	uint32_t size() const { return m_size; }

    void insert(K k) { 
		m_root = Node<K>::insert_new_node(m_root, k);
		m_size++;
	}
};

}

bool test_avl_tree()
{
    int test_values[] {
        2, 3, 10, 1, -12, -5, 0, 24, 13, 9, 
        15, 25, 5, 20, 27, 18, 6, -1, 8, 11,
        31, 16, 14, 7, -2, -4, -11, -9, -13, 4,
        28, -72, 21, 17, 12, -15, 52, 42,
        29, -35, 45, 19, -8, 22, 33, 50
    };

    avl_tree::Tree<int> tree;

    for (auto value : test_values)
    {
        tree.insert(value);

		float n = static_cast<float>(tree.size());
		float h = static_cast<float>(tree.height());
		assert(std::log2f(n + 1.f) <= h);
		assert(h <= 1.44f * std::log2f(n + 2.f) - 0.328f);
    }

	std::cout << "Size: " << tree.size() << std::endl;
    std::cout << "Height: " << static_cast<int>(tree.height()) << std::endl;
    return true;
}
