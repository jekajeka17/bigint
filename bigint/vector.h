//
// Created by oktet on 30.05.2020.
//

#ifndef BIGINT_VECTOR_H
#define BIGINT_VECTOR_H

template<typename T>
struct vector {
private:

    void to_big_object(size_t to_allocate = _small_object_limit * 2) {
        _allocated = to_allocate;
        _big_object.reset(static_cast<T*>(operator new[](_allocated * sizeof(T))));
        for (size_t i = 0; i < _size; ++i) {
            new(_big_object.get() + i) T(_small_object[i]);
            _small_object[i].~T();
        }
    }

    void extend(size_t to_allocate = _allocated * 2) {
        _allocated = to_allocate;
        T* new_big_object = static_cast<T*>(operator new[](_allocated * sizeof(T)));
        for (size_t i = 0; i < _size; ++i) {
            new(new_big_object + i) T(_big_object[i]);
        }
        _big_object.reset(new_big_object);
    }

public:

    vector() : _size(0), _allocated(0) {}

    vector(const vector<T> &that) : _size(that._size), _allocated(that._allocated), _big_object(that._big_object) {
        if (that._allocated == 0) {
            for (size_t i = 0; i < that.size(); ++i) {
                new(_small_object + i) T(that._small_object[i]);
            }
        }
    }

    ~vector() {
        if (that._allocated == 0) {
            for (size_t i = 0; i < _size; ++i) {
                _small_object[i].~T();
            }
        } else {
            for (size_t i = 0; i < _size; ++i) {
                _big_object[i].~T();
            }
        }
    }

    vector& operator=(const vector &that) {
        if (that._allocated == 0) {
            for (size_t i = 0; i < that.size(); ++i) {
                new(_small_object_i) T(that._small_object[i]);
            }
            _big_object.reset();
        } else {
            if (_allocated == 0) {
                for (size_t i = 0; i < _size; ++i) {
                    _small_object[i].~T();
                }
            }
            _big_object = that._big_object;
        }
        _size = that._size;
        _allocated = that._allocated;

        return *this;
    }

    void push_back(const T value) {
        if (_size == _small_object_limit && _allocated == 0) {
            convert_to_big_object();
        }
        if (_allocated == 0) {
            new(_small_object + _size) T(value);
        } else {
            if (_allocated == _size) {
                extend();
            }
            new(_big_object.get() + _size) T(value);
        }
        ++_size;
    }

    // TODO: resize, reserve, size, empty, checkout, operator[]

private:
    static const size_t _small_object_limit = 2;

    size_t _size;
    size_t _allocated;

    T _small_object[_small_object_limit];
    shared_pointer<T> _big_object;
};

#endif //BIGINT_VECTOR_H
