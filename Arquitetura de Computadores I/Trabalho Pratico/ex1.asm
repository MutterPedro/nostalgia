#1. Dado um número inteiro positivo n, calcular a soma dos n primeiros números inteiros positivos.

.data

msg_result: .asciiz "A soma e: "
msg_init: .asciiz "Digite um numero inteiro: "

.text 
	li $v0, 4	# chamada de sistema para exibir na tela (endereço da string)		
	la $a0, msg_init
	syscall	
	li $v0, 5	# chamada de sistema para ler variavel
	syscall
	move $t1,$v0
	add $t2,$zero,$zero
	while:
		beq $t1,$zero,end
		add $t2,$t2,$t1
		subi $t1,$t1, 1
		j while	
	end:
		li $v0, 4				
		la $a0, msg_result
		syscall		
		li $v0, 1		# chamada de sistema para exibir inteiro na tela
		add $a0,$zero, $t2
		syscall
		li  $v0, 10    		# chamada de sistema para sair
	        syscall 