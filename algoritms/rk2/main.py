import re
def regex(text):
    pattern = r'(?:\t|\n| )\d+-(?:й|я|м|ю|е|х|а|и|го|му|мя|ми)\b'
    print(pattern)
    a = re.findall(pattern, text)
    #print("Result by regex:")
  #  if a:
  #      for i in range(len(a)):
  #          print(a[i])
  #  else:
   #     print("Not found")

    return a


def fsm(text):
    nums = '0123456789'
    simple = 'йяюехаи'
    after_m = 'уяи'
    dels = ' \t\n'
    
    state = 'begin'
    result = []

    i = 0
    tlen = len(text)
    begin = 0
    for i in range(tlen):
        c = text[i]
        if state == 'begin':
            if c in nums and (i == 0 or text[i-1] == ' ' or text[i-1] in dels):
                begin = i
                state = 'num'
        elif state == 'num':
            if c == '-':
                state = '-'
            elif not c in nums:
                state = 'begin'
        elif state == '-':
            if c == 'м':
                state = 'м'
            elif c == 'г':
                state = 'г'
            elif c in simple:
                state = 'end'
            else:
                state = 'begin'
        elif state == 'м':
            if c in after_m:
                state = 'end'
            elif c == ' ' or c in dels:
                result.append(text[begin:i])
                state = 'begin'
            else:
                state ='begin'
        elif state == 'г':
            if c == 'о':
                state = 'end'
            else:
                state = 'begin'
        elif state == 'end':
            if c == ' ' or c in dels:
                result.append(text[begin:i])
                state = 'begin'
            else:
                state = 'begin'
   # print("FSM results:")   
  #  if result:
   #     for s in result:
   #         print(s)
    #else:
     #   print("Not found")

    return result
            

filename = input("Input filename: ")
f = open(filename, "r")
if f:
    text = ''
    for line in f:
        text += line
    print(text)
    reg = regex(text)
    print("\n")
    fs = fsm(text)
    f.close()
    lenm = max(len(reg), len(fs))
    print('reg\t    fsm')
    for i in range(lenm):
        if i < len(reg) and i < len(fs):
            print(reg[i][1:] + '\t    ' +fs[i])
        elif i < len(reg) and not i >= len(fs):
            print(reg[i][1:] + '\t    ' +'no  ')
        elif i >= len(reg) and not i < len(fs):
            print('no  ' + '\t    ' +fs[i])
            
            
            
