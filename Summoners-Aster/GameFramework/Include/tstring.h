#ifndef TSTRING_H
#define TSTRING_H

#include <tchar.h>
#include <xstring>
#include <sstream>
#include <istream>
#include <ostream>

/// <summary>
/// 基礎構築に関するものをまとめた名前空間
/// </summary>
namespace gameframework
{
	//namespaceは関係ない
	#define totstring std::_Integral_to_string<TCHAR>

	using tstring = std::basic_string<TCHAR>;
	using tstringstream = std::basic_stringstream<TCHAR>;
	using tistringstream = std::basic_istringstream<TCHAR>;
	using tostringstream = std::basic_ostringstream<TCHAR>;
}

#endif //!TSTRING_H
