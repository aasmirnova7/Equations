#include <stdio.h>
#include <conio.h>

int main()
{
	char x, z; //байты
	short int y, v, v_c, v_as; //слова
	int i;
	unsigned char test1;

	printf("Homework A2. Variant 21\n");
	//выбот теста
	printf("1 - Test 1; \n2 - Test 2;\n");
	scanf_s("%d", &i);

	//Test 1 or 2
	switch (i) {
	case 1:
		printf("1 Test!\n");
		x = -0x4;
		y = -0x3;
		z = 0x2;
		v = 0x12;
		break;
	case 2:
		printf("2 Test!\n");
		x = 0x7F; //127
		y = -0x15AC; //-5548
		z = 0x5F; //95
		v = -0xA; //-10
		break;
	default:
		break;
	}
	//Подсчёт значения в С
	v_c = (((3 + x)*z - 7 * y) / (y + 4)) - 1;

	//Ассемблерная вставка
	__asm
	{
		//Числитель
		mov al, x;
		cbw;
		add AX, 3; //AX -> (3+x) - слово
		mov  BX, AX; // BX -> (3+x) 
		mov al, z;
		cbw;
		imul BX; // DX:AX -> (3+x)z - двойное слово
		mov BX, AX; // BX -> AX
		mov CX, DX // CX -> DX
		mov al, -7;
		cbw;
		imul y; // DX:AX -> -7y - двойное слово 

		add AX, BX;
		adc DX, CX;
		//числитель лежит в  DX:AX

		//Знаменатель
		mov BX, y;
		add BX, 4; // BX-> (y+4) - слово
		
		//Деление
		idiv BX;
		//Вычитание из дроби
		dec AX;
		//Получаем ответ
		mov v_as, AX;
	}
	printf("Answer from C: \ndec = %d \nhex = %hx", v_c, v_c);
	printf("\nAnswer from assembler: \ndec = %d \nhex =  %hx", v_as, v_as);
	printf("\nAnswer:\ndec =  %d \nhex =  %hx", v, v);

	_getch();
	return 0;
}