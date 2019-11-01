	.file	"asgn1.c" 											#file name
	.text
	.section	.rodata											#datasection is read-only
	.align 8													#next address is evenly divisible by 8
.LC0:															#local constant
	.string	"Enter the dimension of a square matrix: "			#string literal
.LC1:
	.string	"%d" 												#string literal
	.align 8 													#next address is evenly divisible by 8
.LC2:
	.string	"Enter the first matix (row-major): " 				#string literal
	.align 8 													#next address is evenly divisible by 8
.LC3:
	.string	"Enter the second matix (row-major): " 				#string literal
.LC4:
	.string	"\nThe result matrix:" 								#string literal
.LC5:
	.string	"%d "
	.text									# code starts	
	.globl	main 							# main is globally visible
	.type	main, @function					# main is a function
main:
.LFB0:
	.cfi_startproc							# Call Frame Information directive
	pushq	%rbp							# save old base pointer
	.cfi_def_cfa_offset 16					# Call Frame Information directives
	.cfi_offset 6, -16
	movq	%rsp, %rbp						# stack pointer is new		
	.cfi_def_cfa_register 6
	subq	$4832, %rsp						# Allocate bytes of space on the stack
	movq	%fs:40, %rax					#			
	movq	%rax, -8(%rbp)					# rbp - 8 <-- rax	
	xorl	%eax, %eax						#
	leaq	.LC0(%rip), %rdi				# rdi <-- starting of the format string, 1st param
	movl	$0, %eax						# eax <-- 0
	call	printf@PLT						# calls the printf function
	leaq	-4828(%rbp), %rax 				# rax <-- rbp - 4828 (rbp - 4828 is address of n)
	movq	%rax, %rsi						# rsi <-- rax 
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax						# eax <-- 0
	call	__isoc99_scanf@PLT 				# calls the scanf function -> takes input n from user
	leaq	.LC2(%rip), %rdi
	movl	$0, %eax						# eax <-- 0	
	call	printf@PLT
	movl	-4828(%rbp), %eax				# eax <-- rbp - 4828 address of number n 
	leaq	-4816(%rbp), %rdx				# rdx <-- rpb - 4816 address of matrix A
	movq	%rdx, %rsi						# rsi <-- rdx (quadword (64 bit))
	movl	%eax, %edi						# edi <-- eax (long (32 bit))						
	call	ReadMat 						# calls function ReadMat with arguments n, A
	leaq	.LC3(%rip), %rdi
	movl	$0, %eax 						# eax <-- 0	
	call	printf@PLT						# calls the print function
	movl	-4828(%rbp), %eax				# eax <-- rbp - 4828 address of n					
	leaq	-3216(%rbp), %rdx				# rdx <-- rbp - 3216 address of matrix B		
	movq	%rdx, %rsi						# rsi <-- rdx (quadword (64 bit))
	movl	%eax, %edi						# edi <-- eax (long (32 bit))
	call	ReadMat 						# calls function ReadMat with arguments n , B
	movl	-4828(%rbp), %eax				# eax <-- rbp - 4828 address of n		
	leaq	-1616(%rbp), %rcx				# rcx <-- rbp - 1616 address of Matrix C
	leaq	-3216(%rbp), %rdx				# rdx <-- rbp - 3216 address of Matrix B
	leaq	-4816(%rbp), %rsi				# rsi <-- rbp - 4816 address of Matrix A
	movl	%eax, %edi						# edi <-- eax
	call	MatMult 						# calls function MatMult with arguments n, A, B, C
	leaq	.LC4(%rip), %rdi
	call	puts@PLT						# calls the puts function
	movl	$0, -4824(%rbp)					# rbp - 4824 <-- 0 , i is set to 0 (i = 0)
	jmp	.L2 								# jump to .L2
.L5:
	movl	$0, -4820(%rbp)					# rbp - 4820 <-- 0 , j is set to 0 (j = 0)
	jmp	.L3 								# jump to .L3
