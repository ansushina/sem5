.386Р ; (1)Раsрешение коwаид МП 386 и 486 
; Структура для опксания дескрипторов сегментов 
descr struc  ;(2) 
limit dw О ; (3)Граница (биты О ... 15) 
base_1 dw О ; (4)База, биты 0...15 
base_m db О ; (5)База, биты 16.. 23 
attr_1 db О ; (б)Байт атрибутов 1 
attr_2 db О ; (7)Граница (биты 16 ... 19) и атрибуты 2 
base_h db О ; (8)База, биты 24 ... 31 
descr ends  ; (9)
data segment ; (10) Начапо сегмента данных 
; Таблица глобальных дескриnторов GDT 
gdt_null descr <0,0,0,0,0,0>; (11);Hyneaoй дескриnтор 
gdt_data descr <data_size-1,0,0,92h>; (12)Ceл-р 8, сеrмент данных 
gdt_code descr <code size-1,,,98h>; (13)Селектор 16, сеrмент команд 
gdt_atack descr <255,0,0,92h>; (14)Селектор 24, сегмент стека 
gdt_screen descr <4095,8000h,ОВЬ,92h>; (15)Селектор 32, видеобуфер 
gdt_sise=$-gdt_null ; (16) Размер GDТ 
; Поля данных прогаммы
pdescr dq О ;(17)Псевдодескриnтор 
sym db 1 ; (18) Символ для вывода иа экран
attr db 1Eh ; (19) его атрибут 
mes db 27,'[31,42m Вернулись в реальный режим ',27,' [Om$'; (20) 
data_size=$-gdt_null ; (21) Размер сегмента данных 
data ends ; ( 22) Кокец сеruеита даниых 
text segment 'code' usel6; (23)Укажем 16-разряный режим 
assume CS:text,DS:data; (24) 
main proc ; (25) 
xor EАХ, EАХ ;  (26) Очистим EАХ 
mov AX,data ; (27)Загрузим в DS сеrмеитиый 
mov DS,AX ; (28) адрес сеrмеита данных 
; Вычислим 32-битовый линейный адрес сеrмента даииых и загрузим ero 
; в дескриптор сеrмеита данных а GDT. 
shl EАХ, 4 ;  (29) В EAX пинейинй баsоаый адрес 
mov EBP,EAX ; (3О)Сохраним его в EBP 
mov BX,offset gdt_data; (31)В ВХ адрес дескриптора 
mov [ВХ].basе_m,AL; (32)Заrруsим NIIaдiDYJO часть баsы 
ro1 EАХ, 16 ; (33)0бмен С'l!аршей и МJJадшей попоаии EАХ 
mov [ВХ].base_m, AL; (34) Эаl'руsим cpeдИICIIO часть баsы 
; Allanor...мo дп11 пииейхоrо адреса сеrмекта коN&НД 
xor EАХ, EАХ ; (35)0чистим EАХ 
mov AX,CS ; (36)ЛIIpec сеrмента коN&НД 
ahl EАХ, 4 ; (37)Ywкo3DD& иа 16 .
mov ВX,offset gdt_code; (38)Адрес дескриптора 
mov [BX].base_m,AL; (39) Заl'руsим NJJaдiDYJO часть баsы 
rol EАХ,16 ; ( 40) Обмен попоаии eАХ 
mov [ВХ].base_m,AL; (41)Эаrруsим cpeдИICIIO часть баsк 
;AIIano:t'ичиo дn• пииейиоrо адреса cerNeaтa стека 
xor EAX,EAX ; (421 
mov АХ, SS ; (43) 
ahl EАХ, 4 ; (441 
mov ВХ,offset gdt_stack; (45)
mov [ВХ].base_l,AX; (46) 
rol EАХ, 16 ; (471 
mov [ВХ].base_m ,AL; (48) 
;1Doaroeoaнw аоеадодескрКПтор pdescr и s&:t'pysим реrистр GDТR 
mov dword ptr pdescr+2,EBP; (49)Sasa GDT, биты о ... 31 
mov word ptr pdescr, gdt_size-1; (50)I'раиица GDТ 
lgdt: pdescr ; ( 511 Зarpys101 реrистр GDТR 
;JПOJ~rOT08NNC8 к вереходу а sащкщеииый р~ 
oli ; (52)Эаnрет апnаратных арерыааиий 
mov AL, 80h ; (53) Заnрет NМI 
out 70h,AL ;J(541Порт КМОП-мккросхеNЫ 
;Переходим а sUDCJaeИКIIIIЙ режим 
mov EAX, CRO ;1 (55 ) Попучим содера;иwое CRO 
or EAX,1 ; (56)Устаноаим бит Р! 
mov CRO, ЕАХ ; (57 1 9ашааек иаsад в CRO 
;Тепер• процессор paбO'.I!acw а a..,ar,e1111CIН ~ 
;9аrру.каем в CS:IP сепехтор:смещеиие точхи continue 
;и sаодно очищаем очередь коwаид 
db OEAh ; (58 1 Код команды far j:111p dw offset continue; (591Смащеиие dw 16 ; (601Се.пектор сеrмента комаид continue: ; (611 ;Депаем адресуе~ даииые шоv АХ, 8 ;  ( 62 1 Сепектор сеrмента дiUUUoiX шоv DS,AX ; (631 ; Депаем адресуеwым стек шоv АХ, 24 ;  ( 641 Се.пектор сеrмента стека шоv SS,AX ; (651 ;Ииици:а.пиsИруем ES и ВЫIIОДИМ симвопъr шоv АХ,Э2 ; (ббiСепектор сеrмента видеобуtера шоv ES,AX ; (671 шоv ВХ, 800 ; 1 68 1 НачАЛьное смещение на :~кране шоv СХ, 64 О ;  ( б 9 1 Чиспо IIЫIIOдюaa« симво.поа 311 шоv AX,word ptr sуш; (701Начuьный симво.п с атрибутом screen: шоv ES: [ВХ], АХ ; (11 1 В11111од в аидеобуфер add ВХ,2 ; (721Сместкыс~ в видеобуфере inc АХ ;  ( 1 Э 1 СпедУJСХЦИЙ симво.п loop screen ; (74 1 Ци1<J1 11111110да на :акраи ;Подrотовим переход в реальный реzкм ;Сформируем и sarpysим дескрипторы АЛ~ реапьноrо режима шоv qdt data.liшit,OFFFFh; (751Гракица сеrwента дахккх шоv qdt-code.liшit,OFFFFh; (761Гракица сеrwента комаид шоv qdt-stack.liшit,OFFFFh; (77)Граница сеrмента стека mov qdt:screen.liшit,OFFFFh; (781Гракица допопнитепьиоrо ;сеrмента шоv АХ, 8 ;  ( 79 ) Эаrруsим теневой реrистр шоv DS,AX ; (80)сеrмента данных шоv АХ, 24 ; (81) 9аrруsим теневой реrистр mov SS,AX ; (82)стека mov АХ, 32 ; (83) Эаrруsим теневой реrистр mov ES,AX ; (841допОJIИИтепьиоrо сеrмента ;Выпопким дапьиий переход АЛ~ тоrо, чтобы sаново sаrруsить ;сепектор в реrистр CS и модифицироаать ero теиеаой реrистр db OEAh ; (851Коwаидой дanJtнero перехода dw offset qo ; (861 sarpysим тенеаой реrистр dw 16 ; (871сеrыента коwаид ; ПepeiiUIIDЧИМ pe:uuc процессера qo: mov EAX,CRO ; (881По.пучим' содер:кимое CRO and ЕАХ, OFFFFFFnh; (891Сбросим бит Pl mov CRO, ЕАХ ; ISO 1 9&lUOIIeM и а s ад в CRO db OEAh ;  ( 911 Код КОМАнд• far jlllp dw offset return; (921Смещеиие dw text ; (931Сеrмеит ;Тепер• процеосор CIIOIIa рабО'.I!ам/ 11 pe~IICIН ~ ; Восстановим операциоииУJD среду pean•иoro p-return: IIIOV AX,dat& ; (94)80CC'JI&JIOIIJ04 шоv DS,AX ; (95)адресуемость даииых mov AX,stk ; (9618осстановим шоv SS, АХ ;  ( 971 адресуемость стека ;Раsрешим аnпаратике и иеwаскируамые преркваии~ sti ; (981Раsр .. еиие прерыааиий 
312 Статья62 IIIOV AL,O 1(991Сброс бита 7 а порте СМОS-out 70h,AL 1 (1001 -раsр-еиие NNI 1 Проаер10о1 JlloiПO.JUie-• ФYJUCIIИЙ DOS поспе аоsарата а pea.nьiiiiЙ piUDD& IIIOV АН, 09h ; (1011 IIIOV DX,offset Ш881 (1021 int 21h 1 11031 IIIOV АХ, 4C00h ; (1041 Завершим пporpU84' int 21h ; (1051 ;об~АИ~о~N обраsом ~~ain endp ; (1061 code size•$-~~ain ; (1071PasNep сеrNеита хомаии text-ends 1 ( 1081 stk seqaent stack 'stack'; (1091 с1Ь 256 dup ( 1 "'' 1; (1101 stk ends 111111 end шain ;(1121ф