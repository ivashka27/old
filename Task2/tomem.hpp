#ifndef SAVE_T
#define SAVE_T
#include<unordered_map>
#include<map>
#include<functional>
#include<boost/filesystem.hpp>
#include<boost/filesystem/fstream.hpp>
#include<exception>
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
#pragma GCC optimize("Ofast")
#define X first
#define Y second
#define int long long
#define double long double
#define pii pair<int, int>
#define vi vector<int>
#define vvi vector<vi>
#define pb push_back
#define mp make_pair
#define all(a) a.begin(), a.end()
#define int long long
using namespace std;
namespace  bfs = boost::filesystem;

class ToSaveClass {
	public:
		ToSaveClass(const ToSaveClass&) = delete; ToSaveClass(ToSaveClass &&) = delete;
ToSaveClass& operator=(const ToSaveClass&) = delete; ToSaveClass& operator=(ToSaveClass&&) = delete;
	static ToSaveClass& EnableCache() { static ToSaveClass cache; return cache; }
		bool check_if_element_is_in_the_cache(const string&); void addToCache(const string& filename, const vector<IncludedModule>);
			vector<IncludedModule> getFromCache(const string& s) const { return cache.at(s); }
	private:
		~ToSaveClass() {}
		ToSaveClass(); size_t CacheLimit; unordered_map<string, vector<IncludedModule>> cache;
};
class cache_limit_reached : public exception {
public:
	virtual const char* what() const noexcept override {
		return "memory limit\n";
	}
};
#endif