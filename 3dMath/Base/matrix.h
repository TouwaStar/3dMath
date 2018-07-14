#pragma once
#include <iosfwd>

template <typename T>
class Matrix3 {
private:
	Vector3<T> el[3];
public:
	inline Matrix3( const T& xx, const T& xy, const T& xz,
					const T& yx, const T& yy, const T& yz,
					const T& zx, const T& zy, const T& zz){
		this->setValues(xx, xy, xz,
						yx, yy, yz,
						zx, zy, zz);
	}
	inline Matrix3(const Vector3<T> Vectors[3]) {
		el[0] = Vectors[0];
		el[1] = Vectors[1];
		el[2] = Vectors[2];
	}
	inline Matrix3(const Vector3<T>& a,const Vector3<T>& b, const Vector3<T>& c) {
		el[0] = a;
		el[1] = b;
		el[2] = c;
	}
	inline Matrix3(const Matrix3<T>& m3) {
		el[0] = m3.el[0];
		el[1] = m3.el[1];
		el[2] = m3.el[2];
	}
	void inline setValues(const T& xx, const T& xy, const T& xz,
					      const T& yx, const T& yy, const T& yz,
						  const T& zx, const T& zy, const T& zz) {
		el[0].setValues(xx, xy, xz);
		el[1].setValues(yx, yy, yz);
		el[2].setValues(zx, zy, zz);
	}
	void inline setValues(const Vector3<T>& a, const Vector3<T>& b, const Vector3<T>& c) {
		el[0] = a;
		el[1] = b;
		el[2] = c;
	}
	Vector3<T> inline *getVectors() {
		return el;
	}
	inline void negate() {
		this->setValues(-el[0].getX(), -el[0].getY(), -el[0].getZ(),
						-el[1].getX(), -el[1].getY(), -el[1].getZ(),
						-el[2].getX(), -el[2].getY(), -el[2].getZ());
	}
	inline Matrix3<T>& operator += (const Matrix3<T>& m) {
		el[0] += m.el[0];
		el[1] += m.el[1];
		el[2] += m.el[2];
		return *this;
	}
	inline Matrix3<T>& operator -= (const Matrix3<T>& m) {
		el[0] -= m.el[0];
		el[1] -= m.el[1];
		el[2] -= m.el[2];
		return *this;
	}
	inline Matrix3<T> operator + (const Matrix3<T>& m) 
	{ return Matrix3(el[0] + m.el[0], el[1] + m.el[1], el[2] + m.el[2]);}
	
	inline Matrix3<T> operator - (const Matrix3<T>& m)
	{ return Matrix3(el[0] - m.el[0], el[1] - m.el[1], el[2] - m.el[2]);}

	Matrix3<T> operator * (Matrix3<T>& m)
	{
		return Matrix3(
			((el[0].getX() * m.el[0].getX()) +
			(el[0].getY() * m.el[1].getX()) +
			(el[0].getZ() * m.el[2].getX())),

			((el[0].getX() * m.el[0].getY()) +
			(el[0].getY() * m.el[1].getY()) +
			(el[0].getZ() * m.el[2].getY())),

			((el[0].getX() * m.el[0].getZ()) +
			(el[0].getY() * m.el[1].getZ()) +
			(el[0].getZ() * m.el[2].getZ())),

			((el[1].getX() * m.el[0].getX()) +
			(el[1].getY() * m.el[1].getX()) +
			(el[1].getZ() * m.el[2].getX())),

			((el[1].getX() * m.el[0].getY()) +
			(el[1].getY() * m.el[1].getY()) +
			(el[1].getZ() * m.el[2].getY())),

			((el[1].getX() * m.el[0].getZ()) +
			(el[1].getY() * m.el[1].getZ()) +
			(el[1].getZ() * m.el[2].getZ())),

			((el[2].getX() * m.el[0].getX()) +
			(el[2].getY() * m.el[1].getX()) +
			(el[2].getZ() * m.el[2].getX())),

			((el[2].getX() * m.el[0].getY()) +
			(el[2].getY() * m.el[1].getY()) +
			(el[2].getZ() * m.el[2].getY())),

			((el[2].getX() * m.el[0].getZ()) +
			(el[2].getY() * m.el[1].getZ()) +
			(el[2].getZ() * m.el[2].getZ())));
			
	}
	inline void transpose() {
		this->setValues(Vector3<T>(el[0].getX(), el[1].getX(),el[2].getX()),
						Vector3<T>(el[0].getY(),el[1].getY(),el[2].getY()),
						Vector3<T>(el[0].getZ(),el[1].getZ(),el[2].getZ()));
	}

