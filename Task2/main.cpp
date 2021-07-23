#include"struct.hpp"
#include"allmodules.hpp"

#include"getparsedinfo.hpp"
#include<iostream>
#include<boost/program_options/options_description.hpp>
#include<boost/program_options/positional_options.hpp>
#include<boost/program_options/parsers.hpp>
#include<boost/program_options/variables_map.hpp>
#include<boost/program_options/cmdline.hpp>
#include<boost/program_options/errors.hpp>
#include<boost/program_options/option.hpp>
#include<boost/program_options/value_semantic.hpp>
#include<boost/program_options/version.hpp>
#include<vector>
#include<string>
#include<iostream>
#include<fstream>
#include<cstring>
#include<algorithm>
#include<functional>
#include<cctype>
#include<locale>
#include<boost/filesystem.hpp>
#include<boost/filesystem/fstream.hpp>

using namespace std;


int main(int argc, char** argv) {
	setlocale(LC_ALL, "");
	string current_prog = boost::filesystem::basename(argv[0]); string info_options;
	string s1 = "Info: ";
	info_options = (s1) + current_prog + (" [ options ] <path to src dir>\nAllowed options:\n\t\t-h, --help - help message\n\t\t"
		"-I, --include - specify directories with headers\n");
	namespace po = boost::program_options;
	po::variables_map vm; po::options_description generic("Usage: " + current_prog + " [options] <path to src dir>");
	po::positional_options_description p;
	try {
		generic.add_options()
			("help,h", "this help message")
			("include,I", po::value< std::vector<std::string> >()->composing())
			("path", po::value<std::string>());
		p.add("path", 1);
		po::parsed_options parsed = po::command_line_parser(argc, argv).options(generic).positional(p).run();
		po::store(parsed, vm); po::notify(vm);
		if (vm.count("help")) { cout << info_options; return 1; }
		if (!vm.count("path")) { cerr << "Empty path\n" << info_options; return 1; }
		namespace  bfs = boost::filesystem;
		bfs::path workpath(vm["path"].as<std::string>());

		if (exists(workpath)) {
			if (!is_directory(workpath)) { cerr << workpath << ": is not a directory.\n"; return 1; }
			bfs::recursive_directory_iterator workdir(workpath), end;
			for (; workdir != end; ++workdir) {
				if (workdir->path().extension() == ".cpp" && is_regular_file(workdir->path())) {
					IncludedModuleList fe(workdir->path()); regex_parse p;
					fe.setParse(&p); p.enableCache();
					if (vm.count("include"))
						for (auto &p : vm["include"].as< vector<string> >()) fe.add_path(p);
					fe.createTree(); cout << fe << "\n";
				}
			}
		}
	}
	catch (boost::filesystem::filesystem_error& e) { cerr << e.what() << "\n"; return 1; }
	catch (string& g) { cout << g << "\n"; }
	catch (exception& e) { cerr << "Error: " << e.what() << "\n"; return 1; }
	catch (...) { cerr << "Error\n"; return 1; }
	return 0;
}
