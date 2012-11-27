
#ifndef __H_GEOMETRY_H_
#define __H_GEOMETRY_H_

#include "H_Standard.h"

#include <fstream>
#include <math.h>
#include <assert.h>

#define FOR_I(code) for(unsigned int i=dim;i--;) {code}
//~same as:
//#define FOR_I(code) for(unsigned int i=0; i<dim ; i++) {code}

template <unsigned int dim, class type> class Point
{
//private:
public:
	enum t_dimName {X=0,Y=1,Z=2,W=3};
	type p[dim];
public:
	inline type &operator[] (unsigned int i) {return p[i];}
	inline const type &operator[] (unsigned int i) const {return p[i];}
	inline Point() {}
	template <class type_b> Point(const Point<dim,type_b> &A) {FOR_I(p[i]=type(A[i]);)}
	inline Point(type x, type y)
		{assert(dim==2); p[X]=x;p[Y]=y;}
	inline Point(type x, type y, type z)
		{assert(dim==3); p[X]=x;p[Y]=y;p[Z]=z;}
	inline Point(type x, type y, type z, type w)
		{assert(dim==4); p[X]=x;p[Y]=y;p[Z]=z;p[W]=w;}
	inline const type &x() const {return p[X];}
	inline const type &y() const {return p[Y];}
	inline const type &z() const {return p[Z];}
	inline const type &w() const {return p[W];}
	inline type &x() {return p[X];}
	inline type &y() {return p[Y];}
	inline type &z() {return p[Z];}
	inline type &w() {return p[W];}
	bool isNull() const
		{FOR_I(if(p[i]!=0) return false;) return true;}
	void reset()
		{FOR_I(p[i]=0;)}
	bool operator== (const Point &A) const
		{FOR_I(if(p[i]!=A.p[i]) return false;) return true;}
	bool operator!= (const Point &A) const
		{return !(*this == A);}
	Point operator* (type e) const
		{Point tmp;FOR_I(tmp.p[i]=p[i]*e;) return tmp;}
	Point operator- (const Point &A) const
		{Point tmp;FOR_I(tmp.p[i]=p[i]-A.p[i];) return tmp;}
	Point operator- () const
		{Point tmp;FOR_I(tmp.p[i]=-p[i];) return tmp;}
	Point operator+ (const Point &A) const
		{Point tmp;FOR_I(tmp.p[i]=p[i]+A.p[i];) return tmp;}
	type operator* (const Point &A) const
		{type sum=0;FOR_I(sum+=p[i]*A.p[i];) return sum;}
	Point operator/ (type e) const
		{Point tmp;FOR_I(tmp.p[i]=p[i]/e;) return tmp;}
	Point &operator/= (type e)
		{FOR_I(p[i]/=e;) return *this;}
	Point &operator+= (const Point &A)
		{FOR_I(p[i]+=A.p[i];) return *this;}
	Point &operator-= (const Point &A)
		{FOR_I(p[i]-=A.p[i];) return *this;}
	
	type norm() const {type sum=0; FOR_I(sum+=p[i]*p[i];) return type(sqrt(double(sum)));}
	type normalize() {type tmp=norm();*this=*this/tmp;return tmp;}
	type normalize(type length) {type tmp=norm();*this=*this*(length/tmp);return tmp;}
	type distance(const Point &A) const {return (*this-A).norm();}

//friend istream & operator>> <dim,type>(istream &in, Point<dim,type> &A);
//friend ostream & operator<< <dim,type>(ostream &out, const Point<dim,type> &A);
};

//nonmember functions:
template <unsigned int dim, class type>
istream & operator>> (istream &in, Point<dim,type> &A)
{for(unsigned int i=0; i<dim ; i++){in>>A.p[i];} return in;} //don't use FOR_I here!!

template <unsigned int dim, class type>
ostream & operator<< (ostream &out, const Point<dim,type> &A)
{for(unsigned int i=0; i<dim ; i++){out<<A.p[i]<<" ";} return out;} //don't use FOR_I here!!

