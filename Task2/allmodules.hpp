#ifndef allmodules
#define allmodules
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<cstring>
#include<algorithm>
#include<functional>
#include<cctype>
#include<locale>
#include<regex>
#include"struct.hpp"
#include"getparsedinfo.hpp"

using namespace std;
namespace bfs = boost::filesystem;

class IncludedModuleList;

class IncludedModuleConstIterator {
public:
	IncludedModuleConstIterator(const IncludedModule* = nullptr,
                                const IncludedModuleList* = nullptr,
                                int = 0);
	const IncludedModule& operator*() const;
	const IncludedModule* operator->() const;
	IncludedModuleConstIterator& operator++();
	const IncludedModuleConstIterator operator++(int);
	int getLevel() const  {
	    return level;
    }
	bool operator != (const IncludedModuleConstIterator&) const;
	bool operator == (const IncludedModuleConstIterator&) const;

private:
	const IncludedModule* h; const IncludedModuleList* hl; int level;
}
class IncludedModuleList : public ParseType {
public:
	typedef IncludedModuleConstIterator const_iterator;
	friend const_iterator& const_iterator::operator++();
	friend const const_iterator const_iterator::operator++(int);
	friend ostream& operator<<(ostream&, const IncludedModuleList&);
	IncludedModuleList(bfs::path);
	~IncludedModuleList();
	IncludedModuleList(const IncludedModuleList&) = delete;
	IncludedModuleList(IncludedModuleList &&) = delete;
	const_iterator cbegin() const; const_iterator cend() const;
	void add_path(bfs::path);
	void createTree();
	bfs::path& getFilename() { return cppfilename; } void setParse(Parser* p) { type = p; }
private:
	vector<IncludedModule> parseFileForIncludes(bfs::path& filename) override { return type->parseFileForIncludes(filename); }
	bfs::path  cppfilename; vector<IncludedModule> headers; vector<bfs::path>paths; const size_t q = 1000000;
};
#endif
