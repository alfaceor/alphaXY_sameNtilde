TARGET=mainAlphaXY_sameNtilde

OBJE= IOParams.o Chain.o HeatBath.o TimeStats.o

OBJS= $(TARGET).o $(OBJE)

LIBS= -lgsl -lgslcblas -lm -lboost_program_options

#%.o : %.c
#	$(COMPILE) -c $< -o $@ -g -pg

all: $(TARGET) $(TARGET)Incorrect $(TARGET)IncorrectNoHB heatBathTest mainAlphaXY_FNB mainAlphaXY_FNBIncorrect testAlphaFNB #genIniCond

IOParams.o:IOParams.cpp
	$(CXX) -O2 -c IOParams.cpp -o $@

HeatBath.o:HeatBath.cpp
	$(CXX) -O2 -c HeatBath.cpp -o $@

Chain.o:Chain.cpp
	$(CXX) -O2 -c Chain.cpp -o $@

TimeStats.o:TimeStats.cpp
	$(CXX) -O2 -c TimeStats.cpp -o $@


$(TARGET).o: $(TARGET).cpp
	$(CXX) -O2 -c $(TARGET).cpp -o $@
  
$(TARGET): $(OBJS)
	$(CXX) -O2 -o $(TARGET) $(OBJS) $(LIBS)

$(TARGET)Incorrect.o: $(TARGET)Incorrect.cpp
	$(CXX) -O2 -c $(TARGET)Incorrect.cpp -o $@


$(TARGET)IncorrectNoHB.o: $(TARGET)IncorrectNoHB.cpp
	$(CXX) -O2 -c $(TARGET)IncorrectNoHB.cpp -o $@

$(TARGET)Incorrect: $(TARGET)Incorrect.o $(OBJE)
	$(CXX) -O2 -o $(TARGET)Incorrect $(TARGET)Incorrect.o $(OBJE) $(LIBS)

$(TARGET)IncorrectNoHB: $(TARGET)IncorrectNoHB.o $(OBJE)
	$(CXX) -O2 -o $(TARGET)IncorrectNoHB $(TARGET)IncorrectNoHB.o $(OBJE) $(LIBS)

mainAlphaXY_FNB:mainAlphaXY_FNB.cpp $(OBJE)
	$(CXX) -O2 -o mainAlphaXY_FNB mainAlphaXY_FNB.cpp $(OBJE) $(LIBS)
	
mainAlphaXY_FNBIncorrect:mainAlphaXY_FNBIncorrect.cpp $(OBJE)
	$(CXX) -O2 -o mainAlphaXY_FNBIncorrect mainAlphaXY_FNBIncorrect.cpp $(OBJE) $(LIBS)

heatBathTest:heatBathTest.cpp IOParams.o
	$(CXX) -O2 -o heatBathTest heatBathTest.cpp IOParams.o $(LIBS)

NtildeIvsNtilde:NtildeIvsNtilde.cpp IOParams.o
	$(CXX) -O2 -o NtildeIvsNtilde NtildeIvsNtilde.cpp IOParams.o $(LIBS)


testAlphaFNB:testAlphaFNB.cpp $(OBJE)
	$(CXX) -O2 -o testAlphaFNB testAlphaFNB.cpp $(OBJE) $(LIBS)

# GENERATE INITIAL CONDITIONS
#genIniCond:genIniCond.cpp $(OBJE)
#	$(CXX) -o genIniCond genIniCond.cpp $(OBJE) $(LIBS)


clean:
	rm -f $(OBJS) $(TARGET) $(TARGET) mainAlphaXY_FNB mainAlphaXY_FNBIncorrect heatBathTest


