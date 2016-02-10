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
/// <summary>
/// Moves the specified direction.
/// </summary>
/// <param name="dir">The dir.</param>
/// <param name="world">The world.</param>
void Camera::move(const Vector& dir, World& world)//direction relative to camera position
{
	vector<sptr<Geometry> >& geos = world.geometry;
	vector<sptr<Light> >& lights = world.lights;

	for(auto it = geos.begin(); it != geos.end(); ++it)
		(**it).translate(dir);

	for(auto it = lights.begin(); it != lights.end(); ++it)
		(**it).translate(dir);
}
/// <summary>
/// Yaws the specified rotation.
/// </summary>
/// <param name="radCCW">rotation in radians Counter ClockWise</param>
/// <param name="world">The world.</param>
void Camera::yaw(double radCCW, World& world)
{
	Matrix rotCam;
	rotCam.setRotMat(up, radCCW);
	transformWorld(rotCam, world);
}
/// <summary>
/// Pitches the specified rotation
/// </summary>
/// <param name="radCCW">rotation in radians Counter ClockWise</param>
/// <param name="world">The world.</param>
void Camera::pitch(double radCCW, World& world)
{
	Matrix rotCam;
	rotCam.setRotMat(up.cross(direction), radCCW);
	transformWorld(rotCam, world);
}
/// <summary>
/// Rolls the specified RAD CCW.
/// </summary>
/// <param name="radCCW">rotation in radians Counter ClockWise</param>
/// <param name="world">The world.</param>
void Camera::roll(double radCCW, World& world)
{
	Matrix rotCam;
	rotCam.setRotMat(direction, radCCW);
	transformWorld(rotCam, world);
}
/// <summary>
/// Gets the position.
/// </summary>
/// <returns></returns>
const Vector& Camera::getPosition()
{
	return position;
}
/// <summary>
/// Gets the direction we are looking.
/// </summary>
/// <returns></returns>
const Vector& Camera::getDirection()
{
	return direction;
}
/// <summary>
/// Gets up vector of camera.
/// </summary>
/// <returns></returns>
const Vector& Camera::getUp()
{
	return up;
}
/// <summary>
/// Transforms the world.
/// </summary>
/// <param name="rotMatrix">The rotation matrix.</param>
/// <param name="world">The world.</param>
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
