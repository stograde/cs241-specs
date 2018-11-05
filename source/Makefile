../CheckDates:	
	$(MAKE) CheckDates17 || $(MAKE) CheckDates14 || $(MAKE) CheckDates11

CheckDates17:	CheckDates.cpp datetime_utils.hpp json.hpp strtk.hpp
	g++ -std=c++17 -o ../CheckDates CheckDates.cpp

CheckDates14:	CheckDates.cpp datetime_utils.hpp json.hpp strtk.hpp
	g++ -std=c++14 -o ../CheckDates CheckDates.cpp

CheckDates11:	CheckDates.cpp datetime_utils.hpp json.hpp strtk.hpp
	g++ -std=c++11 -o ../CheckDates CheckDates.cpp