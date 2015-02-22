#pragma once
#ifndef KPLOG_H
#define KPLOG_H

#include <iostream>
#include <cstring>
#include "kpProfileTimer.h"

namespace JackFruitEngine
{
	class JFE_API kpLog
	{
	private:	
		static void format()
		{
			std::cout << "-------------------------------------------------------------" << std::endl;
		}
	public:
		kpLog(){}	
		static void i(const char* tag)
		{
			format();
			std::cout << "Log:" << tag << std::endl;
			format();
		}
		static void i(const char* tag, const char* msg)
		{
			format();
			std::cout << "Log:" << tag  << "\nMsg:"<< msg << std::endl;
			format();
		}
		static void i(const char* tag, const char* func, const char* msg)
		{
			format();
			std::cout << "Log:" << tag << " Func:" << func << "\nMsg:"<< msg << std::endl;
			format();
		}
		static void i(const char* tag, const char* func, std::string msg)
		{
			format();
			std::cout << "Log:" << tag << " Func:" << func << "\nMsg:"<< msg << std::endl;
			format();
		}
		std::string ie(const char* tag)
		{
			std::string tmp ="Log:";
			tmp += tag;
			return tmp;
		}
		std::string ie(const char* tag, const char* msg)
		{
			std::string tmp ="Log:";
			tmp += tag;
			tmp += "\nMsg:";
			tmp += msg;
			return tmp;
		}
		std::string ie(const char* tag, const char* func, const char* msg)
		{
			std::string tmp ="Log:";
			tmp += tag;
			tmp += " Func:";
			tmp += func;
			tmp += "\nMsg:";
			tmp += msg;
			return tmp;
		}	
	};
}
#endif