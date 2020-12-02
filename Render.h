#ifndef RENDER_H
#define RENDER_H
#pragma once
#include "pch.h"

namespace Render
{

	int* numOfPlayers;
	// 3D to 2D
	bool WorldToScreen(Vec3 posS, Vec2& screen, float matrix[16], int wWidth, int wHeight);
	void DrawBorderBox(int x, int y, int w, int h, int thickness);
	void DrawString(int x, int y, COLORREF color, const char* text);
	void DrawFilledRect(int x, int y, int w, int h);
	void DrawLine(int targetX, int targetY);
	void DrawEsp(uintptr_t* viewMatrix, float Matrix[16], EntList* entList);
};



#endif // !RENDER_H