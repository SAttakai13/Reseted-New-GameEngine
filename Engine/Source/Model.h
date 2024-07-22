#pragma once
#include "Vector2.h"
#include "Color.h"
#include "Renderer.h"
#include "Transform.h"

#include <vector>

// * - pointer -> nullptr
// & - reference -> 

class Model
{
public:
	Model() = default;
	Model(const std::vector<Vector2>& points, const Color& colour) :
		m_points{ points },
		m_colour{ colour }
	{
	}

	void Draw(Renderer& renderer, const Vector2& position, float angle, float scale);
	void Draw(Renderer& renderer, Transform& transform);

private:
	std::vector<Vector2> m_points;
	Color m_colour;
};