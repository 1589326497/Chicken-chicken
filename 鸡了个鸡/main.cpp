/*
	c代码练习 《鸡了个鸡》 2022年9月27日完成
											—宁子希
*/
#include<easyx.h>
#include<stdio.h>
#include <windows.h>
#pragma  comment (lib,"winmm.lib")
const int WIDTH = 400;   // 宽度
const int HEIGHT = 760;  // 高度
const int INTERVAL = 48; // 间隔
//  定义图片
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
	//播放音乐
	mciSendString(_T("open micc/jkun.mp3"),0,0,0);
	mciSendString(_T("play micc/jkun.mp3"),0,0,0);
	//创建头数组
	//初始化
	int map[3][3] = { 0 };
	for (int r = 0; r < 3; r++)
	{
		for (int c = 0; c < 3; c++)
		{
			map[r][c] = r + 1;  //给数组每个元素赋值{111 222 333}
			
		}
	}
	//打乱数组 
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
	//数组的位置
	int offsetX = (WIDTH - (2 * INTERVAL + 3 * 48)) / 2;
	int offsetY= (HEIGHT - (2 * INTERVAL + 3 * 48)) / 2;

	int store[7] = { 0 };
	while (true)
	{
		BeginBatchDraw();
		// 绘制地图  背景地图
		putimage(0, 0, &img_bk);
		// 绘制  渲染
		char s[] = "《鸡了个鸡》v1.1      ——宁子希";
		setbkmode(TRANSPARENT);
		settextcolor(BLUE);
		outtextxy(WIDTH-250,HEIGHT-18, s);
		for (int r = 0; r < 3; r++)
		{
			for (int c = 0; c < 3; c++)
			{
				if (map[r][c])
					// 开始渲染             x  , y   图片
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
		//点击检测      
		ExMessage  msg = { 0 };
		// 点击鼠标以后  是否有消息  消息是     VM_LBUTTONDOWN 左键
		if (peekmessage(&msg) && msg.message == WM_LBUTTONDOWN)
		{
			for (int r = 0; r < 3; r++) {

				for (int c = 0; c < 3; c++)
				{
					// 鼠标坐标
					int  x = offsetX + c * (48 + INTERVAL);
					int y = offsetY + r * (48 + INTERVAL);
					// 判断一下鼠标是否点击了图片
					if (msg.x > x && msg.x < x + 48 && msg.y>y && msg.y < y + 48)
					{
						// 求出 图片对应数组得位置 
						int col = (msg.x - offsetX) / (48 + INTERVAL);
						int row = (msg.y - offsetY) / (48 + INTERVAL);

						// 点击到得图片渲染到下面得数组

						for (int i = 0; i < 7; i++)
						{
							
							if (store[i] == 0) 
							{
								
								store[i] = map[row][col];
								break;
							}
						}
						// 记录次数
						int cnt = 0;
						for (int i = 0; i < 7; i++)
						{
							if (store[i] == map[row][col]) 
							{
								cnt++;
							}
						}
						// 如果达到了3 
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


	//创建尾数组

	while (1);
	return 0;
}

