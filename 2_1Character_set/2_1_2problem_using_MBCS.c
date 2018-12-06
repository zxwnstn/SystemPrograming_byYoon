// ★MBCS를 썻을때 어떠한 문제가 발생될수 있는지 코드로 알아보기

#include<stdio.h>
#include<string.h>
//문제점 1
int Problem1()
{
	char str[] = "ABC한글";
	int size = sizeof(str);
	int len = strlen(str);
	
	printf("배열의 크기: %d \n", size);
	//배열의 크기는 "ABC"의 3과 "한글"의 4 그리고 null문자 1의 값으로 8이 나온다

	printf("배열의 길이: %d \n", len);
	//배열의 길이는 "ABC"는 각각 1의 길이를 가지지만 "한글"의 글자는 각각 2의 길이를 가져
	//7이라는 숫자가 출력되게 된다.

	return 0;

}

//문제점2
int Problem2()
{
	char str[] = "한글입니다";
		int i;

	for (i = 0; i < 5; i++);
	fputc(str[i], stdout);				//한글은 한글자에 2byte이므로 한글 까지만 나옴

	fputs("\n", stdout);

	for (i = 0; i < 10; i++);
	fputc(str[i], stdout);				//한글입니다 를 출력하려면 i를 10까지 지정해주어야함

	fputs("\n", stdout);
	return 0;							//실행결과는 한글, 한글입니다
}



// ★WBCS 기반의 프로그래밍 문법

int WBCS_practice()
{
	wchar_t str[] = L"ABC"; // 스트링 변수 선언을 wchar_t로 하고 스트링을 L""의 형태로 쓰면된다.

	return 0;
}

/*SBCS를 WBCS기반 함수로!
strlen		size_twcslen
strcpy		wchar_t*wcscpy
strncpy		wchar_t*wcsncpy
strcat		wchar_t*wcscat
strncat		wchar_t*wcsncat
strcmp		wchar_t*wcscmp
strncmp		wchar_t*wcsncmp   */
