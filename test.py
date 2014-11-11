#!/usr/bin/python

from random import randint, random

MAX_PRICE=1e7
MAX_QTY_PER_TICK=20
MAX_TICK=5

id_markets=range(0,100)
offerts_table={}

last_used_id=0

for id in id_markets:
    offerts_table[id]=[]

class Offer:
    def __init__(self,price, qty, tick):
        global last_used_id
        last_used_id+=1
        self.id=last_used_id
        self.price=price
        self.qty=qty
        self.tick=tick

for i in range(int(1e5)):
    ciao = random()
    if ciao < 0.1:
        action = 2
    else:
        action = randint(0, 1)
    # Fill the table at the beginning
    if i < 100:
        action=1
        
    if action == 0:
        id=randint(0, len(id_markets)-1)
        if len(offerts_table[id]) == 0:
            continue
        offert_index=randint(0, len(offerts_table[id])-1)
        offert=offerts_table[id].pop(offert_index)
        print 0, 0, offert.id, 0, offert.price, offert.tick
    elif action == 1:
        id=randint(0, len(id_markets)-1)
        price=randint(0,MAX_PRICE)
        tick=randint(1,MAX_TICK)
        qty=randint(0,MAX_QTY_PER_TICK)*tick
        offert=Offer(price=price,qty=qty, tick=tick)
        offerts_table[id].append(offert)
        print 0, 0, offert.id, offert.qty, offert.price, offert.tick
    elif action==2:
        qty_to_buy=randint(0,MAX_QTY_PER_TICK*MAX_TICK*5/4)
        print 1, 0, qty_to_buy
        
