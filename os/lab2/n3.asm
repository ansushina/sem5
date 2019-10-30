.386P 
 
descr struc 
limit dw 0 
base_l dw 0 
base_m db 0 
attr_1 db 0 
attr_2 db 0 
base_h db 0 
descr ends 

intr struc
offs_l dw 0
sel    dw 0
rsv    db 0
attr1  db 0
offs_h dw 0
intr   ends

PM segment para public use32
assume CS:PM, DS:PM
	GDT label byte
	gdt_null descr <0,0,0,0,0,0> ;Hyлевoй дескриnтор 
	gdt_data descr <data_size-1,0,0,92h> 
    ;Ceлектор 8, сегмент данных, 92h = 10010010b
	gdt_code16 descr <RM_size-1,,,98h> 
    ;Селектор 16, сегмент команд, 98h = 10011000b
	gdt_stack descr <255,0,0,92h> ;Селектор 24, сегмент стека 
	gdt_screen descr <4095,8000h,0Bh,92h> ;Селектор 32, видеобуфер 
	gdt_code32 descr <PM_size-1,,,98h,40h> ;40h = 01000000b
	gdt_data2 descr <0FFFFh,0,0,92h,10001111b> ;Ceлектор 48, сегмент данных на 4 Гб
	gdt_size=$-GDT
	
	IDT label word
	intr 32 dup (<>)
	idt_08 intr <0,40,0,8Eh,0>
	idt_09 intr <0,40,0,8Eh,0>
	idt_size=$-IDT

	pdescr dw 0, 0, 0 ;Псевдодескриnтор 
	mes1   db 27,'Real mode' 
	mes2   db 27,'Protected mode'
	timer  dd 0
	s_pos  dw 500
	escape db 0  
	mmask  db ?
	smask  db ?
	ascii  db 0, 0, 49, 50, 51, 52, 53, 54, 55, 56, 57, 48, 45, 61, 0, 0
		   db 81, 87, 69, 82, 84, 89, 85, 73, 79, 80, 91, 93, 0, 0, 65, 83
		   db 68, 70, 71, 72, 74, 75, 76, 59, 39, 96, 0, 92, 90, 88, 67
		   db 86, 66, 78, 77, 44, 46, 47
	data_size=$-GDT

print_eax_in_ebx macro base
	local divide
	push EAX
	push EDI
	push EDX
	
	mov EDI, base
	
divide:	
	xor EDX, EDX
	div EDI
	add EDX, '0'
	mov DH, 1Eh
	mov ES:[EBX], DX
	sub BX, 2
	cmp EAX, 0
	jnz divide
	
	pop EDX
	pop EDI
	pop EAX
endm
	
exc proc
	iret
exc endp

new_08h proc
	push EAX
	push EBX
	
	mov EAX, timer
	mov EBX, 380
	print_eax_in_ebx 10
	inc EAX
	mov timer, EAX
	
	mov	AL, 20h
	out	20h, AL
	pop EBX
	pop EAX

	iretd
new_08h endp

new_09h proc
	push EAX
	push EBX
	push EDX
	
	xor EAX, EAX
	in AL, 60h
	cmp AL, 1Ch
	jne next
	mov escape, 1
	jmp exit

next:
	cmp AL, 80h
	ja exit
	xor EDX, EDX
	mov BX, s_pos
	mov DL, ascii[EAX]
	mov DH, 1Eh
	mov ES:[BX], DX
	add BX, 2
	mov s_pos, BX

exit:	
	in Al, 61h
	or AL, 80h
	out 61h, AL
	
	mov AL, 20h
	out 20h, AL
	pop EDX
	pop EBX
	pop EAX
	iretd
new_09h endp

continue:
	;Делаем адресуемыми данные и стек
	mov AX, 8 
	mov DS, AX
	
	mov AX, 24
	mov SS, AX
	
	mov AX, 32 ;Селектор сеrмента видеобуфера 
	mov ES, AX 
	
	mov DI, 160 
	mov AH, 1Eh
	mov EBX, offset mes2	
	mov CX, 15
screen2:
	mov AL, byte ptr [EBX]
	stosw
	inc BX
	loop screen2
	
	;Обработка прерываний в цикле, пока не нажат Enter
	sti
interrupts:
	test escape, 1	
	jz interrupts
	
	cli
	
	;Определим объём доступной физ. памяти
mem:
	mov EAX, 48
	mov FS, AX
	mov EBX, 100001h
	mov EDI, 49h ;рандомное значение
	mov ECX, 0FFFFFFFFh

check_mem:
	mov EDX, FS:[EBX]
	mov FS:[EBX], EDI ; запись сигнатуры
	mov EAX, FS:[EBX] ; чтение сигнатуры
	cmp EAX, EDI ; сравнение сигнатуры
	jne end_mem
	mov FS:[EBX], EDX
	inc EBX
	cmp ECX, EBX
	jne check_mem
	
