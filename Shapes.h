#pragma once
#include<glew.h>
#include<vector>
#include<glm.hpp>

using namespace std;
using namespace glm;

class Shape
{
protected:
	unsigned int VAO, VBO;
public :
	
	Shape()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
	}
	~Shape()
	{
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
	}
	virtual void Draw() = 0;
	virtual void SetOriginPosition(vec2 origin) = 0;
	virtual void SetOtherPosition(vec2 _point) = 0;
	virtual void SetBufferData() = 0;
};



class Circle : public Shape
{
	vec2 positions[2];
	vector<vec2> vertices;
	float angleDifference;

public:
	Circle()
	{
		positions[0] = positions[1] = vec2(0, 0);
		angleDifference = 10.0;
	}

	void SetOriginPosition(vec2 origin)
	{
		positions[0] = origin;
	}
	void SetOtherPosition(vec2 point)
	{
		positions[1] = point;
	}

	void SetAngleDiff(float diff)
	{
		angleDifference = diff;
	}
	void SetBufferData()
	{
		vertices.clear();//To ensure that there isnt anything in the vertices
		float radius = distance(positions[0], positions[1]);
		vec2 point = positions[0];
		vertices.push_back(point);
		for (float i = 0.0; i < 360.0; i += angleDifference)
		{
			point.x = positions[0].x + cos(radians(i)) *radius;
			point.y = positions[0].y + sin(radians(i))*radius;

			vertices.push_back(point);
		}
		vertices.push_back(positions[0] + vec2(radius, 0.0f));
	}

	void Draw()
	{
		if (positions[0] != positions[1])
		{
			SetBufferData();

			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER,VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vec2)*vertices.size(), vertices.data(), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glDrawArrays(GL_TRIANGLE_FAN, 0, vertices.size());
			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);

    	}
		else
		{

		}
	}
};
class Line : public Shape
{
	vec2 positions[2];
	vector<vec2> vertices;

public :
	Line()
	{
		positions[0] = positions[1] = vec2(0.0f, 0.0f);
	}
	~Line()
	{

	}
	void SetOriginPosition(vec2 origin)
	{
		positions[0] = origin;
	}
	void SetOtherPosition(vec2 _point)
	{
		positions[1] = _point;
	}
	void SetBufferData()
	{
		vertices.clear();
		vertices.push_back(positions[0]);
		vertices.push_back(positions[1]);
	}
	void Draw()
	{
		if (positions[0] != positions[1])
		{
			SetBufferData();
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), vertices.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
};

class Rectangle : public Shape
{
	vec2 positions[2];
	vector<vec2> vertices;

public:
	Rectangle()
	{
		positions[0] = positions[1] = vec2(0.0f, 0.0f);
	}
	~Rectangle()
	{

	}
	void SetOriginPosition(vec2 origin)
	{
		positions[0] = origin;
	}
	void SetOtherPosition(vec2 _point)
	{
		positions[1] = _point;
	}
	void SetBufferData()
	{
		vertices.clear();
		float xdiff = positions[1].x - positions[0].x;
		float ydiff = positions[1].y - positions[0].y;

		vec2 point;
		point= positions[0];
		vertices.push_back(point);

		point = vec2(positions[0].x, positions[1].y);
		vertices.push_back(point);

		point = positions[1];
		vertices.push_back(point);

		point = vec2(positions[1].x, positions[0].y);
		vertices.push_back(point);
	}
	void Draw()
	{
		if (positions[0] != positions[1])
		{
			SetBufferData();
			glBindVertexArray(VAO);
			glBindBuffer(GL_ARRAY_BUFFER, VBO);

			glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vec2), vertices.data(), GL_STATIC_DRAW);
			glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glBindVertexArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}
	}
};