#pragma once

struct pos2d { float x, y; };

struct pos3d { float x, y, z; };

struct vertex {
	pos3d pos; float xRot = 0.0f, yRot = 0.0f, fov = 130.0f;
	// this is the function that allows to convert 3d positions into 2d
	// big thanks to: https://scratch.mit.edu/projects/25977969/ for teaching
	// me how to do something like that
	pos2d sample() {
		pos2d renderPos;
		// renderPos.x = (cos(xRot) * pos.x) - (sin(xRot) * pos.y);
		// renderPos.y = cos(yRot) * ((cos(xRot) * pos.y) + (sin(xRot) * pos.x)) + (pos.z * sin(yRot));
		renderPos.x = (cos(xRot)*pos.x) - (sin(xRot)*pos.y)*(fov/((((cos(xRot)*pos.y) + (sin(xRot)*pos.x))*sin(yRot)) + fov - (pos.z*cos(yRot))));
		renderPos.y = (cos(yRot)*((cos(xRot)*pos.y) + (sin(xRot)*pos.x)) + (pos.z*sin(yRot)))*(fov / ((((cos(xRot)*pos.y) + (sin(xRot)*pos.x))*sin(yRot)) + fov - (pos.z*cos(yRot))));
		return renderPos;
	}

	vertex & operator*=(const float value) {
		pos.x *= value;
		pos.y *= value;
		pos.z *= value;
		return *this;
	}
	vertex & operator/=(const float value) {
		pos.x /= value;
		pos.y /= value;
		pos.z /= value;
		return *this;
	}
	vertex & operator+=(const float value) {
		pos.x += value;
		pos.y += value;
		pos.z += value;
		return *this;
	}
	vertex & operator-=(const float value) {
		pos.x -= value;
		pos.y -= value;
		pos.z -= value;
		return *this;
	}


};

struct triangle {
	vertex data[3];
};
