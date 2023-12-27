/*
	c������ϰ �����˸����� 2022��9��27�����
											������ϣ
*/
#include<easyx.h>
#include<stdio.h>
#include <windows.h>
#pragma  comment (lib,"winmm.lib")
const int WIDTH = 400;   // ���
const int HEIGHT = 760;  // �߶�
const int INTERVAL = 48; // ���
//  ����ͼƬ
IMAGE img_bk;
IMAGE img_item[3];
void loadImg()
{	
	loadimage(&img_bk, "images/jk.png", WIDTH, HEIGHT);
	loadimage(img_item + 0, "images/j1.png", 48, 48);
	loadimage(img_item + 1, "images/j2.png", 48, 48);
	loadimage(img_item + 2, "images/j3.png", 48, 48);
}


int main()
{
	initgraph(WIDTH, HEIGHT);
	loadImg();
	//��������
	mciSendString(_T("open micc/jkun.mp3"),0,0,0);
	mciSendString(_T("play micc/jkun.mp3"),0,0,0);
	//����ͷ����
	//��ʼ��
	int map[3][3] = { 0 };
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			map[r][c] = r + 1;  //������ÿ��Ԫ�ظ�ֵ{111 222 333}
			
		}
	}
	//�������� 
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			int r1 = rand() % 3;
			int c1 = rand() % 3;
			int temp = map[r1][c1];
			map[r1][c1] = map[r][c];
			map[r][c] = temp;
		}
	}
	//�����λ��
	int offsetX = (WIDTH - (2 * INTERVAL + 3 * 48)) / 2;
	int offsetY= (HEIGHT - (2 * INTERVAL + 3 * 48)) / 2;

	int store[7] = { 0 };
	while (true)
	{
		BeginBatchDraw();
		// ���Ƶ�ͼ  ������ͼ
		putimage(0, 0, &img_bk);
		// ����  ��Ⱦ
		char s[] = "�����˸�����v1.1      ��������ϣ";
		setbkmode(TRANSPARENT);
		settextcolor(BLUE);
		outtextxy(WIDTH-250,HEIGHT-18, s);
		for (int r = 0; r < 3; r++)
		{
			for (int c = 0; c < 3; c++)
			{
				if (map[r][c])
					// ��ʼ��Ⱦ             x  , y   ͼƬ
					putimage(offsetX + c * (48 + INTERVAL), offsetY + r * (48 + INTERVAL),
						img_item + (map[r][c] - 1));
			}
		}
		for (int i = 0; i < 7; i++)
		{
			if (store[i])
			{
				putimage((i * 50) + 26, 620, img_item + (store[i] - 1));
			}

		}
		EndBatchDraw();
		//������      
		ExMessage  msg = { 0 };
		// �������Ժ�  �Ƿ�����Ϣ  ��Ϣ��     VM_LBUTTONDOWN ���
		if (peekmessage(&msg) && msg.message == WM_LBUTTONDOWN)
		{
			for (int r = 0; r < 3; r++) {

				for (int c = 0; c < 3; c++)
				{
					// �������
					int  x = offsetX + c * (48 + INTERVAL);
					int y = offsetY + r * (48 + INTERVAL);
					// �ж�һ������Ƿ�����ͼƬ
					if (msg.x > x && msg.x < x + 48 && msg.y>y && msg.y < y + 48)
					{
						// ��� ͼƬ��Ӧ�����λ�� 
						int col = (msg.x - offsetX) / (48 + INTERVAL);
						int row = (msg.y - offsetY) / (48 + INTERVAL);

						// �������ͼƬ��Ⱦ�����������

						for (int i = 0; i < 7; i++)
						{
							
							if (store[i] == 0) 
							{
								
								store[i] = map[row][col];
								break;
							}
						}
						// ��¼����
						int cnt = 0;
						for (int i = 0; i < 7; i++)
						{
							if (store[i] == map[row][col]) 
							{
								cnt++;
							}
						}
						// ����ﵽ��3 
						if (cnt == 3)
						{
							for (int i = 0; i < 7; i++)
							{
								if (store[i] == map[row][col])
								{
									store[i] = 0;
								}
							}
						}
						map[row][col] = 0;
					}

				}

			}
		}

	}


	//����β����

	while (1);
	return 0;
}

