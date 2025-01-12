#ifndef MY_UTIL_H
#define MY_UTIL_H

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

float StringToFloat(const std::string str)
{
    return atof(str.c_str());
}

#endif // MY_UTIL_H