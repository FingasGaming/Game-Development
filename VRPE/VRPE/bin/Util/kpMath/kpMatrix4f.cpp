#include "kpMatrix4f.h"


JackFruitEngine::kpMatrix4f::kpMatrix4f()
{
	for(int i = 0;i < 4; i++)
		for(int j = 0; j < 4; j++)
			m[i][j] = 0;
}
JackFruitEngine::kpMatrix4f::kpMatrix4f(float matrix[16])
{
	*this = toMatrix4f(matrix);
}
JackFruitEngine::kpMatrix4f::~kpMatrix4f()
{
	//for(int i = 0; i < 4; i++)
	{
		//delete [] m[i];
	}
	//delete [] m;
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpMatrix4f::transpose()
{
	kpMatrix4f t;
	for (int j = 0; j < 4; j++) {
		for (int i = 0; i < 4; i++) {
			t.m[i][j] = m[j][i];
		}
	}
	return t;
}
JackFruitEngine::kpVector3f JackFruitEngine::kpMatrix4f::transform(kpVector3f r)
{
	kpVector3f r2;
	r2.change(r);
	return r2;
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpMatrix4f::identity()
{
	m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
	m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = 0;
	m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = 0;
	m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
	return *this;
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpMatrix4f::initTranslation(float x, float y, float z)
{
	//m = new float*[4]();

	m[0][0] = 1; m[0][1] = 0; m[0][2] = 0; m[0][3] = x;
	m[1][0] = 0; m[1][1] = 1; m[1][2] = 0; m[1][3] = y;
	m[2][0] = 0; m[2][1] = 0; m[2][2] = 1; m[2][3] = z;
	m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
	return *this;
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpMatrix4f::initTranslation(kpVector3f &vec)
{
	//m = new float*[4]();

	m[0][0] = 1; 
	m[0][1] = 0;
	m[0][2] = 0; 
	m[0][3] = vec.x;

	m[1][0] = 0; 
	m[1][1] = 1; 
	m[1][2] = 0; 
	m[1][3] = vec.y;
		
	m[2][0] = 0; 
	m[2][1] = 0; 
	m[2][2] = 1; 
	m[2][3] = vec.z;
		
	m[3][0] = 0; 
	m[3][1] = 0; 
	m[3][2] = 0; 
	m[3][3] = 1;
	return *this;
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpMatrix4f::initRotation(float x, float y, float z)
{
	//m = new float*[4]();
	kpMatrix4f rx, ry, rz;

	x = (float)(RAD*x);
	y = (float)(RAD*y);
	z = (float)(RAD*z);

	rz.m[0][0] = (float)cos(z);	rz.m[0][1] = -(float)sin(z);	rz.m[0][2] = 0;	rz.m[0][3] = 0;
	rz.m[1][0] = (float)sin(z);	rz.m[1][1] = (float)cos(z);	rz.m[1][2] = 0;	rz.m[1][3] = 0;
	rz.m[2][0] = 0;	rz.m[2][1] = 0;	rz.m[2][2] = 1;	rz.m[2][3] = 0;
	rz.m[3][0] = 0;	rz.m[3][1] = 0;	rz.m[3][2] = 0;	rz.m[3][3] = 1;

	rx.m[0][0] = 1;	rx.m[0][1] = 0;	rx.m[0][2] = 0;	rx.m[0][3] = 0;
	rx.m[1][0] = 0;	rx.m[1][1] = (float)cos(x);	rx.m[1][2] = -(float)sin(x);	rx.m[1][3] = 0;
	rx.m[2][0] = 0;	rx.m[2][1] = (float)sin(x);	rx.m[2][2] = (float)cos(x);	rx.m[2][3] = 0;
	rx.m[3][0] = 0;	rx.m[3][1] = 0;	rx.m[3][2] = 0;	rx.m[3][3] = 1;

	ry.m[0][0] = (float)cos(y);	ry.m[0][1] = 0;	ry.m[0][2] = -(float)sin(y);	ry.m[0][3] = 0;
	ry.m[1][0] = 0;	ry.m[1][1] = 1;	ry.m[1][2] = 0;	ry.m[1][3] = 0;
	ry.m[2][0] = (float)sin(y);	ry.m[2][1] = 0;	ry.m[2][2] = (float)cos(y);	ry.m[2][3] = 0;
	ry.m[3][0] = 0;	ry.m[3][1] = 0;	ry.m[3][2] = 0;	ry.m[3][3] = 1;

	kpMatrix4f tmp  = rz.mul(ry.mul(rx));
		
	m[0][0] = tmp.m[0][0];
	m[0][1] = tmp.m[0][1];
	m[0][2] = tmp.m[0][2];
	m[0][3] = tmp.m[0][3];

	m[1][0] = tmp.m[1][0];
	m[1][1] = tmp.m[1][1];
	m[1][2] = tmp.m[1][2];
	m[1][3] = tmp.m[1][3];

	m[2][0] = tmp.m[2][0];
	m[2][1] = tmp.m[2][1];
	m[2][2] = tmp.m[2][2];
	m[2][3] = tmp.m[2][3];

	m[3][0] = tmp.m[3][0];
	m[3][1] = tmp.m[3][1];
	m[3][2] = tmp.m[3][2];
	m[3][3] = tmp.m[3][3];

	return *this;
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpMatrix4f::initRotation(kpVector3f &vec)
{
	return initRotation(vec.x, vec.y, vec.z);
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpMatrix4f::initScale(float x, float y, float z)
{
	//m = new float*[4]();
	m[0][0] = x; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
	m[1][0] = 0; m[1][1] = y; m[1][2] = 0; m[1][3] = 0;
	m[2][0] = 0; m[2][1] = 0; m[2][2] = z; m[2][3] = 0;
	m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
	return *this;
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpMatrix4f::initScale(kpVector3f &vec)
{
	//m = new float*[4]();
	m[0][0] = vec.x; m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
	m[1][0] = 0; m[1][1] = vec.y; m[1][2] = 0; m[1][3] = 0;
	m[2][0] = 0; m[2][1] = 0; m[2][2] = vec.z; m[2][3] = 0;
	m[3][0] = 0; m[3][1] = 0; m[3][2] = 0; m[3][3] = 1;
	return *this;
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpMatrix4f::projection(float width, float height, float zNear, float zFar, float fov)
{
	float tanHFOV = (float)tan((RAD*fov)/2);//half of FOV
	float aspec = width/height;
	float dRange = zNear - zFar;

	m[0][0] = 1.0f/(tanHFOV*aspec);	m[0][1] = 0;	m[0][2] = 0;	m[0][3] = 0;
	m[1][0] = 0;	m[1][1] = 1.0f/(tanHFOV*aspec);	m[1][2] = 0;	m[1][3] = 0;
	m[2][0] = 0;	m[2][1] = 0;	m[2][2] = (-zNear - zFar)/dRange;	m[2][3] = (2 * zNear * zFar / dRange);
	m[3][0] = 0;	m[3][1] = 0;	m[3][2] = 1;	m[3][3] = 0;
	return *this;
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpMatrix4f::View(kpVector3f &forward,kpVector3f &up)
{
	kpVector3f f = forward;
	f.normalize();

	kpVector3f r = up;
	r.normalize();
	r = r.crossProduct(f);

	kpVector3f u = f.crossProduct(r);

		
	return initRot(f, u, r);
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpMatrix4f::initRot(kpVector3f forward,kpVector3f up,kpVector3f right)
{
	//m = new float*[4]();
	kpVector3f f = forward;

	kpVector3f r = right;

	kpVector3f u = up;

	m[0][0] = r.x;	m[0][1] = r.y;	m[0][2] = r.z;	m[0][3] = 0;
	m[1][0] = u.x;	m[1][1] = u.y;	m[1][2] = u.z;	m[1][3] = 0;
	m[2][0] = f.x;	m[2][1] = f.y;	m[2][2] = f.z;	m[2][3] = 0;
	m[3][0] = 0;	m[3][1] = 0;	m[3][2] = 0;	m[3][3] = 1;
	return *this;
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpMatrix4f::ortho(float left, float right, float bottom, float top, float neara, float fara)
{//code ref from glm matrix4x4
	m[0][0] = 2.0f/(right - left); m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
	m[1][0] = 0; m[1][1] = 2.0f /(top - bottom); m[1][2] = 0; m[1][3] = 0;
	m[2][0] = 0; m[2][1] = 0; m[2][2] = -2.0f /(fara - neara); m[2][3] = 0;
	m[3][0] = (right + left) / (right - left); m[3][1] = (top + bottom)/(top - bottom); m[3][2] = ((fara + neara)/(fara - neara)); m[3][3] = 1;
	return *this;
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpMatrix4f::frustum(float left, float right, float bottom, float top, float neara, float fara)
{//code ref from glm matrix4x4
	m[0][0] = (1.0f *(neara) / (right - left)); m[0][1] = 0; m[0][2] = 0; m[0][3] = 0;
	m[1][0] = 0; m[1][1] = ((1.0f * neara) / (top - bottom)); m[1][2] = 0; m[1][3] = 0;
	m[2][0] = (right + left) / (right - left); m[2][1] = (top + bottom)/(top - bottom); m[2][2] = -(fara + neara) /(fara - neara); m[2][3] = -1;
	m[3][0] = 0; m[3][1] = 0; m[3][2] = -(1.0f *fara * neara) / (fara - neara); m[3][3] = 1;
	return *this;
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpMatrix4f::initRotationFromVectors(kpVector3f& n, kpVector3f& v, kpVector3f& u)
{
	(m)[0][0] = u.x;   (m)[1][0] = u.y;   (m)[2][0] = u.z;   (m)[3][0] = (0);
	(m)[0][1] = v.x;   (m)[1][1] = v.y;   (m)[2][1] = v.z;   (m)[3][1] = (0);
	(m)[0][2] = n.x;   (m)[1][2] = n.y;   (m)[2][2] = n.z;   (m)[3][2] = (0);
	(m)[0][3] = (0);   (m)[1][3] = (0);   (m)[2][3] = (0);   (m)[3][3] = (1); 
	return *this;
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpMatrix4f::initRotationFromDirection(kpVector3f& forward, kpVector3f& up)
{
	forward.normalize();
	kpVector3f n = forward;
	up.normalize();
	kpVector3f u = kpVector3f(up).crossProduct(n);
	kpVector3f v = n.crossProduct(u);
	return initRotationFromVectors(n,v,u);
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpMatrix4f::mul(kpMatrix4f r)
{
	kpMatrix4f res;
	for(int i = 0; i < 4; i++)
	{
		for(int j = 0; j < 4; j++)
		{
			r.set(i,j, m[i][0] * r.get(0,j) +
						m[i][1] * r.get(1,j) +
						m[i][2] * r.get(2,j) +
						m[i][3] * r.get(3,j));
		}
	}
	res = r;
	return res;
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpMatrix4f::mulToMatrix(float matrix[16])
{
	kpMatrix4f tmp;

	return this->mul(toMatrix4f(matrix));
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpMatrix4f::toMatrix4f(float matrix[16])
{
	kpMatrix4f tmp;
	tmp.m[0][0] = matrix[0];
	tmp.m[0][1] = matrix[1];
	tmp.m[0][2] = matrix[2];
	tmp.m[0][3] = matrix[3];

	tmp.m[1][0] = matrix[4];
	tmp.m[1][1] = matrix[5];
	tmp.m[1][2] = matrix[6];
	tmp.m[1][3] = matrix[7];

	tmp.m[2][0] = matrix[8];
	tmp.m[2][1] = matrix[9];
	tmp.m[2][2] = matrix[10];
	tmp.m[2][3] = matrix[11];

	tmp.m[3][0] = matrix[12];
	tmp.m[3][1] = matrix[13];
	tmp.m[3][2] = matrix[14];
	tmp.m[3][3] = matrix[15];

	return tmp;
}
JackFruitEngine::kpMatrix4f JackFruitEngine::kpMatrix4f::initPerspective( float fov, float aspectRatio, float neara, float fara)
{
	const float zRange = neara - fara;
	const float halfFOV = tanf(fov / 2);

	m[0][0] = 1/(halfFOV * aspectRatio);
	m[0][1] = 0;
	m[0][2] = 0;
	m[0][3] = 0;

	m[1][0] = 0;
	m[1][1] = 1/(halfFOV);
	m[1][2] = 0;
	m[1][3] = 0;
		
	m[2][0] = 0;
	m[2][1] = 0;
	m[2][2] = (neara - fara)/ zRange;
	m[2][3] = 0;
		
	m[3][0] = 0;
	m[3][1] = 0;
	m[3][2] = (2 *(neara * fara))/ zRange;
	m[3][3] = 0;
				
	return *this;
}
float* JackFruitEngine::kpMatrix4f::getM()
{
	return *m;
}
float JackFruitEngine::kpMatrix4f::get(int x, int y)
{
	return m[x][y];
}
void JackFruitEngine::kpMatrix4f::set(int x, int y, float value)
{
	m[x][y] = (float)value;
}
bool JackFruitEngine::kpMatrix4f::operator==(kpMatrix4f mat)
{
	return (m[0][0] == mat.m[0][0] && m[0][1] == mat.m[0][1] && m[0][2] == mat.m[0][2] && m[0][3] == mat.m[0][3] &&
			m[1][0] == mat.m[1][0] && m[1][1] == mat.m[1][1] && m[1][2] == mat.m[1][2] && m[0][3] == mat.m[1][3] &&
			m[2][0] == mat.m[2][0] && m[2][1] == mat.m[2][1] && m[2][2] == mat.m[2][2] && m[0][3] == mat.m[2][3] &&
			m[3][0] == mat.m[3][0] && m[3][1] == mat.m[3][1] && m[3][2] == mat.m[3][2] && m[0][3] == mat.m[3][3]);
}
bool JackFruitEngine::kpMatrix4f::operator = (kpMatrix4f mat) const
{
	return (m[0][0] == mat.m[0][0] && m[0][1] == mat.m[0][1] && m[0][2] == mat.m[0][2] && m[0][3] == mat.m[0][3] &&
			m[1][0] == mat.m[1][0] && m[1][1] == mat.m[1][1] && m[1][2] == mat.m[1][2] && m[0][3] == mat.m[1][3] &&
			m[2][0] == mat.m[2][0] && m[2][1] == mat.m[2][1] && m[2][2] == mat.m[2][2] && m[0][3] == mat.m[2][3] &&
			m[3][0] == mat.m[3][0] && m[3][1] == mat.m[3][1] && m[3][2] == mat.m[3][2] && m[0][3] == mat.m[3][3]);
}