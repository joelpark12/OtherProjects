#! /usr/bin/env pythonpytho

import sys, time, random
import pygame

e_aplh = "abcdefghijklmnopqrstuvwxyz"
dna_alph = "ACGT"

# generate random string drawn from the given alphabet and of a given length
def gen_random_string(alphabet, length):
    a_len = len(alphabet)
    ret = ""
    for n in range(length):
        ret += alphabet[random.randint(0, a_len-1)]
    return ret

# print gen_random_string(e_aplh, 5)

SPACE_CHAR = '_'
SPACE_PENALTY = -1

# the scoring function
def s(x, y):
    if x == SPACE_CHAR or y == SPACE_CHAR:
        return SPACE_PENALTY
    elif x == y:
        return 2
    else:
        return -2


TILE_SIZE = 40
tile_color = (255, 255, 255)
highlight_color = (120, 129, 250)

def init_board(m, n):
    screen = pygame.display.set_mode(((m+2)*TILE_SIZE, (n+2)*TILE_SIZE))
    screen.fill((0, 0, 0))
    pygame.display.set_caption('Dot Board')
    pygame.font.init()
    font = pygame.font.Font(None, 15)
    return screen, font

def create_tile(font, text, color):
    tile = pygame.Surface((TILE_SIZE, TILE_SIZE))
    tile.fill(color)
    b1 = font.render(text, 1, (0, 0, 0))
    tile.blit(b1, (TILE_SIZE/2, TILE_SIZE/2))
    return tile

def render_board(board, font, s1, s2, F):
    for i in range(len(s1)):
        tile = create_tile(font, s1[i], tile_color)
        board.blit(tile, ((i+2)*TILE_SIZE, 0))
    tile = create_tile(font, '', tile_color); board.blit(tile, (0, 0))
    tile = create_tile(font, '', tile_color); board.blit(tile, (TILE_SIZE, 0))
    for j in range(len(s2)):
        tile = create_tile(font, s2[j], tile_color)
        board.blit(tile, (0, (j+2)*TILE_SIZE))
    tile = create_tile(font, '', tile_color); board.blit(tile, (0, TILE_SIZE))
    for (x,y) in sorted(F.keys()):
        tile = create_tile(font, str(F[(x,y)]), tile_color)
        board.blit(tile, ((x+1)*TILE_SIZE, (y+1)*TILE_SIZE))

def insert_gap(index, st):
    return st[:index] + SPACE_CHAR + st[index:]
def makestr(path, s1 ,s2):
    s3 = ''
    s4 = ''

    x = 0
    y = 0
    i = len(path)-2
    while i >= 0:
        if path[i] == 'd':
            s3 += s1[x]
            s4 += s2[y]
            x+=1
            y+=1
        elif path[i] == 'u':
            s3 += SPACE_CHAR
            s4 += s2[y]
            y+=1
        else:
            s3 += s1[x]
            s4 += SPACE_CHAR
            x+=1 
        i -= 1

    return s3,s4

def scorecheck(s1, s2):
    fin = 0
    for i in range(len(s1)):
        fin += s(s1[i], s2[i])
    return fin
def directions(board, x, y):
    fin = []
    n = x-1
    m = y-1
    while n != 0 and m != 0:
        corner = board[n-1,m-1]
        left = board[n-1, m]
        up = board[n, m-1]
        top = max (corner, left, up)
        if top==corner:
            fin.append("d")
            m = m - 1
            n = n -1
        elif top == left:
            fin.append("l")
            n = n-1
        else:
            fin.append("u")
            m = m -1
    if m != 0 and n == 0:
        while m != 0:
            fin.append("u")
            m =  m-1
    elif m==0 and n !=0:
        while n!=0:
            fin.append("l")
            n = n-1
    return fin
        
    
def seq_align(s1, s2, enable_graphics=True):
    s3 = SPACE_CHAR + s1
    s4 = SPACE_CHAR + s2
    board = {}
    board[(0,0)] = 0
    for i in range(0, len(s3)):
        for j in range(0, len(s4)):
           if i == 0 and j == 0:
               board[(0,0)] = 0
           else:
                if i > 0 and j > 0:
                    corner = s(s3[i],s4[j]) + board[(i-1,j-1)]
                else:
                    corner = None
                if i > 0:
                    left = board[(i-1,j)] -1
                else:
                    left = None
                if j > 0:
                    up = board[(i,j-1)] -1
                else:
                    up = None
                winner = max(corner,left,up)
                board[(i,j)] = winner
    direc =  directions(board, len(s3), len(s4))
    surface, f = init_board(len(s1),len(s2))
    if enable_graphics:
        render_board(surface, f, s1, s2, board)
        pygame.display.flip()
        time.sleep(10)
    #return board[len(s3)-1, len(s4)-1],  makestr(direc, s1, s2)
    return makestr(direc, s1, s2)
    
def bestSoln(orig_a1, orig_a2, ret_a1, ret_a2, a1, a2):
    if len(ret_a1) != len(ret_a2):
        return False

    ansScore = 0
    for ctr in range(len(a1)):
        ansScore += s(a1[ctr], a2[ctr])

    retScore = 0
    for ctr in range(len(ret_a1)):
        retScore += s(ret_a1[ctr], ret_a2[ctr])

    if retScore > ansScore:
        return False

    orig_ctr = 0
    for ctr in range(len(ret_a1)):
        if ret_a1[ctr] != "_":
            if ret_a1[ctr] != orig_a1[orig_ctr]:
                return False
            orig_ctr += 1

    orig_ctr = 0
    for ctr in range(len(ret_a2)):
        if ret_a2[ctr] != "_":
            if ret_a2[ctr] != orig_a2[orig_ctr]:
                return False
            orig_ctr += 1
        
    return True

if len(sys.argv) == 2 and sys.argv[1] == 'test':
    f=open('tests.txt', 'r');tests= eval(f.read());f.close()
    cnt = 0; passed = True
    for ((s1, s2), (a1, a2)) in tests:
        (ret_a1, ret_a2) = seq_align(s1, s2, False)
        #if (ret_a1 != a1) or (ret_a2 != a2):
        if( not bestSoln(s1, s2, ret_a1, ret_a2, a1, a2) ):
            print s1, s2 
            print a1, a2
            print ret_a1, ret_a2
            print("test#" + str(cnt) + " failed...")
            passed = False
        cnt += 1
    if passed: print("All tests passed!")
elif len(sys.argv) == 2 and sys.argv[1] == 'gentests':
    tests = []
    for n in range(25):
        m = random.randint(8, 70); n = random.randint(8, 70)
        (s1, s2) = (gen_random_string(dna_alph, m), gen_random_string(dna_alph, n))
        (a1, a2) = seq_align(s1, s2, False)
        tests.append(((s1, s2), (a1, a2)))
    f=open('tests.txt', 'w');f.write(str(tests));f.close()
else:
    l = [('ACACACTA', 'AGCACACA'), ('IMISSMISSISSIPI', 'MYMISSISAHIPPIE')]
    enable_graphics = True
    if enable_graphics: pygame.init()
    for (s1, s2) in l:
        print 'sequences:'
        print (s1, s2)
        
        m = len(s1)
        n = len(s2)
        
        print 'alignment: '
        print seq_align(s1, s2, enable_graphics)
    
    if enable_graphics: pygame.quit()