	friend inline std::ostream& operator<<(std::ostream& os,Matrix3<T>& e) {
		os  << e.el[0].getX() << " " << e.el[0].getY() << " " << e.el[0].getZ() << std::endl
			<< e.el[1].getX() << " " << e.el[1].getY() << " " << e.el[1].getZ() << std::endl
			<< e.el[2].getX() << " " << e.el[2].getY() << " " << e.el[2].getZ() << std::endl;
		return os;
	}
};


template <typename T>
class Matrix4 {
private:
	Vector4<T> el[4];
public:
	inline Matrix4() {
		this->setValues(1.f, 0, 0, 0,
						0, 1.f, 0, 0,
						0, 0, 1.f, 0,
						0, 0, 0, 1.f);
	}
	inline Matrix4(const T& xx, const T& xy, const T& xz, const T& xw,
				   const T& yx, const T& yy, const T& yz, const T& yw,
				   const T& zx, const T& zy, const T& zz, const T& zw,
				   const T& wx, const T& wy, const T& wz, const T& ww) {
		this->setValues(xx, xy, xz, xw,
						yx, yy, yz, yw,
						zx, zy, zz, zw,
						wx, wy, wz, ww);
	}

	inline Matrix4(const Vector4<T> Vectors[4]) {
		el[0] = Vectors[0];
		el[1] = Vectors[1];
		el[2] = Vectors[2];
		el[3] = Vectors[3];
	}
	inline Matrix4(const Vector4<T> a, const Vector4<T> b, const Vector4<T> c,const Vector4<T> d) {
		el[0] = a;
		el[1] = b;
		el[2] = c;
		el[3] = d;
	}
	inline Matrix4(const T a[4][4]) {
		el[0] = (a[0][0], a[0][1], a[0][2], a[0][3]);
		el[1] = (a[1][0], a[1][1], a[1][2], a[1][3]);
		el[2] = (a[2][0], a[2][1], a[2][2], a[2][3]);
		el[3] = (a[3][0], a[3][1], a[3][2], a[3][3]);
	}
	inline Matrix4(const Matrix4<T>& m4) {
		el[0] = m4.el[0];
		el[1] = m4.el[1];
		el[2] = m4.el[2];
		el[3] = m4.el[3];
	}
	inline Matrix4<T>& operator += (const Matrix4<T>& m) {
		el[0] += m.el[0];
		el[1] += m.el[1];
		el[2] += m.el[2];
		el[3] += m.el[3];
		return *this;
	}
	inline Matrix4<T>& operator -= (const Matrix4<T>& m) {
		el[0] -= m.el[0];
		el[1] -= m.el[1];
		el[2] -= m.el[2];
		el[3] -= m.el[3];
		return *this;
	}
	inline Matrix4<T> operator + (const Matrix4<T>& m)
	{
		return Matrix4(el[0] + m.el[0], el[1] + m.el[1], el[2] + m.el[2],el[3] + m.el[3]);
	}

	inline Matrix4<T> operator - (const Matrix4<T>& m)
	{
		return Matrix4(el[0] - m.el[0], el[1] - m.el[1], el[2] - m.el[2], el[3] - m.el[3]);
	}

