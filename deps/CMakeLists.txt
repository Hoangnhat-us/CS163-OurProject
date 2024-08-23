include(FetchContent)

FetchContent_Declare(
	wxwidgets
	URL https://github.com/wxWidgets/wxWidgets/releases/download/v3.2.5/wxWidgets-3.2.5.zip
	URL_HASH SHA1=dda19cebdcc1906902d88edcad1c052f40c9460b
)

FetchContent_Declare(
	uni-algo
	URL https://github.com/uni-algo/uni-algo/archive/refs/tags/v1.2.0.zip
	URL_HASH SHA1=2476419cf95dbde2b07a510206274908379503bb
)

add_subdirectory("wxwidgets")
add_subdirectory("uni-algo")