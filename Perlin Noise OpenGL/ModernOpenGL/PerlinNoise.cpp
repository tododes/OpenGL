#include "PerlinNoise.h"


PerlinNoise::PerlinNoise(long s)
{
	seed = s;
}


PerlinNoise::~PerlinNoise()
{
}

int PerlinNoise::random(int x, int y, int range)
{
	return random(x + y * 65535, range);
}

int PerlinNoise::random(int x, int range)
{
	return (int)(((x + seed) ^ 5) % range);
}

float PerlinNoise::lerp(float a, float b, float l)
{
	return (a * (1 - l)) + (b * l);
}

int PerlinNoise::max(int a, int b)
{
	return a > b ? a : b;
}

int PerlinNoise::getNoise(int x, int y, int range)
{
	float noise = 0.0f;
	int chunkSize = 6;
	range /= 2;

	while (chunkSize > 0)
	{
		float chunkX = x / chunkSize;
		float chunkY = y / chunkSize;

		float progX = (x % chunkSize) / (chunkSize * 1.0f);
		float progY = (y % chunkSize) / (chunkSize * 1.0f);

		float r00 = random(chunkX + 0, chunkY + 0, range);
		float r01 = random(chunkX + 0, chunkY + 1, range);
		float r10 = random(chunkX + 1, chunkY + 0, range);
		float r11 = random(chunkX + 1, chunkY + 1, range);

		float r0 = lerp(r00, r01, progY);
		float r1 = lerp(r10, r11, progY);

		noise += lerp(r0, r1, progX);

		range /= 2;
		chunkSize /= 2;
		range = max(1, range);
	}
	return (int)noise;
}

void PerlinNoise::ResetSeed(long s)
{
	seed = s;
}
