	.data
prompt:	.asciiz	"Enter Your Name: "		# declares the prompt string
hello:	.asciiz	"Hello "			# declares the hello string
name:	.space	64			# 64 bytes of space reserved


	.text
	
	# print prompt
	la $a0, prompt	# load address of prompt
	li $v0, 4		# sys code
	syscall
	
	# user enters name
	la $a0, name	# load address of name
	li $a1, 64	# max of 63 characters + a NULL character
	li $v0, 8		# sys code
	syscall
	
	# print hello
	la $a0, hello	# load address of hello
	li $v0, 4		# sys code
	syscall
	
	# print name
	la $a0 name	# load address of name
	li $v0, 4		# sys code
	syscall
	
	
	
	
	# end gracefully
	li $v0, 10	# sys code
	syscall