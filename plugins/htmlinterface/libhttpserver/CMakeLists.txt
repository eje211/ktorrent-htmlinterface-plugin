set(
    chunked_request_stream.cpp
    chunked_response_stream.cpp
    config.cpp
    file_stream.cpp
    gzip_response_stream.cpp
    header_buffer.cpp
    headers.cpp
    httpserver.cpp
    mime_types.cpp
    multipart_response_stream.cpp
    query_string.cpp
    request.cpp
    request_headers.cpp
    request_router.cpp
    request_stream.cpp
    response.cpp
    response_stream.cpp
    socket.cpp
)

add_library(libhttpserver STATIC
    chunked_request_stream.cpp
    chunked_response_stream.cpp
    config.cpp
    file_stream.cpp
    gzip_response_stream.cpp
    header_buffer.cpp
    headers.cpp
    httpserver.cpp
    mime_types.cpp
    multipart_response_stream.cpp
    query_string.cpp
    request.cpp
    request_headers.cpp
    request_router.cpp
    request_stream.cpp
    response.cpp
    response_stream.cpp
    socket.cpp
)

find_package(Threads)

set_property(TARGET libhttpserver PROPERTY POSITION_INDEPENDENT_CODE ON)

target_link_libraries(libhttpserver ${Boost_SYSTEM_LIBRARY} ${Boost_FILESYSTEM_LIBRARY} ${Boost_THREAD_LIBRARY} ${Boost_REGEX_LIBRARY} ${Boost_DATE_TIME_LIBRARY})
target_link_libraries(libhttpserver z)
target_link_libraries(libhttpserver ${CMAKE_THREAD_LIBS_INIT})
