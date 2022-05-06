#include<iostream>
template<typename...Args>
decltype(auto) print(Args&&...args) {
    ((std::cout << args << ' '), ...);
}
int main() {
    print(1, 2, 3, 4, 5, 6, "离谱");
}