.L4:
	movl	-4820(%rbp), %eax 				# eax <-- rbp - 4820  (makes eax point to j)
	movslq	%eax, %rcx						# rcx <-- eax (Shift to 64 bits) (rcx = j)
	movl	-4824(%rbp), %eax				# eax <-- rbp - 4824  (makes eax point to i)
	movslq	%eax, %rdx						# rdx <-- eax (Shift to 64 bits) (rdx = i)
	movq	%rdx, %rax						# rax <-- rdx (rax = i)
	salq	$2, %rax						# left shift rax by 2: rax = rax * 4 (rax = 4*i)
	addq	%rdx, %rax						# add rdx to rax (rax = 5*i)
	salq	$2, %rax 						# left shift rax by 2: rax = rax * 4 (rax = 20*i)
	addq	%rcx, %rax 						# add rcx to rax (rax = 20*i+j)
	movl	-1616(%rbp,%rax,4), %eax 		# eax <--C[i][j] as { C[i][j] = rbp - 1616 (C[0][0]) + 80*i+4j (4 (int bytes) * (i rows and j columns))} 
	movl	%eax, %esi 						# esi <-- eax
	leaq	.LC5(%rip), %rdi
	movl	$0, %eax
	call	printf@PLT 						# calls the printf function (prints C[i][j])
	addl	$1, -4820(%rbp) 				# add 1 to rbp - 4820 (j=j+1)
.L3:
	movl	-4828(%rbp), %eax 				# eax <-- rbp - 4828 (rbp - 4828 is n)
	cmpl	%eax, -4820(%rbp) 				# compare eax (n) & rbp - 4820 (j)
	jl	.L4 								# if j < n jump to .L4
	movl	$10, %edi 						# edi <-- 10
	call	putchar@PLT 					# calls the putchar function ( prints "\n" )
	addl	$1, -4824(%rbp) 				# add 1 to rbp - 4824 (i = i+1 )
.L2:
	movl	-4828(%rbp), %eax 				# eax <-- rbp - 4828 (rbp - 4828 is n)
	cmpl	%eax, -4824(%rbp) 				# compare eax (n) & rbp - 4824 (i)
	jl	.L5 								# if i < n jump to .L5
	movl	$0, %eax 						# eax <-- 0
	movq	-8(%rbp), %rcx 					# rcx <-- rbp - 8
	xorq	%fs:40, %rcx								
	je	.L7 								
	call	__stack_chk_fail@PLT
.L7:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc							# Call Frame Information directive
.LFE0:
	.size	main, .-main
	.globl	ReadMat 						# ReadMat is globally visible
	.type	ReadMat, @function				# ReadMat is a function				
ReadMat: 									# Function ReadMat starts
.LFB1:
	.cfi_startproc 							# Call Frame Information directive
	pushq	%rbp 							# save old base pointer
	.cfi_def_cfa_offset 16 					# Call Frame Information directive
	.cfi_offset 6, -16
	movq	%rsp, %rbp 						# stack pointer is new
	.cfi_def_cfa_register 6
	subq	$32, %rsp 						# Allocate bytes of space on the stack for local variables 
	movl	%edi, -20(%rbp) 				# rbp - 20 <-- edi, rbp - 20 stores n
	movq	%rsi, -32(%rbp) 				# rbp - 32 <-- rsi, rbp - 32 stores data[0][0]
	movl	$0, -8(%rbp) 					# rbp - 8 <-- 0 , rbp - 8 is i (i = 0)
	jmp	.L9 								# jump to .L9 (L9 is outer for loop)
.L12:
	movl	$0, -4(%rbp) 					# rbp - 4 <--0, rbp - 4 is j (j = 0)
	jmp	.L10 								# jump to .L10 
.L11:
	movl	-8(%rbp), %eax 					# eax <-- rbp - 8 (rbp - 8 is i), eax = i
	movslq	%eax, %rdx 						# rdx <-- eax (Shift to 64 bits), rdx = i
	movq	%rdx, %rax 						# rax <-- rdx, rax = i
	salq	$2, %rax 						# left shift rax by 2: rax = rax * 4, rax = 4*i
	addq	%rdx, %rax 						# add rdx to rax, rax = 5*i 
	salq	$4, %rax 						# left shift rax by 4: rax = rax * 16, rax = 80*i
	movq	%rax, %rdx 						# rdx <-- rax, rdx = 80*i 
	movq	-32(%rbp), %rax 				# rax <-- rbp - 32, rax stores data[0][0]
	addq	%rax, %rdx 						# add rax to rdx, rdx stores data[i][0]
	movl	-4(%rbp), %eax 					# eax <-- rbp - 4 (rbp - 4 is j) 
	cltq									# sign-extends eax to a quadword			
	salq	$2, %rax 						# left shift rax by 2: rax = 4*j
	addq	%rdx, %rax 						# add rdx to rax, rdx stores data[i][j] 
	movq	%rax, %rsi 						# rsi <-- rax
	leaq	.LC1(%rip), %rdi
	movl	$0, %eax 						# eax <-- 0
	call	__isoc99_scanf@PLT 				# calls scanf function -> takes input data[i][j]
	addl	$1, -4(%rbp) 					# add 1 to rbp - 4 ( j = j + 1 ) 
