#include"struct.hpp"
#include<fstream>
#include<vector>
#include<string>
#include<iostream>
#include<cstring>
#include<algorithm>
#include<functional>
#include<cctype>
#include<locale>

IncludedModule::IncludedModule(path n) : path(n), left{ nullptr }, next{ nullptr }, parent{ nullptr }, last{ false }, exist{ false }, global{ false } {}