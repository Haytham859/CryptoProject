cmake_minimum_required(VERSION 3.16)

project(CryptoDesk LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt6
find_package(Qt6 REQUIRED COMPONENTS Widgets Core Gui)

set(SOURCES
    main.cpp
    cryptodesk.cpp
    caesar.cpp
    playfair.cpp
    hill.cpp
       multiplicative.cpp
)

set(HEADERS
    cryptodesk.h
    caesar.h
    playfair.h
    hill.h
       multiplicative.h
)

add_executable(CryptoDesk ${SOURCES} ${HEADERS}
    multiplicative.h
    multiplicative.cpp
    Affine.h
    Affine.cpp
    vigenere.h
    vigenere.cpp
    dna.h
    dna.cpp
    autokey.h
    autokey.cpp
    vernam.h
    vernam.cpp
    transposition.h
    transposition.cpp
    rsa.h
    rsa.cpp
    customRSA.cpp
    customRSA.h
    dialogutils.h
    dialogutils.cpp)

# Link Qt6 libraries
target_link_libraries(CryptoDesk Qt6::Widgets Qt6::Core Qt6::Gui)

# Enable AUTOMOC, AUTOUIC, AUTORCC
set_target_properties(CryptoDesk PROPERTIES
    AUTOMOC ON
    AUTOUIC ON
    AUTORCC ON
)