.L10:
	movl	-4(%rbp), %eax 					# eax <-- rbp - 4 (rbp - 4 is j)
	cmpl	-20(%rbp), %eax 				# compare rbp - 20 (n) and eax (j)
	jl	.L11 								# if j<n jump to .L11 (L10 is inner for loop)
	addl	$1, -8(%rbp) 					# add 1 to rbp - 8 ( i = i + 1 )
.L9:
	movl	-8(%rbp), %eax 					# eax <-- rbp - 8 (rbp - 8 is i)
	cmpl	-20(%rbp), %eax 				# compare rbp - 20 (n) and eax (i)
	jl	.L12 								# if i < n jump to .L12 
	nop
	leave
	.cfi_def_cfa 7, 8
	ret 									# return
	.cfi_endproc
.LFE1:
	.size	ReadMat, .-ReadMat
	.section	.rodata
	.align 8
.LC6:
	.string	"\nThe transpose of the second matrix:"
	.text
	.globl	TransMat                		# TransMat is globally visible
	.type	TransMat, @function 			# TransMat is a function
TransMat: 									# Function TransMat starts
.LFB2:
	.cfi_startproc 							# Call Frame Information directive 
	pushq	%rbp 							# save old base pointer
	.cfi_def_cfa_offset 16 					# Call Frame Information directive 
	.cfi_offset 6, -16
	movq	%rsp, %rbp 						# stack pointer is new
	.cfi_def_cfa_register 6
	subq	$32, %rsp  						# Allocate bytes of space on the stack for local variables 
	movl	%edi, -20(%rbp) 				# rbp - 20 <-- edi (rbp - 20 is n)
	movq	%rsi, -32(%rbp) 				# rbp - 32 <-- edi (rbp - 32 is data[0][0])
	movl	$0, -12(%rbp) 					# rbp - 12 <-- 0, rbp - 12 is i (i = 0)
	jmp	.L14 								# jump to .L14 (L14 is outer for loop) 
.L17:
	movl	$0, -8(%rbp) 					# rbp - 8 <-- 0 (j = 0)
	jmp	.L15 								# jump to .L15
