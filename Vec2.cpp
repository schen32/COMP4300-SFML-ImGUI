#include <iostream>

class Vec2
{
public:
	float x = 0, y = 0;

	Vec2() {}
	Vec2(float xin, float yin)
		: x(xin), y(yin) { }

	void print() const
	{
		std::cout << x << " " << y << std::endl;
	}

	Vec2& add(const Vec2& v)
	{
		x += v.x;
		y += v.y;
		return *this;
	}

	Vec2& scale(float s)
	{
		x *= s;
		y *= s;
		return *this;
	}

	Vec2 operator + (const Vec2& rhs)
	{
		return Vec2(x + rhs.x, y + rhs.y);
	}

	Vec2 operator * (float scale)
	{
		return Vec2(x * scale, y * scale);
	}
};

int main()
{
	Vec2 v1(100, 200);
	Vec2 v2(500, 500);
	
	v1.add(v2).scale(5).add(v2);

	v1.print();

	return 0;
}