#ifndef MY_UTIL_H
#define MY_UTIL_H

#include <memory>
#include <string>
#include <stdexcept>

// split string into vector
std::vector<std::string> split(const std::string str, std::string token);

// remove leading and trailing whitespaces (or other characters)
std::string trim(const std::string& str, const std::string& whitespace = " \t\n\r");

// access key value in map with default parameter
template <typename K, typename V>
const V & GetWithDef(const  std::map <K,V> & m, const K & key, const V & defval);

// convert string to float
float StringToFloat(const std::string str);


std::vector<std::string> split(std::string str, const std::string token)
{
    std::vector<std::string>result;
    while (str.size()) {
        int index = str.find(token);
        if (index != std::string::npos){
            result.push_back(str.substr(0,index));
            str = str.substr(index + token.size());
            if (str.size() == 0) result.push_back(str);
        } else {
            result.push_back(str);
            str = "";
        }
    }
    return result;
}

std::vector<std::string> split_trim(std::string str, const std::string token)
{
    std::vector<std::string>result;
    while (str.size()) {
        int index = str.find(token);
        if (index != std::string::npos){
            result.push_back(trim(str.substr(0,index)));
            str = str.substr(index + token.size());
            if (str.size() == 0) result.push_back(str);
        } else {
            result.push_back(trim(str));
            str = "";
        }
    }
    return result;
}

std::string trim(const std::string& str, const std::string& whitespace)
{
    const auto strBegin = str.find_first_not_of(whitespace);
    if (strBegin == std::string::npos)
        return ""; // no content

    const auto strEnd = str.find_last_not_of(whitespace);
    const auto strRange = strEnd - strBegin + 1;

    return str.substr(strBegin, strRange);
}

template <typename K, typename V>
const V & GetWithDef(const std::map <K,V>& m, const K& key, const V& defval)
{
   typename std::map<K,V>::const_iterator it = m.find( key );
   if ( it == m.end() ) {
      return defval;
   }
   else {
      return it->second;
   }
}

bool startsWith(std::string text, std::string cmp)
{
   return (text.rfind(cmp, 0) == 0);
}

bool endsWith(std::string text, std::string cmp)
{
    if (text.length() >= cmp.length()) {
        return (0 == text.compare (text.length() - cmp.length(), cmp.length(), cmp));
    } else {
        return false;
    }    
}

float StringToFloat(const std::string str)
{
    return atof(str.c_str());
}

int StringToInt(const std::string str)
{
    return atoi(str.c_str());
}

#include <memory>
#include <string>
#include <stdexcept>

template<typename ... Args>
std::string string_format(const std::string& format, Args ... args)
{
    int size_s = std::snprintf(nullptr, 0, format.c_str(), args ...) + 1; // Extra space for '\0'
    if (size_s <= 0) { return ""; }
    auto size = static_cast<size_t>(size_s);
    std::unique_ptr<char[]> buf (new char[size]);
    std::snprintf(buf.get(), size, format.c_str(), args ...);
    return std::string(buf.get(), buf.get() + size - 1); // We don't want the '\0' inside
}

#endif // MY_UTIL_H