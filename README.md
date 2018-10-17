Specs and Tools for the Hardware Design course


**./updateSpecs**
Updates your specs to the latest version in the repository.

This is done with:
	
	rm -r specs/_cache
	git pull origin master

The rm removes the cached .json files because they can get messed up when a new assignment is added.


**./CheckDates (hw# | lab#)**
*To create CheckDates, run make from the source subdirectory.* 
Finds the date of the first commit for each student for the specified assignment. These are printed out to the terminal. If specs are not cached, the program will automatically run cs251tk to cache them.