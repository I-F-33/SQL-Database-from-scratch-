#ifndef TYPEDEF_H
#define TYPEDEF_H

#include <vector>
#include <string>
#include <queue>
#include "../bplustree/multimap.h"
#include "../bplustree/map.h"

using namespace std;

typedef vector<std::string> vectorstr;

typedef vector<long> vectorlong;

typedef queue<std::string> queuestr;

typedef Map<std::string,long> map_sl;

typedef Map<std::string,std::string> map_ss;

typedef MMap<std::string, std::string> mmap_ss;

typedef MMap<std::string, long> mmap_sl;










#endif