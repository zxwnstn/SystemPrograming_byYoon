## MBCS와 WBCS 동시지원

<br>

### 개요
아직까지 모든 시스템이 유니코드를 지원하지 않는다. 왜냐하면 개발및 소프트웨어를 돌리는 환경이 통일 되지 않았기 때문이다.
문제는 이러한 연유로 하나의 프로그램인데도 불구하고 MBCS기반 프로그램과 WBCS 기반프로그램, 
2개의 프로그램을 따로 만들어 관리해야 하는 상황이나, 배포상의 문제가 발생할 수도 있다는 점이다.<br>
이에 두개의 문자셋을 동시에 지원하는 프로그램을 만들면 된다는 좋은 해결책이 있다.
windows는 이미 이렇게 사용할수 있는 여러 메크로와 템플릿을 지원하며,
궁극적으로 더 좋은 개발자가 되기 위해서 MBCS와 WBCS를 동시에 지원하는 프로그래밍을 해야한다.

<br>

### windows 정의 자료형
	#include<windows.h)

	typedef	char			CHAR;
	typedef	wchar			WCHAR;

	#define CONST			const

	typedef	CHAR *			LPSTR;
	typedef	CONST CHAR *	LPCSTR;
	
	typedef	WCHAR *			LPWSTR;
	typedef	CONST WCHAR *	LPCWSTR;
회사, 팀별 더작게는 프로젝트별로 네이밍을 달리 하는 경우가 있기 때문에 이것이 최선이라 할 수는 없다.
네이밍은 프로젝트의 성격과 타입에 따라 달라질수 있는 부분이기 때문이다.

<br>

때문에 이런것을 쓸수 있다라는 활용가능성이 중요한 것이지, 이것의 사용을 강요하는 것은 아니다.

<br>

### MBCS와 WBCS 동시지원 메크로

조건부 컴파일을 하면된다.

###### 단순선언의 경우
	#ifdef UNICODE
		typedef	WCHAR		TCHAR;
		typedef	LPWSTR		LPTSTR;
		typedef LPCWSTR		LPCTSTR;
	#else
		typedef CHAR		TCHAR
		typedef	LPSTR		LPTSR;
		typedef LPCSTR		LPCTSTR;
	#endif

>코드를 해석해 보자면
메크로 UNICODE가 정의 되어있다면
TCHAR -> WCHAR -> wchar_t
메크로 UNICODE가 정의되지 않았다면
TCHAR -> CHAR -> char
이 된다는 뜻이다.

<br>

###### L""의 형태로 문자열을 선언할때

	#ifdef _UNICODE
		#define			__T(x)	L##x	// __T("ABC") -> L"ABC"
	#else
		#define			__T(x)	x
	#endif
		
	#define _T(x)		__T(x)
	#define _TEXT(x)	__T(x)			// 두개가 같다는 소리..

>코드를 해석해 보자면
메크로 _UNICODE가 정의되 있다면
_T("ABC") -> __T("ABC") -> L"ABC"
메크로 _UNICODE가 정의되 있지 않다면
_T("ABC") -> __T("ABC") -> "ABC"
이 된다는 뜻이다.

### MBCS와 WBCS 동시지원 함수

	#ifdef _UNICODE
		#define				_tmain		wmain
		#define				_tcslen		wcslen
		#define				_tprintf	wprintf
		#define				_tscanf		wscanf
	#else
		#define				_tmain		main
		#define				_tcslen		strlen
		#define				_tprintf	printf
		#define				_tscanf		scanf
	#endif
