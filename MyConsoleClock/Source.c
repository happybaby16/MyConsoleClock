#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <Windows.h>


int H, tempH;
int M, tempM;
int S, tempS;

int mode;


VOID WINAPI ThreadClockManager(VOID);

VOID WINAPI ConsoleClock(VOID);

VOID WINAPI ConsoleSecond(VOID);


HANDLE hF[2];

int main()
{
	system("chcp 1251");
	mode = 0; //0-����� �����, 1-����� �����������, 2-����� �������
	H = 13;
	M = 9;
	S = 57;


	hF[0] = CreateThread(NULL, 0, ConsoleClock, NULL, 0, 0);
	hF[1] = CreateThread(NULL, 0, ThreadClockManager, NULL, 0, 0);
	WaitForMultipleObjects(2, hF, TRUE, INFINITE);


	return 0;
}

VOID WINAPI ThreadClockManager(VOID)
{
	while (TRUE)
	{
		if (kbhit())
		{
			int i = getch();
			switch (i)
			{
			case 49:
				printf("\n�����...");
				SuspendThread(hF[0]);
				break;
			case 50:
				printf("\n�����...");
				ResumeThread(hF[0]);
				break;
			case 51:
				system("cls");
				SuspendThread(hF[0]);
				while (TRUE)
				{
					printf("\n������� ���-�� �����: ");
					scanf("%d", &H);
					if (H >= 0 && H <= 23)
					{
						break;
					}
					else
					{
						printf("�������� ������ �������. ��������� ����!!");
					}
				}

				while (TRUE)
				{
					printf("\n������� ���-�� �����: ");
					scanf("%d", &M);
					if (M >= 0 && M <= 59)
					{
						break;
					}
					else
					{
						printf("�������� ������ �������. ��������� ����!!");
					}
				}

				while (TRUE)
				{
					printf("\n������� ���-�� ������: ");
					scanf("%d", &S);
					if (S >= 0 && S <= 59)
					{
						break;
					}
					else
					{
						printf("�������� ������ �������. ��������� ����!!");
					}
				}
				ResumeThread(hF[0]);
				break;
			case 52:
				tempH = H;
				tempM = M;
				tempS = S;
				H = 0;
				M = 0;
				S = 0;
				mode = 1;
				SuspendThread(hF[0]);
				system("cls");
				printf("��� ������ ������ ����������� ������� 2\n");
				break;

			case 53:
				system("cls");
				tempH = H;
				tempM = M;
				tempS = S;
				SuspendThread(hF[0]);
				while (TRUE)
				{
					printf("\n������� ���-�� �����: ");
					scanf("%d", &H);
					if (H >= 0 && H <= 23)
					{
						break;
					}
					else
					{
						printf("�������� ������ �������. ��������� ����!!");
					}
				}

				while (TRUE)
				{
					printf("\n������� ���-�� �����: ");
					scanf("%d", &M);
					if (M >= 0 && M <= 59)
					{
						break;
					}
					else
					{
						printf("�������� ������ �������. ��������� ����!!");
					}
				}

				while (TRUE)
				{
					printf("\n������� ���-�� ������: ");
					scanf("%d", &S);
					if (S >= 0 && S <= 59)
					{
						break;
					}
					else
					{
						printf("�������� ������ �������. ��������� ����!!");
					}
				}
				mode = 2;
				system("cls");
				printf("��� ������ ������ ������� ������� 2\n");
				break;


			case 48:
				system("cls");
				H = tempH;
				M = tempM;
				S = tempS;
				tempH = 0;
				tempM = 0;
				tempS = 0;
				mode = 0;
				ResumeThread(hF[0]);
			default:
				break;


			}
		}
	}
}



VOID WINAPI ConsoleClock(VOID)
{
	while (TRUE)
	{
		if (mode != 2)
		{
			S++;
			if (S > 59)
			{
				S = 0;
				M++;
			}
			if (M > 59)
			{
				M = 0;
				H++;
			}
			if (H > 23)
			{
				H = 0;
			}
			Sleep(1000);
			system("cls");
		}
		else
		{
			S--;
			if (S < 0)
			{
				S = 59;
				M--;
			}
			if (M < 0)
			{
				M = 59;
				H--;
			}
			if (H < 0)
			{
				H = 0;
			}
			Sleep(1000);
			system("cls");
			if (H == 0 && M == 0 && S == 0)
			{
				mode = 0;
				printf("������ ����������. ��� ������ ������� 0");
				SuspendThread(hF[0]);
			}
		}
		
		
		char strH[2], strM[2], strS[2];
		if (H < 10)
		{
			sprintf(strH, "0%i", H);
		}
		else
		{
			sprintf(strH, "%i", H);
		}


		if (M < 10)
		{
			sprintf(strM, "0%i", M);
		}
		else
		{
			sprintf(strM, "%i", M);
		}


		if (S < 10)
		{
			sprintf(strS, "0%i", S);
		}
		else
		{
			sprintf(strS, "%i", S);
		}

		if (mode == 0)
		{
			printf("%s:%s:%s\n", strH, strM, strS);
			printf("\n��� ������? \n1 - ����� �����\n2 - ����� ���� � �����\n3 - ���������� �����\n4 - ����������\n5 - ������\n�������� �����:");
		}
		if (mode == 1)
		{
			printf("����� �����������. ��� ������ ������� 0\n");
			printf("%s:%s:%s\n", strH, strM, strS);
		}
		if (mode == 2)
		{
			printf("����� �������. ��� ������ ������� 0\n");
			printf("%s:%s:%s\n", strH, strM, strS);
		}
		
	}
}


