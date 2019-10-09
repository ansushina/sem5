.386P ;(1)
;Структура для описания дескрипторов сегментов 

descr struc  ;(2) 
limit dw 0; (3)ГрAHица (биты О ... 15) 
base_l dw 0 ; (4)База, биты 0...15 
base_m db 0 ; (5)База, биты 16.. 23 
attr_1 db 0 ; (б)Байт атрибутов 1 
attr_2 db 0 ; (7)Граница (биты 16 ... 19) и атрибуты 2 
base_h db 0 ; (8)База, биты 24 ... 31 
descr ends  ; (9)

data segment ; (10) Начало сегмента данных 
;Таблица глобальных дескриnторов GDT 
gdt_null descr <0,0,0,0,0,0>; (11);нулевой дескриптор 
gdt_data descr <data_size-1,0,0,92h>; (12)Ceлектор 8, сеrмент данных 
gdt_code descr <code_size-1,,,98h>; (13)Селектор 16, сеrмент комAHд 
gdt_stack descr <255,0,0,92h>; (14)Селектор 24, сегмент стека 
gdt_screen descr <4095,8000h,0Bh,92h>; (15)Селектор 32, видеобуфер 
gdt_size=$-gdt_null ; (16) Размер GDТ 

; Поля данных прогаммы
pdescr 	dq 0 	;(17)Псевдодескриnтор 
sym 	db 1 	; (18) Символ для вывода иа экрAH
attr	db 1Eh 	; (19) его атрибут 
mes 	db 27,'[0 real modeee ',27,' [O$'; (20) 
s      db ?
data_size=$-gdt_null ; (21) Размер сегмента данных 
data ends ; ( 22) Кокец сеruеита дAHиых 


text segment 'code' use16; (23)Укажем 16-разряный режим 
	assume CS:text,DS:data; (24) 
main proc ; (25) 
	xor EAX, EAX 				;  (26) Очистим EAX 
	mov AX, data 				; (27)Загрузим в DS сеrмеитиый 
	mov DS, AX 					; (28) адрес сеrмеита данных 
; Вычислим 32-битовый линейный адрес сеrмента даииых и загрузим ero 
; в дескриптор сеrмеита данных а GDT. 
	shl EAX, 4 					;  (29) В EAX пинейинй баsоаый адрес 
	mov EBP, EAX				; (3О)СохрAHим его в EBP 
	mov EBX, offset gdt_data	; (31)В BX адрес дескриптора 
	mov [BX].base_l, AX 		; (32)Заrруsим NIIaдiDYJO часть баsы 
	rol EAX, 16 				; (33)0бмен С'l!аршей и МJJадшей попоаии EAX 
	mov [BX].base_m, AL			; (34) Эаl'руsим cpeдИICIIO часть баsы 
