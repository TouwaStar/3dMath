#pragma once
#include <iosfwd>
template <typename T>
class Vector4;
template <typename T>
class Vector3;
template <typename T>
class Vector2;

template<typename T>
class Vector2 {
private:
	T x, y;
public:
	bool CheckForNaNs() const { return std::isnan(x) || std::isnan(y); }
	
	inline Vector2() { x = 0; y = 0; }
	
	inline Vector2(const T a, const T b) {
		x = a; y = b;
		assert(!CheckForNaNs());
	}

	inline Vector2(const Vector2<T> &vec) 
	{ x = vec.getX(); y = vec.y;}
	
	inline Vector2<T> operator + (const Vector2<T> &vec) const 
	{ return Vector2(x + vec.x, y + vec.y);}
	
	inline Vector2<T> operator - (const Vector2<T> &vec) const
	{ return Vector2(x - vec.x, y - vec.y);}

	inline Vector2<T> operator + (const T a) const
	{ return Vector2(x + a, y + a);}

	inline Vector2<T> operator - (const T a) const
	{ return Vector2(x - a, y - a);}

	template <typename V>
	inline Vector2<T> operator * (const V a) const
	{ return Vector2(x*a, y*a);}

	template <typename V>
	inline Vector2<T> operator / (const V a) const {
		float inv = (float)1 / a;
		return Vector2(x * inv, y * inv);
	}

	inline bool operator == (const Vector2<T>& vec) const
	{ return bool(x == vec.x && y == vec.y);}

	inline bool operator != (const Vector2<T>& vec) const
	{ return bool(x != vec.x || y != vec.y );}

	inline void negate()
	{ return this->setValues(-x, -y);}

	inline Vector2<T>& operator += (const Vector2<T>& vec) {
		x += vec.x;
		y += vec.y;
		return *this;
	}
	inline Vector2<T>& operator -= (const Vector2<T>& vec) {
		x -= vec.x;
		y -= vec.y;
		return *this;
	}
	template <typename V>
	inline Vector2<T>& operator *= (const V a) {
		x *= a;
		y *= a;
		return *this;
	}
	template <typename V>
	inline Vector2<T>& operator /= (const V a) {
		float inv = (float)1 / a;
		x *= a;
		y *= a;
		return *this;
	}

	inline void setX(const T a)
	{ x = a;}

	inline void setY(const T a)
	{ y = a;}

	inline void setValues(const T a, const T b, const T c)
	{ x = a, y = b;}

	inline T getX() const
	{ return x;}

	inline T getY() const
	{ return y;}

	inline T getLenSquared() const 
	{ return x * x + y * y; }

	inline T getLen() const 
	{ return std::sqrt(x*x+y*y); }

	friend inline std::ostream& operator<<(std::ostream& os, Vector2<T>& e) {
		os << e.getX() << " " << e.getY();
		return os;
	}
};

template<typename T>
class Vector3 {
private:
	T x, y, z;
public:
	//bool CheckForNaNs() const { return std::isnan(x) || std::isnan(y) || std::isnan(z); }

	inline Vector3() { x = 0; y = 0; z = 0; }
	
	inline Vector3(const T a, const T b, const T c) {
		x = a; y = b; z = c; 
		//assert(!CheckForNaNs());
	}

	inline Vector3 (const Vector3<T> & vec) 
	{x = vec.x; y = vec.y; z = vec.z; }

	inline Vector3<T> operator + (const Vector3<T>& vec) const 
	{ return Vector3(x + vec.x, y + vec.y, z + vec.z);}

	inline Vector3<T> operator - (const Vector3<T>& vec) const
	{ return Vector3(x - vec.x, y - vec.y, z - vec.z);}

	inline Vector3<T> operator + (const T a) const
	{ return Vector3(x + a, y + a, z + a);}

	inline Vector3<T> operator - (const T a) const
	{ return Vector3(x - a, y - a, z - a);}

	inline Vector3<T> operator * (const T a) const
	{ return Vector3(x*a, y*a, z*a);}

	inline Vector3<T> operator *(const Vector3<T>& vec) const
	{ return Vector3(x*vec.x, y*vec.y, z*vec.z);}

