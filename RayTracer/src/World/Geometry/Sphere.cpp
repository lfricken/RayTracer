#include "Sphere.hpp"
#include "Ray.hpp"

using namespace leon;

Sphere::Sphere(Vector position, float radiusi)
{
	pos = position;
	radius = radiusi;
}
Sphere::~Sphere()
{

}
/// <summary>
/// hook function for ray intersection
/// </summary>
/// <param name="rRay">the ray.</param>
/// <param name="world">The world.</param>
/// <returns></returns>
bool Sphere::intersectsHook(Ray& rRay, const World& world) const
{
	float a = rRay.dir.dot(rRay.dir);
	float b = (2 * ((rRay.pos - pos).dot(rRay.dir)));
	float c = (rRay.pos - pos).dot(rRay.pos - pos) - (radius*radius);

	float underRoot = (b*b) - (4 * a * c);

	if(underRoot >= 0)
	{
		float t = (-b + sqrt(underRoot)) / (2 * a);
		float t2 = (-b - sqrt(underRoot)) / (2 * a);

		if(t < 0 && t2 < 0)//are they both negative times?
			return false;
		if(t2 >= 0 && t2 < t)//is the second time smaller and non negative?
			t = t2;

		rRay.time = t;
		return true;
	}

	return false;
}
/// <summary>
/// Gets the normal for a point on the sphere.
/// </summary>
/// <param name="point">The point.</param>
/// <returns></returns>
Vector Sphere::getNormal(const Vector& point) const
{
	Vector norm = pos.to(point).normal();
	norm.w = 0;
	return norm;
}
/// <summary>
/// Translates the specified distance.
/// </summary>
/// <param name="dist">The dist.</param>
void Sphere::translate(const Vector& dist)
{
	pos = pos + dist;
}
/// <summary>
/// Transforms the specified rotation.
/// </summary>
/// <param name="rot">The rot.</param>
void Sphere::transform(const Matrix& rot)
{
	pos = rot*pos;
}
void Sphere::calcBoundBox() const
{
	m_box = BoundingBox(pos, radius * 2);
}
sf::Color Sphere::getTextureColor(const Vector& hitPoint) const
{
	Vector uv;//no z

	Vector unitHit = (hitPoint - pos) / radius;
	float theta = std::acos(unitHit.y);
	float phi = std::atan(unitHit.x / unitHit.z);

	uv.x = ((phi / 6.28318f) + 1) / 2;
	uv.y = ((1 - (theta / 3.14159f)) + 1) / 2;

	uv.x *= m_spTexture->getSize().x - 1;
	uv.y *= m_spTexture->getSize().y - 1;

	return m_spTexture->getPixel(uv.x, uv.y);
}

