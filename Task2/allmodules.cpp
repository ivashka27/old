#include"allmodules.hpp"
#include"struct.hpp"
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
#include"cacheme.hpp"

using namespace std;
namespace  bfs = boost::filesystem;
IncludedModuleList::IncludedModuleList(bfs::path f) : cppfilename{ f } {
	headers.reserve(q);
}
IncludedModuleList::~IncludedModuleList() {}
void IncludedModuleList::createTree() {
	vector<IncludedModule> tmpvector;
	tmpvector.reserve(1024);
	headers = parseFileForIncludes(cppfilename);
	if (headers.empty()) return;
	headers.back().setLast(true);
	size_t i = headers.size();
	for (size_t s = 0; s < i; s++) {
		if (s == q) break;
		bfs::path fileForParse;
		if (headers.at(s).is_global())
			for (auto &a : paths) {
				bfs::exists(a / headers.at(s).filename()) ? headers.at(s).setExist(true) : headers.at(s).setExist(false);
				if (headers.at(s).is_exist()) {
					fileForParse = a / headers.at(s).filename();
					break;
				}
			}
		else if (!headers.at(s).is_global()) {
			bfs::exists(headers.at(s).string()) ? headers.at(s).setExist(true) : headers.at(s).setExist(false);
			fileForParse = headers.at(s).string();
		}
		tmpvector = parseFileForIncludes(fileForParse);
		if (tmpvector.size()) {
			tmpvector.back().setLast(true);
			size_t  prev_i = i;
			for (auto &it : tmpvector) {
				it.setParent(&headers.at(s));
				headers.push_back(it); headers.at(s).setLeft(&tmpvector[0]);
			}
			headers.at(s).setLeft(&headers.at(prev_i));
			i += tmpvector.size();
		}
		tmpvector.clear();
	}
	for (size_t j = 0; j < i - 1; ++j)
		if (!headers.at(j).getLast())
			headers.at(j).setNext(&headers.at(j + 1));
}

void IncludedModuleList::add_path(bfs::path a) {
	paths.push_back(a);
}
IncludedModuleConstIterator::IncludedModuleConstIterator(const IncludedModule* hr, const IncludedModuleList* hrl, int lev) : h{ hr }, hl{ hrl }, level{ lev } {}
auto IncludedModuleConstIterator::operator*() const -> const IncludedModule&{
	return *h;
}
auto IncludedModuleConstIterator::operator->() const -> const IncludedModule*{
	return h;
}
auto IncludedModuleList::cbegin() const -> const_iterator {
	return headers.size() ? const_iterator(&(this->headers.front()), this) : const_iterator();
}
auto IncludedModuleList::cend() const -> const_iterator {
	return const_iterator();
}

auto IncludedModuleConstIterator::operator++() -> IncludedModuleConstIterator& {
	if (h->getLeft())
		h = h->getLeft(), level++;
	else if (h->getLast()) {
		while (h->getLast() && h->getParent())
			h = h->getParent(), level--;
		h = h->getNext();
	}
	else if (!h->getLast()) h = h->getNext();
	return *this;
}
auto IncludedModuleConstIterator::operator ++(int) -> const IncludedModuleConstIterator{
	return ++(*this);
}
auto IncludedModuleConstIterator::operator ==(const IncludedModuleConstIterator& hli) const -> bool {
	if (this == &hli)
		return true;
	return (this->h == hli.h) || (this->hl == hli.hl);
}
auto IncludedModuleConstIterator::operator !=(const IncludedModuleConstIterator& hli) const -> bool {
	if (this == &hli)
		return false;
	return (this->h != hli.h) && (this->hl != hli.hl);
}

ostream& operator<<(ostream& st, const IncludedModuleList& hl) {
	if (!bfs::exists(hl.cppfilename)) return st;
	if (hl.headers.empty()) st << "File " << hl.cppfilename << " has no includes\n";
	else st << "File " << hl.cppfilename << " has includes:\n";
	for (auto i = hl.cbegin(); i != hl.cend(); ++i) {
		string prefix("");
		for (int j = 0; j < i.getLevel(); j++) prefix += "..";
		st << prefix << i->filename() << " " << (i->is_exist() ? "\n" : "(!)\n");
	}
	return st;
}