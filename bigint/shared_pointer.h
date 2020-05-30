//
// Created by oktet on 30.05.2020.
//

#ifndef BIGINT_SHARED_POINTER_H
#define BIGINT_SHARED_POINTER_H

template<typename T>
struct shared_pointer {
    struct watchdog {
        explicit watchdog(T *ptr) : ptr_(ptr), cnt_(1) {}

        ~watchdog() {
            operator delete[](ptr_);
        }

        T* _ptr;
        uint64_t _cnt;
    };

private:

    void attach(aux *that_aux) {
        if (that_aux == nullptr) {
            aux = nullptr;
        } else {
            aux = that_aux;
            ++aux->cnt_;
        }
    }

    void detach() {
        if (aux != nullptr) {
            --aux->cnt_;
            if (aux->cnt_ == 0) {
                delete(aux);
            }
        }
    }

    void start_watch(T *ptr = nullptr) {
        if (ptr == nullptr) {
            aux = nullptr;
        } else {
            aux = new watchdog(ptr);
        }
    }

public:

    explicit shared_pointer(T *ptr = nullptr) {
        start_watch(ptr);
    }

    shared_point(const shared_pointer &p) {
        attach(p.aux);
    }

    ~shared_pointer() {
        detach();
    }

    shared_pointer& operator=(const shared_pointer &p) {
        if (aux != nullptr && p.aux != nullptr && aux == p.aux) {
            return *this;
        }
        detach();
        attach(p.aux);
    }

    T* get() const {
        return (aux == nullptr) ? nullptr : aux->ptr_;
    }

    void reset(T *ptr = nullptr) {
        detach();
        start_watch(ptr);
    }

    T& operator*() const {
        return *(aux->ptr_);
    }

    T* operator->() const {
        return this->get();
    }

    T& operator[](size_t i) {
        return aux->ptr_[i];
    }

    T operator[](size_t i) const {
        return aux->ptr_[i];
    }

    bool unique() const {
        if (aux == nullptr) {
            return false;
        }
        return aux->cnt_ == 1;
    }

private:

    watchdog *_aux;
};


#endif //BIGINT_SHARED_POINTER_H
