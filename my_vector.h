/*# include <iostream>
# include <stdlib.h>*/
# ifdef _WIN64
    typedef unsigned long long size_t;
# elif defined __SIZE_TYPE__
    typedef __SIZE_TYPE__ size_t;
# else
    typedef unsigned int size_t;
# endif

# ifndef null
# define null 0
# endif


# ifndef _MY_SKIPLIST_
# define _MY_SKIPLIST_
# define _OUT_MAX_ 0xffffffff
# define _MAX_LAYER_ 8

unsigned long long ____SEED = 12345; 
int ___rand() {
    // return rand();
    const unsigned long long a = 1664525;
    const unsigned long long c = 1013904223;
    const unsigned long long m = 4294967296; 
    ____SEED = (a * ____SEED + c) % m;
    return (int)(____SEED & _OUT_MAX_);
}

int ___layernumgenerate() {
    int layer = 1;
    int base = 4;//2;
    if (___rand() % (base * base) == 0)  layer++;
    else return layer;
    while (1) {
        if (___rand() % base == 0)  layer++;
        else    break;
    }
    if (layer > _MAX_LAYER_)    return _MAX_LAYER_;
    return layer;
}

void memcopy(const char *in, char *out, size_t n) {
    if (in == null || out == null || n <= 0) return;
    for (auto i = 0; i < n; i++) {
        out[i] = in[i];
    }
}

# define type_size (sizeof(type) * sizeof(char))
# define sizeofptr (sizeof(____node_ptr) * sizeof(char))
typedef struct ____node ____node;
typedef ____node* ____node_ptr;
struct ____node {
    char *data;
    int nextlen;
    int key[_MAX_LAYER_];
    ____node_ptr next[_MAX_LAYER_];
};

