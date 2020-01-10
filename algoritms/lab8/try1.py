from faker import Faker
from random import choice, sample,randint
import time

def getu(a):
    return np.unique(a)

fake= Faker()

dictionary = []

def generate_films(cnt):
    print("GENERATE_FILMS ",cnt)
    
    f = open('films.txt', 'w')
    for i in range(cnt):
        s = str(i) +';' + fake.word() + ';'
        sentences = fake.sentences(fake.random_int(2,5))
        for sen in sentences:
            s += sen
        s += ';'
        s += fake.country() + ';'
        s += fake.year() + ';'
        s += '\n'
        f.write(s)
        #print(s)
    f.close()
    print("FILMS GENERATION DONE")

def read_films(filename):
     print('START READIND')
     f = open(filename, 'r')
     for row in f:
         row_arr = row.split(';')
         value = dict()
         value['index'] = row_arr[0]
         value['title'] = row_arr[1]
         value['desc'] = row_arr[2]
         value['country'] = row_arr[3]
         value['year'] = row_arr[4]
         dictionary.append(value)
     f.close()
     print("READING END")

letters = "abcdefghijklmnopqrstuvwxyz"

def make_analysys():
    
    #letters = "qwertyuiopasdfghjklzxcvbnm"
    print('START ANALYSYS')
    st = dict()
    for l in letters:
        st[l] = 0
    for d in dictionary:
        st[d['title'][0].lower()] += 1


    s = []
    for l in st:
        k = {}
        k['letter'] = l
        k['count'] = st[l]
        s.append(k)
    print('ANALYSYS DONE')
    return s

segments = []
            

generate_films(1000000)
read_films('films.txt')
#print(dictionary)
st = make_analysys()
st.sort(key=lambda val: val['count'], reverse=True)
#print(st)

print('START creating')
for s in st:
    s['array'] = []
    for d in dictionary: 
        if (d['title'][0].lower() == s['letter']):
            s['array'].append(d)
    s['array'].sort(key=lambda val: val['title'])
print('done')
#print(st)

def binary_search(value, a): 
    mid = len(a) // 2
    low = 0
    high = len(a) - 1
    
    while a[mid]['title'] != value and low <= high:
        if value > a[mid]['title']:
            low = mid + 1
        else:
            high = mid - 1
        mid = (low + high) // 2
    return a[mid]

def search(word, st): 
    first = word[0]
    for s in st:
        if first == s['letter']:
            #print(s['array'])
            #print('\n\n' + word)
            res = binary_search(word, s['array'])
            #Sprint(res)
            return res

def search_simple(word):
    for d in dictionary:
        if word == d['title']:
            #print(d)
            return d

print ('start testing') 
for s in st:
    if len(s['array']) == 0:
        continue
    word = choice(s['array'])
    #print('letter ')
    letter = word['title'][0]
    t = 0
    count = 100
    for i in range(count):
        start = time.time() 
        search(word['title'], st)
        t += time.time() - start
    t1 = t/count


    t = 0

    for i in range(count):
        start = time.time() 
        search_simple(word['title'])
        t += time.time() - start
    t2 = t/count
    print(letter + ', ' + '{:.10f}'.format(t1) + ', ' + '{:.10f}'.format(t2) )


print('testing done')

