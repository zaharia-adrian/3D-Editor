#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>
#include "../../src/utils/Vec3d.hpp"


class Camera {
	Vec3d pos, target, up;
	Mat4x4 mat;
	float thetaX, thetaY; /// rotation angles
	float speed;
public:

	Camera();
	Mat4x4 getViewMat() const;
	Vec3d getPos() const;
	void update();
	void handleEvent(sf::Event);

};

#endif