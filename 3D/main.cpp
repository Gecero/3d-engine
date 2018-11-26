#include <iostream>
#include <time.h>
#include <vector>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

class game : public olc::PixelGameEngine {
private:
	struct pos2d { float x, y; };
	struct pos3d { float x, y, z; };
	struct obj {
		pos3d pos; float xRot = 0.0f, yRot = 0.0f;
		// this is the function that allows to convert 3d positions into 2d
		// big thanks to: https://scratch.mit.edu/projects/25977969/ for teaching
		// me how to do something
		pos2d sample() {
			pos2d renderPos;
			renderPos.x = (cos(xRot) * pos.x) - (sin(xRot) * pos.y);
			renderPos.y = cos(yRot) * ((cos(xRot) * pos.y) + (sin(xRot) * pos.x)) + (pos.z * sin(yRot));
			return renderPos;
		}
		obj & operator*=(const float multiplier) {
			pos.x *= multiplier;
			pos.y *= multiplier;
			pos.z *= multiplier;
			return * this;
		}

	};
	pos2d centerize(pos2d positions) {
		positions.x += ScreenWidth() / 2;
		positions.y += ScreenHeight() / 2;
		return positions;
	}
	std::vector<obj> objects;
	obj o1{ {8.0f, 1.0f, 0.0f} };
	obj o2{ {22.0f, 1.0f, 0.0f} };
	obj o3{ {8.0f, 23.0f, 0.0f} };
	obj o4{ {22.0f, 23.0f, 0.0f} };
	obj o5{ {15.0f, 12.0f, -12.5f} };

public:
	game() {
		sAppName = "3D";
	}
private:
	virtual bool OnUserCreate() override {
		SetPixelMode(olc::Pixel::Mode::ALPHA);
		objects.push_back(o1);
		objects.push_back(o2);
		objects.push_back(o3);
		objects.push_back(o4);
		objects.push_back(o5);

		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime) override {
		Clear(olc::BLACK);

		for (obj o : objects) {
			o *= 5.0f;
			o.xRot = (float)GetMouseX() / ((float)ScreenWidth() / 5.0f);
			o.yRot = (float)GetMouseY() / ((float)ScreenHeight() / 5.0f);
			pos2d renderPos = centerize(o.sample());
			for (obj o2 : objects) {
				o2 *= 5.0f;
				o2.xRot = (float)GetMouseX() / ((float)ScreenWidth() / 5.0f);
				o2.yRot = (float)GetMouseY() / ((float)ScreenHeight() / 5.0f);
				pos2d otherPos = centerize(o2.sample());
				DrawLine(renderPos.x, renderPos.y, otherPos.x, otherPos.y, olc::YELLOW);
				Draw(otherPos.x, otherPos.y, olc::RED);
			}
			Draw(renderPos.x, renderPos.y, olc::RED);

		}
		return true;
	}

	virtual bool OnUserDestroy() override {

		return true;
	}

};

using namespace std;

int main()
{
	game theGame;
	if (theGame.Construct(160*2, 90*2, 4, 4))
		theGame.Start();
}
