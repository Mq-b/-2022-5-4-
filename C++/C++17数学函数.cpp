#include <numeric>

int i{42};
long l{30};

auto x{std::gcd(i, l)};     // x是long 6 最大公约数
auto y{std::lcm(i, l)};     // y是long 210 最小公倍数