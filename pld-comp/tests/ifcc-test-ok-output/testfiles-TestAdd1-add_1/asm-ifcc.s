# declaration de a
# declaration de b
# expression avec a
# expression avec b
.globl  main
main:

# prologue
 pushq	%rbp
 movq	%rsp, %rbp

# declaration de _tmp8 avec la valeur 8
 movl	$8, -8(%rbp)


# declaration de _tmp12 avec la valeur 6
 movl	$6, -12(%rbp)


# declaration de _tmp16 avec la valeur _tmp8 + _tmp12
 movl	-8(%rbp), %eax
 addl	-12(%rbp), %eax
 movl	%eax, -16(%rbp)


# declaration de a avec _tmp16
 movl	-16(%rbp), %eax
 movl	%eax, -4(%rbp)


# declaration de b avec a
 movl	-4(%rbp), %eax
 movl	%eax, -20(%rbp)


# retour de b
 movl	-20(%rbp), %eax


# epilogue
 movq	%rbp, %rsp
 popq  %rbp
 ret