; Allanor...мo дп11 пииейхоrо адреса сеrмекта коN&НД 
	xor EAX, EAX 				; (35)0чистим EAX 
	mov AX, CS 					; (36)ЛIIpec сеrмента коN&НД 
	shl EAX, 4 					; (37)Ywкo3DD& иа 16 .
	mov EBX,offset gdt_code		; (38)Адрес дескриптора 
	mov [BX].base_l, AX		; (39) Заl'руsим NJJaдiDYJO часть баsы 
	rol EAX,16 					; ( 40) Обмен попоаии EAX 
	mov [BX].base_m, AL			; (41)Эаrруsим cpeдИICIIO часть баsк 
	
	
	;AIIano:t'ичиo дn• пииейиоrо адреса cerNeaтa стека 
	xor EAX, EAX					 ; (421 
	mov AX, SS					; (43) 
	shl EAX, 4					; (441 
	mov EBX, offset gdt_stack	; (45)
	mov [BX].base_l, AX			; (46) 
	rol EAX, 16 ; (471 
	mov [BX].base_m, AL				; (48) 
	;1Doaroeoaнw аоеадодескрКПтор pdescr и s&:t'pysим реrистр GDТR 
	
	mov dword ptr pdescr + 2, EBP				; (49)Sasa GDT, биты о ... 31 
	mov word ptr pdescr, gdt_size-1				; (50)I'раиица GDТ 
	lgdt pdescr 						; ( 511 Зarpys101 реrистр GDТR 
	
	;JПOJ~rOT08NNC8 к вереходу а sащкщеииый р~ 
	cli 							; (52)Эаnрет апnаратных арерыааиий 
	mov AL, 80h 				; (53) Заnрет NМI 
	out 70h, AL 				;J(541Порт КМОП-мккроCXеNЫ 
	;Переходим а sUDCJaeИКIIIIЙ режим 
	mov EAX, CR0 				;1 (55 ) Попучим содера;иwое CR0 
	or 	EAX, 1 						; (56)УстAHоаим бит Р! 
	mov CR0, EAX 				; (57 1 9ашааек иаsад в CR0 
;Тепер• процессор paбO'.I!acw а a..,ar,e1111CIН ~ 
;9аrру.каем в CS:IP сепехтор:смещеиие точхи continue 
;и sаодно очищаем очередь коwаид 
	db 0EAh 				; (58 1 Код комAHды far j:111p 
	dw offset continue			; (591Смащеиие 
	dw 16			 ; (601Се.пектор сеrмента комаид 
	
	
continue:      ; (611 ;Депаем адресуе~ даииые 
	mov AX, 8 				;  ( 62 1 Сепектор сеrмента дiUUUoiX 
	mov DS, AX 				;			 (631 ; Депаем адресуеwым стек 
	
	mov AX, 24 				;  ( 641 Се.пектор сеrмента стека 
	mov SS,AX 			; (651 
	
	;Ииици:а.пиsИруем ES и ВЫIIОДИМ симвопъr 
	mov AX,32 				; (ббiСепектор сеrмента видеобуtера 
	mov ES,AX 				; (671 
	mov BX, 800 				; 1 68 1 НачАЛьное смещение на :~крAHе 
	mov CX, 64 				;  ( б 9 1 Чиспо IIЫIIOдюaa« симво.поа 311 
	mov AX,word ptr sym				; (701Начuьный симво.п с атрибутом 
	
screen: 
	mov ES:[BX], AX 			; (11 1 В11111од в аидеобуфер 
	add BX, 2 				; (721Сместкыс~ в видеобуфере 
	inc AX 				;  ( 1 Э 1 СпедУJCXЦИЙ симво.п 
	loop screen				 ; (74 1 Ци1<J1 11111110да на :акраи 
	
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
	xor EDX, EDX
	mov EAX, EBX
	mov BX, 972
	mov ECX, 10
divide:	
	div ECX
	add EDX, '0'
	mov s, DL
	mov DX, word ptr s
	mov ES:[BX], DX
	sub BX, 2
	mov EDX, 0
	cmp EAX, 0
	jnz divide
	
	
	;Подrотовим переход в реальный реzкм 
	;Сформируем и sarpysим дескрипторы АЛ~ реапьноrо режима 
	mov gdt_data.limit,0FFFFh; (751Гракица сеrwента дAXккх 
	mov gdt_code.limit,0FFFFh; (761Гракица сеrwента комаид 
	mov gdt_stack.limit,0FFFFh; (77)ГрAHица сеrмента стека 
	mov gdt_screen.limit,0FFFFh; (781Гракица допопнитепьиоrо 
	
	;сеrмента 
	mov AX, 8 ;  ( 79 ) Эаrруsим теневой реrистр 
	mov DS,AX ; (80)сеrмента данных 
	mov AX, 24 ; (81) 9аrруsим теневой реrистр 
	mov SS,AX ; (82)стека 
	mov AX, 32 ; (83) Эаrруsим теневой реrистр 
	mov ES,AX ; (841допОJIИИтепьиоrо сеrмента 
	
	;Выпопким дапьиий переход АЛ~ тоrо, чтобы sAHово sаrруsить 
	;сепектор в реrистр CS и модифицироаать ero теиеаой реrистр 
	db 0EAh ; (851Коwаидой дanJtнero перехода 
	dw offset go ; (861 sarpysим тенеаой реrистр 
	dw 16 ; (871сеrыента коwаид ; ПepeiiUIIDЧИМ pe:uuc процессера 
	
	
go: mov EAX,CR0 ; (881По.пучим' содер:кимое CR0 
	and EAX, 0FFFFFFEh; (891Сбросим бит Pl 
	mov CR0, EAX ; ISO 1 9&lUOIIeM и а s ад в CR0 
	db 0EAh ;  ( 911 Код КОМAHд• far jlllp 
	dw offset return; (921Смещеиие 
	dw text ; (931Сеrмеит ;Тепер• процеосор CIIOIIa рабО'.I!ам/ 11 pe~IICIН ~ 
	; ВосстAHовим операциоииУJD среду pean•иoro p-
	
	
	return: 
	mov AX,data ; (94)80CC'JI&JIOIIJ04 
	mov DS,AX ; (95)адресуемость даииых 
	mov AX,stk ; (9618осстAHовим 
	mov SS, AX ;  ( 971 адресуемость стека 
	;Раsрешим аnпаратике и иеwаскируамые прер
	
	sti ; (981Раsр .. еиие прерыааиий 
    mov AL,0 ;1(991Сброс бита 7 а порте СМОS-
	out 70h,AL ; (1001 -раsр-еиие NNI 1
	
	;	Проаер10о1 JlloiПO.JUie-• ФYJUCIIИЙ DOS поспе аоsарата а pea.nьiiiiЙ piUDD&
	mov AH, 09h ; (1011 
	mov EDX,offset mes ;(1021 
	int 21h ;1 11031 
	mov AX, 4C00h ; (1041 Завершим пporpU84' 
	int 21h ; (1051 ;об~АИ~о~N обраsом 
	
main endp ; (1061 

code_size=$-main ; (1071PasNep сеrNеита хомаии 
text ends ; ( 1081 

stk segment stack 'stack'; (1091 
	db 256 dup ('^') ; (1101 
stk ends ;111111 

end main ;(1121ф