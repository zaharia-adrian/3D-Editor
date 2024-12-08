#include "Camera.hpp"


Camera::Camera() {
	speed = 0.05f;
	pos = Vec3d(0.0f,0.f, -10.0f);
	target = Vec3d(0.0f, 0.0f, 1.0f);
	up = Vec3d(0.0f, 1.0f, 0.0f);
	thetaX = thetaY = 0;
	update();
}

void Camera::update() {

	float alfa; /// multiplication coefficient to set the camera position
	if (abs(target.x) > 0.01f) alfa = -pos.x / target.x;
	else if (abs(target.y) > 0.01f) alfa = -pos.y / target.y;
	else alfa = -pos.z / target.z;

	///updating the rotation 
	Vec3d Yaxis(0.0f, 1.0f, 0.0f);

	Vec3d View(0.0f, 0.0f, 1.0f);
	View.rotate(Yaxis, thetaX).normalize();

	Vec3d U = Yaxis.crossProd(View).normalize();
	View.rotate(U, thetaY);

	target = View.normalize();
	up = target.crossProd(U).normalize();

	pos = target * (-alfa);

	Mat4x4 rotation = Mat4x4({
		U.x, U.y, U.z, 0.0f,
		up.x, up.y, up.z, 0.0f,
		target.x, target.y, target.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
		});
	Mat4x4 translation = Mat4x4::translation(-pos.x, -pos.y, -pos.z);
	mat = rotation * translation;
}
Mat4x4 Camera::getViewMat() {
	return mat;
}

void Camera::moveLeft() {
	thetaX -= speed;
	update();
}

void Camera::moveRight() {
	thetaX += speed;
	update();
}
 
void Camera::moveUp() {
	thetaY -= speed;
	update();
}
void Camera::moveDown() {
	thetaY += speed;
	update();
}
void Camera::moveForward() {
	if(pos.length()>2.0f)
	pos += (target * speed);
	update();
}
void Camera::moveBackward() {
	pos -= (target * speed);
	update();
}


