
include_directories (
    "${CMAKE_CURRENT_LIST_DIR}"
    )

MESSAGE(STATUS "Including ASTERIX code")

target_sources(atsdb
    PUBLIC
        "${CMAKE_CURRENT_LIST_DIR}/asterixconfigwidget.h"
        "${CMAKE_CURRENT_LIST_DIR}/asterixoverridewidget.h"
        "${CMAKE_CURRENT_LIST_DIR}/asterixframingcombobox.h"
        "${CMAKE_CURRENT_LIST_DIR}/asterixeditioncombobox.h"
        "${CMAKE_CURRENT_LIST_DIR}/asterixrefeditioncombobox.h"
        "${CMAKE_CURRENT_LIST_DIR}/asterixspfeditioncombobox.h"
        "${CMAKE_CURRENT_LIST_DIR}/asterixcategoryconfig.h"
        "${CMAKE_CURRENT_LIST_DIR}/asterixstatusdialog.h"
        "${CMAKE_CURRENT_LIST_DIR}/asterixpostprocess.h"
    PRIVATE
        "${CMAKE_CURRENT_LIST_DIR}/asterixconfigwidget.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/asterixstatusdialog.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/asterixoverridewidget.cpp"
        "${CMAKE_CURRENT_LIST_DIR}/asterixpostprocess.cpp"
)


