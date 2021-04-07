#include <iostream>

#define EX1

#ifdef EX1
constexpr int size = 10;

void linear_structures()
{
	struct static_structure
	{

		int array[size]{};

		static_structure()
		{
			for (int& i : array)
				i = -1;
		}

		int get_free_index(const int& index)
		{
			int return_index = -1;

			for (int i = 0; i < size; ++i)
				if (array[i] == -1 && (return_index == -1 || abs(index - i) < abs(index - return_index)))
					return_index = i;

			return return_index;
		}

		void add_elm(const int& value, const int& position)
		{
			if (check(position))
			{
				const int index = position - 1;

				if (array[index] == -1)
					array[index] = value;

				else
				{
					const int free_index = get_free_index(index);

					if (free_index == -1)
						std::cout << "Нет свободного места\n";

					else
					{
						if (free_index < index)
						{
							for (int i = free_index; i < index; ++i)
								array[i] = array[i + 1];

							array[index] = value;
						}

						else
						{
							for (int i = free_index; i > index; --i)
								array[i] = array[i - 1];

							array[index] = value;
						}
					}
				}

				for (int i = 0; i < size - 1; ++i)
					if (array[i] == -1 && array[i + 1] != -1)
					{
						for (int j = i; j < size - 1; ++j)
							array[j] = array[j + 1];
						i = -1;
					}

			}
		}

		void delete_elm(const int& position)
		{
			if (check(position))
			{
				const int index = position - 1;

				if (array[index] != -1)
					array[index] = -1;

				else
					std::cout << "В указанной позиции нет элементов\n";
			}
		}

		void print()
		{
			for (int& i : array)
				if (i != -1)
					std::cout << i << std::endl;
		}

		static bool check(const int& position)
		{
			if (position < 1 || position > size)
			{
				std::cout << "Позиция за пределами массива\n";
				return false;
			}
			return true;
		}
	};

	static_structure structureArray;

	structureArray.add_elm(3, 3);
	structureArray.add_elm(2, 2);
	structureArray.add_elm(6, 3);
	structureArray.add_elm(8, 4);
	structureArray.add_elm(81, 5);
	structureArray.add_elm(10, 6);
	structureArray.add_elm(33, 7);
	std::cout << "Массив:\n";
	structureArray.print();

	structureArray.add_elm(100, 6);
	std::cout << "Массив после добавления элемента на шестую позицию:\n";
	structureArray.print();

	structureArray.delete_elm(5);
	std::cout << "Массив после удаления элемента на пятой позиции:\n";
	structureArray.print();
}

#endif
#ifdef EX2

void linear_structures()
{
	struct dynamic_structure
	{
		int value;
		dynamic_structure* next;

		explicit dynamic_structure(const int value = 0, dynamic_structure* next = nullptr)
			: value(value), next(next) {}

		static dynamic_structure* add_elm(const int& value, dynamic_structure* head)
		{
			dynamic_structure* new_elm = new dynamic_structure(value), * ptr = head;
			if (head == nullptr) return new_elm;
			while (ptr->next)
				ptr = ptr->next;
			ptr->next = new_elm;
			return head;
		}

		static dynamic_structure* delete_elm(dynamic_structure* head)
		{
			if (head == nullptr) return head;
			dynamic_structure* ptr = head;
			while (ptr->next->next)
				ptr = ptr->next;
			ptr->next = nullptr;
			return head;
		}

		static dynamic_structure* create(const int& size)
		{
			std::cout << "Введите элементы" << std::endl;
			int value;
			dynamic_structure* head = nullptr;
			for (int i = 0; i < size; i++)
			{
				std::cin >> value;
				head = add_elm(value, head);
			}
			return head;
		}

		static void print(dynamic_structure* head)
		{
			dynamic_structure* ptr = head;
			while (ptr != nullptr)
			{
				std::cout << ptr->value << std::endl;
				ptr = ptr->next;
			}
		}
	};

	int size;
	std::cout << "Введите размер списка: ";
	std::cin >> size;

	dynamic_structure* head = dynamic_structure::create(size);
	std::cout << "Список:\n";
	dynamic_structure::print(head);

	int value;
	std::cout << "Введите добавляемый элемент: ";
	std::cin >> value;
	dynamic_structure::add_elm(value, head);
	std::cout << "После добавления:\n";
	dynamic_structure::print(head);

	dynamic_structure::delete_elm(head);
	std::cout << "После удаления:\n";
	dynamic_structure::print(head);
}

#endif

int main()
{
	setlocale(LC_ALL, "Russian");
	linear_structures();
	return 0;
}