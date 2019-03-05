S_DIR := $(shell pwd)/src
T_DIR := $(shell pwd)/test

CC := g++ #clang++ #g++
# -lxcb for xcb lib
# -lX11 for X11 lib
# -g for include debugging symbols
# -pthread enable multithreading
CCFLAGS := -std=c++11 -g

# список каталогов с исходыми кодами
SRC_DIRS := $(shell find $(S_DIR) -type d)
TEST_DIRS := $(shell find $(T_DIR) -type d) $(SRC_DIRS)

# список всех файлов *.cpp
SRC := $(shell find $(S_DIR) -name *.cpp)
# test files contains all files in ../src and exclude sba-main file
TEST_SRC := $(shell find {$(T_DIR),$(S_DIR)} -name *.cpp | sed '/sba-main/d')

# Укороченный вызов функции patsubst
# $(имя_переменной:.старый_суффикс=.новый_суффикс)
# полный вызов выглядит так: OBJS := $(patsubst   %.cpp, %.o, $(SRCS))
# получится список всех объектных файлов *.o разделенный пробелами
#OBJS := $(SRCS:.cpp=.o)
SRC_OBJS := $(notdir $(patsubst %.cpp, %.o, $(SRC)))
TEST_OBJS := $(notdir $(patsubst %.cpp, %.o, $(TEST_SRC)))


all: test

# all: sba sba_test

# создание выполняемого файла
sba: $(SRC_OBJS)
	$(CC) $(CCFLAGS) $^ -o $@
	
# создание выполняемого файла test
sba_test: $(TEST_OBJS)
	$(CC) $(CCFLAGS) $^ -o $@
	
test: sba_test
	@./$<
	
# список каталогов, где шаблонные правила будут искать зависимости
VPATH := $(TEST_DIRS)

# шаблонное правило создания объектных файлов
# флаг -I для того чтобы разрешить компилятору искать заголовочные файлы
# в указанных директориях
# флаг -MMD для создания файлов *.d со списком зависимостей: сам исходный файл,
# и файлы, включаемые с помощью директивы #include "имя_файла"  
%.o: %.cpp
	$(CC) $(CCFLAGS) -c -MMD $(addprefix -I, $(TEST_DIRS)) $<
	@printf "\e[36m$(CC)\e[32m %s\e[0m\n" $@
include $(wildcard *.d)

# очистка	
clean:
	rm -rf *.o *.d sba sba_test

print:
	echo $(TEST_DIRS)
	
.PHONY: clean

