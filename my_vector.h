// # define DEBUG
# ifndef _MY_SKIPLIST_
# define _MY_SKIPLIST_
# ifdef DEBUG
# include <iostream>
# endif
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

# define _MAX_LAYER_ 8
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

# include <random>
class random {
private:
    int min, max;
    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution;
public:
    random() {
        this->min = 0;
        this->max = 1023;
        this->distribution = std::uniform_int_distribution<int>(this->min, this->max);
    }
    int get_rand() {
        return this->distribution(this->generator);
    }
};

class memexcpetion: public std::exception {
private:
    char message[30];
public:
    memexcpetion(const char *str) {
        int idx = 0;
        while(str[idx] != 0) {
            message[idx] = str[idx];
            idx++;
        }
        message[idx] = 0;
    }
    virtual const char* what() const throw () {
        return this->message;
    } 
};

class fakeskiplist: private random {
private:
    int _____curr_lay = 1;
    size_t len = 0;
    size_t data_size = 0;
    ____node head;
    ____node_ptr tail;
protected:
    void memcopy(const char *in, char *out, size_t n) {
        if (in == null || out == null || n <= 0) return;
        for (auto i = 0; i < n; i++) {
            out[i] = in[i];
        }
    }
private:
    int ___layernumgenerate() {
# ifdef DEBUG
        int tmp = this->_____curr_lay;
        this->_____curr_lay++;
        if (this->_____curr_lay > _MAX_LAYER_)  this->_____curr_lay = 1;
        return tmp;
# endif
        int layer = 1;
        int base = 4;
        if (this->get_rand() % (base * base) == 0)  layer++;
        else return layer;
        while (1) {
            if (this->get_rand() % base == 0)  layer++;
            else    break;
        }
        if (layer > _MAX_LAYER_)    return _MAX_LAYER_;
        return layer;
    }
    ____node_ptr newnode(const void *data) {
        ____node_ptr newptr = new ____node;
        char *newdata = new char[data_size];
        if (newdata == 0 || newptr == 0)    throw memexcpetion("Out of memory!!!");
        this->memcopy((char *)data, newdata, data_size);
        newptr->data = newdata;
        newptr->nextlen = ___layernumgenerate();
        for (int i = 0; i < _MAX_LAYER_; i++) {
            newptr->next[i] = null;
            newptr->key[i] = 0;
        }
        return newptr;
    }
    ____node_ptr prev_curr_next_find(size_t target, ____node_ptr *prev = null, ____node_ptr *next = null, size_t *prev_pos = null) {
        if (target == -1 || target >= this->length())   return null;
        ____node_ptr curr = &(this->head);
        size_t curr_pos = -1;
        int curr_layer = _MAX_LAYER_ - 1;
        if (target == 0) {
            for (int i = 0; i < this->head.nextlen; i++) {
                if (prev != null)   prev[i] = &(this->head);
                if (next != null)   next[i] = this->head.next[i];
                if (prev_pos != null)   prev_pos[i] = -1;
            }
            return this->head.next[0];
        }
        else if (target == this->length() - 1) {
            while (curr->next[curr_layer] != this->tail) {
                while (curr->next[curr_layer] == null && curr_layer != 0) {
                    if (prev != null)   prev[curr_layer] = curr;
                    if (prev_pos != null)   prev_pos[curr_layer] = curr_pos;
                    curr_layer--;
                }
                if (curr_layer == 0)    break;
                while (curr->next[curr_layer] != this->tail) {
                    if (curr->next[curr_layer] == null)  break;
                    if (prev_pos != null)   curr_pos += curr->key[curr_layer];
                    curr = curr->next[curr_layer];
                }
                if (curr->next[curr_layer] == this->tail) {
                    if (prev != null)   prev[curr_layer] = curr;
                    if (prev_pos != null)   prev_pos[curr_layer] = curr_pos;
                    curr_layer--;
                }
            }
            if (curr_layer == 0) {
                while (curr->next[curr_layer] != this->tail) {
                    if (prev_pos != null)   curr_pos += 1;
                    curr = curr->next[0];
                }
            }
            for (int i = 0; i < curr->nextlen; i++) {
                if (prev != null)   prev[i] = curr;
                if (prev_pos != null)   prev_pos[i] = curr_pos;
            }
            for (int i = 0; i < curr->nextlen && next != null; i++) {
                next[i] == null;
            }
            return this->tail;
        }
        while (curr_pos != target - 1) {
            while (curr->next[curr_layer] == null && curr_layer != 0) {
                if (prev != null)   prev[curr_layer] = curr;
                if (prev_pos != null)   prev_pos[curr_layer] = curr_pos;
                if (next != null)   next[curr_layer] = null;
                curr_layer--;
            }
            if (curr_layer == 0)    break;
            while (curr_pos + curr->next[curr_layer]->key[curr_layer] > target - 1 && curr_layer != 0) {
                if (prev != null)   prev[curr_layer] = curr;
                if (prev_pos != null)   prev_pos[curr_layer] = curr_pos;
                if (next != null)   next[curr_layer] = curr->next[curr_layer];
                curr_layer--;
            }
            if (curr_layer == 0)    break;
            while (curr_pos + curr->next[curr_layer]->key[curr_layer] <= target - 1) {
                curr_pos += curr->next[curr_layer]->key[curr_layer];
                curr = curr->next[curr_layer];
                if (curr->next[curr_layer] == null) break;
            }
            if (prev != null)   prev[curr_layer] = curr;
            if (prev_pos != null)   prev_pos[curr_layer] = curr_pos;
            if (next != null)   next[curr_layer] = curr->next[curr_layer];
            curr_layer--;
        }
        if (curr_layer == 0) {
            while (curr_pos != target - 1) {
                curr_pos += 1;
                curr = curr->next[0];
            }
        }
        for (int i = 0; i < curr->nextlen; i++) {
            if (prev != null)   prev[i] = curr;
            if (prev_pos != null)   prev_pos[i] = curr_pos;
        }
        curr = curr->next[0];
        for (int i = 0; i < curr->nextlen; i++) {
            if (next != null)   next[i] = curr->next[i];
        }

        return curr;
    }
    void *remove_head(void) {
        if (this->length() == 0)    return null;
        ____node_ptr curr = this->head.next[0];
        for (int i = 0; i < curr->nextlen; i++) this->head.next[i] = curr->next[i];
        for (int i = curr->nextlen; i < _MAX_LAYER_; i++) {
            if (this->head.next[i] != null) {
                this->head.next[i]->key[i]--;
            }
        }
        char *data = curr->data;
        this->len--;
        delete curr;
        if (this->length() == 0)    this->tail = null;
        return data;
    }
    void *remove_tail(void) {
        ____node_ptr prev_rec_list[_MAX_LAYER_];
        ____node_ptr curr = this->prev_curr_next_find(this->length() - 1, prev_rec_list);       
        
        for (int i = 0; i < this->tail->nextlen; i++) {
            if (prev_rec_list[i] != null) {
                prev_rec_list[i]->next[i] = null;
            }
        }
        char *data = this->tail->data;
        delete this->tail;
        this->tail = prev_rec_list[0];
        this->tail->next[0] = null;
        this->len--;
        return data;
    }
    size_t insert_head(const void *data) {
        ____node_ptr newptr = this->newnode(data);
        for (int i = newptr->nextlen; i < _MAX_LAYER_; i++) {
            if (this->head.next[i] != null) {
                this->head.next[i]->key[i]++;
            }
        }
        for (int i = 0; i < newptr->nextlen; i++) {
            if (i > 0)  newptr->key[i] = 1;
            newptr->next[i] = this->head.next[i];
            this->head.next[i] = newptr;
        }
        this->len++;
        if (this->tail == null) this->tail = newptr;
        return 0;
    }
    size_t insert_tail(const void *data) {
        ____node_ptr prev_rec_list[_MAX_LAYER_];
        size_t prev_key_rec[_MAX_LAYER_];
        ____node_ptr curr = this->prev_curr_next_find(this->length() - 1, prev_rec_list, null, prev_key_rec);
        ____node_ptr newptr = this->newnode(data);
        for (int i = 0; i < curr->nextlen && i < newptr->nextlen; i++) {
            curr->next[i] = newptr;
        }
        for (int i = curr->nextlen; i < _MAX_LAYER_ && i < newptr->nextlen; i++) {
            if (prev_rec_list[i] != null) {
                prev_rec_list[i]->next[i] = newptr;
            }
        }
        this->len++;
        this->tail = newptr;
        return 0;
    }
public:
    fakeskiplist(size_t data_size) {
        this->data_size = data_size;
        this->head.data = null;
        this->head.nextlen = _MAX_LAYER_;
        for (int i = 0; i < _MAX_LAYER_; i++) this->head.key[i] = -1;
        for (int i = 0; i < _MAX_LAYER_; i++) this->head.next[i] = null;
        this->tail = null;
    }
    ~fakeskiplist() {
        this->removeall();
    }
    size_t length() {
        return this->len;
    }
    size_t insert(const void *data, size_t after_key) {
        if (after_key >= this->length() && after_key != -1)    return -1;
        if (after_key == -1)    return this->insert_head(data);
        if (after_key == this->length() - 1)    return this->insert_tail(data);
        ____node_ptr newptr = this->newnode(data);
        ____node_ptr next_update_list[_MAX_LAYER_];
        ____node_ptr prev_rec_list[_MAX_LAYER_];
        size_t key_rec[_MAX_LAYER_];
        ____node_ptr curr = this->prev_curr_next_find(after_key, prev_rec_list, next_update_list, key_rec);
        for (int i = 0; i < newptr->nextlen; i++) {
            newptr->next[i] = next_update_list[i];
            if (i < curr->nextlen) {
                curr->next[i] = newptr;
                newptr->key[i] = 1;
            }
            else {
                if (prev_rec_list[i] != null)   prev_rec_list[i]->next[i] = newptr;
                newptr->key[i] = after_key - key_rec[i] + 1;
            }
            if (next_update_list[i] != null)    next_update_list[i]->key[i] -= (newptr->key[i] - 1);
        }
        newptr->key[0] = 0;
        next_update_list[0]->key[0] = 0;
        for (int i = newptr->nextlen; i < _MAX_LAYER_; i++) {
            if (next_update_list[i] != null)    next_update_list[i]->key[i]++;
        }
        this->len++;
        return after_key + 1;
    }   

