cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)

project(emul CXX)
add_executable(emul
	emul.cpp
	lcd.cpp
	main.cpp
	observer.cpp
)

include_directories("doctest\\doctest")

project(unit_tests CXX)
add_executable(unit_tests
	emul.cpp
	observer.cpp
	unit_tests.cc
)
