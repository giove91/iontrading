#include <cstdlib>
#include <cstdio>
#include <set>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

struct Offer {
    int id;
    int tick;
    int price; // cambio, in milionesimi di unità
    int quantity;
    
    Offer() {}
    
    Offer(int _id, int _t, int _r, int _q) {
        id = _id;
        tick = _t;
        price = _r;
        quantity = _q;
    }
    
};

bool operator< (Offer const& a, Offer const& b) {
    if (a.price != b.price) return (a.price < b.price);
    return (a.id < b.id);
}


set<Offer> offers;

void create(int problem_id, int offer_id, int quantity, int price, int tick) {
    offers.insert( Offer( offer_id, tick, price, quantity ) );
}

void remove(int problem_id, int offer_id, int quantity, int price, int tick) {
    offers.erase( Offer( offer_id, tick, price, quantity ) );
}



pair<int, vector<Offer> > solve(int problem_id, int buy) {
    int remaining = buy;
    vector<Offer> result;
    bool skipped = false;

    set<Offer>::iterator i;
    for (i = offers.begin(); i != offers.end(); i++) {
        int num = min(remaining, i->quantity) / i->tick;
        if (num*(i->tick) < i->quantity) skipped = true;
        if (num > 0) {
            result.push_back( Offer(i->id, i->tick, i->price, num*(i->tick)) );
            remaining -= num*(i->tick);
        }
    }
    
    if (remaining != 0 && skipped)
        fprintf(stderr, "Could not solve problem exactly\n");
    
    return make_pair(remaining, result);
}


int main() {
    
    while (!feof(stdin)) {
        int type;
        fscanf(stdin, "%d", &type);
        if (type == 0) {
            int problem_id, offer_id, quantity, price, tick;
            fscanf(stdin, "%d %d %d %d %d", &problem_id, &offer_id, &quantity, &price, &tick);
            if (quantity == 0) remove(problem_id, offer_id, quantity, price, tick);
            else create(problem_id, offer_id, quantity, price, tick);
        } else {
            int problem_id, buy;
            fscanf(stdin, "%d %d", &problem_id, &buy);
            pair<int, vector<Offer> > res = solve(problem_id, buy);
            for (vector<Offer>::iterator i = res.second.begin(); i != res.second.end(); i++) {
                fprintf(stdout, "%d %d ", i->id, i->quantity);
            }
            fprintf(stdout, "\n");
        }
    }
}


