#include "OctTree.hpp"
#include "Geometry.hpp"

using namespace leon;

OctTree::OctTree(const Vector& center, int size, int minSize)
{
	m_center = center;
	m_size = size;
	m_minSize = minSize;
	m_root.reset(new OctNode(center, size, this));
}
OctTree::~OctTree()
{

}
void OctTree::addObject(const Geometry* data)
{
	vector<Vector> corners = data->getBoundBox().getCorners();
	for(auto it = corners.cbegin(); it != corners.cend(); ++it)
		m_root->add(data, *it);
}


