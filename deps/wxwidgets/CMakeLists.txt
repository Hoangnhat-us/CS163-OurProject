message(STATUS "fetching wxwidgets...")

set(wxBUILD_SHARED OFF)

FetchContent_MakeAvailable(wxwidgets)