	inline Vector3<T> operator / (const T a) const{
		float inv = (float)1 / a;
		return Vector3(x * inv, y * inv, z * inv);
	}

	inline bool operator == (const Vector3<T>& vec) const
	{ return bool(x == vec.x && y == vec.y && z == vec.z);}

	inline bool operator != (const Vector3<T>& vec) const
	{ return bool(x != vec.x || y != vec.y || z != vec.z);}

	inline void negate()  
	{ return this->setValues(-x, -y, -z);}
	
	inline Vector3<T>& operator += (const Vector3<T>& vec){
		x += vec.x;
		y += vec.y;
		z += vec.z;
		return *this;
	}
	inline Vector3<T>& operator -= (const Vector3<T>& vec){
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		return *this;
	}
	template <typename V>
	inline Vector3<T>& operator *= (const V a){
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}
	template <typename V>
	inline Vector3<T>& operator /= (const V a){
		float inv = (float)1 / a;
		x *= a;
		y *= a;
		z *= a;
		return *this;
	}

	inline operator Vector4<T>();
	// End of overloaded operators

	inline void setX(const T a)
	{ x = a;}

	inline void setY(const T a)
	{ y = a;}

	inline void setZ(const T a)
	{ z = a;}

	inline void setValues(const T a, const T b, const T c)
	{ x = a, y = b, z = c;}

	inline T getX() const
	{ return x;}

	inline const T getY() const
	{ return y;}

	inline const T getZ() const
	{ return z;}

	inline T getDot(const Vector3<T>& vec) const
	{ return T(x*vec.x + y*vec.y + z*vec.z);}

	inline T getLen() const
	{ return std::sqrt(x*x + y*y + z*z);}

	inline T getLenSquared() const 
	{ return x*x + y*y + z*z;}
	
	inline void normalize() 
	{ *this /= this->getLen();}

	inline T getMinComponent()
	{
		return math3d::min(this->getX(), math3d::min(this->getY(), this->getZ()));
	}
	
	inline void cross(const Vector3<T>& vec) {
		return this->setValues
		(y* vec.z - z * vec.y,
		 z* vec.x - x * vec.z,
		 x* vec.y - y * vec.x);
	}

	inline Vector3<T> getCross(const Vector3<T>& vec) {
		return Vector3<T>(y* vec.z - z * vec.y,
					   z* vec.x - x * vec.z,
					   x* vec.y - y * vec.x);
	}

	inline void clamp(T length) {
		T len = this->getLenSquared();
		if (len <= length *length) 
		{ return;}
		*this *= length / std::sqrt(len);
	}
	friend inline std::ostream& operator<<(std::ostream& os, Vector3<T>& e) {
		os << e.getX() << " " << e.getY() << " " << e.getZ();
		return os;
	}
};



template <typename T>
class Vector4 {
private:
	T x, y, z, w;
public:
	bool CheckForNaNs() const { return std::isnan(x) || std::isnan(y) || std::isnan(z) || std::isnan(w); }

	inline Vector4() { x = 0; y = 0; z = 0; w = 0; }

	inline Vector4(const T a, const T b, const T c, const T d = 0) {
		x = a; y = b; z = c; w = d; 
		assert(!CheckForNaNs());
	}

	inline Vector4(const Vector4& vec) {
		x = vec.x; y = vec.y; z = vec.z; w = vec.w; }

	inline Vector4<T> operator + (const Vector4<T>& vec) const
	{ return Vector4(x + vec.x, y + vec.y, z + vec.z, w + vec.w);}

	inline Vector4<T> operator + ( Vector3<T>& vec) const
	{ return Vector4(x + vec.getX(), y + vec.getY(), z + vec.getZ());}

	inline Vector4<T> operator - (const Vector4<T>& vec) const
	{ return Vector4(x - vec.x, y - vec.y, z - vec.z, w - vec.w);}

	inline Vector4<T> operator - (Vector3<T>& vec) const
	{ return Vector4(x - vec.getX(), y - vec.getY(), z - vec.getZ());}

