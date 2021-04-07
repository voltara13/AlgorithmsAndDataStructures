#include <iostream>

struct treap
{
	treap* left;
	treap* right;
	std::pair<int, int> key_priority;
	treap(const int& x, const int& y, treap* left = nullptr, treap* right = nullptr)
	{
		this->left = left;
		this->right = right;
		key_priority = std::make_pair(x, y);
	}

	std::pair<treap*, treap*> split(treap* treap, const int& key)
	{
		if (treap == nullptr)
			return std::make_pair(nullptr, nullptr);

		else if (key > treap->key_priority.first)
		{
			std::pair<::treap*, ::treap*> pair_treap = split(treap->right, key);
			treap->right = pair_treap.first;
			return std::make_pair(treap, pair_treap.second);
		}

		else
		{
			std::pair<::treap*, ::treap*> pair_treap = split(treap->left, key);
			treap->left = pair_treap.second;
			return std::make_pair(pair_treap.first, treap);
		}		
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	
	return 0;
}