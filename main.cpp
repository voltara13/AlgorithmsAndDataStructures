#include <fstream>
#include <iostream>
#include <utility>
#include <bitset>
#include <string>

#define HASH2

struct hash_row
{
    std::string product_name;
    double product_cost;
    hash_row* next = nullptr;
	hash_row(std::string product_name, const double& product_cost) :
        product_name(std::move(product_name)), product_cost(product_cost) {}
};

struct hash_table
{
    static inline int count_row;
    static inline int count_collision;
    hash_row* row = nullptr;
};

void add_row(hash_table* hash_table, hash_row* hash_row, const int& hash)
{
    if (hash_table[hash].row == nullptr)
        hash_table[hash].row = hash_row;
    else
    {
    	hash_table::count_collision++;
        ::hash_row* hash_row_temp = hash_table[hash].row;
        while (hash_row_temp->next)
            hash_row_temp = hash_row_temp->next;
        hash_row_temp->next = hash_row;
    }
}
#ifdef HASH1
int get_hash(const std::string& str)
{
    unsigned __int64 hash = 0;
    for (const auto& element : str)
        hash += element;
    return hash % hash_table::count_row;
}
#endif

#ifdef HASH2
int get_hash(const std::string& str)
{
    unsigned __int64 hash = 0;
    int base = 1;
    std::string hash_str;
    for (const auto& element : str)
        hash_str += std::bitset<8>(element).to_string();
    for (int i = hash_str.length() - 1; i >= 0; i--) 
    {
        if (hash_str[i] == '1')
            hash += base;
        base *= 2;
    }
    return hash % hash_table::count_row;
}
#endif

void read(hash_table** hash_table, const std::string& file_name)
{
    if (std::ifstream file(file_name); file.is_open())
    {
        hash_table::count_collision = 0;
        hash_table::count_row = std::count(std::istreambuf_iterator<char>(file),
            std::istreambuf_iterator<char>(), '\n');
        *hash_table = new ::hash_table[hash_table::count_row];
        file.clear();
        file.seekg(std::ios::beg);
        double product_cost;
        std::string product_name;
        while (file >> product_name >> product_cost)
            add_row(
                *hash_table,
                new hash_row(product_name, product_cost),
                get_hash(product_name));
        file.close();
    }
    else
		std::cout << "\nFailed open file " << file_name;
}

int main()
{
    std::ofstream file("out_file.csv");
	for (int i = 0; i < 10; ++i)
	{
        hash_table* hash_table = nullptr;
        read(&hash_table, "price_list" + std::to_string(i) + ".txt");
        file << hash_table::count_row << ";" << hash_table::count_collision << "\n";
        delete hash_table;
	}
    file.close();
    system("out_file.csv");
    return 0;
}