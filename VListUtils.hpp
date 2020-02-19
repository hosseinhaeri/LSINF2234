#pragma once

#include <iostream>
#include <string>

#include "VListSetup.hpp"
#include "VList.hpp"

namespace vlists
{

template<typename> struct convert_init;
template<typename> struct convert_last;

template<auto... Xs> struct convert_init<List<Xs...>>
{
  static std::string to_string()
  {
    if constexpr (sizeof... (Xs) > 0)
      return std::to_string(head<List<Xs...>>::value) +
             ", " +
             convert_init<typename tail<List<Xs...>>::type>::to_string();
    else
      return "";
  }
};

template<auto... Xs> struct convert_last<List<Xs...>>
{
  static std::string to_string()
  {
    if constexpr (sizeof... (Xs) > 0)
      return std::to_string(last<List<Xs...>>::value);
    else
      return "";
  }
};

template<auto... Xs>
std::string to_string(List<Xs...> l)
{
  return "[" +
         convert_init<typename init<List<Xs...>>::type>::to_string() +
         convert_last<List<Xs...>>::to_string() +
         "]";
}

}//namespace vlists

namespace std
{

template<auto... Xs>
std::ostream& operator << (std::ostream& out, vlists::List<Xs...> l)
{
  out << to_string(l);
  return out;
}

}//namespace std
