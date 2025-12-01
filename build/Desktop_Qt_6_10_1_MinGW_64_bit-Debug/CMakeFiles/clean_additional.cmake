# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\CryptoDesk_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\CryptoDesk_autogen.dir\\ParseCache.txt"
  "CryptoDesk_autogen"
  )
endif()
