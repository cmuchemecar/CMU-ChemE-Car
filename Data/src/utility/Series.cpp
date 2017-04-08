#include "Series.h"

Series::Series(int size) {
    if (size < 2) {
  	    this->_size = 2;
    }
    else if (size > _maxSize) {
  	    this->_size = _maxSize;
    }
    else {
  	    this->_size = size;
    }

    this->_updates = 0;
    this->_i = _size-1;
    this->_values = (float*) calloc(_size, sizeof(float));
}

void Series::update(float value) {
    if (_updates < _size) {
        _updates++;
    }

	_i = _inc(_i);
    _values[_i] = value;
}

bool Series::ready() {
    return (_updates == _size);
}

float Series::get(int i) {
    if (i < 0 || i > _size-1) {
        return 0;
    }

    return _values[(_i - i + _size) % _size];
}

float Series::sum() {
    float sum = 0;

    int j = _i;
    for (int i = 0; i < _size; i++) {
        sum += _values[j];
        j = _dec(j);
    }

    return sum;
}

float Series::sum(int num) {
    if (num < 1 || num > _size) {
        return 0;
    }

    float sum = 0;

    int j = _i;
    for (int i = 0; i < num; i++) {
        sum += _values[j];
        j = _dec(j);
    }

    return sum;
}

float Series::sum(int start, int num) {
    if (start < 0 || start > _size-1 || num < 1 || num > _size
        || start+num > _size) {
        return 0;
    }

    float sum = 0;

    int j = _i;
    for (int i = 0; i < start; i++) {
        j = _dec(j);
    }

    for (int i = 0; i < num; i++) {
        sum += _values[j];
        j = _dec(j);
    }

    return sum;
}

float Series::average() {
    return sum() / _size;
}

float Series::average(int num) {
    if (num == 0) {
        return 0;
    }

    return sum(num) / num;
}

float Series::average(int start, int num) {
    if (num == 0) {
        return 0;
    }

    return sum(start, num) / num;
}

float Series::change() {
    return get(0) - get(1);
}

float Series::averageChange(int num) {
    if (2*num > _size) {
        return 0;
    }

    return average(0, num) - average(num, num);
}

void Series::reset() {
    for (int i = 0; i < _size; i++) {
        _values[i] = 0;
    }

    _updates = 0;
    _i = _size-1;
}

void Series::print(int dec) {
    int j = _i;
    for (int i = 0; i < _size; i++) {
        Serial.print(FloatToString(_values[j], dec));
        Serial.print(" ");
        j = _dec(j);
    }
}

void Series::println(int dec) {
    int j = _i;
    for (int i = 0; i < _size; i++) {
        Serial.print(FloatToString(_values[j], dec));
        Serial.print(" ");
        j = _dec(j);
    }
    Serial.println();
}

int Series::_inc(int i) {
    if (i == (_size-1)) {
    	return 0;
    }
    else {
    	return i+1;
    }
}

int Series::_dec(int i) {
    if (i == (0)) {
    	return _size-1;
    }
    else {
    	return i-1;
    }
}

