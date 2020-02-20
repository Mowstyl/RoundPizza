import heapq
import pizzahandler
import random
class libreria:



    id = None
    n_books = None #numero de libros
    signup_process = None #dias de singup
    ship = None #libros que escanea por dia
    books = []#lista de duplas con (id, score)
    score_books = []
    score = 0
    t_days = None #numero de dias totales

    def __init__(self, id, n_books, signup_process, ship, books, score_books, t_days):
            self.id = id
            self.n_books = n_books
            self.signup_process = signup_process
            self.ship = ship
            self.books = books
            self.score_books = score_books
            self.t_days = t_days
            self.score = self.f_score()


    def f_score(self):
        books_scan = (self.t_days-self.signup_process)*self.ship
        val_books = 0
        for book in self.score_books:
            #print(book)
            val_books = val_books + book
        val_m = val_books/self.n_books

        return val_m * self.ship * (1-(self.signup_process/self.t_days))

    def shuffle_books(self):
        random.shuffle(books)


    def __lt__(self, other):
        return self.score < other.score


class Heap:

    heap = []
    def get_first(self):
        return heapq.heappop(self.heap)
    def insert_item(self, item):
        heapq.heappush(self.heap, item)
    def n_elements(self):
        return len(self.heap)


#a = libreria(1, 2, 3, 2, [(1,34), (2,45), (4,3)], 70)
#c = libreria(1, 2, 3, 2, [(1,34), (2,45), (4,3)], 100)
#d = libreria(1, 2, 3, 2, [(1,34), (2,45), (4,3)], 30)
#print(a.signup_process)
#print(a.t_days)
#print(a.score)
#b = Heap()
#b.insert_item(a)
#b.insert_item(c)
#b.insert_item(d)
#n=b.n_elements()
#for i in range(n):
#    print(b.get_first().score)







class Grasp:

    nlib = None
    nbib = None
    maxd = None
    scores = None
    librerias = None


    score_best = None
    conf_best = None


    def __init__(self, nlib, nbib, maxd, scores, librerias):
        self.nlib = nlib
        self.nbib = nbib
        self.maxd = maxd
        self.scores = scores
        self.librerias = librerias

        #self.score_best, self.conf_best = pizzahandler.pedirLibros(self.nlib, self.nbib, self.maxd, self.scores, self.librerias)
        #self.score_best, signupnum, idbibs, nbookbib, libbib =