	inline Vector4<T> operator + (const T a) const
	{ return Vector4(x + a, y + a, z + a, w + a);}

	inline Vector4<T> operator - (const T a) const
	{ return Vector4(x - a, y - a, z - a, w -a);}

	template <typename V>
	inline Vector4<T> operator * (const V a) const
	{ return Vector4(x*a, y*a, z*a, w *a);}

	template <typename V>
	inline Vector4<T> operator / (const V a) const
	{
		float inv = (float)1 / a;
		return Vector4(x * a, y * a, z * a, w * a);
	}

	inline bool operator == (const Vector4<T>& vec) const
	{ return bool(x == vec.x && y == vec.y && z == vec.z && w == vec.w);}

	inline bool operator == (Vector3<T>& vec) const
	{ return bool(x == vec.getX() && y == vec.getY() && z == vec.getZ());}

	inline bool operator != (const Vector4<T>& vec) const
	{ return bool(x != vec.x || y != vec.y || z != vec.z || w != vec.w);}

	inline bool operator != (Vector3<T>& vec) const
	{ return bool(x != vec.getX() || y != vec.getY() || z != vec.getZ());}
	
	inline void negate()
	{
		return this->setValues(-x, -y, -z, -w);
	}

	inline operator Vector3<T>() const {
		return Vector3<T>(x, y, z);
	}

	inline Vector4<T>& operator += (const Vector4<T>& a) {
		x += a.x;
		y += a.y;
		z += a.z;
		w += a.w;
		return *this;
	}
	inline Vector4<T>& operator += (Vector3<T>& vec) {
		x += vec.getX();
		y += vec.getY();
		z += vec.getZ();
		return *this;

	}
	inline Vector4<T>& operator -= (const Vector4<T>& vec) {
		x -= vec.x;
		y -= vec.y;
		z -= vec.z;
		w -= vec.w;
		return *this;
	}
	inline Vector4<T>& operator -= (Vector3<T>& vec) {
		x -= vec.getX();
		y -= vec.getY();
		z -= vec.getZ();
	}
	template <typename V>
	inline Vector4<T>& operator *= (const V a) {
		x *= a;
		y *= a;
		z *= a;
		w *= w;
		return *this;
	}
	template <typename V>
	inline Vector4<T>& operator /= (const V a) {
		float inv = (float)1 / a;
		x *= a;
		y *= a;
		z *= a;
		w *= a;
		return *this;
	}
	// End of overloaded operators

	inline void setX(const T a)
	{
		x = a;
	}

	inline void setY(const T a)
	{
		y = a;
	}

	inline void setZ(const T a)
	{
		z = a;
	}
	
	inline void setW(const T a) 
	{
		w = a;
	}

	inline void setValues(const T a, const T b, const T c, const T d)
	{
		x = a, y = b, z = c, w = d;
	}

	inline void setValues(const T a, const T b, const T c)
	{
		x = a, y = b, z = c;
	}
	inline T getX() const
	{
		return x;
	}

	inline T getY() const
	{
		return y;
	}

	inline T getZ() const
	{
		return z;
	}
	
	inline T getW() const
	{
		return w;
	}

	inline T getDot(const Vector4<T>& vec) const
	{
		return T(x*vec.x + y*vec.y + z*vec.z + w*vec.w);
	}
	inline T getDot(Vector3<T>& a) const
	{
		return T(x*a.getX() + y*a.getY() + z*a.getZ());
	}
	inline T getLen() const
	{
		return std::sqrt(x*x + y*y + z*z+ w*w);
	}

	inline T getLenSquared() const
	{
		return x*x + y*y + z*z + w*w;
	}

	inline void normalize()
	{
		*this /= this->getLen();
	}
	
	inline void clamp(T length) {
		T len = this->getLenSquared();
		if (len <= length *length)
		{
			return;
		}
		*this *= length / std::sqrt(len);
	}
	friend inline std::ostream& operator<<(std::ostream& os, Vector4<T>& e) {
		os << e.getX() << " " << e.getY() << " " << e.getZ() << " "<< e.getW();
		return os;
	}
};


