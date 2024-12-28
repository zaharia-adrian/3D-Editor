#include "Camera.hpp"


Camera::Camera() {
	speed = 0.01f;
	target = Vec3d(0.0f, 0.0f, 1.0f);
	pos = Vec3d(0.0f,2.0f,-10.0f);
	center = Vec3d();
	up = Vec3d(0.0f, 1.0f, 0.0f);

	thetaX = 0;
	thetaY = 0.06f;

	isDragging = false;

	update();
}

void Camera::update(bool orbit) {

	///updating the rotation 
	Vec3d Yaxis(0.0f, 1.0f, 0.0f);
											
	Vec3d View(0.0f, 0.0f, 1.0f);
	View.rotate(Yaxis, thetaX).normalize();		

	Vec3d U = Yaxis.crossProd(View).normalize();
	View.rotate(U, thetaY);

	target = View.normalize();
	up = target.crossProd(U).normalize();

	if (orbit) pos = center + target * ( - (pos - center).getLength());

	Mat4x4 rotation = Mat4x4({
		U.x, U.y, U.z, 0.0f,
		up.x, up.y, up.z, 0.0f,
		target.x, target.y, target.z, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	});
	Mat4x4 translation = Mat4x4::translation(-pos.x, -pos.y, -pos.z);
	mat = rotation * translation;
}
Mat4x4 Camera::getViewMat() const {
	return mat;
}
Vec3d Camera::getPos() const {
	return pos;
}

void Camera::handleEvent(sf::RenderWindow& window, sf::Event event) {
	switch (event.type){
	case sf::Event::MouseButtonPressed:
		if (event.mouseButton.button == sf::Mouse::Middle) {
			isDragging = true;
			lastMousePos = sf::Mouse::getPosition(window);
		}
		break;
	case sf::Event::MouseButtonReleased:
		if (event.mouseButton.button == sf::Mouse::Middle)
			isDragging = false;
		break;
	case sf::Event::MouseMoved: {

		if (!isDragging) break;

		sf::Vector2i currentMousePos = sf::Mouse::getPosition(window);
		sf::Vector2i delta = currentMousePos - lastMousePos;
		lastMousePos = currentMousePos;

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift)) {
			Vec3d U = up.crossProd(target);
			Vec3d add = (U * delta.x + up * delta.y) * speed;
			pos += add; center += add;
			update(false);
		}
		else {
			thetaY -= delta.y * speed * 0.5f;
			thetaX += delta.x * speed * 0.5f;
			update(true);
		}
		break;
	}
	case sf::Event::MouseWheelScrolled: {
		Vec3d add = target * event.mouseWheelScroll.delta * speed * 20.0f;
		pos += add;
		update(true);
		break;
	}
	default:
		break;
	}
}


