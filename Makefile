#------------------------------------------------------------------------------
#  Makefile for CSE 101 Programming Assignment 8
#
#  make                     makes WordFrequency
#  make DictionaryClient    makes DictionaryClient
#  make clean               removes all binaries
#  make WordFrequencyCheck  runs WordFrequency under valgrind on Gutenberg
#  make DictionaryCheck     runs DictionaryClient under valgrind
#------------------------------------------------------------------------------

MAIN           = WordFrequency
ORDER          = Order
ADT            = Dictionary
SOURCE         = $(MAIN).cpp
OBJECT         = $(MAIN).o
ORDER_OBJECT    = $(ORDER).o
ORDER_SOURCE   = $(ORDER).cpp
ADT_TEST       = $(ADT)Client
ADT_SOURCE     = $(ADT).cpp
ADT_OBJECT     = $(ADT).o
ADT_HEADER     = $(ADT).h
COMPILE        = g++ -std=c++17 -Wall -c
LINK           = g++ -std=c++17 -Wall -o
REMOVE         = rm -f
MEMCHECK       = valgrind --leak-check=full

$(MAIN): $(OBJECT) $(ADT_OBJECT)
	$(LINK) $(MAIN) $(OBJECT) $(ADT_OBJECT)

$(ORDER): $(ORDER_OBJECT) $(ADT_OBJECT)
	$(LINK) $(ORDER) $(ORDER_OBJECT) $(ADT_OBJECT)

$(ADT_TEST): $(ADT_TEST).o $(ADT_OBJECT)
	$(LINK) $(ADT_TEST) $(ADT_TEST).o $(ADT_OBJECT)

$(OBJECT): $(SOURCE) $(ADT_HEADER)
	$(COMPILE) $(SOURCE)

$(ADT_TEST).o: $(ADT_TEST).cpp $(ADT_HEADER)
	$(COMPILE) $(ADT_TEST).cpp

$(ADT_OBJECT): $(ADT_SOURCE) $(ADT_HEADER)
	$(COMPILE) $(ADT_SOURCE)

$(ORDER_OBJECT): $(ORDER_SOURCE)
	$(COMPILE) $(ORDER_SOURCE)

clean:
	$(REMOVE) $(MAIN) $(ORDER) $(ADT_TEST) $(OBJECT) $(ORDER_OBJECT) $(ADT_TEST).o $(ADT_OBJECT)

$(MAIN)Check: $(MAIN)
	$(MEMCHECK) $(MAIN) Gutenberg myGutenberg-out

$(ADT)Check: $(ADT_TEST)
	$(MEMCHECK) $(ADT_TEST)

