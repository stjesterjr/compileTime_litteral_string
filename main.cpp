#ifndef CT_STRING
#define CT_STRING

#include <cstddef>
#include <stddef.h>
#include <utility>
#include <iostream>

template<size_t N>
struct S{
    const char data[N];
public:
    template<size_t... Is, size_t... Js>
    constexpr S(const char* lhs, const char* rhs, std::index_sequence<Is...>, std::index_sequence<Js...>)
    : data{(lhs[Is])..., (rhs[Js])... }
    {}
    
private:
    template<size_t... Is>
    constexpr S(const char (&arg)[N], std::index_sequence<Is...>)
    : data{arg[Is]...}
    {}
public:
    constexpr S(const char (&arg)[N])
    : S(arg, std::make_index_sequence<N>{})
    {}

    using Litteral = const char*;
    operator Litteral() const {
        return &data[0];
    } 
};

template<size_t N>
S(const char(&)[N]) -> S<N>;

template<size_t A, size_t B, size_t Res = A+B-1>
constexpr auto operator+(const S<A>& lhs, const S<B>& rhs){
    return S<Res>(lhs.data, rhs.data, std::make_index_sequence<A-1>{}, std::make_index_sequence<B>{});
}

template<S str>
constexpr auto operator""_ct()
{
    return str;
}

constexpr auto s0 = "ooo"_ct;

constexpr auto s1 = S("abc");
using s1_t = decltype(s1.data);
constexpr auto s2 = S("def");
using s2_t = decltype(s2.data);
constexpr auto s3 = s1 + s2;
using s3_t = decltype(s3.data);

constexpr auto AB = "A"_ct + "B"_ct;

void use_string(const char* txt){
    std::cout << txt;
}

#endif
