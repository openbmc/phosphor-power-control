AC_PREREQ([2.69])
AC_INIT([phosphor-state-manager], [1.0], [https://github.com/openbmc/phosphor-state-manager/issues])
AC_LANG([C++])
AC_CONFIG_HEADERS([config.h])
AM_INIT_AUTOMAKE([subdir-objects -Wall -Werror foreign dist-xz])
AM_SILENT_RULES([yes])

# Checks for programs
AC_PROG_CXX
AC_PROG_INSTALL #Checks/sets the install variable to be used
AC_PROG_MAKE_SET

# Check for libraries
PKG_CHECK_MODULES([SYSTEMD], [libsystemd >= 221])
PKG_CHECK_MODULES([PHOSPHOR_DBUS_INTERFACES], [phosphor-dbus-interfaces],,\
    AC_MSG_ERROR(["Requires phosphor-dbus-interfaces package."]))
PKG_CHECK_MODULES([SDBUSPLUS], [sdbusplus],,
    AC_MSG_ERROR(["Requires sdbusplus package."]))
PKG_CHECK_MODULES([SDEVENTPLUS], [sdeventplus],,
    AC_MSG_ERROR(["Requires sdeventplus package."]))
PKG_CHECK_MODULES([PHOSPHOR_LOGGING], [phosphor-logging],,\
    AC_MSG_ERROR(["Requires phosphor-logging package."]))
PKG_CHECK_MODULES([GPIOPLUS], [gpioplus],,\
    [AC_MSG_ERROR([Could not find gpioplus...openbmc/gpioplus package required])])

# Checks for typedefs, structures, and compiler characteristics.
AX_CXX_COMPILE_STDCXX_17([noext])
AX_APPEND_COMPILE_FLAGS([-Wall -Werror], [CXXFLAGS])

# Checks for library functions
LT_INIT # Removes WARNING: unrecognized options: --with-libtool-sysroot

# Check for header files.
AC_CHECK_HEADER(systemd/sd-bus.h, ,[AC_MSG_ERROR([Could not find systemd/sd-bus.h...systemd development package required])])
AC_CHECK_HEADER(sdbusplus/server.hpp, ,[AC_MSG_ERROR([Could not find sdbusplus/server.hpp...openbmc/sdbusplus package required])])
AC_CHECK_HEADER(phosphor-logging/log.hpp, ,[AC_MSG_ERROR([Could not find phosphor-logging/log.hpp...openbmc/phosphor-logging package required])])
AC_CHECK_HEADER(nlohmann/json.hpp, ,[AC_MSG_ERROR([Could not find nlohmann/json.hpp...nlohmann/json package required])])

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
