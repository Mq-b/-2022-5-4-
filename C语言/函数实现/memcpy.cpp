#include<stdio.h>
#include<stdlib.h>
void my_memcpy(void* Str1, void* Str2, size_t Size) {
    unsigned char* str1_ = (unsigned char*)Str1;
    unsigned char* str2_ = (unsigned char*)(Str2);
    while(Size)
    {
        *str1_++ = *str2_++;
        --Size;
    }
}
int main() {
    char ch[] = "66";
    char ch2[3];
    my_memcpy(ch2, ch, 3);
    printf("%s\n", ch2);

    int num[5] = { 1,2,3,4,5 };
    int num2[5];
    my_memcpy(num2, num, 20);
    for (int i = 0; i < 5; i++)
        printf("%d ", num2[i]);
        
    system("pause");
}
