#include "Camera.hpp"
#include "World.hpp"
#include "Geometry.hpp"
#include "Light.hpp"

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
void Camera::move(const Vector& dir, World& world)//direction relative to camera position
{
	vector<sptr<Geometry> >& geos = world.geometry;
	vector<sptr<Light> >& lights = world.lights;

	for(auto it = geos.begin(); it != geos.end(); ++it)
		(**it).translate(dir);

	for(auto it = lights.begin(); it != lights.end(); ++it)
		(**it).translate(dir);
}
void Camera::yaw(double radCCW, World& world)
{
	Matrix rotCam;
	rotCam.setRotMat(up, radCCW);
	transformWorld(rotCam, world);
}
void Camera::pitch(double radCCW, World& world)
{
	Matrix rotCam;
	rotCam.setRotMat(up.cross(direction), radCCW);
	transformWorld(rotCam, world);
}
void Camera::roll(double radCCW, World& world)
{
	Matrix rotCam;
	rotCam.setRotMat(direction, radCCW);
	transformWorld(rotCam, world);
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
void Camera::transformWorld(Matrix rotMatrix, World& world) const
{
	rotMatrix.transpose();
	vector<sptr<Geometry> >& geos = world.geometry;
	vector<sptr<Light> >& lights = world.lights;

	for(auto it = geos.begin(); it != geos.end(); ++it)
		(**it).transform(rotMatrix);

	for(auto it = lights.begin(); it != lights.end(); ++it)
		(**it).transform(rotMatrix);
}
