####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding diles
# MOD_DEPS: (optional) module dependencies
#
# Note: using PROJECT_NAME as EXECUTABLE_NAME
####
set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/RadioHead/RH_RF22.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/RadioHead/RHHardwareSP1I.cpp"
    #"${CMAKE_CURRENT_LIST_DIR}/RadioHead/"
    #"${CMAKE_CURRENT_LIST_DIR}/RadioHead/"
    #"${CMAKE_CURRENT_LIST_DIR}/RadioHead/"
    #"${CMAKE_CURRENT_LIST_DIR}/RadioHead/"

    
)
register_fprime_module()

#set(UT_SOURCE_FILES
#    "${CMAKE_CURRENT_LIST_DIR}/ComStub.fpp"
#    "${CMAKE_CURRENT_LIST_DIR}/test/ut/Tester.cpp"
#    "${CMAKE_CURRENT_LIST_DIR}/test/ut/TestMain.cpp"
#)
#set(UT_MOD_DEPS
#    STest
#)
#register_fprime_ut()
