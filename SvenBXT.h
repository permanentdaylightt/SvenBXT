//
// Created by scriptedsnark on 7/18/24.
//

#ifndef SVENBXT_H
#define SVENBXT_H

//WINDOWS
#ifdef WIN32
#include <windows.h>
#include <DbgHelp.h>
#else
#include <dlfcn.h>
#include <stdarg.h>
#endif

//STL
#include <sstream>
#include <vector>
#include <map>
#include <string>
#include <functional>
#include <array>
#include <random>
#include <fstream>
#include <filesystem>
#include <thread>

#include <stdio.h>

#include "hlsdk_mini.hpp"

//OWN STUFF
#include "Utils.h"

#endif //SVENBXT_H
