#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <SFML/Graphics.hpp>
#include "../../src/utils/Vec3d.hpp"


class Camera {
	Vec3d pos, target, up;
	Vec3d center; ///the point for camera to orbit around
	Mat4x4 mat;
	float thetaX, thetaY; /// rotation angles
	float speed;

	bool isDragging; 
	sf::Vector2i lastMousePos;
public:

	Camera();
	Mat4x4 getViewMat() const;
	Vec3d getPos() const;
	void update(bool = true);
	void handleEvent(sf::RenderWindow&, sf::Event);
};

#endif