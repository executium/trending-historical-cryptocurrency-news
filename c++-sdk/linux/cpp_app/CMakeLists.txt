cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME CppCurl)
project(${PROJECT_NAME})

find_package(OpenSSL REQUIRED)
include_directories(${OPENSSL_INCLUDE_DIR})

set(CURL_LIBRARY "-lcurl") 
find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

include_directories(/usr/include)
include_directories(3rdparty/jwt-cpp)
include_directories(src)

set(HEADER_FILES 
	src/ApiAccess.h)
	
set(SOURCE_FILES
	src/main.cpp
	src/ApiAccess.cpp)

add_executable(${PROJECT_NAME}
	${HEADER_FILES}
	${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} ${CURL_LIBRARY} ${OPENSSL_LIBRARIES})