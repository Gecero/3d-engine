#include <iostream>
#include <time.h>
#include <vector>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "elements.h"
// for the loadfile function
#include <fstream>
#include <strstream>

// TO-DO:
// - add a triangle struct and a object struct
// - update the obj file parser to parse triangles
// - texture mapping

class game : public olc::PixelGameEngine {
private:
	pos2d centerize(pos2d positions) {
		positions.x += ScreenWidth() / 2;
		positions.y += ScreenHeight() / 2;
		return positions;
	}
	std::vector<vertex> objects;
	vertex o1{ {8.0f, 1.0f, 0.0f} };
	vertex o2{ {22.0f, 1.0f, 0.0f} };
	vertex o3{ {8.0f, 23.0f, 0.0f} };
	vertex o4{ {22.0f, 23.0f, 0.0f} };
	vertex o5{ {15.0f, 12.0f, -12.5f} };

	void loadFile(std::string fileName) {
		objects.clear();
		std::ifstream reader(fileName.c_str());
		if (reader.fail() || !reader.is_open()) {
			std::cout << "error D:\n";
			return;
		}
		reader.seekg(4);
		while (!reader.eof()) {
			std::strstream parser;
			char line[128];
			char buffer;
			reader.getline(line, 128);
			parser << line;

			if (line[0] == 'v' && line[1] == ' ') { // removing the line[1]==' ' will increase object vector size
				vertex tmp;
				parser >> buffer >> tmp.pos.x >> tmp.pos.y >> tmp.pos.z;
				objects.push_back(tmp);
			}

		}

		
		reader.close();

	}

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
		loadFile("C:\\users\\mariu\\Desktop\\kunybertV2.obj");
		std::cout << sizeof(objects)*objects.size() << std::endl;
		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime) override {
		Clear(olc::BLACK);

		for (int i = 0; i < objects.size(); i++) {
			objects[i].xRot = (float)GetMouseX() / ((float)ScreenWidth() / 5.0f);
			objects[i].yRot = (float)GetMouseY() / ((float)ScreenHeight() / 5.0f);
			pos2d renderPos = centerize(objects[i].sample());

			Draw(renderPos.x, renderPos.y, olc::RED);
		}

		


		if (GetKey(olc::Key::Q).bHeld) {
			for (int i = 0; i < objects.size(); i++) {
				objects[i] *= 1.00125;
			}
		}
		else if(GetKey(olc::Key::W).bHeld){
			for (int i = 0; i < objects.size(); i++) {
				objects[i] /= 1.00125;
			}
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
