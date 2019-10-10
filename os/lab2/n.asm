.386P 
 
descr struc 
limit dw 0 
base_l dw 0 
base_m db 0 
attr_1 db 0 
attr_2 db 0 
base_h db 0 
descr ends 

data segment 
;Таблица глобальных дескрипторов GDT 
gdt_null descr <0,0,0,0,0,0> ;Hyлевoй дескриnтор 
gdt_data descr <data_size-1,0,0,92h> ;Ceлектор 8, сегмент данных 
gdt_code descr <code_size-1,,,98h> ;Селектор 16, сегмент команд 
gdt_stack descr <255,0,0,92h> ;Селектор 24, сегмент стека 
gdt_screen descr <4095,8000h,0Bh,92h> ;Селектор 32, видеобуфер 
gdt_size=$-gdt_null

pdescr dq 0 ;Псевдодескриnтор 
attr   db 1Eh
mes1   db 27,'Real mode' 
mes2   db 27,'Protected mode'
data_size=$-gdt_null 
data ends 

text segment 'code' use16  
assume CS:text,DS:data 
main proc
	xor EAX, EAX 
	mov AX, data 
	mov DS, AX
	
	mov AX, 0B800h
	mov ES, AX
	mov EBX, offset mes1
	mov AH, attr
	mov DI, 0
	mov CX, 10
screen1:
	mov AL, byte ptr [EBX]
	stosw
	inc BX
	loop screen1
 
 
	mov AX, DS
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
	mov EBX, offset gdt_code 
	mov [BX].base_l, AX
	rol EAX, 16 
	mov [BX].base_m, AL 
	
	xor EAX,EAX 
	mov AX, SS 
	shl EAX, 4 
	mov EBX, offset gdt_stack
	mov [BX].base_l, AX
	rol EAX, 16 
	mov [BX].base_m, AL
	;Подготовим псевдодескриптор и загрузим регистр GDTR
	mov dword ptr pdescr+2, EBP
	mov word ptr pdescr, gdt_size-1
	lgdt pdescr
	;Подготовим переход в защищённый режим
	cli 
	mov AL, 80h
	out 70h, AL
	;Переход в защищённый режим
	mov EAX, CR0
	or  EAX, 1 ; (56)Установим бит РЕ
	mov CR0, EAX 
	
	db 0EAh 
	dw offset continue
	dw 16 ;Селектор сегмента команд 
	
continue: 
	;Делаем адресуемыми данные и стек
	mov AX, 8 
	mov DS, AX
	
	mov AX, 24
	mov SS, AX
	
	mov AX, 32 ;Селектор сеrмента видеобуфера 
	mov ES, AX 
	mov DI, 160 
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
	mov EBX, 100001h
	mov DL, 49h ;рандомное значение
	mov ECX, 0ffeffffeh

check_mem:
	mov DH, DS:[EBX]
	mov DS:[EBX], DL ; запись сигнатуры
	cmp DS:[EBX], DL ; сравнение сигнатуры
	jne end_mem
	mov DS:[EBX], DH
	inc EBX
	loop check_mem
	
end_mem:
	mov EAX, EBX
	mov BX, 340
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
	
	
	;Подrотовим переход в реальный режим 
	;Сформируем и загрузим дескрипторы для реапьноrо режима 
	mov gdt_data.limit, 0FFFFh
	mov gdt_code.limit, 0FFFFh
	mov gdt_stack.limit, 0FFFFh
	mov gdt_screen.limit, 0FFFFh
	
	mov AX, 8 ;Загрузим теневой регистр 
	mov DS, AX ;сегмента данных 
	mov AX, 24 ;Заrрузим теневой регистр 
	mov SS, AX ;стека 
	mov AX, 32 ;Загрузим теневой регистр 
	mov ES, AX ;дополнительноrо сегмента 

	db 0EAh
	dw offset go
	dw 16 
	
	;Переход в реальный режим
go: 
	mov EAX, CR0 
	and EAX, 0FFFFFFFEh ;Сбросим бит PЕ
	mov CR0, EAX 
	db 0EAh 
	dw offset return
	dw text 
	
	; Восстановим операционную среду реального режима
return: 
	mov AX, data
	mov DS, AX
	mov AX, stk
	mov SS, AX 

	sti
	mov AL, 0 
	out 70h, AL  
	
	mov EBX, offset mes1
	mov AH, attr
	mov DI, 640
	mov CX, 10
screen3:
	mov AL, byte ptr [BX]
	stosw
	inc BX
	loop screen3

	mov AX, 4C00h
	int 21h 
main endp 

code_size=$-main 
text ends

stk segment stack 'stack'
	db 256 dup ('^')
stk ends 

end main 