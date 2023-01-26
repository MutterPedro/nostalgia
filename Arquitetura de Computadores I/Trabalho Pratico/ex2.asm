# 2. Dado um número inteiro positivo n, calcular o fatorial de n. Neste caso, a multiplicação deve ser implementada como um procedimento.

.data

msg_init: .asciiz "Digite um numero inteiro: "
msg_result: .asciiz "Fatorial do inteiro e: "

.text
	li $v0, 4
	la $a0, msg_init
	syscall
	li $v0, 5
	syscall
	add $t2,$t2,$v0
	add $t3,$t3,$v0
	fatorial:
		slti $s0,$t3,2
		bne $s0,$zero, exit
		add $a0,$zero,$t2
		subi $t3,$t3,1
		add $a1,$zero,$t3
		jal multiplication
		add $t2,$zero,$v0
		j fatorial
	exit:
		li $v0, 4
		la $a0, msg_result
		syscall
		li $v0, 1
		add $a0,$zero,$t2
		syscall
		li $v0, 10
		syscall
	
	
	multiplication: addi $sp, $sp, -4
			add $t0, $zero,$a0
			add $t1, $zero,$a1
			add $v0, $zero,$zero
			for:
				beq $t1,$zero, end
				add $v0, $v0,$t0
				subi $t1,$t1,1
				j for
			end:
				addi $sp, $sp, 4
				jr $ra
							