.L16:
	movl	-12(%rbp), %eax 				# eax <-- rbp - 12 (rbp - 12 is i)
	movslq	%eax, %rdx 						# rdx <-- eax (Shift to 64 bits) (rdx = i)
	movq	%rdx, %rax 						# rax <-- rdx (rax = i)	
	salq	$2, %rax 						# left shift rax by 2: rax = rax * 4 (rax = 4*i)
	addq	%rdx, %rax 						# add rdx to rax (rax = 5*i) 
	salq	$4, %rax 						# left shift rax by 4: rax = rax * 16 (rax = 80*i)		
	movq	%rax, %rdx 						# add rax to rdx (rdx = 80*i)
	movq	-32(%rbp), %rax 				# rax <-- rbp - 32 (rax is data[0][0])
	addq	%rax, %rdx 						# add rax to rdx (rdx is data[i][0])
	movl	-8(%rbp), %eax 					# eax <-- rbp - 8 (rbp - 8 is j)
	cltq 									# sign-extends eax to a quadword
	movl	(%rdx,%rax,4), %eax  			# eax <-- data[i][j] as rdx + 4*rax = data[i][0] + 4*j = data[i][j] 
	movl	%eax, -4(%rbp) 					# rbp - 4 <-- eax (rbp - 4 is t) 
	movl	-8(%rbp), %eax 					# eax <-- rbp - 8 (rbp - 8 is j)
	movslq	%eax, %rdx 						# rdx <-- eax (Shift to 64 bits) (rdx = j)
	movq	%rdx, %rax 						# rax <-- rdx	(rax = j)
	salq	$2, %rax   						# left shift rax by 2: rax = rax * 4 (rax = 4*j)
	addq	%rdx, %rax 						# add rdx to rax (rax = 5*j)
	salq	$4, %rax 						# left shift rax by 4: rax = rax * 16 (rax = 80*j)
	movq	%rax, %rdx 						# rdx <-- rax 	(rdx = 80*j)
	movq	-32(%rbp), %rax					# rax <-- rbp - 32 (rax stores data[0][0])
	leaq	(%rdx,%rax), %rsi				# rsi <-- data[j][0] 
	movl	-12(%rbp), %eax 				# eax <-- rbp - 12 (rbp - 12 is i)
	movslq	%eax, %rdx 						# rdx <-- eax (Shift to 64 bits) (rdx = i)
	movq	%rdx, %rax                      # rax <-- rdx (rax = i)
	salq	$2, %rax 						# left shift rax by 2: rax = rax * 4 (rax = 4*i)
	addq	%rdx, %rax 						# add rdx to rax (rax = 5*i)
	salq	$4, %rax 						# left shift rax by 4: rax = rax * 16 (rax = 80*i)
	movq	%rax, %rdx 						# rdx <-- rax (rdx = 80*i)
	movq	-32(%rbp), %rax 				# rax <-- rbp - 32 (rax stores data[0][0])
	leaq	(%rdx,%rax), %rcx 				# rcx <-- data[i][j]
	movl	-12(%rbp), %eax 				# eax <-- rbp - 12 (rbp - 12 is i)
	cltq 									# sign-extends eax to a quadword
	movl	(%rsi,%rax,4), %edx 			# edx <-- data[j][i]
	movl	-8(%rbp), %eax 					# eax <-- rbp - 8 (rbp - 8 is j)
	cltq 									# sign-extends eax to a quadword
	movl	%edx, (%rcx,%rax,4) 			# data[i][j] <-- data[j][i]
	movl	-8(%rbp), %eax 					# eax <-- rbp - 8 (rbp - 8 is j)
	movslq	%eax, %rdx 						# rdx <-- eax (Shift to 64 bits) (rdx = j)
	movq	%rdx, %rax 						# rax <-- rdx (rax = j)
	salq	$2, %rax 						# left shift rax by 2: rax = rax * 4 (rax = 4*j)
	addq	%rdx, %rax 						# add rdx to rax (rax = 5*j)
	salq	$4, %rax 						# left shift rax by 4: rax = rax * 16 (rax = 80*j)
	movq	%rax, %rdx 						# rdx <-- rax (rdx = 80*j)
	movq	-32(%rbp), %rax 				# rax <-- rbp - 32 (rax stores data[0][0])
	leaq	(%rdx,%rax), %rcx 				# rcx <-- data[j][0]
	movl	-12(%rbp), %eax 				# eax <-- rbp - 12 (rbp - 12 is i)
	cltq 									#
	movl	-4(%rbp), %edx 					# edx <-- rbp - 4 (rbp - 4 is t)
	movl	%edx, (%rcx,%rax,4) 			# data[j][i] <-- t
	addl	$1, -8(%rbp) 					# add 1 to rbp - 8 (j = j + 1)
.L15:
	movl	-8(%rbp), %eax 					# eax <-- rbp - 8 ( rbp - 8 is j)
	cmpl	-12(%rbp), %eax 				# compare eax (j) & rbp - 12 (i) 
	jl	.L16 								# if j < i jump to .L16
	addl	$1, -12(%rbp)   				# add 1 to rbp - 12 (i = i + 1)
.L14:
	movl	-12(%rbp), %eax 				# eax <-- rbp - 12 (rbp - 12 is i)
	cmpl	-20(%rbp), %eax 				# compare eax (i) and rbp - 20 (n)
	jl	.L17 								# if i < n jump to .L17
	leaq	.LC6(%rip), %rdi 				# 
	call	puts@PLT 						# calls the puts
	movl	$0, -12(%rbp) 					# rbp - 12 <-- 0 (i = 0)
	jmp	.L18 								# jump to .L18
