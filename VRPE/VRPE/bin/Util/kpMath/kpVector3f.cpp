#include "kpVector3f.h"


JackFruitEngine::kpVector3f::kpVector3f()
{
	x=y=z=0;
}
JackFruitEngine::kpVector3f::kpVector3f(float a,float b)
{
	x=a;
	y=b;
	z=0;
}

JackFruitEngine::kpVector3f::kpVector3f(float a,float b,float c)
{
	x=a;
	y=b;
	z=c;
}
		
float JackFruitEngine::kpVector3f::Max()
{
	float max;
	if(x > y)
	{
		max = x;
	}
	else
	{
		max = y;
	}
	if(z > max)
	{
		max = z;
	}
	else
	{
		return max;
	}
	return max;
}

float JackFruitEngine::kpVector3f::dotProduct(const kpVector3f& vec2)
{
	return (x*vec2.x+y*vec2.y+z*vec2.z);
}

JackFruitEngine::kpVector3f JackFruitEngine::kpVector3f::crossProduct(const kpVector3f& vec2)
{
	kpVector3f tmp;

	tmp.x = y * vec2.z - z * vec2.y;
	tmp.x = z * vec2.x - x * vec2.z;
	tmp.x = x * vec2.y - y * vec2.x;

	return tmp;
}

float JackFruitEngine::kpVector3f::length()
{
	return sqrt(x*x+y*y+z*z);
}

void JackFruitEngine::kpVector3f::normalize()
{
	float len=length();
	if(len!=0)
	{
		x/=len;
		y/=len;
		z/=len;
	}
}

JackFruitEngine::kpVector3f JackFruitEngine::kpVector3f::scalar(float scale)
{
	kpVector3f tmp;
	tmp.x = x * scale;
	tmp.y = y * scale;
	tmp.z = z * scale;

	return tmp;
}


void JackFruitEngine::kpVector3f::change(float a,float b,float c)
{
	x=a;
	y=b;
	z=c;
}

void JackFruitEngine::kpVector3f::change(kpVector3f vec2)
{
	x=vec2.x;
	y=vec2.y;
	z=vec2.z;
}

void JackFruitEngine::kpVector3f::changeX(float a)
{
	x=a;
}
void JackFruitEngine::kpVector3f::changeY(float a)
{
	y=a;
}
void JackFruitEngine::kpVector3f::changeZ(float a)
{
	z=a;
}
		
JackFruitEngine::kpVector3f JackFruitEngine::kpVector3f::operator+(const kpVector3f& vec2)
{
	return kpVector3f(x+vec2.x,y+vec2.y,z+vec2.z);
}

JackFruitEngine::kpVector3f JackFruitEngine::kpVector3f::operator-(const kpVector3f& vec2)
{
	return kpVector3f(x-vec2.x,y-vec2.y,z-vec2.z);
}
JackFruitEngine::kpVector3f JackFruitEngine::kpVector3f::operator*(const kpVector3f& vec2)
{
	kpVector3f tmp;

	tmp.x = y * vec2.z - z * vec2.y;
	tmp.x = z * vec2.x - x * vec2.z;
	tmp.x = x * vec2.y - y * vec2.x;

	return tmp;
}

JackFruitEngine::kpVector3f JackFruitEngine::kpVector3f::operator*(float num)
{
	return kpVector3f(x*num,y*num,z*num);
}

JackFruitEngine::kpVector3f JackFruitEngine::kpVector3f::operator/(float num)
{
	if(num!=0)
		return kpVector3f(x/num,y/num,z/num);
	else
		return kpVector3f();
}

JackFruitEngine::kpVector3f& JackFruitEngine::kpVector3f::operator+=(const kpVector3f& vec2)
{
	x+=vec2.x;
	y+=vec2.y;
	z+=vec2.z;
	return *this;
}

JackFruitEngine::kpVector3f& JackFruitEngine::kpVector3f::operator-=(const kpVector3f& vec2)
{
	x-=vec2.x;
	y-=vec2.y;
	z-=vec2.z;
	return *this;
}

JackFruitEngine::kpVector3f& JackFruitEngine::kpVector3f::operator*=(float num)
{
	x*=num;
	y*=num;
	z*=num;
	return *this;
}

JackFruitEngine::kpVector3f& JackFruitEngine::kpVector3f::operator/=(float num)	
{
	if(num!=0)
	{
		x/=num;
		y/=num;
		z/=num;
	}
	return *this;
}

bool JackFruitEngine::kpVector3f::operator==(const kpVector3f vec2)
{
	return (x==vec2.x && y==vec2.y && z==vec2.z);
}
bool JackFruitEngine::kpVector3f::operator==(const int i)
{
	return (x==i && y==i && z==i);
}
bool JackFruitEngine::kpVector3f::operator=(const int i)
{
	return (x==i && y==i && z==i);
}
bool JackFruitEngine::kpVector3f::operator!=(const kpVector3f vec2)
{
	return !(*this==vec2);
}
		
/*std::ostream& operator<<(std::ostream& out,const kpVector3f& vec)
{
	out << vec.x << " " << vec.y << " " << vec.z << std::endl;
	return out;
}*/

