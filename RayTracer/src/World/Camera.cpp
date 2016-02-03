#include "Camera.hpp"
#include "World.hpp"

using namespace leon;

Camera::Camera()
{
	up = Vector(0, 0, 1);
	position = Vector(0, 0, 0);
	direction = Vector(1, 0, 0);
	eyedist = 100;
}
Camera::~Camera()
{

}
void Camera::move(const Vector& pos, World& world)
{
	//apply translation pos to world
}
void Camera::yaw(double radCCW, World& world)
{
	Mat3d rotCam;
	rotCam.setRotMat(up, radCCW);
	rotCam.transpose();
}
void Camera::pitch(double radCCW, World& world)
{

}
void Camera::roll(double radCCW, World& world)
{

}
const Vector& Camera::getPosition()
{
	return position;
}
const Vector& Camera::getDirection()
{
	return direction;
}
const Vector& Camera::getUp()
{
	return up;
}