    void *remove(size_t target_key) {
        if (target_key >= this->length() || target_key < 0)    return null;
        if (target_key == 0)    return this->remove_head();
        if (target_key == this->length() - 1)    return this->remove_tail();
        ____node_ptr next_update_list[_MAX_LAYER_];
        ____node_ptr prev_rec_list[_MAX_LAYER_];
        ____node_ptr curr = this->prev_curr_next_find(target_key, prev_rec_list, next_update_list);
        for (int i = 0; i < _MAX_LAYER_; i++) {
            if (prev_rec_list[i] != null)   prev_rec_list[i]->next[i] = next_update_list[i];
            if (next_update_list[i] != null) {
                if (i < curr->nextlen) {
                    next_update_list[i]->key[i] += (curr->key[i] - 1); 
                }
                else {
                    next_update_list[i]->key[i]--;
                }
            }
        }
        next_update_list[0]->key[0] = 0;

        char *data = curr->data;
        delete curr;
        this->len--;
        return data;
    }

    void *get(size_t target_key) {
        if (target_key >= this->length() || target_key < 0)    return null;
        if (target_key == 0)    return this->head.next[0]->data;
        if (target_key == this->length() - 1)    return this->tail->data;
        ____node_ptr curr = this->prev_curr_next_find(target_key);        
        return curr->data;
    }

