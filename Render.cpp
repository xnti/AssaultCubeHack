#include "pch.h"


HWND hwndAC_Client;
HDC hdcAC_client;
HBRUSH Brush;
HFONT Font;
COLORREF TextCOLOR;
COLORREF TextCOLORRED;

bool Render::WorldToScreen(Vec3 pos, Vec2& screen, float matrix[16], int wWidth, int wHeight)
{
	//Matrix-vector Product, multiplying world(eye) coordinates by projection matrix = clipCoords
	Vec4 clipCoords;
	try
	{
		clipCoords.x = pos.x * matrix[0] + pos.y * matrix[4] + pos.z * matrix[8] + matrix[12];
		clipCoords.y = pos.x * matrix[1] + pos.y * matrix[5] + pos.z * matrix[9] + matrix[13];
		clipCoords.z = pos.x * matrix[2] + pos.y * matrix[6] + pos.z * matrix[10] + matrix[14];
		clipCoords.w = pos.x * matrix[3] + pos.y * matrix[7] + pos.z * matrix[11] + matrix[15];

		if (clipCoords.w < 0.1f)
			return false;

		//perspective division, dividing by clip.W = Normalized Device Coordinates
		Vec3 NDC;
		NDC.x = clipCoords.x / clipCoords.w;
		NDC.y = clipCoords.y / clipCoords.w;
		NDC.z = clipCoords.z / clipCoords.w;

		//Transform to window coordinates
		screen.x = (wWidth / 2 * NDC.x) + (NDC.x + wWidth / 2);
		screen.y = -(wHeight / 2 * NDC.y) + (NDC.y + wHeight / 2);
		return true;

	}
	catch (std::exception err)
	{
		
	}


}

void Render::DrawBorderBox(int x, int y, int w, int h, int thickness)
{

	DrawFilledRect(x, y, w, thickness);

	DrawFilledRect(x, y, thickness, h);

	DrawFilledRect((x + w), y, thickness, h);

	DrawFilledRect(x, y + h, w + thickness, thickness);
}

void Render::DrawString(int x, int y, COLORREF color, const char* text)
{
	SetTextAlign(hdcAC_client, TA_CENTER | TA_NOUPDATECP);

	SetBkColor(hdcAC_client, RGB(0, 0, 0));
	SetBkMode(hdcAC_client, TRANSPARENT);

	SetTextColor(hdcAC_client, color);

	SelectObject(hdcAC_client, Font);

	TextOutA(hdcAC_client, x, y, text, strlen(text));

	DeleteObject(Font);
}

void Render::DrawFilledRect(int x, int y, int w, int h)
{
	RECT rect = { x, y, x + w, y + h };
	FillRect(hdcAC_client, &rect, Brush);
}

void Render::DrawLine(int targetX, int targetY)
{
	MoveToEx(hdcAC_client, 960, 1080, NULL);
	LineTo(hdcAC_client, targetX, targetY);
}

void Render::DrawEsp(uintptr_t* viewMatrix, float Matrix[16], EntList* entList)
{
	TextCOLOR = RGB(255, 255, 255);
	hwndAC_Client = FindWindow(0, L"AssaultCube");//Gets Window

	memcpy(&Matrix, (PBYTE*)(viewMatrix), sizeof(Matrix));
	hdcAC_client = GetDC(hwndAC_Client);
	//Base of player
	Vec2 vScreen;
	//Head of player
	Vec2 vHead;

	//our entity list loop
	for (int i = 0; i < *Hack::pData()->numOfPlayers; i++)
	{

		//if (entList && Hack::pFunctions()->IsValidEnt(entList->ents[i]))
		//{
		//	std::cout << entList->ents[i]->name << std::endl;
		//	Sleep(100);
		//	// Doðru çalýþýyor
		//}

		if (entList && Hack::pFunctions()->IsValidEnt(entList->ents[i]))
		{

			//The entitys Pos
			float enemyX = entList->ents[i]->pos.x;
			float enemyY = entList->ents[i]->pos.y;
			float enemyZ = entList->ents[i]->pos.z;

			Vec3 enemyPos = { enemyX, enemyY, enemyZ };

			//Enemys Head Pos
			float enemyXHead = entList->ents[i]->head.x;
			float enemyYHead = entList->ents[i]->head.y;
			float enemyZHead = entList->ents[i]->head.z;

			Vec3 enemyHeadPos = { enemyXHead, enemyYHead, enemyZHead };

			//Sets each entitys health
			DWORD health = entList->ents[i]->health;

			//converts 3d to 2d
			if (WorldToScreen(enemyPos, vScreen, Matrix, 1920, 1080))
			{
				std::cout << "Yes I am true" << std::endl;
				//if (WorldToScreen(enemyHeadPos, vHead, Matrix, 1920, 1080))
				//{
				//	std::cout << "Yes I am true" << std::endl;
				//	//Creates the head height
				//	float head = vHead.y - vScreen.y;
				//	//Creates Width
				//	float width = head / 2;
				//	//Creates Center
				//	float center = width / -2;
				//	//Creates Extra area above head
				//	float extra = head / -6;

				//	//Sets the Brush Color
				//	Brush = CreateSolidBrush(RGB(158, 66, 244));
				//	//Draws the box
				//	DrawBorderBox(vScreen.x + center, vScreen.y, width, head - extra, 1);
				//	DeleteObject(Brush);


				//	//Draw our heath by converting a int to a char
				//	char healthChar[255];
				//	sprintf_s(healthChar, sizeof(healthChar), " %i", (int)(health));
				//	DrawString(vScreen.x, vScreen.y, TextCOLOR, healthChar);


				//	//Turns on snaplines
				//	if (GetKeyState(VK_F2) & 1)
				//	{
				//		DrawLine(vScreen.x, vScreen.y);
				//	}
				//}
			}
		}
	}
	//This prevents a fat memory leak
	Sleep(1);
	DeleteObject(hdcAC_client);
}