namespace vector {
	template <typename T>
	inline Vector4<T> Negate(Vector4<T>& vec)
	{
		return Vector4(-vec.getX(), -vec.getY(), -vec.getZ(), -vec.getW());
	}
	template <typename T>
	inline Vector3<T> Negate(Vector3<T>& vec)
	{
		return Vector3<T>(-vec.getX(), -vec.getY(), -vec.getZ());
	}

	template <typename T>
	inline Vector3<T> Cross(Vector3<T>& vec1, Vector3<T>& vec2) {
		return Vector3<T>{
				vec1.getY() * vec2.getZ() - vec1.getZ() * vec2.getY(),
				vec1.getZ() * vec2.getX() - vec1.getX() * vec2.getZ(),
				vec1.getX() * vec2.getY() - vec1.getY() * vec2.getX()
		};
	}

	template <typename T>
	inline T Dot( Vector3<T> &vec1,  Vector3<T> &vec2)
	{
		return vec1.getX() * vec2.getX() + vec1.getZ() * vec2.getZ() + vec1.getY() * vec2.getY();
	}
	template <typename T>
	inline T Dot( Vector4<T> &vec1,  Vector3<T> &vec2)
	{
		return vec1.getX() * vec2.getX() + vec1.getZ() * vec2.getZ() + vec1.getY() * vec2.getY();
	}

	template <typename T>
	inline T Dot( Vector3<T> &vec1,  Vector4<T> &vec2)
	{
		return vec1.getX() * vec2.getX() + vec1.getZ() * vec2.getZ() + vec1.getY() * vec2.getY();
	}

	template <typename T>
	inline T Dot( Vector4<T> &vec1,  Vector4<T> &vec2)
	{
		return vec1.getX() * vec2.getX() + vec1.getZ() * vec2.getZ() + vec1.getY() * vec2.getY() + vec1.w * vec2.w;
	}

	template <typename T>
	inline double DDot(Vector3<T> &vec1, Vector3<T> &vec2)
	{
		return vec1.getX() * vec2.getX() + vec1.getZ() * vec2.getZ() + vec1.getY() * vec2.getY();
	}
	template <typename T>
	inline double DDot(Vector4<T> &vec1, Vector3<T> &vec2)
	{
		return vec1.getX() * vec2.getX() + vec1.getZ() * vec2.getZ() + vec1.getY() * vec2.getY();
	}

	template <typename T>
	inline double DDot(Vector3<T> &vec1, Vector4<T> &vec2)
	{
		return vec1.getX() * vec2.getX() + vec1.getZ() * vec2.getZ() + vec1.getY() * vec2.getY();
	}

	template <typename T>
	inline double DDot(Vector4<T> &vec1, Vector4<T> &vec2)
	{
		return vec1.getX() * vec2.getX() + vec1.getZ() * vec2.getZ() + vec1.getY() * vec2.getY() + vec1.w * vec2.w;
	}

	template <typename T>
	inline T AbsDot(const Vector3<T> &vec1, const Vector3<T> &vec2)
	{
		return std::abs(math3d::Dot(vec1, vec2));
	}

	template <typename T>
	inline T AbsDot(const Vector4<T> &vec1, const Vector4<T> &vec2)
	{
		return std::abs(math3d::Dot(vec1, vec2));
	}

	template <typename T>
	inline Vector3<T> Normalize(const Vector3<T> &x) {
		double mg = sqrt(x.getX()*x.getX() + x.getY() * x.getY() + x.getZ() * x.getZ());
		return Vector3f(x.getX() / mg, x.getY() / mg, x.getZ() / mg);
	}

	template <typename T>
	inline Vector4<T> Normalize(const Vector4<T> &x) {
		double mg = sqrt(x.getX()*x.getX() + x.getY() * x.getY() + x.getZ() * x.getZ()+x.getW() * x.getW() );
		return Vector4f(x.getX() / mg, x.getY() / mg, x.getZ() / mg,x.getW()/mg);
	}

}
	template <typename T>
	Vector3<T>::operator Vector4<T>() {
		return Vector4<T>(x, y, z);
	}



typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;
typedef Vector4<float> Vector4f;
typedef Vector4<int> Vector4i;
typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;