template <unsigned int dim, class type>
Point<dim,type> operator* (type e, const Point<dim,type> &A)
{
	Point<dim,type> tmp;
	FOR_I(tmp.p[i]=e*A.p[i];)
	return tmp;
}

template <class type>
Point<3,type> operator^ (const Point<3,type> &A, const Point<3,type> &B)
{
	return Point<3,type>(
		(A.y()*B.z()-A.z()*B.y()),
		(A.z()*B.x()-A.x()*B.z()),
		(A.x()*B.y()-A.y()*B.x())
	);
}

template <class type> void RotateAround(Point<3,type> &A, Point<3,type> B)
{
	Point<3,type> tmp(A);
	type angle = B.normalize();

	type s, c;
	type xx, yy, zz, xy, yz, zx, xs, ys, zs, one_c;

	s = (type)sin((double)angle);
	c = (type)cos((double)angle);

	if (angle>0)
	{
		xx = B.x() * B.x();
		yy = B.y() * B.y();
		zz = B.z() * B.z();
		xy = B.x() * B.y();
		yz = B.y() * B.z();
		zx = B.z() * B.x();
		xs = B.x() * s;
		ys = B.y() * s;
		zs = B.z() * s;
		one_c = 1 - c;

		A.x() = ((one_c * xx) + c)*tmp.x() + ((one_c * xy) - zs)*tmp.y() + ((one_c * zx) + ys)*tmp.z();
		A.y() = ((one_c * xy) + zs)*tmp.x() + ((one_c * yy) + c)*tmp.y() + ((one_c * yz) - xs)*tmp.z();
		A.z() = ((one_c * zx) - ys)*tmp.x() + ((one_c * yz) + xs)*tmp.y() + ((one_c * zz) + c)*tmp.z();
	}
}

typedef Point<2,REAL> Point2D;
typedef Point<3,REAL> Point3D;
//#include "Point3D.h"

class HRect
{
public:
	REAL left, top, right, bottom;
public:
	HRect();
	HRect(REAL l, REAL t, REAL r, REAL b );
	HRect(const Point2D &A, const Point2D &B);
	REAL GetWidth() const;
	REAL GetHeight() const;
	bool IsContained(const Point2D &APoint2D);
	bool IsContained(const HRect &HRect);
	void Scale(REAL factor);
	void Move(const Point2D &Vector);
	Point2D GetCenter() const;
};

class Ref
{
public:
	Point3D X,Y,Z;
	Point3D Position;
	Point3D Speed,Momentum;
	static REAL TimeIncrement;

public:
	Ref();
	Ref(const Point3D &APosition, const Point3D &AY, const Point3D &AZ);
	void reset();
	Point3D GetAbsCoord(const Point3D &RelPos) const;
	Ref GetRef(const Point3D &RelPos) const;
	Ref GetRef(const Ref &ARef) const;
	void Straighten();
	void Move(const Point3D &point);
	void Rotate(const Point3D &Axe);
	Point3D GetDirection() const;
	Point3D GetUp() const;
	Point3D GetW() const;
	Point3D GetX() const;
	Point3D GetY() const;
	Point3D GetZ() const;
};
istream &operator >> (istream &infile, Ref &ARef);
ostream &operator << (ostream &outfile, const Ref &ARef);

class FixedVector
{
public:
	FixedVector();
	FixedVector(const Point3D &APosition, const Point3D &AValue);
	void reset();
public:
	Point3D Position;
	Point3D Value;
};

class InertRef : public Ref
{
private:
	Point3D SigmaForce; //the sum of the forces
	Point3D SigmaForceMoment; //sum of the force's moment
	REAL Mass, RotInertia;
public:
	inline REAL GetMass() {return Mass;}
	InertRef();
	InertRef(REAL AMass, REAL ARotInertia);
	void Apply(const FixedVector &AForce);
	void TimeClick();
};

class Contact
{
public:
	Contact();
public:
	Point3D Position;
	Point3D Normal;
	int SurfaceType;
	bool Found;
};

unsigned int LargestPowOf2(unsigned int x);


#endif //__H_GEOMETRY_H_
