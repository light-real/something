CXXFLAGS = -std=c++11
del = rm -f
CXX = g++

# 目标文件
TARGET = reverseString

#源文件
SRCS = head.hpp reverseString.cpp

all:$(TARGET) reverseStr replaceNumber removeExtraSpaces removeElement

$(TARGET):$(SRCS)
	$(CXX) $(CXXFLAGS) -o reverseString reverseString.cpp

reverseStr:reverseStr.cpp
	$(CXX) $(CXXFLAGS) -o reverseStr reverseStr.cpp

replaceNumber:replaceNumber.cpp
	g++ $(CXXFLAGS) -o replaceNumber replaceNumber.cpp

removeExtraSpaces:removeExtraSpaces.cpp
	g++ $(CXXFLAGS) -o removeExtraSpaces removeExtraSpaces.cpp 

removeElement:removeElement.cpp
	g++ $(CXXFLAGS) -o removeElement removeElement.cpp
#清理规则
clean:
	$(del) $(TARGET) reverseStr replaceNumber removeExtraSpaces removeElement