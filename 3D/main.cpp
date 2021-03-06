#include <iostream>
#include <time.h>
#include <vector>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "elements.h"
#include "render.h"

// TO-DO:
// - texture mapping
// - light
// - A LOT of optimizations

class game : public olc::PixelGameEngine {
private:
	pos2d centerize(pos2d positions) {
		positions.x += ScreenWidth() / 2;
		positions.y += ScreenHeight() / 2;
		return positions;
	}
	pos2d centerize() {
		pos2d positions;
		positions.x = ScreenWidth() / 2;
		positions.y = ScreenHeight() / 2;
		return positions;
	}
	object obj;

public:
	game() {
		sAppName = "3D";
	}
private:
	virtual bool OnUserCreate() override {
		Clear(olc::BLACK);
		DrawString(0, 0, "now loading... this may take a while", olc::WHITE, 3);
		SetPixelMode(olc::Pixel::Mode::ALPHA);
		obj.loadFromFile("C:\\users\\mariu\\Desktop\\teapot.obj");
		
		return true;
	}

	pos3d cam;

	virtual bool OnUserUpdate(float fElapsedTime) override {
		Clear(olc::BLACK);

		for (int i = 0; i < obj.triangles.size(); i++) {
			for (int j = 0; j < 3; j++) {
				obj.triangles[i].vertexes[j].xRot = (float)GetMouseX() / ((float)ScreenWidth() / 5.0f);
				obj.triangles[i].vertexes[j].yRot = (float)GetMouseY() / ((float)ScreenHeight() / 5.0f);
			}
		}

		renderObject(this, obj, cam, centerize());

		if (GetKey(olc::Key::K1).bHeld) {
			for (int i = 0; i < obj.triangles.size(); i++) {
				obj.triangles[i] *= 10.125f * fElapsedTime;
			}
		}
		if (GetKey(olc::Key::K2).bHeld) {
			for (int i = 0; i < obj.triangles.size(); i++) {
				obj.triangles[i] /= 10.125f * fElapsedTime;
			}
		}
		if (GetKey(olc::Key::W).bHeld) {
			cam.y += 10.0f * fElapsedTime;
		}
		if (GetKey(olc::Key::S).bHeld) {
			cam.y -= 10.0f * fElapsedTime;
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
