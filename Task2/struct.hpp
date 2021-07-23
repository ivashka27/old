#ifndef STRUCT
#define STRUCT
#include<string>
#include<boost/filesystem.hpp>
#include<boost/filesystem/fstream.hpp>
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<cstring>
#include<algorithm>
#include<functional>
#include<cctype>
#include<locale>

class IncludedModule : public boost::filesystem::path {
public:
	explicit IncludedModule(path);
	void setLast(bool l) { last = l; }
	bool getLast() const { return last; }
	bool is_exist() const { return exist; }
	void setExist(bool y) { exist = y; }
	void setLeft(IncludedModule *h) { left = h; }
	IncludedModule* getLeft() const { return left; }
	bool is_global() const { return global; }
	void setGlobal(bool a) { global = a; }
	void setNext(IncludedModule* n) { next = n; }
	IncludedModule* getNext() const { return next; }
	void setParent(IncludedModule *p) { parent = p; }
	IncludedModule* getParent() const { return parent; }
private:
	IncludedModule* left;
	IncludedModule* next;
	IncludedModule* parent;
	bool last;
	bool exist;
	bool global;
};
#endif
