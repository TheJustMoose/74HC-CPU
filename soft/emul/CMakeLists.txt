cmake_minimum_required(VERSION 3.11)

project(emul CXX)
set(CMAKE_CXX_STANDARD 17)

add_executable(emul
	emul.cpp
	lcd.cpp
	main.cpp
	observer.cpp
)
