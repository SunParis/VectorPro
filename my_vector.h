# include <system_error>

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
    const unsigned long long a = 1664525;
    const unsigned long long c = 1013904223;
    const unsigned long long m = 4294967296; 
    ____SEED = (a * ____SEED + c) % m;
    return (int)(____SEED & _OUT_MAX_);
}

int ___layernumgenerate() {
    int layer = 1;
    int base = 4;
    if (___rand() % 16 == 0)  layer++;
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
    int key[_MAX_LAYER_];
    char *data;
    int nextlen;
    ____node_ptr next[_MAX_LAYER_];
};

class fakeskiplist {
private:
    size_t len = 0;
    size_t data_size = 0;
    ____node head;
    ____node_ptr tail = &(this->head);
private:
    ____node_ptr newnode(void *data = null) {
        ____node_ptr newptr = new ____node;
        char *newdata = new char[data_size];
        memcopy((char *)data, newdata, data_size);
        newptr->data = newdata;
        newptr->nextlen = ___layernumgenerate();
        for (int i = 0; i < _MAX_LAYER_; i++) newptr->next[i] = null;
        for (int i = 0; i < _MAX_LAYER_; i++) newptr->key[i] = 0;
        return newptr;
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
    }  
public:
    fakeskiplist(size_t data_size) {
        this->data_size = data_size;
        this->head.data = null;
        this->head.nextlen = _MAX_LAYER_;
        for (int i = 0; i < _MAX_LAYER_; i++) this->head.key[i] = -1;
        for (int i = 0; i < _MAX_LAYER_; i++) this->head.next[i] = null;
    }
    ~fakeskiplist() {
        this->Destroyall();
    }
    size_t length() {
        return this->len;
    }
    size_t insert(void *data, size_t after_key) {
        ____node_ptr newptr = this->newnode(data);
        ____node_ptr curr = &(this->head);
        ____node_ptr updatelist[_MAX_LAYER_];
        ____node_ptr *reclist = null;
        int *keyrec = null;
        for (int i = 0; i < _MAX_LAYER_; i++) updatelist[i] = null;
        int add_key_flag = (newptr->nextlen > 1 ? 1 : 0);
        size_t count = -1;
        int curr_layer = _MAX_LAYER_ - 1;
        if (add_key_flag == 1) {
            reclist = new ____node_ptr[_MAX_LAYER_];
            keyrec = new int[_MAX_LAYER_];
            for (int i = 0; i < _MAX_LAYER_; i++) keyrec[i] = 0;
            for (int i = 0; i < _MAX_LAYER_; i++) reclist[i] = null;
        }
        while (count != after_key) {
            while (curr->next[curr_layer] == null && curr_layer != 0) {
                if (reclist != null)    reclist[curr_layer] = curr;
                curr_layer--;
            }
            if (curr_layer == 0)    break;
            while (curr->next[curr_layer]->key[curr_layer] + count > after_key && curr_layer != 0) {
                updatelist[curr_layer] = curr->next[curr_layer];
                curr_layer--;
            }
            if (curr_layer == 0)    break;
            count += curr->next[curr_layer]->key[curr_layer];
            curr = curr->next[curr_layer];
            if (keyrec != null) keyrec[curr_layer] += curr->key[curr_layer];
        }
        if (curr_layer == 0) {
            for (auto i = count; i < after_key; i++) {
                curr = curr->next[0];
                if (keyrec != null) keyrec[0]++;
            }
        }
        else {
            for (int i = curr_layer; i > 0; i++) {
                updatelist[i] = curr->next[i];
                if (reclist != null) {
                    reclist[i] = curr;
                }
            } 
        }
        if (keyrec != null) keyrec[0]++;

        newptr->next[0] = curr->next[0];
        curr->next[0] = newptr;
        if (add_key_flag == 0) {
            for (int i = _MAX_LAYER_ - 1; i > 0; i--) {
                if (updatelist[i] != null)  updatelist[i]->key[i]++;
            }
        }
        else {
            ____node_ptr tmp = null;
            for (int i = 1; i <= newptr->nextlen - 1; i++) {
                newptr->key[i] = newptr->key[i-1] + keyrec[i];
                if (reclist[i] != null) reclist[i]->next[i] = newptr;
                if (updatelist[i] != null)  updatelist[i]->key[i] += (1 - newptr->key[i]);
            }
            for (int i = newptr->nextlen; i <= _MAX_LAYER_ - 1; i++) {
                if (updatelist[i] != null)  updatelist[i]->key[i] += 1;
            }
        }
        return after_key + 1;
    }
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