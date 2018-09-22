list(APPEND mul-core-headers
    include/mul/delegate.hpp
    include/mul/event.hpp
    include/mul/factory.hpp
    include/mul/memory.hpp
    include/mul/non_copyable.hpp
    include/mul/signal.hpp
    include/mul/timer.hpp
    include/mul/type_traits.hpp
)

list(APPEND mul-core-sources
    src/mul/event.cpp 
    src/mul/signal.cpp
)

add_library(mul-core ${mul-core-sources})

set_target_properties(mul-core PROPERTIES PUBLIC_HEADER "${mul-core-headers}")

target_include_directories(mul-core PUBLIC include)

install(TARGETS mul-core
    PUBLIC_HEADER DESTINATION include/mul 
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib)
