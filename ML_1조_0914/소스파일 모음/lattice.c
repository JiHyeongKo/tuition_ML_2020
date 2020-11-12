// ���� ���� ����̴ϴ�.

#include <stdio.h>
#include <string.h>
#include "main.h"

int makeGraphic(void)
{
	FILE* yFile;
	fopen_s(&yFile, ".\\output_data.txt", "r");

	char str_buf[100];
	int output = 0;
	int cnt = 0;
	int coor = 0;
	int flag = 0;
	double x1 = 0;
	double x2 = 0;
	double x1_buffer = 0xff;
	double x2_buffer = 0xff;

	memset(str_buf, 0, sizeof(str_buf));

	if (yFile)
	{
		fgets(str_buf, sizeof(str_buf), yFile);	// �ʹ� line ó��

		while (!feof(yFile))
		{
			fgets(str_buf, sizeof(str_buf), yFile);

			if (feof(yFile))
				break;	// �ߺ����� ����

			sscanf_s(str_buf, "%d\t%lf\t%lf", &output, &x1, &x2);

			if (output == 1)
			{
				printf("%s ", DOT);

				if (x1_buffer == 0xff && x2_buffer == 0xff)
				{
					x1_buffer = x1;
					x2_buffer = x2;
				}
			}

			else
				printf("%s ", SPACE);

			cnt++;
			if (cnt % 21 == 0)
			{
				coorBuffer.X1[coor] = x1_buffer;	// �ش� row�� y�� 1�� �Ǵ� ��ǥ�� ������ ��ǥ�� 0xff�� ����.
				coorBuffer.X2[coor] = x2_buffer;
				coor++;

				x1_buffer = 0xFF;
				x2_buffer = 0xFF;
				printf("\n\n");
			}
		}
		fclose(yFile);
	}

	//printf("cnt : %d\n", cnt);
	return cnt;

	// y������ ���� ���� �����
}

int classification(Coordinator* buffer)
{
	int i = 0;
	double X1_buffer[2] = { 0, 0 };
	double X2_buffer[2] = { 0, 0 };

	
	if (buffer->X1[i] == 0xff && buffer->X2[i] == 0xff)
	{
		while(buffer->X1[i] == 0xff && buffer->X2[i] == 0xff)
			i++;
	}

	{
		X1_buffer[0] = buffer->X1[i];
		X2_buffer[0] = buffer->X2[i];

		i++;

		X1_buffer[1] = buffer->X1[i];
		X2_buffer[1] = buffer->X2[i];

		double m = (X2_buffer[1] - X2_buffer[0]) / (X1_buffer[1] - X1_buffer[0]);
		double n = X2_buffer[1] - X2_buffer[0];

		return line_data(m, n);
	}
}