    size_t edit(void *data, size_t target_key) {
        if (target_key >= this->length() || target_key < 0)    return -1;
        if (target_key == 0) {
            this->memcopy((char *)data, this->head.next[0]->data, data_size);
            return target_key;
        }
        if (target_key == this->length() - 1) {
            this->memcopy((char *)data, this->tail->data, data_size);
            return target_key;
        }
         ____node_ptr curr = this->prev_curr_next_find(target_key);
        this->memcopy((char *)data, curr->data, data_size);
        return target_key;
    }
    
    void removeall() {
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
# ifdef DEBUG
    void show() {
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
    }
    void show_2() {
        std::cout << "=========================================" << std::endl;
        ____node_ptr curr = &(this->head);
        for (int i = 0; i < _MAX_LAYER_; i++) {
            std::cout << i << "::: ";
            while (curr != null) {
                std::cout << curr->key[i];
                std::cout << "---";
                curr = curr->next[i];
            }
            std::cout << std::endl;
            curr = &(this->head);
        }
        std::cout << "=========================================" << std::endl;
    }
# endif
};

# endif


# ifndef _MY_VECTOR_
# define _MY_VECTOR_

class MyVectorException: public std::exception {
private:
    char message[30];
public:
    MyVectorException(const char *str) {
        int idx = 0;
        while(str[idx] != 0) {
            message[idx] = str[idx];
            idx++;
        }
        message[idx] = 0;
    }
    virtual const char* what() const throw () {
        return this->message;
    } 
};

template <typename type>
class myvector {
private:
    fakeskiplist data;
public:
    size_t length() {
        return this->data.length();
    }
    size_t size() {
        return this->data.length() * sizeof(type);
    }
    myvector(): data(sizeof(type)){
        ;
    }
    ~myvector() {
        this->data.removeall();
    }
    size_t insert(type *data, size_t pos) {
        size_t ret = this->data.insert(data, pos);
        if (ret == -1) {
            MyVectorException except("Position out of range!!!");
            throw except;
        }
        return ret;
    }
    size_t append(type *data) {
        size_t ret = this->data.insert(data, this->data.length() - 1);
        if (ret == -1) {
            MyVectorException except("Position out of range!!!");
            throw except;
        }
        return ret;
    }
    size_t push(type *data) {
        size_t ret = this->data.insert(data, this->data.length() - 1);
        if (ret == -1) {
            MyVectorException except("Position out of range!!!");
            throw except;
        }
        return ret;
    }
    size_t enqueue(type *data) {
        size_t ret = this->data.insert(data, this->data.length() - 1);
        if (ret == -1) {
            MyVectorException except("Position out of range!!!");
            throw except;
        }
        return ret;
    }
    type *pop() {
        type *ret = (type *)this->data.remove(this->data.length() - 1);
        if (ret == null) {
            MyVectorException except("Position out of range!!!");
            throw except;
        }
        return ret;
    }
    type *dequeue() {
        type *ret = (type *)this->data.remove(0);
        if (ret == null) {
            MyVectorException except("Position out of range!!!");
            throw except;
        }
        return ret;
    }
    int empty() {
        if (this->data.length() == 0)   return 1;
        return 0;
    }
    void remove(size_t pos) {
        char *ret = (char *)this->data.remove(pos);
        if (ret == null) {
            MyVectorException except("Position out of range!!!");
            throw except;
        }
        delete [] ret;
    }
    const type *at(size_t pos) {
        type *ret = (type *)this->data.get(pos);      
        if (ret == null) {
            MyVectorException except("Position out of range!!!");
            throw except;
        }
        return ret;
    }
    size_t set(type *data, size_t pos) {
        size_t ret = this->data.edit(data, pos);
        if (ret == -1) {
            MyVectorException except("Position out of range!!!");
            throw except;
        }
        return ret;
    }
    void destroy() {
        this->data.removeall();
    }
};

# endif