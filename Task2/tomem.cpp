#include"tomem.hpp"
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
namespace  bfs = boost::filesystem;
ToSaveClass::ToSaveClass() : CacheLimit{1000000} { cache.max_load_factor(0.7); cache.reserve(CacheLimit); }
bool ToSaveClass::check_if_element_is_in_the_cache(const std::string& fname) { if (cache.find(fname) != cache.end()) return true; return false; }
void ToSaveClass::addToCache(const std::string& filename, const std::vector<IncludedModule> h) { if (cache.size() < cache.max_size()) cache.insert({filename, h}); }