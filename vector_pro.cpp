# ifndef MYVECTOR
# include "vector_pro.h"
# endif

template <typename T>
vector_pro<T>::vector_pro(const long int ini_size) {
    if (ini_size <= 0) {
        throw "Initail size of vector should bt 0.";
    }
    this->data = new T* [ini_size];
    if (this->data ==null) {
        throw "Out of memory, nothing was done.";
    }
    this->curr_size = ini_size;
    this->end = 0;
}

template <typename T>
vector_pro<T>::~vector_pro() {
    if (this->data != null) {
        if (this->end > 0) {
            for (auto idx = 0; idx < this->end; idx++) {
                delete this->data[idx];
            }
            this->end = 0;
        }
        delete [] this->data;
        this->data = null;
        this->curr_size = 0;
    }
    if (this->trash_head != null) {
        trash<T> *curr = this->trash_head;
        while (curr != null) {
            delete curr->data;
            this->trash_head = curr->next;
            delete curr;
            curr = this->trash_head;
        }
        this->trash_head = null;
    }
}

template <typename T>
void vector_pro<T>::clean() {
    for (auto idx = 0; i < this->end; i++) {
        delete this->data[idx];
    }
    this->end = 0;
}

template <typename T>
int vector_pro<T>::empty() {
    if (this->end == 0) return 1;
    return 0;
}

template <typename T>
T& vector_pro<T>::at(const long int idx) {
    if (this->data == null || this->end <= 0) throw "Vector is empty.";
    if (idx >= this->end) throw "Illegal index.";
    return *(this->data[idx]);
}

template <typename T>
long int vector_pro<T>::push(const T& target) {
    if (this->end == this->curr_size) {
        this->resize(this->curr_size * 2);
    }
    this->data[this->end] = new T(target);
    this->end += 1;
    return (this->end - 1);
}

template <typename T>
T& vector_pro<T>::pop() {
    if (this->end <= 0) throw "Vector is empty.";
    T *ret = this->data[this->end];
    trash<T> *tmp = new trash<T>;
    if (tmp == null) {
        throw "Out of memory, nothing was done.";
    }
    tmp->data = ret;
    tmp->next = this->trash_head;
    this->trash_head = tmp;
    this->end -= 1;
    return *ret;
}

template <typename T>
T& vector_pro<T>::tail() {
    if (this->end <= 0) throw "Vector is empty.";
    return this->data[this->end];
}

template <typename T>
long int vector_pro<T>::length() {
    return this->end;
}

template <typename T>
long int vector_pro<T>::capacity() {
    return this->curr_size;
}

template <typename T>
long int vector_pro<T>::find(const T& target, int(compare2)(const T &, const T &)) {
    if (this->end <= 0) return -1;

    for (auto idx = 0; idx < this->end; idx++) {
        if (compare2(*(this->data[idx]), target) == 0)  return idx;
    }

    return -1;
}

template <typename T>
void vector_pro<T>::resize(const long int re_size) {
    if (re_size <= this->end)   return;
    T **tmp = new T*[re_size];
    if (tmp == null)    throw "Out of memory, nothing was done.";
    for (auto idx = 0; idx < this->end; idx++) {
        tmp[idx] = this->data[idx];
    }
    delete [] this->data;
    this->data = tmp;
    return;
}

template <typename T>
void vector_pro<T>::swap(const long int idx1, const long int idx2) {
    if (this->data == null || this->end <= 0) throw "Vector is empty.";
    if (idx1 >= this->end || idx2 >= this->end) throw "Illegal index.";
    if (idx1 < 0 || idx2 < 0) throw "Illegal index.";
    if (idx1 == idx2)   return;
    T *tmp = this->data[idx1];
    this->data[idx1] = this->data[idx2];
    this->data[idx2] = tmp;
}

template <typename T>
T& vector_pro<T>::operator[](long int idx) {
    if (this->data == null || this->end <= 0) throw "Vector is empty.";
    if (idx >= this->end) throw "Illegal index.";
    return *(this->data[idx]);
}


template<typename T>
void vector_pro<T>::insertionSort(int left, int right, int(compare2)(const T &, const T &)) {
    T **arr = this->data;
    for (int i = left + 1; i <= right; i++) {
        T *temp = arr[i];
        int j = i - 1;
        while (j >= left && compare2(*(this->data[j]), *temp) > 0) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = temp;
    }
}

template<typename T>
void vector_pro<T>::mergesort(int l, int m, int r, int(compare2)(const T &, const T &)) {
    T **arr = this->data;
    int len1 = m - l + 1, len2 = r - m;
    T **left = new T*[len1];
    T **right = new T*[len2];
    
    for (int i = 0; i < len1; i++)
        left[i] = arr[l + i];
    for (int i = 0; i < len2; i++)
        right[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < len1 && j < len2) {
        if (compare2(*(left[i]), *(right[j])) <= 0) {
            arr[k] = left[i];
            i++;
        } else {
            arr[k] = right[j];
            j++;
        }
        k++;
    }

    while (i < len1) {
        arr[k] = left[i];
        i++;
        k++;
    }

    while (j < len2) {
        arr[k] = right[j];
        j++;
        k++;
    }

    delete [] left;
    delete [] right;
}

template<typename T>
void vector_pro<T>::sort(int(compare2)(const T &, const T &)) {
    if (this->data == null || this->end <= 0) throw "Vector is empty.";
    const int RUN = 32;
    long int n = this->length();
    for (long int i = 0; i < n; i += RUN)
        insertionSort(i, (i + 31 < n - 1) ? (i + 31) : (n - 1), compare2);

    for (long int size = RUN; size < n; size = 2 * size) {
        for (long int left = 0; left < n; left += 2 * size) {
            long int mid = left + size - 1;
            long int right = (left + 2 * size - 1 < n - 1) ? (left + 2 * size - 1) : (n - 1);

            if (mid < right)
                mergesort(left, mid, right, compare2);
        }
    }
}

template<typename T>
void vector_pro<T>::merge(const vector_pro<T> &another) {
    if (another.empty() == 0)   return;
    this->resize(this->curr_size + another.length());
    
}
