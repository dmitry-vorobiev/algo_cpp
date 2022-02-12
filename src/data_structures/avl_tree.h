/*
 *https://habr.com/ru/post/150732/
 */
#include <cassert>
#include <cmath>
#include <stdint.h>
#include <type_traits>
#include <iostream>
#include <vector>

namespace avl_tree {

template <typename K, typename std::enable_if<std::is_arithmetic<K>::value>::type* = nullptr>
struct Node
{
	K key;
	uint8_t h;
	Node<K>* left;
	Node<K>* right;

	Node(K k) noexcept
	{
		key = k;
		left = right = nullptr;
		h = 1;
	}

	~Node()
	{
		if (this->left)	delete left;
		if (this->right) delete right;
	}

	static uint8_t height(const Node<K>* const p) { return p ? p->h : 0; }

	static int8_t bfactor(const Node<K>* const p) { return height(p->right) - height(p->left); }

	static Node<K>* insert(Node<K>* p, const K k)
	{
		if (!p)
			return new Node<K>(k);

		if (k < p->key)
			p->left = insert(p->left, k);
		else
			p->right = insert(p->right, k);

		return balance(p);
	}

	static Node<K>* remove(Node<K>* p, const K k)
	{
		if (!p)	return nullptr;

		if (k < p->key)
			p->left = remove(p->left, k);
		else if (k > p->key)
			p->right = remove(p->right, k);
		else // key is found
		{
			Node<K>* q = p->left;
			Node<K>* r = p->right;

			p->left = nullptr;
			p->right = nullptr;
			delete p;

			if (!r) return q;
			Node<K>* m = const_cast<Node<K>*>(r->find_min());
			m->right = remove_min(r);
			m->left = q;

			return balance(m);
		}
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

	static Node<K>* remove_min(Node<K>* p)
	{
		if (!p->left)
			return p->right;

		p->left = remove_min(p->left);
		return balance(p);
	}

	const Node<K>* find_min() const
	{
		const Node<K>* min_el = this;

		while (min_el->left)
		{
			min_el = min_el->left;
		}
		return min_el;
	}

	const Node<K>* find_max() const
	{
		const Node<K>* max_el = this;

		while (max_el->right)
		{
			max_el = max_el->right;
		}
		return max_el;
	}

	void fix_height()
	{
		this->h = std::max(height(this->left), height(this->right)) + 1;
	}
};

template <typename K, typename std::enable_if<std::is_arithmetic<K>::value>::type* = nullptr>
class Tree
{
private:
	Node<K>* m_root;
	uint32_t m_size;

public:
	Tree() noexcept
	{
		m_root = nullptr;
		m_size = 0;
	};
	~Tree() { delete m_root; };

	uint8_t height() const { return Node<K>::height(m_root); }

	uint32_t size() const { return m_size; }

	void insert(const K k)
	{
		m_root = Node<K>::insert(m_root, k);
		m_size++;
	}

	void remove(const K k)
	{
		if (has_key(k))
		{
			m_root = Node<K>::remove(m_root, k);
			m_size--;
		}
	}

	bool has_key(const K k) const
	{
		const Node<K>* curr = this->m_root;

		while (curr != nullptr)
		{
			if (curr->key == k)
				return true;
			curr = k < curr->key ? curr->left : curr->right;
		}
		return false;
	}

	std::vector<K> traverse_ascend() const
	{
		std::vector<K> result;
		result.reserve(m_size);

		std::vector<const Node<K>*> stack;
		const Node<K>* curr = this->m_root;

		while (curr != nullptr || stack.size() > 0)
		{
			if (curr == nullptr)
			{
				curr = stack.back();
				stack.pop_back();
				result.push_back(curr->key);
				curr = curr->right;
			}
			else
			{
				stack.push_back(curr);
				curr = curr->left;
			}
		}
		return result;
	}

	K min() const
	{
		return m_root ? m_root->find_min()->key : 0;
	}

	K max() const
	{
		return m_root ? m_root->find_max()->key : 0;
	}
};

}

bool test_avl_tree()
{
	int test_values[]{
		2, 3, 10, 1, -12, -5, 0, 24, 13, 9,
		15, 25, 5, 20, 27, 18, 6, -1, 8, 11,
		31, 16, 14, 7, -2, -4, -11, -9, -13, 4,
		28, -72, 21, 17, 12, -15, 52, 42,
		29, -35, 45, 19, -8, 22, 33, 50};

	avl_tree::Tree<int> tree;

	for (auto &&v : test_values)
	{
		tree.insert(v);

		float n = static_cast<float>(tree.size());
		float h = static_cast<float>(tree.height());
		assert(std::log2f(n + 1.f) <= h);
		assert(h <= 1.44f * std::log2f(n + 2.f) - 0.328f);
	}

	for (auto &&v : test_values)
	{
		assert(tree.has_key(v));
	}

	int missing_keys[]{ -100, 90, 51, 23, -38 };

	for (auto &&v : missing_keys)
	{
		assert(!tree.has_key(v));
	}

	std::vector<int> sorted = tree.traverse_ascend();
	int prev_key = -9000;

	for (auto &&v : sorted)
	{
		assert(v >= prev_key);
		prev_key = v;
	}
	
	std::cout << "Size: " << tree.size() << std::endl;
	std::cout << "Height: " << static_cast<int>(tree.height()) << std::endl;
	std::cout << "Min: " << tree.min() << std::endl;
	std::cout << "Max: " << tree.max() << std::endl;

	for (auto &&value : test_values)
	{
		tree.remove(value);

		float n = static_cast<float>(tree.size());
		float h = static_cast<float>(tree.height());
		assert(std::log2f(n + 1.f) <= h);
		assert(h <= 1.44f * std::log2f(n + 2.f) - 0.328f);
	}
	return true;
}
