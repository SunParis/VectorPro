# ifndef _MY_VECTOR_
# define _MY_VECTOR_
# include <exception>
# include <cstddef>
// # define DEBUG

# ifdef DEBUG
# include <iostream>
# endif

# ifndef null
# define null 0
# endif

class ____MemoryException: public std::exception {
private:
    char message[30];
public:
    ____MemoryException(const char *str) {
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

class ____MyVectorException: public std::exception {
private:
    char message[30];
public:
    ____MyVectorException(const char *str) {
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


# define _MAX_LAYER_ 30
# define _____MAXCURR 0x3fffffff
class ____LayerGenerator {
private:
    size_t curr = 0;
public:
    ____LayerGenerator() {
        this->curr = 0;
    }
    int ___layernumgenerate() {
        int ret = 1;
        size_t tmp = this->curr;
        this->curr++;
        if (this->curr > _____MAXCURR)  this->curr = 0;
        if ((tmp & 63) == 63)  ret += 1;
        else    return ret;
        tmp = tmp >> 6;
        while (ret < _MAX_LAYER_) {
            if ((tmp & 3) == 3)  ret += 1;
            else    return ret;
            tmp = tmp >> 2;
        }
        return _MAX_LAYER_;
    }
};

# define type_size (sizeof(type) * sizeof(char))
# define sizeofptr (sizeof(____node_ptr) * sizeof(char))
typedef struct ____node ____node;
typedef ____node* ____node_ptr;
struct ____node {
    char *data;
    int nextlen;
    int *key;
    ____node_ptr *next;
};

class ____fakeskiplist: private ____LayerGenerator {
private:
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
    ____node_ptr newnode(const void *data) {
        ____node_ptr newptr = new ____node;
        if (newptr == 0)    throw ____MemoryException("Out of memory!!!");
        newptr->nextlen = this->___layernumgenerate();
        newptr->data = new char[data_size];
        newptr->key = new int[newptr->nextlen];
        newptr->next = new ____node_ptr[newptr->nextlen];
        if (newptr->data == null || newptr->key == null || newptr->next == null) {
            if (newptr->data == null)   delete [] newptr->data;
            if (newptr->key == null)    delete [] newptr->key;
            if (newptr->next == null)   delete [] newptr->next;
            delete newptr;
            throw ____MemoryException("Out of memory!!!");
        }
        this->memcopy((char *)data, newptr->data, data_size);
        for (int i = 0; i < newptr->nextlen; i++) {
            newptr->next[i] = null;
            newptr->key[i] = 0;
        }
        return newptr;
    }
    char *free_node(____node_ptr target) {
        if (target == null) return null;
        char *ret = target->data;
        delete [] target->key;
        delete [] target->next;
        delete target;
        return ret;
    }
    ____node_ptr prev_curr_next_find(size_t target, ____node_ptr *prev = null, ____node_ptr *next = null, size_t *prev_pos = null) {
        if (target == -1 || target >= this->length())   return null;
        ____node_ptr curr = &(this->head);
        size_t curr_pos = -1;
        int curr_layer = _MAX_LAYER_ - 1;
        if (target == 0) {
            for (int i = 0; i < this->head.next[0]->nextlen; i++) {
                if (prev != null)   prev[i] = &(this->head);
                if (next != null)   next[i] = this->head.next[0]->next[i];
                if (prev_pos != null)   prev_pos[i] = 0;
            }
            return this->head.next[0];
        }
        else if (target == this->length() - 1) {
            while (curr->next[0] != this->tail) {
                while (curr->next[curr_layer] == null && curr_layer != 0) {
                    if (prev != null)   prev[curr_layer] = curr;
                    if (prev_pos != null)   prev_pos[curr_layer] = curr_pos;
                    curr_layer--;
                }
                if (curr_layer == 0)    break;
                while (curr->next[curr_layer] != this->tail) {
                    if (curr->next[curr_layer] == null)  break;
                    curr = curr->next[curr_layer];
                    curr_pos += curr->key[curr_layer];
                }
                if (curr->next[curr_layer] == this->tail) {
                    if (prev != null)   prev[curr_layer] = curr;
                    if (prev_pos != null)   prev_pos[curr_layer] = curr_pos;
                    curr_layer--;
                }
            }
            if (curr_layer == 0) {
                while (curr->next[0] != this->tail) {
                    curr_pos += 1;
                    curr = curr->next[0];
                }
            }
            for (int i = 0; i < curr->nextlen; i++) {
                if (prev != null)   prev[i] = curr;
                if (prev_pos != null)   prev_pos[i] = curr_pos;
                if (next != null)   next[i] == null;
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
        char *data = this->free_node(curr);
        this->len--;
        if (this->length() == 0)    this->tail = null;
        return data;
    }
    void *remove_tail(void) {
        ____node_ptr prev_rec_list[_MAX_LAYER_];
        ____node_ptr curr = this->prev_curr_next_find(this->length() - 1, prev_rec_list);       
        
        for (int i = 0; i < this->tail->nextlen; i++) {
            prev_rec_list[i]->next[i] = null;
        }
        char *data = this->free_node(this->tail);
        this->len--;
        this->tail = prev_rec_list[0];
        this->tail->next[0] = null;
        if (this->length() == 0)    this->tail = null;
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
        for (int i = 0; i < newptr->nextlen; i++) {
            if (i < curr->nextlen) {
                curr->next[i] = newptr;
                newptr->key[i] = 1;
            }
            else {
                prev_rec_list[i]->next[i] = newptr;
                newptr->key[i] = this->length() - prev_key_rec[i];
            }
        }
        newptr->key[0] = 0;
        this->len++;
        this->tail = newptr;
        return 0;
    }
public:
    ____fakeskiplist(size_t data_size) {
        this->data_size = data_size;
        this->head.data = null;
        this->head.nextlen = _MAX_LAYER_;
        this->head.key = new int[_MAX_LAYER_];
        this->head.next = new ____node_ptr[_MAX_LAYER_];
        for (int i = 0; i < _MAX_LAYER_; i++) {
            this->head.key[i] = -1;
            this->head.next[i] = null;
        }
        this->tail = null;
    }
    ~____fakeskiplist() {
        this->destroy();
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
                prev_rec_list[i]->next[i] = newptr;
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
        return (after_key + 1);
    }   

    void *remove(size_t target_key) {
        if (target_key >= this->length() || target_key < 0)    return null;
        if (target_key == 0)    return this->remove_head();
        if (target_key == this->length() - 1)    return this->remove_tail();
        ____node_ptr next_update_list[_MAX_LAYER_];
        ____node_ptr prev_rec_list[_MAX_LAYER_];
        ____node_ptr curr = this->prev_curr_next_find(target_key, prev_rec_list, next_update_list);
        for (int i = 0; i < _MAX_LAYER_; i++) {
            prev_rec_list[i]->next[i] = next_update_list[i];
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

        char *data = this->free_node(curr);
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

    ____node_ptr get_node_ptr(size_t target_key) {
        if (target_key >= this->length() || target_key < 0)    return null;
        if (target_key == 0)    return this->head.next[0];
        if (target_key == this->length() - 1)    return this->tail;
        ____node_ptr curr = this->prev_curr_next_find(target_key);        
        return curr;
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
        if (this->len == 0) return;
        ____node_ptr curr = this->head.next[0];
        ____node_ptr tmp;
        while (curr != null) {
            tmp = curr;
            curr = curr->next[0];
            delete [] tmp->data;
            this->free_node(tmp);
        }
        for (int i = 0; i < _MAX_LAYER_; i++) this->head.next[i] = null;
        this->len = 0;
        this->tail = null;
    }
    void destroy() {
        if (this->len != 0) this->removeall();
        if (this->head.next != null) {
            delete [] this->head.next;
            this->head.next = null;
        }
        if (this->head.key != null) {
            delete [] this->head.key;
            this->head.key = null;
        }
        this->len = 0;
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

template <typename type>
class myvector {
private:
    ____fakeskiplist data;
    char is_destroy = 0;
    struct trash_node {
        char *data;
        struct trash_node *next;
    };
    struct trash_node *trash_head = null;
    
public:
    size_t length() {
        return this->data.length();
    }
    size_t size() {
        return this->data.length() * sizeof(type);
    }
    myvector(): data(sizeof(type)) {
        this->trash_head = null;
        this->is_destroy = 0;
    }
    ~myvector() {
        this->destroy();
    }
    size_t insert(type &data, size_t pos) {
        if (this->is_destroy == 1)  throw ____MyVectorException("This vector has been destroyed!!!");
        size_t ret = this->data.insert(&data, pos);
        if (ret == -1) {
            throw ____MyVectorException("Position out of range!!!");
        }
        return ret;
    }
    size_t append(type &data) {
        if (this->is_destroy == 1)  throw ____MyVectorException("This vector has been destroyed!!!");
        size_t ret = this->data.insert(&data, this->data.length() - 1);
        if (ret == -1) {
            throw ____MyVectorException("Position out of range!!!");
        }
        return ret;
    }
    size_t append(type *data) {
        if (this->is_destroy == 1)  throw ____MyVectorException("This vector has been destroyed!!!");
        size_t ret = this->data.insert(data, this->data.length() - 1);
        if (ret == -1) {
            throw ____MyVectorException("Position out of range!!!");
        }
        return ret;
    }
    size_t push(type &data) {
        if (this->is_destroy == 1)  throw ____MyVectorException("This vector has been destroyed!!!");
        size_t ret = this->data.insert(&data, this->data.length() - 1);
        if (ret == -1) {
            throw ____MyVectorException("Position out of range!!!");
        }
        return ret;
    }
    size_t push(type *data) {
        if (this->is_destroy == 1)  throw ____MyVectorException("This vector has been destroyed!!!");
        size_t ret = this->data.insert(data, this->data.length() - 1);
        if (ret == -1) {
            throw ____MyVectorException("Position out of range!!!");
        }
        return ret;
    }
    size_t enqueue(type &data) {
        if (this->is_destroy == 1)  throw ____MyVectorException("This vector has been destroyed!!!");
        size_t ret = this->data.insert(&data, this->data.length() - 1);
        if (ret == -1) {
            throw ____MyVectorException("Position out of range!!!");
        }
        return ret;
    }
    size_t enqueue(type *data) {
        if (this->is_destroy == 1)  throw ____MyVectorException("This vector has been destroyed!!!");
        size_t ret = this->data.insert(data, this->data.length() - 1);
        if (ret == -1) {
            throw ____MyVectorException("Position out of range!!!");
        }
        return ret;
    }
    type& pop() {
        if (this->is_destroy == 1)  throw ____MyVectorException("This vector has been destroyed!!!");
        type *data = (type *)this->data.remove(this->data.length() - 1);
        if (data == null) {
            throw ____MyVectorException("Position out of range!!!");
        }
        struct trash_node *trash = new struct trash_node;
        trash->data = (char *)data;
        trash->next = this->trash_head;
        this->trash_head = trash;
        type& ret = *data;
        return ret;
    }
    type& dequeue() {
        if (this->is_destroy == 1)  throw ____MyVectorException("This vector has been destroyed!!!");
        type *data = (type *)this->data.remove(0);
        if (data == null) {
            throw ____MyVectorException("Position out of range!!!");
        }
        struct trash_node *trash = new struct trash_node;
        trash->data = (char *)data;
        trash->next = this->trash_head;
        this->trash_head = trash;
        type& ret = *data;
        return ret;
    }
    int is_empty() {
        if (this->is_destroy == 1)  return 1;
        if (this->data.length() == 0)   return 1;
        return 0;
    }
    void remove(size_t pos) {
        if (this->is_destroy == 1)  throw ____MyVectorException("This vector has been destroyed!!!");
        char *ret = (char *)this->data.remove(pos);
        if (ret == null) {
            throw ____MyVectorException("Position out of range!!!");
        }
        delete [] ret;
    }
    type& at(size_t pos) {
        if (this->is_destroy == 1)  throw ____MyVectorException("This vector has been destroyed!!!");
        type *data = (type *)this->data.get(pos);      
        if (data == null) {
            throw ____MyVectorException("Position out of range!!!");
        }
        type& ret = *data;
        return ret;
    }
    size_t set(type& data, size_t pos) {
        if (this->is_destroy == 1)  throw ____MyVectorException("This vector has been destroyed!!!");
        size_t ret = this->data.edit(&data, pos);
        if (ret == -1) {
            throw ____MyVectorException("Position out of range!!!");
        }
        return ret;
    }
    size_t set(type *data, size_t pos) {
        if (this->is_destroy == 1)  throw ____MyVectorException("This vector has been destroyed!!!");
        size_t ret = this->data.edit(data, pos);
        if (ret == -1) {
            throw ____MyVectorException("Position out of range!!!");
        }
        return ret;
    }
    type& operator[](size_t pos) {
        if (this->is_destroy == 1)  throw ____MyVectorException("This vector has been destroyed!!!");
        type *data = (type *)this->data.get(pos);
        if (data == null) {
            throw ____MyVectorException("Position out of range!!!");
        }
        type& ret = *data;
        return ret;
    }
    void clear() {
        this->data.removeall();
    }
    void destroy() {
        if (this->is_destroy == 1)  return;
        this->data.destroy();
        struct trash_node *curr = this->trash_head;
        while (curr != null) {
            this->trash_head = curr;
            curr = curr->next;
            delete [] this->trash_head->data;
            delete this->trash_head;
        }
        this->is_destroy = 1;
    }
    size_t find(type& target, size_t from = 0, size_t end = -1) {
        if (this->is_destroy == 1)  throw ____MyVectorException("This vector has been destroyed!!!");
        size_t true_start = from;
        size_t true_end = end;
        if (true_start == -1)   true_start = this->length();
        if (true_end == -1) true_end = this->length();
        if (true_start >= this->length() && true_end >= this->length()) return -1;

        if (true_start <= true_end) {
            ____node_ptr curr = this->data.get_node_ptr(true_start);
            for (size_t i = true_start; i < true_end; i++) {
                type *curr_data_ptr = (type *)curr->data;
                type& curr_data = *curr_data_ptr;
                if (curr_data == target)    return i;
                curr = curr->next[0];
            }
            return -1;
        }
        else {
            size_t ret = -1;
            if (true_start - true_end <= 64) {
                ____node_ptr curr = this->data.get_node_ptr(true_end);
                for (size_t i = true_end; i < true_start; i++) {
                    type *curr_data_ptr = (type *)curr->data;
                    type& curr_data = *curr_data_ptr;
                    if (curr_data == target)    ret = i;
                    curr = curr->next[0];
                }
                return ret;
            }
            else {
                ____node_ptr curr = this->data.get_node_ptr(true_start - 64);
                for (size_t i = true_start - 64; i < true_start; i++) {
                    type *curr_data_ptr = (type *)curr->data;
                    type& curr_data = *curr_data_ptr;
                    if (curr_data == target)    ret = i;
                    curr = curr->next[0];
                }
                if (ret != -1)  return ret;
                ret = this->find(target, true_start - 64, true_end);
                return ret;
            }
        }
    }
};

# endif
