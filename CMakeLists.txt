cmake_minimum_required(VERSION 3.2)
project(webstar)

find_package (Threads)
set(CMAKE_CXX_STANDARD 14)

find_package(Boost 1.55 REQUIRED COMPONENTS system filesystem)
find_package(OpenSSL REQUIRED)

include_directories(
        ${Boost_INCLUDE_DIR}
        ${OPENSSL_INCLUDE_DIR}
		"${CMAKE_SOURCE_DIR}/third"
        "${CMAKE_SOURCE_DIR}/third/cinatra/libcinatra_http"
        "${CMAKE_SOURCE_DIR}/third/cinatra/libcinatra")

if (WIN32)
    set(EXTRA_LIB mswsock ws2_32)
endif ()

find_package(Boost 1.55 COMPONENTS coroutine context system thread filesystem REQUIRED)


set(CINATRA_FILES
        third/cinatra/libcinatra/cinatra/middleware/cookies.hpp
        third/cinatra/libcinatra/cinatra/middleware/session.hpp
        third/cinatra/libcinatra/cinatra/aop.hpp
        third/cinatra/libcinatra/cinatra/cinatra.h
        third/cinatra/libcinatra/cinatra/context_container.hpp
        third/cinatra/libcinatra/cinatra/function_traits.hpp
        third/cinatra/libcinatra/cinatra/router.h
        third/cinatra/libcinatra/router.cpp)

set(CINATRA_HTTP_FILES
        third/cinatra/libcinatra_http/cinatra_http/connection.hpp
        third/cinatra/libcinatra_http/cinatra_http/http_parser.h
        third/cinatra/libcinatra_http/cinatra_http/http_server.h
        third/cinatra/libcinatra_http/cinatra_http/io_service_pool.h
        third/cinatra/libcinatra_http/cinatra_http/mime_types.h
        third/cinatra/libcinatra_http/cinatra_http/multipart_parser.h
        third/cinatra/libcinatra_http/cinatra_http/picohttpparser.h
        third/cinatra/libcinatra_http/cinatra_http/request.h
        third/cinatra/libcinatra_http/cinatra_http/response.h
        third/cinatra/libcinatra_http/cinatra_http/utils.h
        third/cinatra/libcinatra_http/cinatra_http/websocket.h
        third/cinatra/libcinatra_http/http_parser.c
        third/cinatra/libcinatra_http/http_server.cpp
        third/cinatra/libcinatra_http/io_service_pool.cpp
        third/cinatra/libcinatra_http/mime_types.cpp
        third/cinatra/libcinatra_http/multipart_parser.c
        third/cinatra/libcinatra_http/picohttpparser.c
        third/cinatra/libcinatra_http/request.cpp
        third/cinatra/libcinatra_http/response.cpp
        third/cinatra/libcinatra_http/utils.cpp
        third/cinatra/libcinatra_http/websocket.cpp)

set(WEBSTAR_FILES
        main.cpp
		third/ormpp/sqlite3.c
		)

add_library(cinatra_http STATIC ${CINATRA_HTTP_FILES})

add_library(cinatra STATIC ${CINATRA_FILES})

add_executable(webstar ${WEBSTAR_FILES})
target_link_libraries(webstar cinatra cinatra_http ${Boost_LIBRARIES} ${OPENSSL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT} ${EXTRA_LIB})

#install(TARGETS cinatra DESTINATION lib)
#install(TARGETS cinatra_http DESTINATION lib)
#install(DIRECTORY libcinatra/cinatra DESTINATION include)
#install(DIRECTORY libcinatra_http/cinatra_http DESTINATION include)
#install(DIRECTORY cmake DESTINATION share/cinatra)
