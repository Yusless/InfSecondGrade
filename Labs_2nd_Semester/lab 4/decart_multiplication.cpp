#include <iostream>
#include <array>
#include <tuple>
#include <type_traits>
#include <utility>

template<size_t Index, size_t Size>
struct ValidateIndex {
    static_assert(Index < Size, "ERROR: Index out of bounds!");
    static constexpr bool value = true;
};

template<typename T, size_t N>
constexpr size_t array_size(const std::array<T, N>&) {
    return N;
}

template<size_t... Indices, typename... Arrays>
constexpr auto cartesian_element(const std::tuple<Arrays...>& arrays) {
    static_assert(sizeof...(Indices) == sizeof...(Arrays),
                  "ERROR: Number of indices must match number of arrays!");
    
    constexpr std::array<size_t, sizeof...(Indices)> idx_array = {Indices...};
    [&]<size_t... Is>(std::index_sequence<Is...>) {
        ((ValidateIndex<idx_array[Is], array_size(std::get<Is>(arrays))>(), ...));
    }(std::index_sequence_for<Arrays...>{});

    return [&]<size_t... Is>(std::index_sequence<Is...>) {
        return std::make_tuple(std::get<idx_array[Is]>(std::get<Is>(arrays))...);
    }(std::index_sequence_for<Arrays...>{});
}

template<typename... Args>
void print_tuple(const std::tuple<Args...>& t) {
    std::cout << "(";
    std::apply([](const auto&... args) {
        size_t i = 0;
        ((std::cout << (i++ ? ", " : "") << args), ...);
    }, t);
    std::cout << ")";
}

int main() {
    constexpr std::array<int, 3> arr1 = {3, 13, 42};
    constexpr std::array<double, 2> arr2 = {3.14, 2.71};
    constexpr std::array<char, 4> arr3 = {'c', 'd', 'f', 'l'};
    constexpr std::array<const char*, 2> arr4 = {"Divine", "Chaos"};
    
    constexpr auto arrays = std::make_tuple(arr1, arr2, arr3, arr4);
    
    constexpr auto elem1 = cartesian_element<0, 0, 0, 0>(arrays);
    std::cout << "  cartesian_element<0,0,0,0>(arrays) -> ";
    print_tuple(elem1);
    std::cout << std::endl;
    
    constexpr auto elem2 = cartesian_element<2, 1, 3, 0>(arrays);
    std::cout << "  cartesian_element<2,1,3,0>(arrays) -> ";
    print_tuple(elem2);
    std::cout << std::endl;
    
    constexpr auto elem3 = cartesian_element<1, 0, 2, 1>(arrays);
    std::cout << "  cartesian_element<1,0,2,1>(arrays) -> ";
    print_tuple(elem3);
    std::cout << std::endl;
    
    std::cout << std::endl; 

    return 0;
}