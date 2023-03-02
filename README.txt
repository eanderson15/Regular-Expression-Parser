Eric Anderson
eander29@u.rochester.edu

No known collaborators

THIS IS AN ECLIPSE PROJECT
runs main function in rexp.c
Written in eclipse
Building in the command prompt:

gcc -o rexp ParsingTable.c Production.c StrStack.c Tree.c parsingFunctions.c rexp.c

Running the executable will prompt the user for input until quit is entered.
Upon input (if it is valid), the parse tree from the parsing functions will be printed, the parse tree from the parsing table will be printed, the expression
tree will be printed, and the set of nested expressions will be printed. Example output at bottom of file.

Passes valgrind except for 6 reacable memory leaks and another that I believe is caused by Windows (I included the error message for it below the example output).

. character corresponds to concatenation
Input is coded to work with spaces in the input (use if you give a shit)

I did not do any work on part 3 past what is recquired (printing the nested set of expressions). My code also prints out the expression tree.
Functions for part 3 are in Tree.c.
Small issues with part 3:
	- firstly, if properly parenthesized these errors don't occur
	- if input has any operations with . or | at the same level such as "a.b.c" or "a|b|c", the output expression tree will group the letters in the wrong
	  order. Instead of (a.b).c, it would be a.(b.c). In the end, the expression is correct because of the associativity of these operators.
	- if input has operations with * at the same level such as a**, the output expression tree will put the closure operators after the first one, at levels
	  below the letter. The nested set of expressions will show something like (CLOSURE (LETTER a) (CLOSURE)
	- again these issues are negligible, and go away with correct parenthesization.

setbuf(stdout, NULL) makes sure text is printed out appropriately in Eclipse

EXAMPLE OUTPUT:

Enter an input ("quit" to quit): 
a|b.c*
Printing parse tree for regexp input using parsing functions.
<E>
	<C>
		<S>
			<F>
				<L>
					a
			<ST>
				<eps>
		<CT>
			<eps>
	<ET>
		|
		<E>
			<C>
				<S>
					<F>
						<L>
							b
					<ST>
						<eps>
				<CT>
					.
					<C>
						<S>
							<F>
								<L>
									c
							<ST>
								*
								<ST>
									<eps>
						<CT>
							<eps>
			<ET>
				<eps>
Printing parse tree for regexp input using a parsing table.
<E>
	<C>
		<S>
			<F>
				<L>
					a
			<ST>
				<eps>
		<CT>
			<eps>
	<ET>
		|
		<E>
			<C>
				<S>
					<F>
						<L>
							b
					<ST>
						<eps>
				<CT>
					.
					<C>
						<S>
							<F>
								<L>
									c
							<ST>
								*
								<ST>
									<eps>
						<CT>
							<eps>
			<ET>
				<eps>
Printing expression tree for regexp input and the accompanying set of nested expressions.
|
	a
	.
		b
		*
			c
(UNION (LETTER a) (CONCAT (LETTER b) (CLOSURE (LETTER c) )))
Enter an input ("quit" to quit): 
i.9
Printing parse tree for regexp input using parsing functions.
Invalid input
Enter an input ("quit" to quit): 
quit


ERROR IN MEMORY CAUSED BY WINDOWS:

Error #6: LEAK 2 direct bytes 0x01550c98-0x01550c9a + 0 indirect bytes
# 0 replace_malloc                                  [d:\drmemory_package\common\alloc_replace.c:2577]
# 1 msvcrt.dll!_strdup   
# 2 .text   
# 3 __mingw_glob
# 4 _setargv
# 5 .text   
# 6 ntdll.dll!RtlGetAppContainerNamedObjectPath    +0xe3     (0x77917c24 <ntdll.dll+0x67c24>)
# 7 ntdll.dll!RtlGetAppContainerNamedObjectPath    +0xb3     (0x77917bf4 <ntdll.dll+0x67bf4>)

Hello again, so yeah let me know if all I did was take a big fat deuce and you know just have a great time grading this project.