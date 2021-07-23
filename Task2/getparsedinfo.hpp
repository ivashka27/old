#ifndef PARSE
#define PARSE
#include<boost/filesystem.hpp>
#include<boost/filesystem/fstream.hpp>
#include"struct.hpp"
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<cstring>
#include<algorithm>
#include<functional>
#include<cctype>
#include<locale>
using namespace std;
class IncludedModule;
namespace bfs = boost::filesystem;
class Parser {
public:
	virtual ~Parser() {}
	virtual vector<IncludedModule> parseFileForIncludes(bfs::path&) = 0;
};
class regex_parse : public Parser {
public:
	~regex_parse() {}
	vector<IncludedModule> parseFileForIncludes(bfs::path&) override;
	void enableCache() { useCache = true; }
	void disableCache() { useCache = false; }
private:
	bool useCache;
};

class ParseType {
protected:
	Parser* type;

public:
	virtual ~ParseType() {}
	virtual vector<IncludedModule> parseFileForIncludes(bfs::path&) = 0; virtual void setParse(Parser*) = 0;
};

#endif