add_library(psx_locale locales/locales.h locales/locales.cpp)
add_library(hh_time
   time/clock_time.h
   time/clock_time.cpp
   time/process_time.h
   time/process_time.cpp
)

add_library(psx_system_info system_info.h system_info.cpp)
target_link_libraries(psx_system_info hh_exception)

add_library(psx2_time
    psx2_time/psx_time.h psx2_time/psx_time.cpp
    psx2_time/psx_timer.h psx2_time/psx_timer.cpp
    )

target_link_libraries(psx2_time psx_signals rt hh_exception)
