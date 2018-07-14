#pragma once
#include <iosfwd>

template <typename T>
class Point2 {
private:
	T x, y;
public:
	bool CheckForNaNs() const { return (std::isnan(x) || std::isnan(y)); };

	inline Point2()
	{ x = 0; y = 0;};

	inline Point2(T a, T b) {
		x = a; y = b;
		assert(!CheckForNaNs());
	};

	Point2<T> operator +( Vector2<T> &vec) const
	{ return Point2<T>(x + vec.getX(), y + vec.getY());};

	Point2<T> operator +=( Vector2<T> vec) const {
		x += vec.x; y += vec.y;
		return *this;
	};

	Point2<T> operator -( Vector2<T> &vec) const
	{ return Point2<T>(x - vec.getX(), y - vec.getY());};

	Point2<T> operator -=( Vector2<T> &vec) const {
		x -= vec.getX(); y -= vec.getY();
		return *this;
	};

	Vector2<T> operator -(const Point2<T> &poi) const
	{ return Vector2<T>(x - poi.x, y - poi.y);};
	
	inline float getDistance(const Point2<T> &p2)
	{ return (*this - p2).getLen();}

	inline float getDistanceSquared(const Point2<T> &p2)
	{return (*this - 2).getLenSquared();}
};

template <typename T>
class Point3 {
private:
	T x, y, z;
public:
	bool CheckForNaNs() const { return (std::isnan(x) || std::isnan(y) || std::isnan(z)); };

	inline Point3()
	{ x = 0; y = 0; z = 0;};

	inline Point3(Vector3<T> &a) {
		x = a.getX();
		y = a.getY();
		z = a.getZ();
	}

	inline Point3(T a, T b, T c){ 
		x = a; y = b; z = c;
		assert(!CheckForNaNs());
	};

	Point3<T> operator +(Vector3<T> &vec) const 
	{ return Point3<T>(x + vec.getX(), y + vec.getY(), z + vec.getZ());};

	Point3<T> operator +=(Vector3<T> vec) const {
		x += vec.getX(); y += vec.getY(); z += vec.getZ();
		return *this;
	}
	
	Point3<T> operator -( Vector3<T> &vec) const
	{ return Point3<T>(x - vec.getX(), y - vec.getY(), z - vec.getZ());}

	Point3<T> operator -=( Vector3<T> &vec) const{
		x -= vec.getX(); y -= vec.getY(); z -= vec.getZ();
		return *this;
	};

	Vector3<T> operator -(const Point3<T> &poi) const
	{ return Vector3<T>(x - poi.x, y - poi.y, z - poi.z);};


	inline operator Point2<T>() const
	{ return Point2<T>(x, y);};

	inline operator Vector3<T>() const
	{ return Vector3<T>(x, y, z); };

	inline float getDistance(const Point3<T> &p2) 
	{ return (*this - p2).getLen();}
	
	inline float getDistanceSquared(const Point3<T> &p2)
	{ return (*this-2).getLenSquared();}
};

namespace point {
	template <typename T>
	inline float Distance(const Point3<T> &p1, const Point3<T> &p2) 
	{return (p1 - p2).getLen();}
	
	template <typename T>
	inline float Distance(const Point2<T> &p1, const Point2<T> &p2) 
	{return (p1 - p2).getLen();}

	template <typename T>
	inline float DistanceSquared(const Point3<T> &p1, const Point3<T> &p2) 
	{return (p1 - p2).getLenSquared();}
	
	template <typename T>
	inline float DistanceSquared(const Point2<T> &p1, const Point2<T> &p2)
	{return (p1 - p2).getLenSquared();}

	template <typename T>
	Point3<T> Lerp(float a, const Point3<T> &p1, const Point3<T> &p2) 
	{return (1-a)*p1+t*p2;}

	template <typename T>
	Point2<T> Lerp(float a, const Point2<T> &p1, const Point2<T> &p2) 
	{return (1-a)*p1+t*p2;}
}

typedef Point2<float> Point2f;
typedef Point2<int> Point2i;
typedef Point3<float> Point3f;
typedef Point3<int> Point3i;