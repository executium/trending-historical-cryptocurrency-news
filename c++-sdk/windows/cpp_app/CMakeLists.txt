cmake_minimum_required(VERSION 2.8)

set(PROJECT_NAME CppCurl)
project(${PROJECT_NAME})

# include_directories(/usr/include)
include_directories(3rdparty/curl/include)
include_directories(3rdparty/jwt-cpp)
include_directories(3rdparty/openssl/include)
include_directories(src)

link_directories(${CMAKE_CURRENT_LIST_DIR}/3rdparty/curl/lib)
link_directories(${CMAKE_CURRENT_LIST_DIR}/3rdparty/openssl/lib)

set(HEADER_FILES 
	src/ApiAccess.h)
	
set(SOURCE_FILES
	src/main.cpp
	src/ApiAccess.cpp)

add_executable(${PROJECT_NAME}
	${HEADER_FILES}
	${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} libcurl_a.lib Normaliz.lib Ws2_32.lib Wldap32.lib advapi32.lib Crypt32.lib libssl.lib libcrypto.lib)