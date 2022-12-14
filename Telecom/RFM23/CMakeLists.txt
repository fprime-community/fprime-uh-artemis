####
# F prime CMakeLists.txt:
#
# SOURCE_FILES: combined list of source and autocoding diles
# MOD_DEPS: (optional) module dependencies
#
# Note: using PROJECT_NAME as EXECUTABLE_NAME
####
set(SOURCE_FILES
    "${CMAKE_CURRENT_LIST_DIR}/RFM23.fpp"
    "${CMAKE_CURRENT_LIST_DIR}/RFM23.cpp"
)
set(MOD_DEPS ${FPRIME_PROJECT_ROOT}/lib)   #must be before register module 
                                           #module dependancies -> we're pointing to the CMakeLists that point to radiohead libraries
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