.L21: 										#
	movl	$0, -8(%rbp) 					# rbp - 8 <-- 0 (j = 0)
	jmp	.L19 								# jump to .L19
.L20: 										# 
	movl	-12(%rbp), %eax 				# eax <-- rbp - 12 (rbp - 12 is i) (eax = i)
	movslq	%eax, %rdx 						# rdx <-- eax (Shift to 64 bits) (rdx = i)
	movq	%rdx, %rax 						# rax <-- rdx  (rax = i)
	salq	$2, %rax 						# left shift rax by 2: rax = rax * 4 (rax = 4*i) 
	addq	%rdx, %rax 						# add rdx to rax (rax = 5*i)
	salq	$4, %rax 						# left shift rax by 4: rax = rax * 16 (rax = 80*i)
	movq	%rax, %rdx 						# rdx <-- rax (rdx = 80*i)
	movq	-32(%rbp), %rax 				# rax <-- rbp - 32 (rax stores data[0][0])
	addq	%rax, %rdx 						# add rax to rdx (rdx stores data[i][j])
	movl	-8(%rbp), %eax 					# eax <-- rbp - 8 (rbp - 8 is j) (eax = j)
	cltq 									# sign-extends eax to a quadword
	movl	(%rdx,%rax,4), %eax 			# eax <-- data[i][j] as rdx + 4*rax= data[i][0]+4*j=data[i][j]
	movl	%eax, %esi 						# esi <-- eax
	leaq	.LC5(%rip), %rdi 				#
	movl	$0, %eax 						#
	call	printf@PLT 						# calls print function
	addl	$1, -8(%rbp) 					# adds 1 to rbp - 8 (j = j + 1)
.L19: 										
	movl	-8(%rbp), %eax					# eax <-- rbp - 8 (rbp - 8 is j)
	cmpl	-20(%rbp), %eax 				# compare eax (j) and rbp - 20 (n)
	jl	.L20 								# if j < n jump to .L20
	movl	$10, %edi 						# edi <-- 10
	call	putchar@PLT 					# calls putchar function
	addl	$1, -12(%rbp) 					# adds 1 to rbp - 12 (i = i + 1) 
.L18: 			
	movl	-12(%rbp), %eax 				# eax <-- rbp - 12 (rbp - 12 is i)
	cmpl	-20(%rbp), %eax 				# compare eax (i) and rbp - 20 (n)
	jl	.L21 								# if i < n jump to .L21
	nop 									#
	leave 									#
	.cfi_def_cfa 7, 8 						#
	ret 									# return
	.cfi_endproc 							#
.LFE2: 										#
	.size	TransMat, .-TransMat 			#
	.globl	VectMult 						# VectMult is globally visible
	.type	VectMult, @function 			# VectMult is a function
VectMult:									# VectMult function starts
.LFB3: 										#
	.cfi_startproc 							# Call Frame Information directive
	pushq	%rbp 							# save old base pointer
	.cfi_def_cfa_offset 16 					# Call Frame Information directive 
	.cfi_offset 6, -16 						#
	movq	%rsp, %rbp    					# stack pointer is new
	.cfi_def_cfa_register 6 				#
	movl	%edi, -20(%rbp) 				# rbp - 20 <-- edi (rbp - 20 is n)
	movq	%rsi, -32(%rbp) 				# rbp - 32 <-- rsi (rbp - 32 is firstMat)
	movq	%rdx, -40(%rbp)					# rbp - 40 <-- rdx (rbp - 40 is secondMat)
	movl	$0, -4(%rbp) 					# rbp - 4 <-- 0 (rbp - 4 is result) (result = 0)
	movl	$0, -8(%rbp) 					# rbp - 8 <-- 0 (rbp - 8 is i) (i=0)
	jmp	.L23 								# jump to .L23 (for loop)
