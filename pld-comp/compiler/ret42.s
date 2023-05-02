# fonction add
# declaration de c
# expression avec a
# expression avec c
# declaration de a
# declaration de b
# declaration de e
# appel de fonction add
# input parametre a
# expression avec a
# input parametre b
# expression avec b
# expression avec e
.globl  add
add:

# prologue
 pushq	%rbp
 movq	%rsp, %rbp

# argument %edi
 movl	%edi, -4(%rbp)


# argument %esi
 movl	%esi, -8(%rbp)


# declaration de c avec a
 movl	-4(%rbp), %eax
 movl	%eax, -12(%rbp)


# retour de c
 movl	-12(%rbp), %eax


# epilogue
 movq	%rbp, %rsp
 popq  %rbp
 ret

.globl  main
main:

# prologue
 pushq	%rbp
 movq	%rsp, %rbp
 subq	  $12, %rsp

# declaration de _tmp20 avec la valeur 1
 movl	$1, -20(%rbp)


# declaration de a avec _tmp20
 movl	-20(%rbp), %eax
 movl	%eax, -16(%rbp)


# declaration de _tmp28 avec la valeur 3
 movl	$3, -28(%rbp)


# declaration de b avec _tmp28
 movl	-28(%rbp), %eax
 movl	%eax, -24(%rbp)


# appel de la fonction add
 movl	-16(%rbp), %edi
 movl	-24(%rbp), %esi
 call add
 movl	%eax, -36(%rbp)


# declaration de e avec _tmp36
 movl	-36(%rbp), %eax
 movl	%eax, -32(%rbp)


# retour de e
 movl	-32(%rbp), %eax


# epilogue
 movq	%rbp, %rsp
 popq  %rbp
 ret