	Matrix4<T> operator * ( Matrix4<T>& m)
	{
		return Matrix4(
			((el[0].getX() * m.el[0].getX()) +
			(el[0].getY() * m.el[1].getX()) +
			(el[0].getZ() * m.el[2].getX())+
			(el[0].getW() * m.el[3].getX())),

			((el[0].getX() * m.el[0].getY()) +
			(el[0].getY() * m.el[1].getY()) +
			(el[0].getZ() * m.el[2].getY()) +
			(el[0].getW() * m.el[3].getY())),

			((el[0].getX() * m.el[0].getZ()) +
			(el[0].getY() * m.el[1].getZ()) +
			(el[0].getZ() * m.el[2].getZ()) +
			(el[0].getW() * m.el[3].getZ())),

			((el[0].getX() * m.el[0].getW()) +
			(el[0].getY() * m.el[1].getW()) +
			(el[0].getZ() * m.el[2].getW()) +
			(el[0].getW() * m.el[3].getW())),

			((el[1].getX() * m.el[0].getX()) +
			(el[1].getY() * m.el[1].getX()) +
			(el[1].getZ() * m.el[2].getX()) +
			(el[1].getW() * m.el[3].getX())),

			((el[1].getX() * m.el[0].getY()) +
			(el[1].getY() * m.el[1].getY()) +
			(el[1].getZ() * m.el[2].getY()) +
			(el[1].getW() * m.el[3].getY())),

			((el[1].getX() * m.el[0].getZ()) +
			(el[1].getY() * m.el[1].getZ()) +
			(el[1].getZ() * m.el[2].getZ()) +
			(el[1].getW() * m.el[3].getZ())),

			((el[1].getX() * m.el[0].getW()) +
			(el[1].getY() * m.el[1].getW()) +
			(el[1].getZ() * m.el[2].getW()) +
			(el[1].getW() * m.el[3].getW())),

			((el[2].getX() * m.el[0].getX()) +
			(el[2].getY() * m.el[1].getX()) +
			(el[2].getZ() * m.el[2].getX()) +
			(el[2].getW() * m.el[3].getX())),

			((el[2].getX() * m.el[0].getY()) +
			(el[2].getY() * m.el[1].getY()) +
			(el[2].getZ() * m.el[2].getY()) +
			(el[2].getW() * m.el[3].getY())),

			((el[2].getX() * m.el[0].getZ()) +
			(el[2].getY() * m.el[1].getZ()) +
			(el[2].getZ() * m.el[2].getZ()) +
			(el[2].getW() * m.el[3].getZ())),
				
			((el[2].getX() * m.el[0].getW()) +
			(el[2].getY() * m.el[1].getW()) +
			(el[2].getZ() * m.el[2].getW()) +
			(el[2].getW() * m.el[3].getW())),

			((el[3].getX() * m.el[0].getX()) +
			(el[3].getY() * m.el[1].getX()) +
			(el[3].getZ() * m.el[2].getX()) +
			(el[3].getW() * m.el[3].getX())),

			((el[3].getX() * m.el[0].getY()) +
			(el[3].getY() * m.el[1].getY()) +
			(el[3].getZ() * m.el[2].getY()) +
			(el[3].getW() * m.el[3].getY())),

			((el[3].getX() * m.el[0].getZ()) +
			(el[3].getY() * m.el[1].getZ()) +
			(el[3].getZ() * m.el[2].getZ()) +
			(el[3].getW() * m.el[3].getZ())),

			((el[3].getX() * m.el[0].getW()) +
			(el[3].getY() * m.el[1].getW()) +
			(el[3].getZ() * m.el[2].getW()) +
			(el[3].getW() * m.el[3].getW())));


	}


	void inline setValues(const T& xx, const T& xy, const T& xz, const T& xw,
					      const T& yx, const T& yy, const T& yz, const T& yw,
						  const T& zx, const T& zy, const T& zz, const T& zw,
						  const T& wx, const T& wy, const T& wz, const T& ww) {
		el[0].setValues(xx, xy, xz, xw);
		el[1].setValues(yx, yy, yz, yw);
		el[2].setValues(zx, zy, zz, zw);
		el[3].setValues(wx, wy, wz, ww);
	}
	void inline setValues(const T& xx, const T& xy, const T& xz, const T& xw,
		const T& yx, const T& yy, const T& yz, const T& yw,
		const T& zx, const T& zy, const T& zz, const T& zw) {
		el[0].setValues(xx, xy, xz, xw);
		el[1].setValues(yx, yy, yz, yw);
		el[2].setValues(zx, zy, zz, zw);
	}
	void inline setValues(const Vector4<T>& a, const Vector4<T>& b, const Vector4<T>& c, const Vector4<T>& d) {
		el[0] = a;
		el[1] = b;
		el[2] = c;
		el[3] = d;
	}

	Vector4<T> inline *getVectors() {
		return el;
	}

	inline void negate() {
		this->setValues(-el[0].getX(), -el[0].getY(), -el[0].getZ(), -el[0].getW(),
						-el[1].getX(), -el[1].getY(), -el[1].getZ(), -el[1].getW(),
						-el[2].getX(), -el[2].getY(), -el[2].getZ(), -el[2].getW(),
						-el[3].getX(), -el[3].getY(), -el[3].getZ(), -el[3].getW() );
	}

	friend inline std::ostream& operator<<(std::ostream& os, Matrix4<T>& e) {
		os  << e.el[0].getX() << " " << e.el[0].getY() << " " << e.el[0].getZ() << " " << e.el[0].getW() << std::endl
			<< e.el[1].getX() << " " << e.el[1].getY() << " " << e.el[1].getZ() << " " << e.el[1].getW() << std::endl
			<< e.el[2].getX() << " " << e.el[2].getY() << " " << e.el[2].getZ() << " " << e.el[2].getW() << std::endl
			<< e.el[3].getX() << " " << e.el[3].getY() << " " << e.el[3].getZ() << " " << e.el[3].getW() << std::endl;
		return os;
	}

};

