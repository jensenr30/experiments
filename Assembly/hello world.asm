# MIPS Hello World program

	.data									# Data declaration section
out_msg:	.asciiz "Hello World! \n"		# the space inbetween '!' and '\n' is where the number will go. it is element 13/15 (including the terminating null char)

	.text
	
main:
	
	li $t0, 3			# put 3 into register $t0
	andi $t0, 7
	addi $t0, $t0, 48	# make $t0 a character
	la $a0, out_msg		# $a0 = address of string to print
	sw $t0, 52($a0) 	# jam the and result into the hello world string
	li $v0, 4 			# 4 = the code that will tell syscall to print a string. and you are storing 4 into the $vo register which syscall will look to for the code.
	syscall				# print "Hello World"
	
	# now to exit gracefully
	li $v0, 10 			# exit code
	syscall				# exit	 (syscall looks in $v0 once again)
	
# END OF PROGRAM
