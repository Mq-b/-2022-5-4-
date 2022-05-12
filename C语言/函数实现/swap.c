void my_memcpy(void* Str1, void* Str2, size_t Size) {
	unsigned char* str1_ = (unsigned char*)Str1;
	unsigned char* str2_ = (unsigned char*)Str2;
	while (Size)
	{
		*str1_++ = *str2_++;
		--Size;
	}
}
void swap(void* a, void* b, int size)
{
	unsigned char* str1_ = (unsigned char*)a;
	unsigned char* str2_ = (unsigned char*)b;
	unsigned char* temp=malloc(size);
	my_memcpy(temp, str1_, size);
	my_memcpy(str1_, str2_, size);
	my_memcpy(str2_, temp, size);
	free(temp);
}
//依靠之前写的my_memcpy进行swap
