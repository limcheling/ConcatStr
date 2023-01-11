#include <vector>
#include <unordered_map>
#include <map>

#include <iostream>
#include <string>

#include <numeric>

template<typename T>
struct is_vector : std::false_type {};

template<typename T>
struct is_vector<std::vector<T>> : std::true_type {};

template <typename Container>
std::string concat_string(Container& con, std::string delimiter = ", ")
{
    if constexpr (is_vector<Container>::value) {
        return std::accumulate(std::next(con.begin()), con.end(), *con.begin(),
            [&delimiter](std::string s, std::string next) { return std::move(s) + delimiter + std::move(next); });
    }
    else
    {
        return std::accumulate(std::next(con.begin()), con.end(), con.begin()->first,
            [&delimiter](std::string s, auto& it_ele) { return s + delimiter + std::move(it_ele.first); });

    }
}

int main()
{
    std::vector<std::string> vec_a{"Michael", "Steven", "Thomas"};
    std::cout << concat_string(vec_a) <<'\n';

    std::unordered_map<std::string, int> um_a{ {"Thomas", 18} , {"Michael", 27}, {"Steven", 25}, {"Julian", 13}};
    std::cout << concat_string(um_a) << '\n';

    std::map<std::string, int> um_b{ {"Thomas", 18} , {"Michael", 27}, {"Steven", 25}, {"Julian", 13} };
    std::cout << concat_string(um_a) << '\n';
    std::cout << concat_string(um_a, " -> ") << '\n';

    std::cin.get();
    return 0;
}