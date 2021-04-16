cmake_minimum_required(VERSION 3.16)
project(targil4_lo_leagasha_Q1)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(targil4_lo_leagasha_Q1
        calendar.cpp
        calendar.h
        main.cpp
        month.cpp
        month.h
        List_Node_meeting.cpp
        List_Node_meeting.h
        List.cpp
        List.h
        day.cpp
        day.h
        )