end_mem:
	mov EAX, EBX
	mov EBX, 336
	print_eax_in_ebx 10
	
	mov gdt_data.limit, 0FFFFh
	mov gdt_code16.limit, 0FFFFh
	mov gdt_code32.limit, 0FFFFh
	mov gdt_screen.limit, 0FFFFh
	mov gdt_stack.limit, 0FFFFh
	
	db 0EAh 
	dd offset return
	dw 16
	
PM_size=$-GDT
PM ends

RM segment para public use16  
assume CS:RM, DS:PM, SS:stk
main:
	xor EAX, EAX 
	mov AX, PM
	mov DS, AX
	
	mov AX, 0B800h
	mov ES, AX
	mov EBX, offset mes1
	mov AH, 0Fh
	mov DI, 0
	mov CX, 10
screen1:
	mov AL, byte ptr [EBX]
	stosw
	inc BX
	loop screen1
 
	mov AX, PM
	;Вычислим 32-битовый лин адрес сегмента данных и загрузим его
	;в дескриптор сегмента данных GDT. 
	shl EAX, 4
	mov EBP, EAX 
	mov EBX, offset gdt_data
	mov [BX].base_l, AX
	rol EAX, 16 
	mov [BX].base_m, AL
	;Аналогично для линейных адресов сегментов команд и стека
	xor EAX, EAX 
	mov AX, CS
	shl EAX, 4
	mov EBX, offset gdt_code16
	mov [BX].base_l, AX
	rol EAX, 16 
	mov [BX].base_m, AL 
	
	xor EAX, EAX 
	mov AX, SS 
	shl EAX, 4 
	mov EBX, offset gdt_stack
	mov [BX].base_l, AX
	rol EAX, 16 
	mov [BX].base_m, AL
	
	xor EAX, EAX
	mov AX, PM
	shl EAX, 4
	mov EBX, offset gdt_code32
	mov [BX].base_l, AX
	rol EAX, 16 
	mov [BX].base_m, AL 
	
	;Подготовим псевдодескриптор и загрузим регистр GDTR
	mov dword ptr pdescr+2, EBP
	mov word ptr pdescr, gdt_size-1
	lgdt fword ptr pdescr
	
	;Подготовим переход в защищённый режим
	cli 
	mov AL, 8Fh
	out 70h, AL
	
	;Сохраним маски контроллеров
	in AL, 21h
	mov mmask, AL
	in AL, 0A1h
	mov smask, AL
	;Установка новой маски и перепрограммирование контроллера прерываний
	mov AL, 11h
	out 20h, AL
	mov AL, 20h
	out 21h, AL
	mov AL, 4
	out 21h, AL
	mov AL, 1
	out 21h, AL
	mov AL, 0FCh
	out 21h, AL
	mov AL, 0FFh
	out 0A1h, AL
	
	;Вычисление адресов новых обработчиков прерываний
	mov EAX, offset new_08h
	mov idt_08.offs_l, AX
	shr EAX, 16
	mov idt_08.offs_h, AX
	
	mov EAX, offset new_09h
	mov idt_09.offs_l, AX
	shr EAX, 16
	mov idt_09.offs_h, AX
	
	;Подготовим псевдодескриптор и загрузим регистр IDTR
	mov word ptr pdescr, idt_size-1
	xor EAX, EAX
	mov EAX, offset IDT
	add EAX, EBP
	mov dword ptr pdescr+2, EAX
	lidt fword ptr pdescr
	
	;Откроем линию А20
	mov AL, 0D1h
	out 64h, AL 
	mov AL, 0DFh
	out 60h, AL

	;Переход в защищённый режим
	mov EAX, CR0
	or  EAX, 1 ; (56)Установим бит РЕ
	mov CR0, EAX 
	
	db 66h
	db 0EAh 
	dd offset continue
	dw 40 ;Селектор 2 сегмента команд 

return: 
	;Закроем линию А20
	mov AL, 0D1h
	out 64h, AL
	mov AL, 0DDh
	out 60h, AL
	
	mov EAX, CR0 
	and EAX, 0FFFFFFFEh ;Сбросим бит PЕ
	mov CR0, EAX 
	
	db 0EAh
	dw $+4
	dw RM
	;Восстановим операционную среду реального режима
	mov AX, PM
	mov DS, AX
	mov AX, stk
	mov SS, AX 
	
	;Восстановим маску и контроллер прерываний
	mov AL, 11h
	out 20h, AL
	mov AL, 8
	out 21h, AL
	mov AL, 4
	out 21h, AL
	mov AL, 1
	out 21h, AL
	mov AL, mmask
	out 21h, AL
	mov AL, smask
	out 0A1h, AL
	
	mov pdescr, 3FFh ;IDTR реального режима
	mov word ptr pdescr+1, 0
	mov word ptr pdescr+2, 0
	lidt fword ptr pdescr

	sti
	mov AL, 0 
	out 70h, AL  
	
	mov EBX, offset mes1
	mov AH, 0Fh
	mov DI, 640
	mov CX, 10
screen3:
	mov AL, byte ptr [BX]
	stosw
	inc BX
	loop screen3

	mov AX, 4C00h
	int 21h 

RM_size=$-main 
RM ends

stk segment stack 'stack'
	db 256 dup ('^')
stk ends 

end main 