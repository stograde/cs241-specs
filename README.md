# Specs and Tools for the Hardware Design course

## updateSpecs
Updates your specs to the latest version in the repository.

```
./updateSpecs
```

Internally, this uses:

	rm -r specs/_cache
	git pull origin master

We remove the cached `.json` files because they can get messed up when a new assignment is added.

## CheckDates
```
./CheckDates [-a (hw# | lab# | ws#)...] [-s students...]
```

> To create CheckDates, run `make` from the source subdirectory.

Finds the date of the first commit for each student for each assignment. Specify individual students with `-s`, otherwise omit for all students. Specify assignments after `-a`. These are printed out to the terminal. If a specified spec is not found in the cache, the program will automatically run `cs251tk` to cache them.
