
#ifndef OFFSETS_H
#define OFFSETS_H


#include "pch.h"

#define PI 3.1415927f
// matrix => 0x501AE8

struct Vec2
{
	float x, y;
};

struct Vec3
{
	float x, y, z;
};

struct Vec4
{
	float x, y, z, w;
};

class vMatrix
{
public:
	Vec4 ViewMatrix; //0x0000
}; //Size: 0x0040

class playerEnt
{
public:
	uint32_t vTable; //0x0000
	Vec3 head; //0x0004
	char pad_0010[36]; //0x0010
	Vec3 pos; //0x0034
	Vec3 angle; //0x0040
	char pad_004C[28]; //0x004C
	int32_t bHop; //0x0068
	char pad_006C[4]; //0x006C
	uint8_t isStable; //0x0070
	uint8_t N0000017C; //0x0071
	uint8_t N0000017F; //0x0072
	uint8_t N0000017D; //0x0073
	char pad_0074[132]; //0x0074
	int32_t health; //0x00F8
	int32_t armor; //0x00FC
	char pad_0100[12]; //0x0100
	int32_t akimbo; //0x010C
	char pad_0110[80]; //0x0110
	int32_t KnifeWaitTime; //0x0160
	int32_t PistolWaitTime; //0x0164
	int32_t CarbineWaitTime; //0x0168
	int32_t ShotgunWaitTime; //0x016C
	int32_t SMGWaitTime; //0x0170
	int32_t SniperWaitTime; //0x0174
	int32_t AssaultWaitTime; //0x0178
	char pad_017C[4]; //0x017C
	int32_t GrenadeWaitTime; //0x0180
	char pad_0184[160]; //0x0184
	uint8_t bAttacking; //0x0224
	char name[16]; //0x0225
	char pad_0235[247]; //0x0235
	uint8_t team; //0x032C
	char pad_032D[11]; //0x032D
	uint8_t state; //0x0338
	char pad_0339[59]; //0x0339
	class weapon* weapon; //0x0374
	char pad_0378[948]; //0x0378
}; //Size: 0x072C

class weapon
{
public:
	char pad_0000[4]; //0x0000
	int32_t ID; //0x0004
	playerEnt* owner; //0x0008
	void* gunInfo; //0x000C
	int* resAmmo; //0x0010
	int* ammo; //0x0014
	char pad_0018[56]; //0x0018
}; //Size: 0x0050


struct EntList
{
public:
	playerEnt* ents[31];
};

#endif // !OFFSETS_H