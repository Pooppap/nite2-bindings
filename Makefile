# location of the Python header files
PYTHON_VERSION = 3.6
PYTHON_INCLUDE = /Library/Frameworks/Python.framework/Versions/$(PYTHON_VERSION)/include/python$(PYTHON_VERSION)m

# location of the Boost Python include files and library
OPENNI2_INC = /usr/local/include/ni2
OPENNI2_LIB = /usr/local/lib/ni2
NITE2_INC = /Users/ca1216/Gits/NiTE2/Include
NITE2_LIB = /Users/ca1216/Gits/NiTE2/Redist
BOOST_INC = /usr/local/Cellar/boost/1.70.0/include
BOOST_LIB = /usr/local/Cellar/boost/1.70.0/lib
NUMPY_INC = /Library/Frameworks/Python.framework/Versions/3.6/lib/python3.6/site-packages/numpy/core/include
NUMPY_LIB = /Library/Frameworks/Python.framework/Versions/3.6/lib/python3.6/site-packages/numpy/core/lib

CC = g++

TARGET = nite2
OBJS = nite2.o openni2.o wrapper.o

$(TARGET).so: $(OBJS)
	$(CC) -shared -Wl,--export-dynamic $^ -L$(BOOST_LIB) -L$(OPENNI2_LIB) -L$(NITE2_LIB) -L$(NUMPY_LIB) -L/usr/lib/python$(PYTHON_VERSION)/config -lpython$(PYTHON_VERSION) -lboost_python-py27 -lOpenNI2 -lNiTE2 -o $@

$(OBJS): %.o: %.cpp
	$(CC) -Wall -Wextra -O2 -I$(PYTHON_INCLUDE) -I$(BOOST_INC) -I$(NITE2_INC) -I$(OPENNI2_INC) -I$(NUMPY_INC) -std=gnu++11 -fPIC -c $< -o $@

clean:
	rm -f *.o
	rm -f *.so

.PHONY: clean

