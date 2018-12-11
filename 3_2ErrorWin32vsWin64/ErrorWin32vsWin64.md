## 프로그램 구현 관점에서의 Win32 vs Win64

<br>

### 64비트 기반 프로그래밍
+64비트 기반 프로그래밍
64비트 스스템을 고려한 프로그래밍으로 자료형에 대해서 고려해야 한다.

+LLP64 vs LP64
32비트 시스템과의 호환성을 중시한 모델

운영체제 | 모델 | char | short | int | long | 포인터
----------|------|-----|-------|------|-------|----------
Windows | LLP64 | 1byte | 2byte | 4byte | 4byte | **8byte**
UNIX | LP64 | 1byte | 2byte | 4byte | **8byte** | **8byte**

64비트 기반으로 프로그래밍을 한다?? LLP64, LP64 고려해준다는 것이다.

<br>

### 64비트와 32비트 공존의 문제점

*데이터 손실의 예 (64비트 기반일때)
	
	#include<stdio.h>
	int main()
	{
		int arr[10]={0,};			//포인터는 8byte
		int arrVal = (int)arr;			//데이터 손실이 발생할 수 있는 위치
							  8바이트인 포인터를 4바이트 인티저 자료형으로 
							  캐스팅하는것 이라 문제가 생길수 있다.
		printf("pointer : %d \n", arrVall);
		return 0;
	}

LLP64기반일때 주의점 - 포인터는 4byte?? 아니다, 포인터는 8byte다

<br>

### Windows 스타일 자료형 - polymorphic 자료형

-Polymorphic

	#if defined(_WIN64)							//64비트 기반환경에서 프로그래밍 할시 기본적으로 들어가는 메크로
		typedef __int64 LONG_PTR;
		typedef unsigned __int64 ULONG_PTR
		typedef __int64 INT_PTR
		typedef unsigned __int64 UNIT_PTR		//이때 UNIT_PTR 64비트로
	#else
		typedef long LONG_PTR
		typedef unsigned ULONG_PTR
		typedef int INT_PTR
		typedef unsigned int UNIT_PTR			//이때 UNIT_PTR 32비트로(다형성)
	#endlf

>PTR은 포인터 타입이 아니고 **포연터 연산을 위한 (polymorphic) 자료형**이다.<br>
다형성(polymorphic) - 하나의 사물이 2개 이상의 특성을 보이는것 

<br>

-코드로 알아보는 문제발생예제

	UINT CalDistance(UINT a, UINT b)
	{
		return a-b;
	}

	int_tmain()
	{
		INT val1 = 10;
		INT val2 = 20;
		
		_tprintf(_T("Position %d, %d \n"),
		(UNIT)&val1, (UNIT)&val2);
		_tprintf(_T("ditance : %d \n"), 
		CalDistance((UNIT)&val1, (UNIT)&val2);		// 쉽게말해 주소간의 거리를 출력하는 코드이다.

		return 0;
	}

1. 여기서 UNIT는 4바이트기 때문에 32비트 기반 에서는 아무런 문제가 없다.
2. 하지만 64비트 기반에서는 문제가 발생될 활률이 농후하다. (주소값이 32비트 범위에서 동일하지 않은한)
3. 어떻게 해결할까?
4. 주소값 포인터 연산을 위한 polymorphic 자료형을 이용(메크로)한다!

	#if defined(_WIN64)
		typedef unsined __int64 UNIT_PTR;
	#else
		typedef unsined int UNIT_PTR;
	#endlif

5. 포인터 연산의 경우에 이러한 오류가 나타날수는 가능성이 높다.

<br>

### 오류 확인

1. 오류를 해결하기 위해, 오류가 왜 발생했는지 이유를 먼저 찾아야 한다.
2. 윈도우즈 시스템에서는 전연적으로 선언된 메모리에 오류의 원인들을 저장해 둔다.
3. 이 전역공간에 접근을 하는 함수가 GetLastError 함수이다.
4. ex) ERROR_ARITHMETIC_OVERFLOW - Arithmetic result exceeded 32bits

<br>

	int_tmain()
	{
		HANDLE hFile=
		CreatFile(						       // Windows system 함수,
			_T("ABC.DAT"), GENERIC_READ, FILE_SHARE_READ,	
			NULL< OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL,
			NULL);					// 쉽게 설명해 없는 파일을 읽기 전용으로 연다는 뜻의 코드다.
                
		
		if (hFile == INVALID_HANDLE_VALUE)	        //**에러가 발생했는지의 여부만**에 판단하는 분기이다.
		{
			_tprintf(_T("erro codes : %d \n"), GetLastError();     //출력결과 error code: 2
			return 0;
		}
		
	}

>GetLastError()함수를 사용할때 주의점<br>
오류가 발생된 직후에 호출해야된다. 만약 오류가 발생된 부분을 지나쳐 정상적인 부분이
있는 부분 뒤에 호출하면, 에러 코드는 출력되지않는다. (마지막에 받은 에러에 대한것 이므로)