namespace matrix {
	template <typename T>
	inline Matrix3<T> Negate(Matrix3<T>& a)
	{
		return Matrix3<T>(vector::Negate(a.getVectors()[0]),
			vector::Negate(a.getVectors()[1]),
			vector::Negate(a.getVectors()[2]));
	}
	template <typename T>
	inline Matrix4<T> Negate(Matrix4<T>& a)
	{
		return Matrix4<T>(math3d::Negate(a.getVectors()[0]),
			vector::Negate(a.getVectors()[1]),
			vector::Negate(a.getVectors()[2]));
	}
	template <typename T>
	inline Matrix3<T> Transpose(Matrix3<T>& a)
	{
		return Matrix3<T>(Vector3(a.getVectors()[0].getX(), a.getVectors()[1].getX(), a.getVectors()[2].getX()),
			Vector3(a.getVectors()[0].getY(), a.getVectors()[1].getY(), a.getVectors()[2].getY()),
			Vector3(a.getVectors()[0].getZ(), a.getVectors()[1].getZ(), a.getVectors()[2].getZ()));
	}
	template <typename T>
	inline Matrix4<T> Transpose(Matrix4<T>& a)
	{
		return Matrix4<T>(Vector4<T>(a.getVectors()[0].getX(), a.getVectors()[1].getX(), a.getVectors()[2].getX(),a.getVectors()[3].getX()),
			Vector4<T>(a.getVectors()[0].getY(), a.getVectors()[1].getY(), a.getVectors()[2].getY(), a.getVectors()[3].getY()),
			Vector4<T>(a.getVectors()[0].getZ(), a.getVectors()[1].getZ(), a.getVectors()[2].getZ(), a.getVectors()[3].getZ()),
			Vector4<T>(a.getVectors()[0].getW(), a.getVectors()[1].getW(), a.getVectors()[2].getW(), a.getVectors()[3].getW()));
	}
	/* pbrt, transform.cpp 82 General matrix Inversion is a complicated topic,
	Possibly look at MESA GLU*/
	template <typename T>
	Matrix4<T> Inverse(const Matrix4<T> &m) {
		int indxc[4], indxr[4];
		int ipiv[4] = { 0, 0, 0, 0 };
		Float minv[4][4];
		memcpy(minv, m.m, 4 * 4 * sizeof(Float));
		for (int i = 0; i < 4; i++) {
			int irow = 0, icol = 0;
			Float big = 0.f;
			// Choose pivot
			for (int j = 0; j < 4; j++) {
				if (ipiv[j] != 1) {
					for (int k = 0; k < 4; k++) {
						if (ipiv[k] == 0) {
							if (std::abs(minv[j][k]) >= big) {
								big = Float(std::abs(minv[j][k]));
								irow = j;
								icol = k;
							}
						}
						else if (ipiv[k] > 1)
							Error("Singular matrix in MatrixInvert");
					}
				}
			}
			++ipiv[icol];
			// Swap rows _irow_ and _icol_ for pivot
			if (irow != icol) {
				for (int k = 0; k < 4; ++k) std::swap(minv[irow][k], minv[icol][k]);
			}
			indxr[i] = irow;
			indxc[i] = icol;
			if (minv[icol][icol] == 0.f) Error("Singular matrix in MatrixInvert");

			// Set $m[icol][icol]$ to one by scaling row _icol_ appropriately
			Float pivinv = 1. / minv[icol][icol];
			minv[icol][icol] = 1.;
			for (int j = 0; j < 4; j++) minv[icol][j] *= pivinv;

			// Subtract this row from others to zero out their columns
			for (int j = 0; j < 4; j++) {
				if (j != icol) {
					Float save = minv[j][icol];
					minv[j][icol] = 0;
					for (int k = 0; k < 4; k++) minv[j][k] -= minv[icol][k] * save;
				}
			}
		}
		// Swap columns to reflect permutation
		for (int j = 3; j >= 0; j--) {
			if (indxr[j] != indxc[j]) {
				for (int k = 0; k < 4; k++)
					std::swap(minv[k][indxr[j]], minv[k][indxc[j]]);
			}
		}
		return Matrix4x4(minv);
	}


}

typedef Matrix3<float> Matrix3f;
typedef Matrix3<int> Matrix3i;
typedef Matrix4<float> Matrix4f;
typedef Matrix4<int> Matrix4i;