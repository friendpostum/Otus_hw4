#include <iostream>
#include <vector>
#include <list>
#include <tuple>
#include <limits>


template<typename IntT, typename = std::enable_if_t<std::numeric_limits<IntT>::is_integer>>
void print_ip(IntT v) {
    auto sz = sizeof(v);
    auto p = (uint8_t *) &v + sz - 1;
    for (size_t i = 0; i < sz - 1; ++i, --p) {
        std::cout << (int) *p << '.';
    }
    std::cout << (int) *p << std::endl;
}

template<typename Str>
auto print_ip(const Str &str)-> decltype((void)Str().c_str()) {
    std::cout << str << std::endl;
}

template<typename ContT, typename = std::enable_if_t<std::is_same_v<ContT, std::vector<typename ContT::value_type>> ||
                                                     std::is_same_v<ContT, std::list<typename ContT::value_type>>>>
void print_ip(const ContT &cont) {
    auto it = cont.begin();
    for (int i = 0; i < cont.size() - 1; ++it, ++i) {
        std::cout << *it << '.';
    }
    std::cout << *it << std::endl;
}

template<typename TupleT, std::size_t... Is>
void printTupleImp(const TupleT &tp, std::index_sequence<Is...>) {
    size_t index = 0;
    auto printElem = [&index](const auto &x) {
        if (index++ > 0)
            std::cout << ".";
        std::cout << x;
    };
    (printElem(std::get<Is>(tp)), ...);
}

template<typename TupleT, typename = std::enable_if_t<std::is_same_v<TupleT, std::tuple< std::tuple_element_t<0, TupleT>,
                                                                                         std::tuple_element_t<0, TupleT>,
                                                                                         std::tuple_element_t<0, TupleT>,
                                                                                         std::tuple_element_t<0, TupleT> >>>,
                                                                              std::size_t TupSize = std::tuple_size_v<TupleT>>
void print_ip(const TupleT &tp) {
    printTupleImp(tp, std::make_index_sequence<TupSize>{});
}

int main() {
    print_ip(int8_t{-1});
    print_ip(int16_t{0});
    print_ip(int32_t{2130706433});
    print_ip(int64_t{8875824491850138409});
    print_ip(std::string{"Hello, World!"});
    print_ip(std::vector<int>{100, 200, 300, 400});
    print_ip(std::list<short>{400, 300, 200, 100});
    print_ip(std::make_tuple(123, 456, 789, 0));

    return 0;
}

