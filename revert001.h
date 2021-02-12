//Revert variadic template arguments (example: print in reversed order)
//source_file.cpp -std=c++1z -o a.exe /EHsc /MD /I C:\boost_1_60_0 /link /LIBPATH:C:\boost_1_60_0\stage\lib

#include <iostream>
#include <tuple>

/******** print all elements of a tuple in ascending order 
 * live example: 
 * http://coliru.stacked-crooked.com/a/5d86aa176f657702
 * but _o_n_l_y_  C++17 and up                                          !!!!!!!
**************/


/**************
 * revert variadic template arguments
 * see: https://stackoverflow.com/questions/15904288/how-to-reverse-the-order-of-arguments-of-a-variadic-template-function
 * 
 *********************/

// forward decl
template<class ...Tn>
struct revert;

template<class TupType, size_t... I>
void print(const TupType& _tup, std::index_sequence<I...>)
{
    std::cout << "(";
    (..., (std::cout << (I == 0? "" : ", ") << std::get<I>(_tup)));
    std::cout << ")\n";
}


template<class... T>
void print(const std::tuple<T...>& _tup)
{
    print(_tup, std::make_index_sequence<sizeof...(T)>());
}


/** my function now: (replace with your specific function) */
template<class... Args>
void ascendingPrint(Args... args)
{
    std::tuple<Args...> tup{args...};
    print(tup);
}


// recursion anchor
template<>
struct revert<>
{
    template<class ...Un>
    static void apply(Un const&... un)
    {
        ascendingPrint(un...);
    }
};

// recursion
template<class T, class ...Tn>
struct revert<T, Tn...> 
{
    template<class ...Un>
    static void apply(T const& t, Tn const&... tn, Un const&... un)
    {
        // bubble 1st parameter backwards
        revert<Tn...>::apply(tn..., t, un...);
    }
};

// using recursive function
template<class A, class ...An>
void descendingPrint(A const& a, An const&... an)
{
    revert<An...>::apply(an..., a);
}

