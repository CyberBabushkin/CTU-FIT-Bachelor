CXX=g++
LD=g++
CXXFLAGS=-std=c++11 -Wall -pedantic -Wno-long-long -O0 -ggdb
OF=./obj/

vpath %.cpp ./src

src = CBarChart.cpp CConfig.cpp CHistogram.cpp CLinePlot.cpp CVirtualPlot.cpp CCSV.cpp CExceptions.cpp CInterlocutor.cpp CPieChart.cpp main.cpp

objects = $(patsubst %.cpp,obj/%.o,$(src))

$(objects) : | obj

obj:
	@mkdir -p $@

all: asciiplots doc

run:
	@./babusand --hist ./examples/data.csv --bar ./examples/bar.csv ./examples/data1.csv

compile: asciiplots

doc:
	@mkdir -p ./doc || :
	@cd src; doxygen ./doxygen.conf
	@cp -R ./doc/html/* ./doc/ || :
	@rm -r ./doc/html || :m

asciiplots: obj/CBarChart.o obj/CConfig.o obj/main.o obj/CCSV.o obj/CExceptions.o obj/CHistogram.o obj/CInterlocutor.o obj/CLinePlot.o obj/CPieChart.o obj/CVirtualPlot.o
	@$(LD) -o babusand $^

clean:
	@rm -rf babusand ./obj ./doc ./Plots

obj/%.o: %.cpp
	@$(CXX) $(CXXFLAGS) -c -o $@ $<
