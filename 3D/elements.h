#pragma once
// all of theese are required for object::loadFromFile
#include <strstream>
#include <fstream>
#include <vector>
#include <string>


typedef float decimal;

struct pos2d { decimal x = 0.0f, y = 0.0f; };

struct pos3d { decimal x = 0.0f, y = 0.0f, z = 0.0f; };

struct vertex {
	pos3d pos; decimal xRot = 0.0f, yRot = 0.0f, fov = 90.0f;
	// this is the function that allows to convert 3d positions into 2d
	// big thanks to: https://scratch.mit.edu/projects/25977969/ for teaching
	// me how to do something like that
	pos2d sample(pos3d modifiers = { 0.0f, 0.0f, 0.0f }) {
		pos2d renderPos;
		// non-fov code
		// renderPos.x = (cos(xRot) * pos.x) - (sin(xRot) * pos.y);
		// renderPos.y = cos(yRot) * ((cos(xRot) * pos.y) + (sin(xRot) * pos.x)) + (pos.z * sin(yRot));
		
		
		pos3d oldPos = pos;
		pos.x += modifiers.x;
		pos.y += modifiers.y;
		pos.z += modifiers.z;

		renderPos.x = (cos(xRot)*pos.x) - (sin(xRot)*pos.y)*(fov/((((cos(xRot)*pos.y) + (sin(xRot)*pos.x))*sin(yRot)) + fov - (pos.z*cos(yRot))));
		renderPos.y = (cos(yRot)*((cos(xRot)*pos.y) + (sin(xRot)*pos.x)) + (pos.z*sin(yRot)))*(fov / ((((cos(xRot)*pos.y) + (sin(xRot)*pos.x))*sin(yRot)) + fov - (pos.z*cos(yRot))));

		pos = oldPos;

		return renderPos;
	}

	vertex & operator*=(const decimal value) {
		pos.x *= value;
		pos.y *= value;
		pos.z *= value;
		return * this;
	}
	vertex & operator*=(const pos3d value) {
		pos.x *= value.x;
		pos.y *= value.y;
		pos.z *= value.z;
		return * this;
	}
	vertex & operator/=(const decimal value) {
		pos.x /= value;
		pos.y /= value;
		pos.z /= value;
		return * this;
	}
	vertex & operator/=(const pos3d value) {
		pos.x *= value.x;
		pos.y *= value.y;
		pos.z *= value.z;
		return * this;
	}
	vertex & operator+=(const decimal value) {
		pos.x += value;
		pos.y += value;
		pos.z += value;
		return * this;
	}
	vertex & operator+=(const pos3d value) {
		pos.x += value.x;
		pos.y += value.y;
		pos.z += value.z;
		return * this;
	}
	vertex & operator-=(const decimal value) {
		pos.x -= value;
		pos.y -= value;
		pos.z -= value;
		return * this;
	}	
	vertex & operator-=(const pos3d value) {
		pos.x -= value.x;
		pos.y -= value.y;
		pos.z -= value.z;
		return * this;
	}

};

struct triangle {
	vertex vertexes[3];
	triangle & operator*=(const decimal value) {
		for (int i = 0; i < 3; i++) {
			vertexes[i] *= value;
		}
		return * this;
	}
	triangle & operator*=(const pos3d value) {
		for (int i = 0; i < 3; i++) {
			vertexes[i] *= value;
		}
		return * this;
	}
	triangle & operator/=(const decimal value) {
		for (int i = 0; i < 3; i++) {
			vertexes[i] /= value;
		}
		return * this;
	}
	triangle & operator/=(const pos3d value) {
		for (int i = 0; i < 3; i++) {
			vertexes[i] /= value;
		}
		return * this;
	}
	triangle & operator+=(const decimal value) {
		for (int i = 0; i < 3; i++) {
			vertexes[i] += value;
		}
		return * this;
	}
	triangle & operator+=(const pos3d value) {
		for (int i = 0; i < 3; i++) {
			vertexes[i] += value;
		}
		return * this;
	}
	triangle & operator-=(const decimal value) {
		for (int i = 0; i < 3; i++) {
			vertexes[i] -= value;
		}
		return * this;
	}
	triangle & operator-=(const pos3d value) {
		for (int i = 0; i < 3; i++) {
			vertexes[i] -= value;
		}
		return * this;
	}

};

struct object {
private:
	// https://stackoverflow.com/questions/14265581/parse-split-a-string-in-c-using-string-delimiter-standard-c#answer-44131093
	std::vector<std::string> split(const std::string &s, const std::string &delimiter) {
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
		} while (end != std::string::npos);
		return ret;
	}

public:
	std::vector<triangle> triangles;

	void loadFromFile(std::string fileName) {
		std::vector<vertex> vertexes;
		triangles.clear();

		std::ifstream reader(fileName.c_str());
		if (reader.fail() || !reader.is_open()) {
			std::cerr << "error initalizing std::ifstream reader";
			return;
		}

		while (!reader.eof()) {
			std::strstream parser;
			char line[128];
			char buffer;
			reader.getline(line, 128);
			parser << line;

			if (line[0] == 'v' && line[1] == ' ') {
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
				vertex1 *= 10.0f;
				vertex2 *= 10.0f;
				vertex3 *= 10.0f;


				triangles.push_back({ { vertex1, vertex2, vertex3 } });

			}

		}

		reader.close();
	}
};
