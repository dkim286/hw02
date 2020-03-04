# NAME
	
	Assignment 2 -- Processes and threads


# DESCRIPTION

	This submission contains both the "processes" part and the "threads" part of
	the assignment.


# SORTING

	If the 'sorting' executable doesn't exist, build using clang:

		$ clang -pthread sorting.c -o sorting
	
	Then run the executable:

		$ ./sorting


# TIME_PIPE

	If the 'time_pipe' executable doesn't exist, build using clang:
		
		$ clang time_pipe.c -o time_pipe

	Then run the executable with any desired command appended. For example:
		
		$ ./time_pipe ls -l -a


# TIME_SHM

	If the 'time_shm' executable doesn't exist, build using clang:

		$ clang time_shm.c -o time_shm -lrt
	
	Then run the executable with any desired command appended. For example:

		$ ./time_shm ls -l -a


# FILES

	readme_first.txt      -- This file.
	execution-details.txt -- Detailed instructions on how to run this assignment

	sorting.c          -- Source code for the 'sorting' assignment.
	sorting            -- Executable for the 'sorting' assignment.
	sorting_output.txt -- Example output of the sorting executable.

	time_pipe.c          -- Source code for the 'pipe' assignment.
	time_pipe            -- Executable.
	time_pipe_output.txt -- Example output.

	time_shm.c          -- Source code.
	time_shm            -- Executable.
	time_shm_output.txt -- Example output.
