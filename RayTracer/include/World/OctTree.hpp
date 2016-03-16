#pragma once

#include "Vector.hpp"
#include "stdafx.hpp"
#include "BoundingBox.hpp"

namespace leon
{
	class OctTree;
	class Geometry;

	class OctNode
	{
	public:
		OctNode(const Vector& center, int size, OctTree* parent) : m_box(center, size)
		{
			for(int i = 0; i < m_numChildren; ++i)
				m_children[i].reset();

			m_tree = parent;
		}

		void add(const Geometry* data, const BoundingBox& box);
		const BoundingBox& getBox() const;

	private:
		static const int m_numChildren = 8;
		sptr<OctNode> m_children[m_numChildren];

		vector<std::pair<BoundingBox, const Geometry*> > m_data;//pair of the point and the data associated

		BoundingBox m_box;//box describing us
		OctTree* m_tree;
	};


	class OctTree
	{
	public:
		OctTree(const Vector& center, int size, int minSize, int maxObj);
		~OctTree();

		void addObject(const Geometry* data);
		int m_minSize;//we stop splitting if new octant would be less than this
		int m_maxObjects;//max objects to have in a cell before attempting a split

	private:
		sptr<OctNode> m_root;

		Vector m_center;//center of initial cell
		int m_size;//Initial Cell size

	};

}

