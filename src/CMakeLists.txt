# CMakeList.txt : CMake project for src, include source and define
# project specific logic here.
#

# Add source to this project's executable.
add_executable (src "dictionary.cpp" "dictionary.h" "dicType.cpp" "dicType.h" "frame.cpp" "frame.h" "mainPage.cpp" "mainPage.h" "searchPage.cpp" "searchPage.h" "searchType.cpp" "searchType.h" "Search.h" "Search.cpp" "favoritePage.cpp" "favoritePage.h" "TernarySearchTree.h" "TernarySearchTree.cpp" "SuffixArray.h" "SuffixArray.cpp" "Random.h" "Random.cpp" "VNSuffixArray.h" "VNSuffixArray.cpp")

if (WIN32)
	set_property(TARGET src PROPERTY WIN32_EXECUTABLE TRUE)
endif()

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET src PROPERTY CXX_STANDARD 20)
endif()

target_link_libraries(src PRIVATE wx::base wx::core)

add_custom_command(TARGET src POST_BUILD
	COMMAND ${CMAKE_COMMAND} -E copy_directory
		${CMAKE_CURRENT_SOURCE_DIR}/Data_Storage
		${CMAKE_CURRENT_BINARY_DIR}/Data_Storage
)

# TODO: Add tests and install targets if needed.
