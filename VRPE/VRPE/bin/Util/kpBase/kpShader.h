#pragma once
#ifndef KPSHADER_H
#define KPSHADER_H

#include "../kpSystem/kpStructure.h"
#include "../kpMath/kpTransform.h"
#include <string>
#include <vector>
#include <fstream>
#include <iostream>



namespace JackFruitEngine
{

	class JFE_API kpShader
	{
	private:		
		unsigned int vs,fs,program;
		void loadFile(const char* fn,std::string& str);
		unsigned int loadShader(std::string& source,unsigned int mode);
	public:
		kpShader(void);
		kpShader(const char* vss,const char* fss);
		~kpShader(void);

		void useShader();
		void delShader();
		unsigned int getProgramId();

		//////////////////////////////////
		int getUniform(const char* pName);
		int getAttribute(const char* pName);
		//////////////////////////////////
		bool setUniform(const char* pName, int value);
		bool setUniform(const char* pName, float value);
		bool setUniform(const char* pName, bool value);		
		bool setUniform(const char* pName, float v1, float v2);
		bool setUniform(const char* pName, kpVector3f value);
		bool setUniform(const char* pName, kpMatrix4f value);
		bool setUniform(const char* pName, float** value);
		bool setUniform(const char* pName, unsigned int image, int slot);

		bool bindAttribute(const char* pName, int index);
	};
}
#endif