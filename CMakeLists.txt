cmake_minimum_required(VERSION 3.16)

project(CryptoDesk LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

set(SOURCES
    main.cpp
    cryptodesk.cpp
)

set(HEADERS
    cryptodesk.h
)

add_executable(CryptoDesk ${SOURCES} ${HEADERS}
    vigenere.h
    vigenere.cpp
    dna.h
    dna.cpp
    vernam.h
    vernam.cpp
    transposition.h
    transposition.cpp
    dialogutils.h
    dialogutils.cpp
    analysisdialog.h
    analysisdialog.cpp
    htmlexporter.h
    htmlexporter.cpp
    historyitemwidget.cpp
    historyitemwidget.h
    historydialog.h
    historydialog.cpp
    Des.h
    Des.cpp
    AES.h
    AES.cpp)

# Link Qt6 libraries
target_link_libraries(CryptoDesk Qt6::Widgets Qt6::Core Qt6::Gui)

# Enable AUTOMOC, AUTOUIC, AUTORCC
set_target_properties(CryptoDesk PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)
