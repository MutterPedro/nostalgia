#3. Dados três números inteiros positivos diferentes, mostrar qual é o maior entre eles. 

.data
msg_init: .asciiz "Digite um numero inteiro: "
msg_result: .asciiz "Maior: "

.text
	li $v0, 4
	la $a0, msg_init
	syscall
	li $v0, 5
	syscall
	add $t0,$t0,$v0
	li $v0, 4
	la $a0, msg_init
	syscall
	li $v0, 5
	syscall
	add $t1,$t1,$v0
	li $v0, 4
	la $a0, msg_init
	syscall
	li $v0, 5
	syscall
	add $t2,$t2,$v0
	add $a0,$zero,$t0
	add $a1,$zero,$t1
	add $a2,$zero,$t2
	jal maior
	add $t3,$zero,$v0
	li $v0, 4
	la $a0, msg_result
	syscall
	li $v0, 1
	add $a0,$zero,$t3
	syscall
	li $v0, 10
	syscall	
	
	maior: addi $sp, $sp, -4
		slt $t3,$t1,$t0
		slt $t4,$t2,$t0
		and $t5,$t3,$t4
		bne $t5,$zero, primeiro
		slt $t3,$t0,$t1
		slt $t4,$t2,$t1
		and $t5,$t3,$t4
		bne $t5,$zero, segundo
		j terceiro
		primeiro:
			add $v0,$zero,$t0
			addi $sp, $sp, 4
			jr $ra
		segundo:
			add $v0,$zero,$t1
			addi $sp, $sp, 4
			jr $ra
		terceiro:
			add $v0,$zero,$t2
			addi $sp, $sp, 4
			jr $ra