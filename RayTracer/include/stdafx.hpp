#pragma once

#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <string>
#include <sstream>
#include <cmath>
#include <unordered_map>
#include <memory>
#include <cstdlib>
#include <ctime>
#include <memory>
#include <functional>
#include <random>
#include <chrono>

#include <time.h>
#include <conio.h>
#include <stdlib.h>
#include <assert.h>
#include <intrin.h>
#include <stdint.h>

//<Comment flag> #419begin #type = 1 #src = http://www.sfml-dev.org/
#include <SFML/System.hpp>/**SFML**/
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
//<Comment flag> #419end

//Global variable content tells where to store images
const std::string content = "../content/";

template<typename T>/**Smart pointers**/
using sptr = std::shared_ptr<T>;

using std::vector;

