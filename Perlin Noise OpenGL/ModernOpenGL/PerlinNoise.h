#pragma once
class PerlinNoise
{
private:
	long seed;
	int random(int x, int y, int range);
	int random(int x, int range);
	float lerp(float a, float b, float l);
	int max(int a, int b);

public:
	PerlinNoise(long s);
	~PerlinNoise();

	int getNoise(int x, int y, int range);
	void ResetSeed(long s);
};
