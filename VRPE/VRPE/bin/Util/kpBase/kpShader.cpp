#include "kpShader.h"


JackFruitEngine::kpShader::kpShader(void)
{
}
JackFruitEngine::kpShader::kpShader(const char* vss,const char* fss)
{
	std::string source;
	loadFile(vss,source);
	vs=loadShader(source,GL_VERTEX_SHADER);
	source="";
	loadFile(fss,source);
	fs=loadShader(source,GL_FRAGMENT_SHADER);
	
	program=glCreateProgram();
	glAttachShader(program,vs);
	glAttachShader(program,fs);
	
	glLinkProgram(program);
	glUseProgram(program);
}

JackFruitEngine::kpShader::~kpShader(void)
{
	glDetachShader(program,vs);
	glDetachShader(program,fs);
	glDeleteShader(vs);
	glDeleteShader(fs);
	glDeleteProgram(program);
}
void JackFruitEngine::kpShader::loadFile(const char* fn,std::string& str)
{
	std::ifstream in(fn);
	if(!in.is_open())
	{
		std::cout << "The file " << fn << " cannot be opened\n";
		return;
	}
	char tmp[300];
	while(!in.eof())
	{
		in.getline(tmp,300);
		str+=tmp;
		str+='\n';
	}
}
unsigned int JackFruitEngine::kpShader::loadShader(std::string& source,unsigned int mode)
{
	unsigned int id;
	id=glCreateShader(mode);
	
	const char* csource=source.c_str();
	
	glShaderSource(id,1,&csource,NULL);
	glCompileShader(id);
	char error[1000];
	glGetShaderInfoLog(id,1000,NULL,error);
	std::cout << "Compile status: \n" << error << std::endl;
	return id;
}
void JackFruitEngine::kpShader::useShader()
{
	glUseProgram(program);
}
unsigned int JackFruitEngine::kpShader::getProgramId()
{
	return program;
}
void JackFruitEngine::kpShader::delShader()
{
	glUseProgram(0);
}
//glUniforms
bool JackFruitEngine::kpShader::setUniform(const char* pName, int value)
{
	if( glGetUniformLocation(getProgramId(), pName) >= 0)
	{
		glUniform1iARB(glGetUniformLocation(getProgramId(), pName), value);
		return true;
	}
	return false;
}
bool JackFruitEngine::kpShader::setUniform(const char* pName, float value)
{
	if( glGetUniformLocation(getProgramId(), pName) >= 0)
	{
		glUniform1fARB(glGetUniformLocation(getProgramId(), pName), value);
		return true;
	}
	return false;
}
bool JackFruitEngine::kpShader::setUniform(const char* pName, bool value)
{
	if( glGetUniformLocation(getProgramId(), pName) >= 0)
	{
		glUniform1iARB(glGetUniformLocation(getProgramId(), pName), value);
		return true;
	}
	return false;
}
bool JackFruitEngine::kpShader::setUniform(const char* pName, float v1, float v2)
{
	if( glGetUniformLocation(getProgramId(), pName) >= 0)
	{
		glUniform2fARB(glGetUniformLocation(getProgramId(), pName), v1, v2);
		return true;
	}
	return false;
}
bool JackFruitEngine::kpShader::setUniform(const char* pName, kpVector3f value)
{
	if( glGetUniformLocation(getProgramId(), pName) >= 0)
	{
		glUniform3fARB(glGetUniformLocation(getProgramId(), pName), value.x, value.y, value.z);
		return true;
	}
	return false;
}/**/
bool JackFruitEngine::kpShader::setUniform(const char* pName, float** value)
{
	if( glGetUniformLocation(getProgramId(), pName) >= 0)
	{
		glUniformMatrix2fvARB(glGetUniformLocation(getProgramId(), pName), 1, GL_FALSE, &value[0][0]);
		return true;
	}
	return false;
}
bool JackFruitEngine::kpShader::setUniform(const char* pName, kpMatrix4f value)
{
	if( glGetUniformLocation(getProgramId(), pName) >= 0)
	{
		glUniformMatrix4fvARB(glGetUniformLocation(getProgramId(), pName), 1, GL_FALSE, &value.m[0][0]);
		return true;
	}
	return false;
}
bool JackFruitEngine::kpShader::setUniform(const char* pName, unsigned int image, int slot = 0)
{
	if( glGetUniformLocation(getProgramId(), pName) >= 0 )
	{
		glActiveTexture(GL_TEXTURE0 + slot);
		glBindTexture(GL_TEXTURE_2D, image);
		glUniform1iARB(glGetUniformLocation(getProgramId(), pName), slot);
		return true;
	}
	return false;
}
//glAttribute
bool JackFruitEngine::kpShader::bindAttribute(const char* pName, int index)
{
	if( glGetAttribLocation(getProgramId(), pName) >= 0)
	{
		glBindAttribLocation(getProgramId(), index, pName);
		return true;
	}
	return false;
}
//////////////////////////////////
int JackFruitEngine::kpShader::getUniform(const char* pName)
{
	if( glGetUniformLocation(getProgramId(), pName) >= 0 )
	{
		return glGetUniformLocation(getProgramId(), pName);
	}
	return -1;
}
int JackFruitEngine::kpShader::getAttribute(const char* pName)
{
	if( glGetAttribLocation(getProgramId(), pName) >= 0)
	{
		return glGetAttribLocation(program, pName);
	}
	return -1;
}



