#pragma once

#include <cuchar>

#include "VListSetup.hpp"

namespace vlists
{

//Forward Declarations*********************************************************

template<typename> struct null;//null :: [a] -> Bool
template<typename> struct head;//head :: [a] -> a
template<typename> struct last;
template<typename, std::size_t> struct bb;//(!!) :: [a] -> Int -> [a]
template<typename, typename> struct append;//append :: [a] -> [a] -> [a]
template<template<auto> typename, typename> struct map;//map :: (a -> b) -> [a] -> [b]
template<typename> struct tail;//tail :: [a] -> [a]
template<typename> struct init;//init :: [a] -> [a]

//Definitions******************************************************************

template<> struct null<List<>>//null []
{static constexpr auto value = true;};//= true

template<auto X, auto... Xs> struct null<List<X, Xs...>>//null (x: xs)
{static constexpr auto value = false;};//= false

//*****************************************************************************

template<auto X, auto... Xs>
struct head<List<X, Xs...>>//head (x: xs)
{
  static constexpr auto value = X;//= x
};

//*****************************************************************************

template<auto X>
struct last<List<X>>
{
  static constexpr auto value = X;
};

template<auto X, auto... Xs>
struct last<List<X, Xs...>>
{
  static constexpr auto value = last<List<Xs...>>::value;
};

//*****************************************************************************

template<auto X, auto... Xs>
struct bb<List<X, Xs...>, 0>
{
  static constexpr auto value = X;
};

//Think about it: Why is the following wrong?
//Can you make sense of the error message you get when trying it?
//template<auto X, auto... Xs, auto N>
//struct bb<List<X, Xs...>, N + 1>
//{
//  static constexpr auto value = bb<List<Xs...>, N>::value;
//};

template<auto X, auto... Xs, std::size_t N>
struct bb<List<X, Xs...>, N>
{
  static constexpr auto value = bb<List<Xs...>, N - 1>::value;
};

//*****************************************************************************

template<auto X, auto... Xs>
struct tail<List<X, Xs...>> {using type = List<Xs...>;};

//*****************************************************************************

template<auto X>
struct init<List<X>> {using type = List<>;};

template<auto X, auto... Xs>
struct init<List<X, Xs...>>
{
  using type = typename prepend<X, typename init<List<Xs...>>::type>::type;
};

//*****************************************************************************

template<typename YsList>//Is YsList safe enough?
struct append<List<>, YsList> {using type = YsList;};

template<auto X, auto... Xs, typename YsList>
struct append<List<X, Xs...>, YsList>
{
  using type = typename prepend<X, typename append<List<Xs...>, YsList>::type>::type;
};

//The following version is simpler and doesn't require recursion.
//Yet, it doesn't take after it's Haskell predecessor.
//template<auto... Xs, auto... Ys>
//struct append<List<Xs...>, List<Ys...>> {using type = List<Xs..., Ys...>;};

//*****************************************************************************

template<template<auto> typename F>
struct map<F, List<>> {using type = List<>;};

template<template<auto> typename F, auto X, auto... Xs>
struct map<F, List<X, Xs...>>
{
  using type = typename prepend<F<X>::value, typename map<F, List<Xs...>>::type>::type;
};

}//namespace vlists
