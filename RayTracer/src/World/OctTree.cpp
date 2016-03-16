#include "OctTree.hpp"
#include "Geometry.hpp"

using namespace leon;

void OctNode::add(const Geometry* data, const BoundingBox& box)
{
	if(!m_children[0])//if we have no children
	{
		m_data.push_back(std::pair<BoundingBox, const Geometry*>(box, data));

		//CHECK IF WE SHOULD SPLIT
		bool childrenAboveMinSize = m_box.getHalfx() > m_tree->m_minSize;
		bool hasTooManyObjects = m_data.size() > (unsigned int)m_tree->m_maxObjects;

		if(hasTooManyObjects && childrenAboveMinSize)
		{
			const Vector center = m_box.getCenter();
			int newSide = m_box.getHalfx();
			int newSide2 = newSide / 2;

			m_children[0].reset(new OctNode(center + Vector(newSide2, newSide2, newSide2), newSide, m_tree));
			m_children[1].reset(new OctNode(center + Vector(newSide2, newSide2, -newSide2), newSide, m_tree));
			m_children[2].reset(new OctNode(center + Vector(newSide2, -newSide2, newSide2), newSide, m_tree));
			m_children[3].reset(new OctNode(center + Vector(newSide2, -newSide2, -newSide2), newSide, m_tree));

			m_children[4].reset(new OctNode(center + Vector(-newSide2, newSide2, newSide2), newSide, m_tree));
			m_children[5].reset(new OctNode(center + Vector(-newSide2, newSide2, -newSide2), newSide, m_tree));
			m_children[6].reset(new OctNode(center + Vector(-newSide2, -newSide2, newSide2), newSide, m_tree));
			m_children[7].reset(new OctNode(center + Vector(-newSide2, -newSide2, -newSide2), newSide, m_tree));

			for(auto it = m_data.begin(); it != m_data.end(); ++it)
				this->add(it->second, it->first);

			m_data.clear();
		}
	}
	else//we have children, give it to them
	{
		for(int i = 0; i < m_numChildren; ++i)
		{
			if(box.intersects(m_children[i]->getBox()))
				m_children[i]->add(data, box);
		}
	}
}
const BoundingBox& OctNode::getBox() const
{
	return m_box;
}



OctTree::OctTree(const Vector& center, int size, int minSize, int maxObj)
{
	m_center = center;
	m_size = size;
	m_minSize = minSize;
	m_maxObjects = maxObj;
	m_root.reset(new OctNode(center, size, this));
}
OctTree::~OctTree()
{

}
void OctTree::addObject(const Geometry* data)
{
	const BoundingBox& box = data->getBoundBox();
	if(m_root->getBox().intersects(box))
		m_root->add(data, box);
}


