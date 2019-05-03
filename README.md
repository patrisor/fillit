# fillit @ 42 Silicon Valley
Can you feel it?
### What is it?
The goal of this assignment is to find the smallest dimensional square by filling a particular set of tetrominoes in the most minimal amount of time. Our implementation involved using bits to represent our tetromino pieces, along with bitwise masking and operations to manipulate it's positions. We recursively backtracked to find the most optimal solution.
### How to use it?
	git clone https://github.com/patrisor/fillit.git
	cd fillit
	sh delete.sh
	./fillit *path-to-fillit-file*
	
	
	**NOTE:**
	cat testfile
	#...
	#...
	#...
	#...
	
	.##.
	.##.
	....
	....

	**Desired Output:**
	ABB.
	ABB.
	A...
	A...
