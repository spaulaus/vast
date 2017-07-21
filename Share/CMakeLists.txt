# @author S.V. Paulauskas
#Configure and install the module file
configure_file("modulefiles/vast" vast @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/vast DESTINATION share/modulefiles/)