class fakeskiplist {
private:
    size_t len = 0;
    size_t data_size = 0;
    ____node head;
    ____node_ptr tail;
private:
    ____node_ptr newnode(void *data) {
        ____node_ptr newptr = new ____node;
        char *newdata = new char[data_size];
        memcopy((char *)data, newdata, data_size);
        newptr->data = newdata;
        newptr->nextlen = ___layernumgenerate();
        for (int i = 0; i < _MAX_LAYER_; i++) newptr->next[i] = null;
        for (int i = 0; i < _MAX_LAYER_; i++) newptr->key[i] = 0;
        return newptr;
    }
public:
    fakeskiplist(size_t data_size) {
        this->data_size = data_size;
        this->head.data = null;
        this->head.nextlen = _MAX_LAYER_;
        for (int i = 0; i < _MAX_LAYER_; i++) this->head.key[i] = -1;
        for (int i = 0; i < _MAX_LAYER_; i++) this->head.next[i] = null;
        this->tail = &(this->head);
    }
    ~fakeskiplist() {
        this->Destroyall();
    }
    size_t length() {
        return this->len;
    }
    size_t insert(void *data, size_t after_key) {
        if (after_key >= this->length() && after_key != -1)    return -1;
        ____node_ptr newptr = this->newnode(data);
        ____node_ptr curr = &(this->head);
        ____node_ptr next_update_list[_MAX_LAYER_];
        ____node_ptr *prev_rec_list = null;
        int *keyrec = null;
        for (int i = 0; i < _MAX_LAYER_; i++) next_update_list[i] = null;
        int add_key_flag = (newptr->nextlen > 1 ? 1 : 0);
        size_t count = -1;
        int curr_layer = _MAX_LAYER_ - 1;
        if (add_key_flag == 1) {
            prev_rec_list = new ____node_ptr[_MAX_LAYER_];
            keyrec = new int[_MAX_LAYER_];
            for (int i = 0; i < _MAX_LAYER_; i++) keyrec[i] = 0;
            for (int i = 0; i < _MAX_LAYER_; i++) prev_rec_list[i] = null;
        }
        while (count != after_key) {
            while (curr->next[curr_layer] == null && curr_layer != 0) {
                if (prev_rec_list != null)    prev_rec_list[curr_layer] = curr;
                curr_layer--;
            }
            if (curr_layer == 0)    break;
            while (curr->next[curr_layer]->key[curr_layer] + count > after_key && curr_layer != 0) {
                next_update_list[curr_layer] = curr->next[curr_layer];
                if (prev_rec_list != null)    prev_rec_list[curr_layer] = curr;
                curr_layer--;
            }
            if (curr_layer == 0)    break;
            count += curr->next[curr_layer]->key[curr_layer];
            curr = curr->next[curr_layer];
            if (keyrec != null) keyrec[curr_layer] += curr->key[curr_layer];
        }
        /*std::cout << "curr_layer:::         " << curr_layer;
        if (curr->next[1] == null)  std::cout << "---XXX" << std::endl;
        else  std::cout << std::endl;*/
        if (count == after_key) {
            for (int i = curr_layer; i >= 0; i--) {
                next_update_list[i] = curr->next[i];
                if (prev_rec_list != null) {
                    prev_rec_list[i] = curr;
                }
            } 
        }
        else if (curr_layer == 0) {
            while (count != after_key) {
                curr = curr->next[0];
                if (keyrec != null) keyrec[0]++;
                count++;
            }
        }
        if (keyrec != null) keyrec[0]++;

        newptr->next[0] = curr->next[0];
        curr->next[0] = newptr;
        if (add_key_flag == 0) {
            for (int i = _MAX_LAYER_ - 1; i > 0; i--) {
                if (next_update_list[i] != null)  next_update_list[i]->key[i]++;
            }
        }
        else {
            ____node_ptr tmp = null;
            int delta = after_key + 2;
            for (int i = _MAX_LAYER_ - 1; i > 0; i--) {
                delta -= keyrec[i];
                if (i < newptr->nextlen) {
                    newptr->key[i] = delta;
                    newptr->next[i] = next_update_list[i];
                    if (prev_rec_list[i] != null) prev_rec_list[i]->next[i] = newptr;
                    if (next_update_list[i] != null)  next_update_list[i]->key[i] += (1 - newptr->key[i]);
                }
            }
        }

        /*if (keyrec != null) {
            std::cout << "keyrec:::             ";
            for (int i = 0; i < _MAX_LAYER_; i++) {
                std::cout << keyrec[i] << "|||";
            }
            std::cout << std::endl;
        }
        if (prev_rec_list != null) {
            std::cout << "prev_rec_list:::      ";
            for (int i = 0; i < _MAX_LAYER_; i++) {
                if (prev_rec_list[i] == null)   std::cout << " " << "|||";
                else    std::cout << prev_rec_list[i]->key[i] << "|||";
            }
            std::cout << std::endl;
        }
        if (next_update_list != null) {
            std::cout << "next_update_list:::   ";
            for (int i = 0; i < _MAX_LAYER_; i++) {
                if (next_update_list[i] == null)   std::cout << " " << "|||";
                else    std::cout << next_update_list[i]->key[i] << "|||";
            }
            std::cout << std::endl;
        }*/

        if (after_key == this->len - 1) this->tail = newptr;
        delete [] prev_rec_list;
        delete [] keyrec;
        this->len++;
        return after_key + 1;
    }
    void Destroyall() {
        ____node_ptr curr = this->head.next[0];
        ____node_ptr tmp;
        while (curr != null) {
            tmp = curr;
            curr = curr->next[0];
            delete [] tmp->data;
            delete tmp;
        }
        for (int i = 0; i < _MAX_LAYER_; i++) this->head.next[i] = null;
        this->tail = &(this->head);
    }
    /*void show() {
        std::cout << "=========================================" << std::endl;
        ____node_ptr curr = this->head.next[0];
        for (int i = 0; i < this->length(); i++) {
            std::cout << i << "::: ";
            for (int i = 0; i < _MAX_LAYER_; i++) {
                std::cout << curr->key[i];
                if (i == curr->nextlen - 1) std::cout << "|||";
                else    std::cout << "---";
            }
            std::cout << std::endl;
            curr = curr->next[0];
        }
        std::cout << "=========================================" << std::endl;
    }*/
};

# endif


# ifndef _MY_VECTOR_
# define _MY_VECTOR_
template <typename type>
class myvector {
private:
    size_t capacity = 0;
    size_t len = 0;
public:
    size_t size() {
        return this->capacity;
    }
    size_t length() {
        return this->len;
    }
};


# endif