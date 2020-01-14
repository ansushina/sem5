.386P 
 
descr struc 
limit dw 0 
base_l dw 0 
base_m db 0 
attr_1 db 0 
attr_2 db 0 
base_h db 0 
descr ends 

PM segment para public use32
assume CS:PM, DS:PM
	GDT label byte
	gdt_null descr <0,0,0,0,0,0> ;Hyлевoй дескриnтор 

	gdt_data descr <data_size-1,0,0,10010010b,00000000b> 
	;Ceлектор 8, сегмент данных

	gdt_code16 descr <RM_size-1,0,0,10011000b,00000000b> 
	;Селектор 16, сегмент команд

	gdt_stack descr <255,0,0,10010010b,00000000b> ;Селектор 24, сегмент стека 

	gdt_screen descr <4095,8000h,0Bh,10010010b,00000000b> ;Селектор 32, видеобуфер 

	gdt_code32 descr <PM_size-1,0,0,10011000b,01000000b> ;40h = 01000000b
	; бит 6 - 1 - разрядность операндов 32 бита 

	gdt_data2 descr <0FFFFh,0,0,10010010b,10001111b> 
	;Ceлектор 48, сегмент данных на 4 Гб
	gdt_size=$-GDT

	pdescr dq 0 ;Псевдодескриnтор 
	attr   db 1Eh
	mes1   db 27,'Real mode' 
	mes2   db 27,'Protected mode'
	data_size=$-GDT

continue:
	;Делаем адресуемыми данные и стек
	mov AX, 8 
	mov DS, AX
	
	mov AX, 24
	mov SS, AX
	
	; выведем соообщение
	mov AX, 32 ;Селектор сеrмента видеобуфера 
	mov ES, AX 
	mov DI, 160 ; отступ 
	mov CX, 15
	mov AH, attr
	mov EBX, offset mes2
	
screen2:
	mov AL, byte ptr [EBX]
	stosw
	inc BX
	loop screen2
	
	;Определим объём доступной физ. памяти
mem:
	mov AX, 48 ; номер селектора данных 
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
	mov BX, 336 ; отступ 
	mov ECX, 10
divide:	
	xor EDX, EDX
	div ECX
	add EDX, '0'
	mov DH, attr
	mov ES:[BX], DX
	sub BX, 2
	cmp EAX, 0
	jnz divide
	
	;Закроем линию А20
	mov AL, 0D1h
	out 64h, AL
	mov AL, 0DDh
	out 60h, AL
	
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
	lgdt pdescr
	;Подготовим переход в защищённый режим
	cli 
	mov AL, 8Fh
	out 70h, AL
	
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
	mov EAX, CR0 
	and EAX, 0FFFFFFFEh ;Сбросим бит PЕ
	mov CR0, EAX 
	
	db 0EAh
	dw $+4
	dw RM
; Восстановим операционную среду реального режима
	mov AX, PM
	mov DS, AX
	mov AX, stk
	mov SS, AX 

	sti
	mov AL, 0 
	out 70h, AL  
	
	mov EBX, offset mes1
	mov AH, 0Fh
	mov DI, 640 ; отступ
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