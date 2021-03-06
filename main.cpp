#include <iostream>

#include "VList.hpp"
#include "VListUtils.hpp"

#include "TListSetup.hpp"
#include "TList.hpp"

using std::cout;
using std::endl;

template<auto X>
struct times2 {static constexpr auto value = X * 2;};

int main()
{
  using L1 = vlists::List<1, 2, 3, 4>;
  using L2 = vlists::List<>;

  using L3 = typename vlists::prepend<0, L1>::type;
  using L4 = typename vlists::postpend<L3, 5>::type;
  using L5 = typename vlists::append<L1, typename vlists::append<L2, L3>::type>::type;
  using L6 = typename vlists::map<times2, L5>::type;

  cout << "head<" << L4() << ">::value = " << vlists::head<L4>::value << endl
       << "last<" << L3() << ">::value = " << vlists::last<L3>::value << endl
       << "vlists::bb<" << L5() << ", 3>::value = " << vlists::bb<L5, 3>::value << endl
       << "typename vlists::map<(\\x -> x * 2)," << L5() << ">::type = " << L6() << endl;

  return 0;
}
