#pragma once
#include "elements.h"
#include "olcPixelGameEngine.h"

const olc::Pixel renderColor = olc::YELLOW;

void renderObject(olc::PixelGameEngine * pge, object obj, pos3d inputModifiers = { 0.0f, 0.0f, 0.0f }, pos2d outputModifiers = { 0.0f, 0.0f }) {
	float xPos0, yPos0; // we define them before the use because that
	float xPos1, yPos1; // way we dont have to initalize the variables
	float xPos2, yPos2; // new and can just overwrite the last value
	triangle tmp;
	for (int triangle = 0; triangle < obj.triangles.size(); triangle++) {
		
		tmp = obj.triangles[triangle];
		
		xPos0 = tmp.vertexes[0].sample(inputModifiers).x + outputModifiers.x;
		yPos0 = tmp.vertexes[0].sample(inputModifiers).y + outputModifiers.y;
		xPos1 = tmp.vertexes[1].sample(inputModifiers).x + outputModifiers.x;
		yPos1 = tmp.vertexes[1].sample(inputModifiers).y + outputModifiers.y;
		xPos2 = tmp.vertexes[2].sample(inputModifiers).x + outputModifiers.x;
		yPos2 = tmp.vertexes[2].sample(inputModifiers).y + outputModifiers.y;

		pge->FillTriangle(xPos0, yPos0, xPos1, yPos1, xPos2, yPos2, renderColor);

	}
}

void renderTriangle(olc::PixelGameEngine * pge, triangle tri, pos2d modifiers = { 0.0f, 0.0f }) {
	float xPos, yPos; // we define them before the use because that way we dont have to initalize the variables new and can just overwrite the last value
	for (int vertex = 0; vertex < 3; vertex++) {
		xPos = tri.vertexes[vertex].sample().x + modifiers.x;
		yPos = tri.vertexes[vertex].sample().y + modifiers.y;
		pge->Draw(xPos, yPos, renderColor);
	}
}

void renderVertex(olc::PixelGameEngine * pge, vertex vtx, pos2d modifiers = { 0.0f, 0.0f }) {
	float xPos = vtx.sample().x + modifiers.x;
	float yPos = vtx.sample().y + modifiers.y;
	pge->Draw(xPos, yPos, renderColor);
}