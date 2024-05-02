# The following file was originally taken from libjxl and adapted to C
# and the __atomic_fetch_add for __uint128_t since all others
# seem to generate direct instructions nowadays on GCC.

# Original issue:
# * https://gitlab.kitware.com/cmake/cmake/-/issues/23021#note_1098733
#
# For reference:
# * https://gcc.gnu.org/wiki/Atomic/GCCMM
#
# ATOMICS_FOUND        - system has c atomics
# ATOMICS_LIBRARIES    - libraries needed to use c atomics

include(CheckCSourceCompiles)

set(atomic_code
    "
    #include <stdatomic.h>
    #include <stdint.h>
    volatile __uint8_t n1 = 0;
    volatile __uint128_t n16 = 0;
    int main() {
      __atomic_fetch_add(&n1, 8, __ATOMIC_SEQ_CST);
      __atomic_fetch_add(&n16, 8, __ATOMIC_SEQ_CST);
      return 0;
    }")

check_c_source_compiles("${atomic_code}" ATOMICS_LOCK_FREE_INSTRUCTIONS)

if(ATOMICS_LOCK_FREE_INSTRUCTIONS)
  set(ATOMICS_FOUND TRUE)
  set(ATOMICS_LIBRARIES)
else()
  set(CMAKE_REQUIRED_LIBRARIES "-latomic")
  check_c_source_compiles("${atomic_code}" ATOMICS_IN_LIBRARY)
  set(CMAKE_REQUIRED_LIBRARIES)
  if(ATOMICS_IN_LIBRARY)
    set(ATOMICS_LIBRARY atomic)
    include(FindPackageHandleStandardArgs)
    find_package_handle_standard_args(Atomics DEFAULT_MSG ATOMICS_LIBRARY)
    set(ATOMICS_LIBRARIES ${ATOMICS_LIBRARY})
    unset(ATOMICS_LIBRARY)
  else()
    if(Atomics_FIND_REQUIRED)
      message(FATAL_ERROR "Neither lock free instructions nor -latomic found.")
    endif()
  endif()
endif()
unset(atomic_code)
