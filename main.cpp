#include <fstream>
#include <iostream>

int count = 0;

struct treap
{
	treap* left;
	treap* right;
	std::pair<int, int> key_priority;
	treap(const int& x, const int& y, treap* left = nullptr, treap* right = nullptr)
	{
		count++;
		this->left = left;
		this->right = right;
		key_priority = std::make_pair(x, y);
	}

	static std::pair<treap*, treap*> split(treap* treap, const int& key)
	{
		if (treap == nullptr)
			return std::make_pair(nullptr, nullptr);

		if (key > treap->key_priority.first)
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

	static treap* merge(treap* treap1, treap* treap2)
	{
		count++;
		if (treap2 == nullptr)
			return treap1;

		if (treap1 == nullptr)
			return treap2;

		else if (treap1->key_priority.second > treap2->key_priority.second)
		{
			treap1->right = merge(treap1->right, treap2);
			return treap1;
		}

		else
		{
			treap2->left = merge(treap1, treap2->left);
			return treap2;
		}
	}

	static treap* insert(treap* head_treap, treap* elm)
	{
		count++;
		std::pair<::treap*, ::treap*> new_pair_treap = split(head_treap, elm->key_priority.first);
		::treap* new_treap = merge(new_pair_treap.first, elm);
		return merge(new_treap, new_pair_treap.second);
	}
};

int main()
{
	setlocale(LC_ALL, "Russian");
	std::srand(std::time(nullptr));

	int N;
	std::cout << "Введите N: ";
	std::cin >> N;
	
	treap* head_treap = nullptr;
	for (int i = 0; i < N; ++i)
	{
		int x = 1 + rand() % 100;
		int y = 1 + rand() % 100;
		treap* new_elm = new treap(x, y);
		head_treap = treap::insert(head_treap, new_elm);
	}

	std::cout <<
		"Количество операций: " << count << "\n" <<
		"Среднее количество операций на вставку одного элемента: " << count / N << "\n";

	return 0;
}