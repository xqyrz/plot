# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BUILD_SOURCE_DIRS "F:/lib/ELFIO;F:/lib/ELFIO/cmake-build-debug")
set(CPACK_CMAKE_GENERATOR "Ninja")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "D:/Program Files/JetBrains/CLion 2025.1.1/bin/cmake/win/x64/share/cmake-3.31/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "elfio built using CMake")
set(CPACK_DMG_SLA_USE_RESOURCE_FILE_LICENSE "ON")
set(CPACK_GENERATOR "ZIP")
set(CPACK_INNOSETUP_ARCHITECTURE "x64")
set(CPACK_INSTALL_CMAKE_PROJECTS "F:/lib/ELFIO/cmake-build-debug;elfio;ALL;/")
set(CPACK_INSTALL_PREFIX "C:/Program Files (x86)/elfio")
set(CPACK_MODULE_PATH "")
set(CPACK_NSIS_DISPLAY_NAME "elfio 3.14")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES64")
set(CPACK_NSIS_PACKAGE_NAME "elfio 3.14")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OBJCOPY_EXECUTABLE "D:/Program Files/JetBrains/CLion 2025.1.1/bin/mingw/bin/objcopy.exe")
set(CPACK_OBJDUMP_EXECUTABLE "D:/Program Files/JetBrains/CLion 2025.1.1/bin/mingw/bin/objdump.exe")
set(CPACK_OUTPUT_CONFIG_FILE "F:/lib/ELFIO/cmake-build-debug/CPackConfig.cmake")
set(CPACK_OUTPUT_FILE_PREFIX "F:/lib/ELFIO/cmake-build-debug/package")
set(CPACK_PACKAGE_CONTACT "Serge Lamikhov-Center")
set(CPACK_PACKAGE_DEFAULT_LOCATION ".")
set(CPACK_PACKAGE_DESCRIPTION_FILE "D:/Program Files/JetBrains/CLion 2025.1.1/bin/cmake/win/x64/share/cmake-3.31/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "elfio built using CMake")
set(CPACK_PACKAGE_DIRECTORY "F:/lib/ELFIO/cmake-build-debug")
set(CPACK_PACKAGE_FILE_NAME "elfio-windows")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "elfio 3.14")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "elfio 3.14")
set(CPACK_PACKAGE_NAME "elfio")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "ELFIO")
set(CPACK_PACKAGE_VERSION "3.14")
set(CPACK_PACKAGE_VERSION_MAJOR "3")
set(CPACK_PACKAGE_VERSION_MINOR "14")
set(CPACK_READELF_EXECUTABLE "D:/Program Files/JetBrains/CLion 2025.1.1/bin/mingw/bin/readelf.exe")
set(CPACK_RESOURCE_FILE_LICENSE "F:/lib/ELFIO/LICENSE.txt")
set(CPACK_RESOURCE_FILE_README "F:/lib/ELFIO/README.md")
set(CPACK_RESOURCE_FILE_WELCOME "D:/Program Files/JetBrains/CLion 2025.1.1/bin/cmake/win/x64/share/cmake-3.31/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "ZIP")
set(CPACK_SOURCE_IGNORE_FILES "/.git.*;/.vs.*;/build;/.clang-format;/doc/site;/doc/elfio.docx;/doc/images/callouts/;/doc/images/colorsvg/;/doc/images/res2/;/doc/images/.*.svg;/doc/images/.*.gif;/doc/images/[^/]*.png$;/doc/images/.*.tif;/examples/sudo_gdb.sh;/tests")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "F:/lib/ELFIO/cmake-build-debug/CPackSourceConfig.cmake")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "elfio-3.14")
set(CPACK_SYSTEM_NAME "win64")
set(CPACK_THREADS "1")
set(CPACK_TOPLEVEL_TAG "win64")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "F:/lib/ELFIO/cmake-build-debug/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
