# compiler
cc := g++

# source code
src := main.cpp src/kMeans.cpp src/myData.cpp src/Point.cpp

# final executable
exe := kmeans

# compile flags
flags := -std=c++17

# compile command
compile.cc = $(cc) $(flags) $^ -o $@

# make
$(exe): $(src)
	@$(compile.cc)

clean:
	@rm -rf $(exe)