.L24:
	movl	-8(%rbp), %eax 					# eax <-- rbp - 8 (rbp - 8 is i)
	cltq 									# sign-extends eax to a quadword
	leaq	0(,%rax,4), %rdx 				# rdx <-- rax * 4 (rdx = 4*i)
	movq	-32(%rbp), %rax 				# rax <-- rbp - 32 (rax stores firstMat[0])
	addq	%rdx, %rax 						# add rdx to rax (rax stores firstMat[i])
	movl	(%rax), %edx 					# edx <-- rax (edx stores firstMat[i])
	movl	-8(%rbp), %eax 					# eax <-- rbp - 8 (rbp - 8 is i)
	cltq 									# sign-extends eax to a quadword
	leaq	0(,%rax,4), %rcx 				# rcx <-- rax * 4 (rcx = 4*i)
	movq	-40(%rbp), %rax 				# rax <-- rbp - 40 (rax stores secondMat[0])
	addq	%rcx, %rax 						# add rcx to rax (rax stores secondMat[i])
	movl	(%rax), %eax 					# eax <-- rax (eax stores secondMat[i])
	imull	%edx, %eax 						# eax = eax * edx (eax stores firstMat[i]*secondMat[i])
	addl	%eax, -4(%rbp) 					# add eax to rbp - 4 (result = result + firstMat[i]*secondMat[i]) 
	addl	$1, -8(%rbp) 					# add 1 to rbp - 8 ( i = i + 1)
.L23: 						
	movl	-8(%rbp), %eax 					# eax <-- rbp - 8 (rbp - 8 is i)
	cmpl	-20(%rbp), %eax 				# compare eax (i) and rbp - 20 (n)
	jl	.L24 								# if i < n jump to .L24
	movl	-4(%rbp), %eax 					# eax <-- rbp - 4 (rbp - 4 is result) 
	popq	%rbp 							# pop the stack
	.cfi_def_cfa 7, 8 						#
	ret 									# return 
	.cfi_endproc 							#
.LFE3: 										
	.size	VectMult, .-VectMult 			#
	.globl	MatMult 						# MatMult is globally visible
	.type	MatMult, @function 				# MatMult function starts
MatMult:
.LFB4:
	.cfi_startproc 							# Call Frame Information directive
	pushq	%rbp 							# save old base pointer
	.cfi_def_cfa_offset 16 					# Call Frame Information directive
	.cfi_offset 6, -16 						#
	movq	%rsp, %rbp 						# stack pointer is new
	.cfi_def_cfa_register 6 				# 
	pushq	%rbx 							#
	subq	$56, %rsp 						# Allocate bytes of space on the stack for local variables
	.cfi_offset 3, -24 						#
	movl	%edi, -36(%rbp) 				# rbp - 36 <-- edi (rbp - 36 is n)
	movq	%rsi, -48(%rbp) 				# rbp - 48 <-- rsi (rbp - 48 is firstMat)
	movq	%rdx, -56(%rbp) 				# rbp - 56 <-- rdx (rbp - 56 is secondMat)
	movq	%rcx, -64(%rbp) 				# rbp - 64 <-- rcx (rbp - 64 is M)
	movq	-56(%rbp), %rdx 				# rdx <-- rbp - 56 (rdx = secondMar)
	movl	-36(%rbp), %eax 				# eax <-- rbp - 36 (eax = n)
	movq	%rdx, %rsi 						# rsi <-- rdx (rsi = secondMat)
	movl	%eax, %edi 						# edi <-- eax (edi = n)
	call	TransMat 						# calls TransMat function with arguments n, secondMat
	movl	$0, -24(%rbp) 					# rbp - 24 <-- 0 (rbp - 24 is i) (i = 0)
	jmp	.L27 								# jump to .L27 (outer for loop)
.L30:
	movl	$0, -20(%rbp) 					# rbp - 20 <-- 0 (j = 0)
	jmp	.L28 								# jump to .L28
