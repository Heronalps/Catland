CMAKE_MINIMUM_REQUIRED(VERSION 3.1...3.14)

PROJECT(CATLAND)

IF(NOT CMAKE_CXX_STANDARD)
  SET(CMAKE_CXX_STANDARD 11)
ENDIF(NOT CMAKE_CXX_STANDARD)
# SET(CMAKE_CXX_STANDARD_REQUIRED ON)
# SET(CMAKE_CXX_EXTENSIONS OFF)

OPTION(INSTALL_RESOURCES "Install resources directory" ON)
OPTION(ENABLE_SSL "Enable cryptography functions, using OpenSSL" ON)
OPTION(ENABLE_SQLITE "Build SQLite3 backend for Wt::Dbo" ON)
OPTION(ENABLE_LIBWTDBO "Build Wt::Dbo" ON)

# The WT_ADD_FILE function builds a DLL in case of ISAPI, and an executable
# in case of FCGI or HTTPD connectors. It also makes sure that the source files
# links to the proper libraries (connector + wt).

MACRO(WT_ADD_FILE name)
  IF(CONNECTOR MATCHES "wtisapi")
    SET(MYLIST ${ARGV})
    LIST(INSERT MYLIST 1 SHARED)
    ADD_LIBRARY(${MYLIST})
    SET_TARGET_PROPERTIES(${name}
      PROPERTIES
        LINK_FLAGS
         "/EXPORT:HttpExtensionProc /EXPORT:GetExtensionVersion /EXPORT:TerminateExtension"
    )
  ELSE(CONNECTOR MATCHES "wtisapi")
    ADD_EXECUTABLE(${ARGV}) # ARGV - name
  ENDIF(CONNECTOR MATCHES "wtisapi")

ENDMACRO(WT_ADD_FILE)

SUBDIRS(src)

IF(INSTALL_RESOURCES)
INSTALL(DIRECTORY ${PROJECT_SOURCE_DIR}/resources DESTINATION
    ${CMAKE_INSTALL_PREFIX}/share/Wt/)
ENDIF(INSTALL_RESOURCES)