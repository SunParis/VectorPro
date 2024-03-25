# ifndef _MY_SKIPLIST_
# define _MY_SKIPLIST_
// # define DEBUG
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
# include <random>
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
        this->memcopy((char *)data, newdata, data_size);
        newptr->data = newdata;
        newptr->nextlen = ___layernumgenerate();
        for (int i = 0; i < _MAX_LAYER_; i++) newptr->next[i] = null;
        for (int i = 0; i < _MAX_LAYER_; i++) newptr->key[i] = 0;
        return newptr;
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
        ____node_ptr curr = &(this->head);
        ____node_ptr prev_rec_list[_MAX_LAYER_];        
        int curr_layer = _MAX_LAYER_ - 1;

        while (curr->next[0] != this->tail) {
            while (curr->next[curr_layer] == null && curr_layer != 0) {
                curr_layer--;
            }
            if (curr_layer == 0)    break;
            while (curr->next[curr_layer] != this->tail) {
                if (curr->next[curr_layer] == null)  break;
                curr = curr->next[curr_layer];
            }
            if (curr->next[curr_layer] == this->tail) {
                prev_rec_list[curr_layer] = curr;
                curr_layer--;
            }
        }
        if (curr_layer == 0) {
            while (curr->next[0] != this->tail) {
                curr = curr->next[0];
            }
        }

        for (int i = 0; i < curr->nextlen; i++) {
            prev_rec_list[i] = curr;
        }
        
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
        this->Destroyall();
    }
    size_t length() {
        return this->len;
    }
    size_t insert(const void *data, size_t after_key) {
        if (after_key >= this->length() && after_key != -1)    return -1;
        if (after_key == -1)    return this->insert_head(data);
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
                else {
                    if (next_update_list[i] != null)  next_update_list[i]->key[i] ++;
                }
            }
        }

        if (after_key == this->len - 1) this->tail = newptr;
        delete [] prev_rec_list;
        delete [] keyrec;
        this->len++;
        return after_key + 1;
    }   

    void *remove(size_t target_key) {
        if (target_key >= this->length() || target_key < 0)    return null;
        if (target_key == 0)    return this->remove_head();
        if (target_key == this->length() - 1)    return this->remove_tail();
        ____node_ptr curr = &(this->head);
        ____node_ptr next_update_list[_MAX_LAYER_];
        ____node_ptr prev_rec_list[_MAX_LAYER_];        
        size_t count = -1;
        size_t prev_key = target_key - 1;
        int curr_layer = _MAX_LAYER_ - 1;

        while (count != prev_key) {
            while (curr->next[curr_layer] == null && curr_layer != 0) {
                prev_rec_list[curr_layer] = curr;
                next_update_list[curr_layer] = null;
                curr_layer--;
            }
            if (curr_layer == 0)    break;
            while (curr->next[curr_layer]->key[curr_layer] + count > prev_key && curr_layer != 0) {
                prev_rec_list[curr_layer] = curr;
                next_update_list[curr_layer] = curr->next[curr_layer];
                curr_layer--;
            }
            if (curr_layer == 0)    break;
            count += curr->next[curr_layer]->key[curr_layer];
            curr = curr->next[curr_layer];
        }
        if (curr_layer == 0) {
            while (count != prev_key) {
                curr = curr->next[0];
                count++;
            }
        }
        
        for (int i = curr->nextlen - 1; i >= 0; i--) {
            prev_rec_list[i] = curr;
            next_update_list[i] = curr->next[i];
        }
        curr = curr->next[0];
        for (int i = curr->nextlen - 1; i > 0; i--) {
            next_update_list[i] = curr->next[i];
        }
        next_update_list[0] = null;
        

        for (int i = 0; i < _MAX_LAYER_; i++) {
            if (i < curr->nextlen) {
                prev_rec_list[i]->next[i] = curr->next[i];
                if (next_update_list[i] != null) {
                    next_update_list[i]->key[i] += (curr->key[i] - 1); 
                }
            }
            else if (next_update_list[i] != null) {
                next_update_list[i]->key[i]--; 
            }
        }
        
        char *data = curr->data;
        delete curr;
        this->len--;
        return data;
    }

    void *get(size_t target_key) {
        if (target_key >= this->length() || target_key < 0)    return null;
        if (target_key == 0)    return this->head.next[0]->data;
        if (target_key == this->length() - 1)    return this->tail->data;
        ____node_ptr curr =&(this->head);
        int curr_layer = _MAX_LAYER_ - 1;   
        size_t count = -1;

        while (count != target_key) {
            while (curr->next[curr_layer] == null && curr_layer != 0) {
                curr_layer--;
            }
            if (curr_layer == 0)    break;
            while (curr->next[curr_layer]->key[curr_layer] + count > target_key && curr_layer != 0) {
                curr_layer--;
            }
            if (curr_layer == 0)    break;
            count += curr->next[curr_layer]->key[curr_layer];
            curr = curr->next[curr_layer];
        }
        if (curr_layer == 0) {
            while (count != target_key) {
                curr = curr->next[0];
                count++;
            }
        }
        
        return curr->data;
    }

    size_t edit(void *data, size_t target_key) {
        if (target_key >= this->length() || target_key < 0)    return -1;
        if (target_key == 0) {
            delete [] this->head.next[0]->data;
            this->head.next[0]->data = new char[data_size];
            this->memcopy((char *)data, this->head.next[0]->data, data_size);
            return target_key;
        }
        if (target_key == this->length() - 1) {
            delete [] this->tail->data;
            this->tail->data = new char[data_size];
            this->memcopy((char *)data, this->tail->data, data_size);
            return target_key;
        }
        ____node_ptr curr =&(this->head);
        int curr_layer = _MAX_LAYER_ - 1;   
        size_t count = -1;

        while (count != target_key) {
            while (curr->next[curr_layer] == null && curr_layer != 0) {
                curr_layer--;
            }
            if (curr_layer == 0)    break;
            while (curr->next[curr_layer]->key[curr_layer] + count > target_key && curr_layer != 0) {
                curr_layer--;
            }
            if (curr_layer == 0)    break;
            count += curr->next[curr_layer]->key[curr_layer];
            curr = curr->next[curr_layer];
        }
        if (curr_layer == 0) {
            while (count != target_key) {
                curr = curr->next[0];
                count++;
            }
        }
        delete [] curr->data;
        curr->data = new char[data_size];
        this->memcopy((char *)data, curr->data, data_size);
        return target_key;
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


# ifndef _MY_VECTOR_EXCEPTION_
# define _MY_VECTOR_EXCEPTION_
class MyVectorException: public std::exception {
private:
    string message;
public:
    MyVectorException(const char *str): message(str) {}
    virtual const char* what() const throw () {
        return message.c_str();
    } 
};

# endif

# ifndef _MY_VECTOR_
# define _MY_VECTOR_
template <typename type>
class myvector {
private:
    fakeskiplist data;
public:
    size_t length() {
        return this->data.length();
    }
    size_t size() {
        return this->data.length();
    }
    myvector(): data(sizeof(type)){
        this->len = 0;
        this->capacity = 0;
    }
    ~myvector() {
        this->data.Destroyall();
    }
    size_t insert(type *data, size_t pos) {
        size_t ret = this->data.insert(data, pos);
        if (ret == -1) {
            MyVectorException except("position out of range!!!");
            throw except;
        }
        return ret;
    }
    size_t append(type *data) {
        size_t ret = this->data.insert(data, this->data.length() - 1);
        if (ret == -1) {
            MyVectorException except("position out of range!!!");
            throw except;
        }
        return ret;
    }
    size_t push(type *data) {
        size_t ret = this->data.insert(data, this->data.length() - 1);
        if (ret == -1) {
            MyVectorException except("position out of range!!!");
            throw except;
        }
        return ret;
    }
    size_t enqueue(type *data) {
        size_t ret = this->data.insert(data, this->data.length() - 1);
        if (ret == -1) {
            MyVectorException except("position out of range!!!");
            throw except;
        }
        return ret;
    }
    type *pop() {
        type *ret = this->data.remove(this->data.length() - 1);
        if (ret == null) {
            MyVectorException except("position out of range!!!");
            throw except;
        }
        return ret;
    }
    type *dequeue() {
        type *ret = this->data.remove(0);
        if (ret == null) {
            MyVectorException except("position out of range!!!");
            throw except;
        }
        return ret;
    }
    int empty() {
        if (this->data.length() == 0)   return 1;
        return 0;
    }
    type *remove(size_t pos) {
        type *ret = this->data.remove(pos);
        if (ret == null) {
            MyVectorException except("position out of range!!!");
            throw except;
        }
        return ret;
    }
    type at(size_t pos) {
        type *ret = this->data.get(pos);        
        if (ret == null) {
            MyVectorException except("position out of range!!!");
            throw except;
        }
        return *ret;
    }
    size_t edit(type *data, size_t pos) {
        size_t ret = this->data.edit(data, pos);
        if (ret == -1) {
            MyVectorException except("position out of range!!!");
            throw except;
        }
        return ret;
    }
    void destroy() {
        this->data.Destroyall();
    }
};

# endif