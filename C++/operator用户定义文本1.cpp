#include<iostream>

auto operator "" _i(char i)
{
    std::cout<<i<<std::endl;
    return static_cast<int>(i);
}
auto operator "" _i(size_t i)
{
    std::cout<<i<<std::endl;
    return static_cast<int>(i);
}
void operator "" _dump_raw(const char* lit)
{
    printf("operator \"\" _dump_raw(const char*)        : ===>%s<===\n",   lit);
};
void operator "" _dump_raw(const long double lit)
{
    printf("operator \"\" _dump_raw(const long double)        : ===>%Lg<===\n",   lit);
};
int main(){
    'A'_i;
    65_i;

    42_dump_raw;            
    3.1415926_dump_raw;
    3.14e+25_dump_raw;
    system("pause");
    //24,25,26行这三个都能匹配const char*，但long double更加匹配，所以在这里后面两个匹配的 const long double
}
