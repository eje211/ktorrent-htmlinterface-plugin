include_directories(${Qt5Widgets_INCLUDE_DIRS})

set(
  httpconnection.cpp
  httpcookie.cpp
  httpgzipcompression.cpp
  httprequest.cpp
  httprequesthandler.cpp
  httpresponse.cpp
  httpserver.cpp
  httpsession.cpp
  httpsessionstore.cpp
  httpsettings.cpp
  httptcpserver.cpp
  shtmlcontroller.cpp
  staticfilecontroller.cpp
)

add_library(hobrasofthttpd SHARED httpconnection.cpp httpcookie.cpp httpgzipcompression.cpp httprequest.cpp httprequesthandler.cpp httpresponse.cpp httpresponse.cpp httpsession.cpp httpsessionstore.cpp httpsettings.cpp httptcpserver.cpp shtmlcontroller.cpp staticfilecontroller.cpp)

target_link_libraries(hobrasofthttpd Qt5::Network)

install(TARGETS hobrasofthttpd DESTINATION ${KTORRENT_PLUGIN_INSTALL_DIR} )
