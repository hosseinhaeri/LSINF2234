#pragma once

namespace vlists
{

//Main Declarations************************************************************

template<auto...> struct List {};

//Forward Declarations*********************************************************

template<auto, typename> struct prepend;
template<typename, auto> struct postpend;

//Definitions******************************************************************

template<auto X, auto... Xs>
struct prepend<X, List<Xs...>> {using type = List<X, Xs...>;};

template<auto X, auto... Xs>
struct postpend<List<Xs...>, X> {using type = List<Xs..., X>;};

}//namespace vlists
