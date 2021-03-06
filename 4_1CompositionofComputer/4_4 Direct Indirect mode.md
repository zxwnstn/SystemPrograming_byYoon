## 4-4강 다이렉트 모드와 인다이렉트 모드
Direct addressing mode 와 Indirect addressing mode.

<br>

### 필요성 대두
만약에 명령어에 허용범위 이상 크기의 주소값이나 숫자를 담아야 한다면.. 어떻게 해야할까?

<br>

### Direct 모드의 문제점
	int a = 10;		//0x0010번지
	int b = 20;		//0x0100번지???
	int c = 0;		//0x0020번지
	c = a + b;<br>
	LOAD r1, 0x0010
	LOAD r2, 0x0100 	//허용범위 이상의 숫자??
>참고로 0x0000은 16진수로서 0x0100은 256번지라는 뜻으로 명령어에 담을수 없는 숫자이다.<br>
(명령어에 담을수 있는 주소값의 최대값은 2의 8승 -1 즉 255)<br>

<br>

16트 시스템으로 구성한 하나의 레지스터(또는 명령어)에 아무리 효율적으로 비트를 다룬다고 해도, 256이라는 정보를 <br>
담기는 무리가 있어보인다.. 그렇다면 어떻게 처리할수있을까??<br>

<br>

### Direct 모드와 Indirect모드
Direct 모드 - 가져오려는 주소값이 명령어에 표현 가능범위이므로 바로 그 주소를 사용하는 것.<br>
Indirect 모드 - 주소값 표현범위를 초과한 경우, 허용범위내 주소값을 가진 메모리에 그 주소값을 할당하고,<br>
다시, 그 주소값이 담긴 메모리 주소를 레지스터로 넘긴다.<br>
여기서 명령어에는 가져온 주소가 참조하려는 주소값임을 반드시 표기해 주어야 하는데,<br>
여기서 우리가 앞에서 남겨뒀던, 명령어 맨앞의 두개의 비트 활용하면 되는 것이다.<br>
예컨데 맨앞 2비트가 11이면 그 주소의 정보를 바로 가져오는게 되는 것이고(Direct), <br>
10이면 그 주소의 정보를 참조하여 그 정보가 나타내는 주소의 메모리 정보를 가져오게 된다는 소리다(Indirect).<br>
쉽게말해 Indirect모드는 한다리 건너 정보를 가져온다는 소리다.<br>

<br>

### 문제 해결
	LOAD r1, 0x0010		//10번지에 있는 정보를 레지스터 r1으로 가저온다.
	
	MUL r0, 4, 4		//중간에 낀 이 명령어 들은 무엇일까..?
	MUL r2, 4, 4		//바로 256이라는 숫자를 만들기 위한 명령어들이다!
	MUL r3, r0, r2		//이 숫자를 레지스터 r3에 저장한다.
				//(r1을 안쓰는 이유는 거기에 이미 20이라는 정보가 들어있기 때문)
	STORE r3, 0x0030	//r3의 정보를 메모리 30번지로 보낸다
	LOAD r2, [0x0030]	//[메모리 30번지의 주소를]를 레지스터 r2로 가져온다.
				/메모리 30번지의 정보는 256번지 라는 주소 정보이고, 이정보로 다시 그 주소의
				//정보를 레지스터 r2로 로드한다.
	ADD r3, r1, r2		//r1과 r2에 저장된 숫자를 더해 r3로 보낸다.
