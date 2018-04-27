
project(iterable)

#set(HEDEAR_FILES Iterable.h IterableIterator.h ZipperIterator.h IterableIteratorWrapper.h EnumerateIterator.h ProductIterator.h)
#set(SOURCE_FILES ZipperIterator.cpp ProductIterator.cpp ProductIterator.cpp)

#add_library(libiterable STATIC ${SOURCE_FILES} ${HEDEAR_FILES})
#target_include_directories(libiterable PUBLIC .)

add_library(libiterable STATIC Iterable.cpp Iterable.h)
target_include_directories(libiterable PUBLIC .)
