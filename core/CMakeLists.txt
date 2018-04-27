list(APPEND mul-core-headers
    include/mul/delegate.hpp
    include/mul/event.hpp
    include/mul/factory.hpp
    include/mul/memory.hpp
    include/mul/non_copyable.hpp
    include/mul/timer.hpp
    include/mul/type_traits.hpp)

add_library(mul-core src/mul/event.cpp)

set_target_properties(mul-core PROPERTIES PUBLIC_HEADER "${mul-core-headers}")

target_include_directories(mul-core PUBLIC include)

install(TARGETS mul-core
    PUBLIC_HEADER DESTINATION include/mul 
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
