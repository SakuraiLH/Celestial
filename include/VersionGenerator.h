#pragma once
#include "GlobalVariable.h"

	// Clang 或是 G++
	string true_cxx =
#ifdef __clang__
	"Clang++";
#else
	"GNU GCC";
#endif

	string current_os =
#ifdef __WIN32
	"Windows";
#elif __unix__ && !__linux__
	"Unix";
#elif __APPLE__
	"MacOS";
#elif __linux__
	"Linux";
#elif __FreeBSD__
	"FreeBSD";
#else
	"Unknown";
#endif
	string compile_time = __TIMESTAMP__;

string Celestial_Short_Version = "0.2";
string Celestial_Stable = "Alpha";
string Celestial_Minor_Version = "208";
string Celestial_Private_Version = "Celestial " + Celestial_Stable + ' ' + Celestial_Short_Version + '(' + Celestial_Minor_Version + ')' + " By SakuraiLH(GitHub)" + '\n'
                        + "(Compiled with " + true_cxx + " at " + compile_time + ")" + '\n'
                        + "Running on Mirai/" + current_os + " for this build.";
string Celestial_Version = Celestial_Private_Version + '\n'
                        + "Long live the open source!" + '\n'
                        + "Github Link: https://github.com/SakuraiLH/Celestial";
