CXX =  g++-14.2.0 -std=c++20 -fmodules-ts
CXXFLAGS = -Wall -g
HEADERFLAGS = -c -x c++-system-header
SOURCES = *.cc
HEADERS = algorithm cctype cmath fstream iostream limits map memory random set sstream string vector
EXEC = watan

$(EXEC): $(SOURCES)
	rm -rf gcm.cache
	$(CXX) $(HEADERFLAGS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SOURCES) -o $(EXEC)

.PHONY: clean 
clean:
	rm -f $(EXEC)
