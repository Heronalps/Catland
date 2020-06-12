INCLUDE(CheckFunctionExists)
SET(WT_PROJECT_TARGET catland.wt)

FIND_PACKAGE(Wt REQUIRED Wt HTTP Dbo DboSqlite3)

SET(CONNECTOR Wt::HTTP)
SET(WT_LIB Wt::Wt)
SET(WTDBO_LIB Wt::Dbo)
SET(WTDBOSQLITE3_LIB Wt::DboSqlite3)
SET(DBO_LIBS ${WTDBO_LIB} ${WTDBOSQLITE3_LIB}) 

WT_ADD_FILE(${WT_PROJECT_TARGET}
  Catland.C
  User.C
  Session.C
  Pomodoro.C
  PomodoroWidget.C
  ItemWidget.C
  LettersWidget.C
  ImagesWidget.C
  HistoryWidget.C
  Item.C
)

TARGET_LINK_LIBRARIES(${WT_PROJECT_TARGET} ${WT_LIB} ${CONNECTOR} ${DBO_LIBS})

# Test whether crypt(3) is provided by libc. If it's not, check if
# libcrypt exists and if it provides crypt(3).
CHECK_FUNCTION_EXISTS(crypt CRYPT_EXISTS)
IF(NOT CRYPT_EXISTS)
  CHECK_LIBRARY_EXISTS(crypt crypt "" CRYPT_LIB_EXISTS)
  IF(CRYPT_LIB_EXISTS)
    SET(CMAKE_REQUIRED_LIBRARIES "crypt")
    CHECK_FUNCTION_EXISTS(crypt CRYPT_EXISTS)
  ENDIF(CRYPT_LIB_EXISTS)
ENDIF(NOT CRYPT_EXISTS)

IF(CRYPT_LIB_EXISTS)
  TARGET_LINK_LIBRARIES(catland.wt crypt)
ENDIF(CRYPT_LIB_EXISTS)

INCLUDE_DIRECTORIES(/usr/local/include/Wt)
