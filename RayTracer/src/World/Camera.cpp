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

	Matrix move;
	move.m[0][3] = -dir.x;
	move.m[1][3] = -dir.y;
	move.m[2][3] = -dir.z;

	for(auto it = geos.begin(); it != geos.end(); ++it)
		(**it).transform(move);

	for(auto it = lights.begin(); it != lights.end(); ++it)
		(**it).transform(move);

	//for(auto it = geos.begin(); it != geos.end(); ++it)
	//	(**it).translate(dir.inv());

	//for(auto it = lights.begin(); it != lights.end(); ++it)
	//	(**it).translate(dir.inv());
}
/// <summary>
/// Yaws the specified rotation.
/// </summary>
/// <param name="radCCW">rotation in radians Counter ClockWise</param>
/// <param name="world">The world.</param>
void Camera::yaw(float radCCW, World& world)
{
	Matrix rotCam;
	rotCam.setRotMat(up, radCCW);

	Vector eye(-eyedist, 0, 0);
	move(eye, world);
	transformWorld(rotCam, world);
	move(eye.inv(), world);
}
/// <summary>
/// Pitches the specified rotation
/// </summary>
/// <param name="radCCW">rotation in radians Counter ClockWise</param>
/// <param name="world">The world.</param>
void Camera::pitch(float radCCW, World& world)
{
	Matrix rotCam;
	rotCam.setRotMat(up.cross(direction), radCCW);

	Vector eye(-eyedist, 0, 0);
	move(eye, world);
	transformWorld(rotCam, world);
	move(eye.inv(), world);
}
/// <summary>
/// Rolls the specified RAD CCW.
/// </summary>
/// <param name="radCCW">rotation in radians Counter ClockWise</param>
/// <param name="world">The world.</param>
void Camera::roll(float radCCW, World& world)
{
	Matrix rotCam;
	rotCam.setRotMat(direction, radCCW);

	Vector eye(-eyedist, 0, 0);
	move(eye, world);
	transformWorld(rotCam, world);
	move(eye.inv(), world);
}
/// <summary>
/// Gets the position.
/// </summary>
/// <returns></returns>
const Vector& Camera::getPosition() const
{
	return position;
}
/// <summary>
/// Gets the direction we are looking.
/// </summary>
/// <returns></returns>
const Vector& Camera::getDirection() const
{
	return direction;
}
/// <summary>
/// Gets up vector of camera.
/// </summary>
/// <returns></returns>
const Vector& Camera::getUp() const
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
