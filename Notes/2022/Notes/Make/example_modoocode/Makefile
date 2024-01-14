# target: prerequisites
# (tab)recipe

# can use patterns only on target and prerequisites
#  <patterns>
# % : wildcard, similar to *

# for recipe use Makefile's auto variables
#  <Makefile's auto variables>
# $@ : target name
# $< : first prerequisites
# $^ : all prerequisites
# $? : newer prerequisites than target
# $+ : similar to $^ but includes all overlaps

# Compiling with Treads
# $ make -j8
# $ make -j$(nproc)

CC = g++
CXXFLAGS = -Wall -O2
LDFLAGS =  # linker opetions
# if header files are in ./include
#INCLUDE = -Iinclude/
SRC_DIR = ./src
OBJ_DIR = ./obj
TARGET = main

# Make 할 소스 파일들
# wildcard 로 SRC_DIR 에서 *.cc 로 된 파일들 목록을 뽑아낸 뒤에
# notdir 로 파일 이름만 뽑아낸다
# (e.g SRCS 는 foo.cc bar.cc main.cc 가 된다)ubuntu keyboard param for rd
SRCS = $(notdir $(wildcard $(SRC_DIR)/*.cc))

# OBJS 에서 .o 로 끝나는 부분을 .d 로 모두 대체
OBJS = $(SRCS:.cc=.o)

# OBJS 안의 %.o 파일들 이름 앞에 $(OBJ_DIR)/ 를 붙인다
OBJECTS = $(patsubst %.o,$(OBJ_DIR)/%.o,$(OBJS))

DEPS = $(OBJECTS:.o=.d)

all: main

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.cc
	$(CC) $(CXXFLAGS) -c $< -o $@ -MD $(LDFLAGS)

$(TARGET) : $(OBJECTS)
	$(CC) $(CXXFLAGS) $(OBJECTS) -o $(TARGET) $(LDFLAGS)

# PHONY : fake, doen't check for edit time -ish.
.PHONY: clean all
clean:
	rm -f $(OBJECTS) $(DEPS) $(TARGET)

# g++ -MD 시 .d 파일생성
# include 로 Makefile 에 포함
-include $(DEPS)