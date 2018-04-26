list(APPEND mul-core-headers
    include/delegate.hpp
    include/event.hpp
    include/factory.hpp
    include/memory.hpp
    include/non_copyable.hpp
    include/timer.hpp
    include/type_traits.hpp)

add_library(mul-core src/event.cpp)

set_target_properties(mul-core PROPERTIES PUBLIC_HEADER "${mul-core-headers}")

target_include_directories(mul-core PUBLIC include)

install(TARGETS mul-core
    PUBLIC_HEADER DESTINATION include/mul 
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
