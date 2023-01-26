#4. Implementar o algoritmo Bubble Sort para ordenação de vetores de números inteiros com 5
#elementos. O programa deve receber como entrada 5 números inteiros e mostrar os números
#ordenados. A troca de valores entre duas posições do vetor deve ser implementada como um
#procedimento.

.data
msg_init: .asciiz "Digite um numero inteiro: "
msg_result: .asciiz "Vetor ordenado: "
quebra: .asciiz " "
.text
	addi $sp,$sp,-20
	la $s0,($sp)
	add $s1,$zero,$s1				#$so sera o valor de endereço no vetor e $s1 será um contador para saber quantas vezes as funções estão sendo chamadas
	lerVetor:    					#função que lera o vetor de 5 posições
		li $v0, 4
		la $a0, msg_init
		syscall
		li $v0, 5
		syscall
		sw $v0, 0($s0)
		addi $s0,$s0,4
		addi $s1,$s1,1
		bne $s1,5,lerVetor
		la $s0,($sp)
		add $s1,$zero,$zero
		add $s2,$zero,$zero
	bubble:					#funcao principal do bubble sort,ele testa se o valor numa casa é menor ou igual do que o proximo
		slti $t3,$s1,4
		bne $t3,1,resetar
		lw $t0, 0($s0)
		lw $t1, 4($s0)
		sle $t2,$t0,$t1
		addi $s0,$s0,4
		addi $s1,$s1,1
		
		beq $t2,1,bubble		#se for nao for menor ou igual ele chama o procedimento trocarValores
		addi $s2,$zero,1	
		add $a0,$zero,$t0
		add $a1,$zero,$t1
		jal trocarValores
		j bubble
		
	imprimirVetor:				#imprime os vetores em ordem crescente, usa a mesma logica do lerVetor
		add $s1,$zero,$zero
		la $s0,($sp)
		continua:		
		li $v0, 1
		lw $a0, ($s0)
		syscall
		li $v0, 4
		la $a0, quebra
		syscall
		
		addi $s1,$s1,1
		addi $s0,$s0,4
		bne $s1,5,continua
		li $v0, 10
		syscall	
	
	resetar:		#essa função é para quando o vetor já foi percorrido completamente, ai precisa ter seus valores iniciais restaurado para um novo percorrimento
		la $s0,($sp)
		add $s1,$zero,$zero
		beq $s2,$zero,imprimirVetor #$s2 é um flag que indica se o bubble entrou em trocarValores, se entrou ele retorna para o bubble, se não imprime o vetor ja ordenado
		add $s2,$zero,$zero
		j bubble
	
	trocarValores:		#função de trocar valores bem simples, na qual apenas trocamos os valores de um registrador com o proximo na memória
		sw $a1, -4($s0)
		sw $a0, 0($s0)
		jr $ra