.L29:
	movl	-20(%rbp), %eax 				# eax <-- rbp - 20 ( rbp - 20 is j)
	movslq	%eax, %rdx 						# rdx <-- eax (Shift to 64 bits) (rdx = j)
	movq	%rdx, %rax 						# rax <-- rdx (rax = j)
	salq	$2, %rax 						# left shift rax by 2: rax = rax * 4 (rax = 4*j)
	addq	%rdx, %rax 						# add rdx to rax (rax = 5*j)
	salq	$4, %rax 						# left shift rax by 4: rax = rax * 16 (rax = 80*j)
	movq	%rax, %rdx   					# rdx <-- rax (rdx = 80*j)
	movq	-56(%rbp), %rax 				# rax <-- rbp - 56 (rax stores secondMat[0][0])
	addq	%rdx, %rax 						# add rdx to rax (rax stores secondMat[j][0])
	movq	%rax, %rsi 						# rsi <-- rax (rsi stores secondMat[j][0])
	movl	-24(%rbp), %eax 				# eax <-- rbp - 24 (rbp - 24 is i)
	movslq	%eax, %rdx 						# rdx <-- eax (Shift to 64 bits) (rdx = i)
	movq	%rdx, %rax 						# rax <-- rdx (rax = i)
	salq	$2, %rax 						# left shift rax by 2: rax = rax * 4 (rax = 4*i)
	addq	%rdx, %rax 						# add rdx to rax (rax - 5*i)
	salq	$4, %rax 						# left shift rax by 4: rax = rax * 16 (rax = 80*i)
	movq	%rax, %rdx 						# rdx <-- rax (rdx = 80*i)
	movq	-48(%rbp), %rax 				# rax <-- rbp - 48 (rax stores firstMat[0][0])
	addq	%rdx, %rax 						# add rdx to rax (rax stores firstMat[i][0])
	movq	%rax, %rcx 						# rcx <-- rax (rcx stores firstMat[i][0])
	movl	-24(%rbp), %eax 				# eax <-- rbp - 24 (rbp - 24 is i)
	movslq	%eax, %rdx 						# rdx <-- eax (Shift to 64 bits) (rdx = i)
	movq	%rdx, %rax 						# rax <-- rdx (rax = i)
	salq	$2, %rax 						# left shift rax by 2: rax = rax * 4 (rax = 4*i)
	addq	%rdx, %rax 						# add rdx to rax (rax = 5*i)
	salq	$4, %rax 						# left shift rax by 4: rax = rax * 16 (rax = 80*i)
	movq	%rax, %rdx 						# rdx <-- rax (rdx = 80*i)
	movq	-64(%rbp), %rax 				# rax <-- rbp - 64 (rax stores M[0][0])
	leaq	(%rdx,%rax), %rbx 				# rbx stores M[i][0]
	movl	-36(%rbp), %eax 				# eax <-- rbp - 36 (rbp - 36 is n)
	movq	%rsi, %rdx						# rdx <-- rsi (rdx stores secondMat[j][0])
	movq	%rcx, %rsi 						# rsi <-- rcx (rsi stores firstMat[i][0])
	movl	%eax, %edi 						# edi <-- eax (edi stores n)
	call	VectMult 						# calls VectMult function with arguments n, firstMat[i][0], secondMat[j][0]
	movl	%eax, %edx 						# edx <-- eax, edx = VectMult(n, &firstMat[i][0], &secondMat[j][0])
	movl	-20(%rbp), %eax 				# eax <-- rbp - 20 ( rbp - 20 is j)
	cltq 									# sign-extends eax to a quadword 
	movl	%edx, (%rbx,%rax,4) 			# rbx + 4*rax <-- edx which is M[i][j] = VectMult(n, &firstMat[i][0], &secondMat[j][0]) as rbx+4*rax = M[i][0]+4*j=M[i][j]
	addl	$1, -20(%rbp) 					# adds 1 to rbp - 20 (j = j + 1)
.L28:
	movl	-20(%rbp), %eax 				# eax <-- rbp - 20 (rbp - 20 is j)
	cmpl	-36(%rbp), %eax 				# compares eax (j) and rbp - 36 (n)
	jl	.L29 								# if j < n jump to .L29 (inner for loop)
	addl	$1, -24(%rbp) 					# add 1 to rbp - 24 ( i = i + 1)
.L27: 										#
	movl	-24(%rbp), %eax 				# eax <-- rbp - 24 (rbp - 24 is i) 
	cmpl	-36(%rbp), %eax 				# compare eax(i) and rbp - 36 (n)
	jl	.L30 								# if i < n jump to .L30
	nop 									#
	addq	$56, %rsp 						# add 56 to rsp
	popq	%rbx 							# pop from stack
	popq	%rbp 							# pop from stack
	.cfi_def_cfa 7, 8 						#
	ret 									# return
	.cfi_endproc 							#
.LFE4: 										#
	.size	MatMult, .-MatMult 				#
	.ident	"GCC: (Ubuntu 7.4.0-1ubuntu1~18.04.1) 7.4.0"    #
	.section	.note.GNU-stack,"",@progbits 				#
