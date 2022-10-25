#include<Windows.h>
#include<iostream>

int main() {
	const char* str = "66666好啊好好";
	HANDLE hFile = CreateFile("1.txt", GENERIC_READ | GENERIC_WRITE, NULL, NULL, OPEN_ALWAYS, NULL, NULL);
	DWORD count = 0;
	if (INVALID_HANDLE_VALUE == hFile) {
		fputs("CreateFile failed!", stderr);
		exit(1);
	}
	BOOL ret = WriteFile(hFile, str , strlen(str), &count, NULL);
	if (false == ret) {
		exit(1);
	}

	printf("%d\n", count);

	CloseHandle(hFile);
}