add_library(psx_locale locales/locales.h locales/locales.cpp)
add_library(psx_time
   time/clock_time.h
   time/clock_time.cpp
   time/process_time.h
   time/process_time.cpp
)

add_library(psx_system_info system_info.h system_info.cpp)
target_link_libraries(psx_system_info hh_exception)
