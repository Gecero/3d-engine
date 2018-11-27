#include <iostream>
#include <time.h>
#include <vector>
#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include "elements.h"
// for the loadfile function
#include <fstream>
#include <strstream>
#include <istream>

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

	std::vector<triangle> object;

	// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c#answer-37454181
	inline std::vector<std::string> split(const std::string &s, const std::string &delimiter) {
		std::vector<std::string> ret;
		size_t start = 0;
		size_t end = 0;
		size_t len = 0;
		std::string token;
		do {
			end = s.find(delimiter, start);
			len = end - start;
			token = s.substr(start, len);
			ret.emplace_back(token);
			start += len + delimiter.length();
			std::cout << token << std::endl;
		} while (end != std::string::npos);
		return ret;
	}

	void loadFile(std::string fileName) {
		std::vector<vertex> vertexes;
		object.clear();

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
				vertexes.push_back(tmp);
			}

			if (line[0] == 'f') {
				char data1[128];
				char data2[128];
				char data3[128];

				parser >> buffer >> data1 >> data2 >> data3;

				int index1 = std::stoi(split(std::string(data1), "/")[0]);
				int index2 = std::stoi(split(std::string(data2), "/")[0]);
				int index3 = std::stoi(split(std::string(data3), "/")[0]);

				vertex vertex1 = vertexes[index1 - 1];
				vertex vertex2 = vertexes[index2 - 1];
				vertex vertex3 = vertexes[index3 - 1];

				object.push_back({ { vertex1, vertex2, vertex3 } });

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
		loadFile("C:\\users\\mariu\\Desktop\\kunybertV2b.obj");
		return true;
	}

	virtual bool OnUserUpdate(float fElapsedTime) override {
		Clear(olc::BLACK);

		for (int i = 0; i < object.size(); i++) {
			for (int j = 0; j < 3; j++) {
				object[i].data[j].xRot = (float)GetMouseX() / (float)(ScreenWidth() / 5);
				object[i].data[j].yRot = (float)GetMouseY() / (float)(ScreenWidth() / 5);

			}

			pos2d trianglePos1 = centerize(object[i].data[0].sample());
			pos2d trianglePos2 = centerize(object[i].data[1].sample());
			pos2d trianglePos3 = centerize(object[i].data[2].sample());
			FillTriangle(trianglePos1.x, trianglePos1.y, trianglePos2.x, trianglePos2.y, trianglePos3.x, trianglePos3.y, olc::GREEN);
		}

		if (GetKey(olc::Key::Q).bHeld) {
			for (int i = 0; i < object.size(); i++) {
				object[i].data[0] *= 1.00125;
				object[i].data[1] *= 1.00125;
				object[i].data[2] *= 1.00125;
			}
		}
		else if(GetKey(olc::Key::W).bHeld){
			for (int i = 0; i < object.size(); i++) {
				object[i].data[0] /= 1.00125;
				object[i].data[1] /= 1.00125;
				object[i].data[2] /= 1.00125;

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
