#include<stdio.h>
#include<string.h>


//완벽한 WBCS기반 코드?
int WBCS_per()
{
	wchar_t str[] = L"abc";
	int size = sizeof(str);
	int len = wcslen(str);

	printf("배열의 크기: %d \n", size);
	printf("배열의 길이: %d \n", len);

	return 0;
}
//언뜻보기에는 별 문제가 없어보이지만, printf 는 WBCS기반 함수가 아니다!

/*SBCS함수와 WBCS함수
printf		int wprintf
scanf		int wscanf
fgets		wchar_t*getws
fputs		int wputws      */


//완벽한 WBCS기반 코드
int wmain(int argc, wchar_t*argv[]) //메인 함수라 할지라도 w를 붙여줘야함
{
	for (int i = 1 < argc; i++;)
	{
		fputws(argv[i], stdout);
		fputws(L"\n", stdout);
	}
	return 0;
}
