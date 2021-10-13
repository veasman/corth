BITS 64
segment .text
print:
	mov	r9, -3689348814741910323
	sub	rsp, 40
	mov	BYTE [rsp+31], 10
	lea	rcx, [rsp+30]
.L2:
	mov	rax, rdi
	lea	r8, [rsp+32]
	mul	r9
	mov	rax, rdi
	sub	r8, rcx
	shr	rdx, 3
	lea	rsi, [rdx+rdx*4]
	add	rsi, rsi
	sub	rax, rsi
	add	eax, 48
	mov	BYTE [rcx], al
	mov	rax, rdi
	mov	rdi, rdx
	mov	rdx, rcx
	sub	rcx, 1
	cmp	rax, 9
	ja 	.L2
	lea	rax, [rsp+32]
	mov	edi, 1
	sub	rdx, rax
	xor	eax, eax
	lea	rsi, [rsp+32+rdx]
	mov	rdx, r8
	mov	rax, 1
	syscall
	add	rsp, 40
	ret
global _start
_start:
	mov [args_ptr], rsp
addr_0:
	;; -- push int 10 --
	mov rax, 10
	push rax
addr_1:
	;; -- push int 20 --
	mov rax, 20
	push rax
addr_2:
	;; -- plus --
	pop rax
	pop rbx
	add rax, rbx
	push rax
addr_3:
	;; -- print --
	pop rdi
	call print
addr_4:
	;; -- push int 15 --
	mov rax, 15
	push rax
addr_5:
	;; -- push int 5 --
	mov rax, 5
	push rax
addr_6:
	;; -- minus --
	pop rax
	pop rbx
	sub rbx, rax
	push rbx
addr_7:
	;; -- print --
	pop rdi
	call print
addr_8:
	;; -- push int 3 --
	mov rax, 3
	push rax
addr_9:
	;; -- push int 4 --
	mov rax, 4
	push rax
addr_10:
	;; -- mul --
	pop rax
	pop rbx
	mul rbx
	push rax
addr_11:
	;; -- print --
	pop rdi
	call print
addr_12:
	;; -- push int 8 --
	mov rax, 8
	push rax
addr_13:
	;; -- push int 3 --
	mov rax, 3
	push rax
addr_14:
	;; -- mod --
	xor rdx, rdx
	pop rbx
	pop rax
	div rbx
	push rax
	push rdx
addr_15:
	;; -- print --
	pop rdi
	call print
addr_16:
	;; -- print --
	pop rdi
	call print
addr_17:
	mov rax, 60
	mov rdi, 0
	syscall
segment .data
segment .bss
args_ptr: resq 1
mem: resb 640000
