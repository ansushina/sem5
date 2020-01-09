from faker import Faker
from random import choice, sample,randint


class node:
    def __init__(self, data = None, left = None, right = None):
        self.data   = data
        self.left   = left
        self.right  = right

    def d(self):
        return self.data

    def __str__(self):
        return 'Node ['+str(self.data)+']'
 
class Tree:
    def __init__(self):
        self.root = None #корень дерева

    def newNode(self, data, cmp = lambda v1,v2: v1<v2s):
        if self.root == None:
            self.root = node(data,None,None)
            return self.root
        parent = None
        n = self.root
        while n != None :
            parent = n
            if cmp(data, n.data):
                n = n.left
            else:
                n = n.right
        if cmp(data, parent.data):
            parent.left = node(data,None,None)
            return parent.left
        else:
            parent.right = node(data,None,None)
            return parent.right

    
    def printGivenLevel(self, root, level):
          if root == None:
            return
          if level == 1:
            print (root.data)
          elif level > 1:
              self.printGivenLevel(root.left, level-1);
              self.printGivenLevel(root.right, level-1);

    def print(self):
        self.printGivenLevel(self.root, 10)

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

def read_films(filename):
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

letters = "abcdefghijklmnopqrstuvwxyz"

def make_analysys():
    
    #letters = "qwertyuiopasdfghjklzxcvbnm"
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
    return s

segments = []

def create_segs(st):
    t = Tree()
    for s in st:
        t.newNode(s, cmp=lambda v1,v2: v1['letter'] < v2['letter'])
        t.print()
    
            

generate_films(1000)
read_films('films.txt')
#print(dictionary)
st = make_analysys()
print(st)
st.sort(key=lambda val: val['count'], reverse=True)
print(st)

create_segs(st)




