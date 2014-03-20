/* Pierre GERARD - 00379259 - INFO2*/
#ifndef DEF_ARRAYBASE
#define DEF_ARRAYBASE

#include "AbstractArray.hpp"

using namespace std;


template <typename T,bool isPtr=false, size_t size = 0 > 
class ArrayBase {}; // pas instanciable car on "tombe" toujours dans une spécialisation


// ----------- Specialization <T,false,size> --------

template <typename T, size_t size>
class ArrayBase<T,false,size> :  virtual public AbstractArray<T>
{
    T _array[size];
public:
    ArrayBase():AbstractArray<T>::AbstractArray(size){
        for(int i = 0; i < size; ++i) 
            _array[i] = T();   
    }
    ArrayBase(size_t arraySize):AbstractArray<T>::AbstractArray(size){
        if (size != arraySize)
            throw "Construction impossible : taille incohérente"; 
        for(int i = 0; i < size; ++i) 
            _array[i] = T();   
    }
    ArrayBase(const ArrayBase<T, false, size>& vec):AbstractArray<T>::AbstractArray(size){
        if (size != vec.getSize())
            throw "Construction impossible : taille incohérente";  
        for (size_t i = 0; i < vec.getSize(); ++i) 
            _array[i] = vec[i];   
    }
    template<typename T2,bool isPtr2, size_t size2>
        ArrayBase(const ArrayBase<T2, isPtr2, size2>& vec):AbstractArray<T>::AbstractArray(size){
            if (size != vec.getSize())
                throw "Construction impossible : taille incohérente";  
            for (size_t i = 0; i < vec.getSize(); ++i) 
                _array[i] = static_cast<T>(vec[i]);   
        }
    virtual ~ArrayBase(){

    }
    virtual const T& operator[] (ptrdiff_t i) const override final{
        if (size_t(i) >= this->getSize()) 
            throw "Index out of range";
        return _array[i];
    }
    virtual T& operator[] (ptrdiff_t i) override final{
        if (size_t(i) >= this->getSize()) 
            throw "Index out of range";
        return _array[i];
    }
    ArrayBase<T,false,size>& operator= (const ArrayBase<T, false, size>& vec){
        this->copyUncheckContent(*this,vec);
        return *this;
    }
    template<typename T2,bool isPtr2, size_t size2>
        ArrayBase<T,false,size>& operator= (const ArrayBase<T2, isPtr2, size2>& vec){
            this->copyContent(*this,vec);
            return *this;
        }
};



//----------- Specialization <T,true,size> ---------


template <typename T, size_t size>
class ArrayBase<T,true,size> :  virtual public AbstractArray<T>
{
    T* _array[size];
public:
    ArrayBase():AbstractArray<T>::AbstractArray(size){
        for(int i = 0; i < size; ++i) 
            _array[i] = new T();   
    }
    ArrayBase(size_t arraySize):AbstractArray<T>::AbstractArray(size){
        if (size != arraySize)
            throw "Construction impossible : taille incohérente"; 
        for(int i = 0; i < size; ++i) 
            _array[i] = new T();   
    }
    ArrayBase(const ArrayBase<T, true, size>& vec):AbstractArray<T>::AbstractArray(size){
        if (size != vec.getSize())
            throw "Construction impossible : taille incohérente";  
        for (size_t i = 0; i < vec.getSize(); ++i) 
            _array[i] = new T(vec[i]);   
    }
    template<typename T2,bool isPtr2, size_t size2>
        ArrayBase(const ArrayBase<T2, isPtr2, size2>& vec):AbstractArray<T>::AbstractArray(size){
            if (size != vec.getSize())
                throw "Construction impossible : taille incohérente";  
            for (size_t i = 0; i < vec.getSize(); ++i){ 
                _array[i] = new T();   
                (*this)[i] = static_cast<T>(vec[i]);  
            } 
        }
    virtual ~ArrayBase(){
        for(int i = 0; i < size; ++i) 
            delete _array[i] ;
    }
    virtual const T& operator[] (ptrdiff_t i) const override final{
        if (size_t(i) >= this->getSize()) 
            throw "Index out of range";
        return *_array[i];
    }
    virtual T& operator[] (ptrdiff_t i) override final{
        if (size_t(i) >= this->getSize())
            throw "Index out of range";
        return *_array[i];
    }
    ArrayBase<T,true,size>& operator= (const ArrayBase<T, true, size>& vec){
        this->copyUncheckContent(*this,vec);
        return *this;
    }
    template<typename T2,bool isPtr2, size_t size2>
        ArrayBase<T,true,size>& operator= (const ArrayBase<T2, isPtr2, size2>& vec){
            this->copyContent(*this,vec);
            return *this;
        }
};



//----------- Specialization <T,false,0> ---------





template <typename T>
class ArrayBase<T,false,0> :  virtual public AbstractArray<T>
{
private:
    T *_array;
    void cleanArray(){
        delete[] _array;
        _array = nullptr;
    }
public:
    ArrayBase(size_t size):AbstractArray<T>::AbstractArray(size),_array(new T[size]){
        for(int i = 0; i < size; ++i) 
            _array[i] = T();   
    }
    ArrayBase(const ArrayBase<T, false, 0>& vec):AbstractArray<T>::AbstractArray(vec.getSize())
                                                ,_array(new T[vec.getSize()]){
        for (size_t i = 0; i < vec.getSize(); ++i) 
            _array[i] = vec[i];   
    }
    template<typename T2,bool isPtr2, size_t size2>
        ArrayBase(const ArrayBase<T2, isPtr2, size2>& vec):AbstractArray<T>::AbstractArray(vec.getSize())
                                                            ,_array(new T[vec.getSize()]){
            for (size_t i = 0; i < vec.getSize(); ++i) 
                _array[i] = static_cast<T>(vec[i]);   
        }
    ArrayBase(ArrayBase<T, false, 0>&& vec):AbstractArray<T>::AbstractArray(vec.getSize())
                                                                ,_array(vec.getArrayPtr()){ 
        vec.setArrayPtr(nullptr);
        vec.setSize(0);
    }
    virtual ~ArrayBase(){
        delete[] _array;
    }
    T* getArrayPtr() const{
        return _array;
    }
    void setArrayPtr(T* array){
        _array = array;
    }
    virtual const T& operator[] (ptrdiff_t i) const override final{
        if (size_t(i) >= this->getSize()) 
            throw "Index out of range";
        return _array[i];
    }
    virtual T& operator[] (ptrdiff_t i ) override final{
        if (size_t(i) >= this->getSize())
            throw "Index out of range";
        return _array[i];
    }
    ArrayBase<T,false,0>& operator= (const ArrayBase<T, false, 0>& vec){
        this->copyUncheckContent(*this,vec);
        return *this;
    }
    template<typename T2,bool isPtr2, size_t size2>
        ArrayBase<T,false,0>& operator= (const ArrayBase<T2, isPtr2, size2>& vec){
            this->copyContent(*this,vec);
            return *this;
        }
    ArrayBase<T,false,0>& operator= (ArrayBase<T, false, 0>&& vec){
        if (this->getSize() != vec.getSize())
            throw "Transfert impossible : taille incohérente";
        cleanArray(); 
        setArrayPtr(vec.getArrayPtr());
        vec.setArrayPtr(nullptr);
        vec.setSize(0);
        return *this;
    }

};



//----------- Specialization <T,true,0> ---------



template <typename T>
class ArrayBase<T,true,0> :  virtual public AbstractArray<T>
{
private:
    T **_array;
    void cleanArray(){
        for(int i = 0; i < this->getSize(); ++i) 
        {
            delete _array[i]; 
            _array[i] = nullptr;
        }
        delete[] _array;
        _array = nullptr;
    }
public:
    ArrayBase(size_t size):AbstractArray<T>::AbstractArray(size),_array(new T*[size]){
        for(int i = 0; i < size; ++i) 
            _array[i] = new T();   
    }
    ArrayBase(const ArrayBase<T, true, 0>& vec):AbstractArray<T>::AbstractArray(vec.getSize())
                                                ,_array(new T*[vec.getSize()]){ 
        for (size_t i = 0; i < vec.getSize(); ++i)
            _array[i] = new T(vec[i]);
    }
    template<typename T2,bool isPtr2, size_t size2>
        ArrayBase(const ArrayBase<T2, isPtr2, size2>& vec):AbstractArray<T>::AbstractArray(vec.getSize())
                                                            ,_array(new T*[vec.getSize()]){ 
            for (size_t i = 0; i < vec.getSize(); ++i){
                _array[i] = new T();   
                (*this)[i] = static_cast<T>(vec[i]); 
            }
        }
    ArrayBase(ArrayBase<T, true, 0>&& vec):AbstractArray<T>::AbstractArray(vec.getSize())
                                            ,_array(vec.getArrayPtr()){ 
        vec.setArrayPtr(nullptr);
        vec.setSize(0);
    }
    virtual ~ArrayBase(){
        for(int i = 0; i < this->getSize(); ++i) 
            delete _array[i]; 
        delete[] _array;
    }
    T** getArrayPtr() const{
        return _array;
    }
    void setArrayPtr(T** array){
        _array = array;
    }
    virtual const T& operator[] (ptrdiff_t i) const override final{
        if (size_t(i) >= AbstractArray<T>::getSize()) 
            throw "Index out of range";
        return (*_array[i]);
    }
    virtual T& operator[] (ptrdiff_t i ) override final{
        if (size_t(i) >= AbstractArray<T>::getSize())
            throw "Index out of range";
        return (*_array[i]);
    }
    ArrayBase<T,true,0>& operator= (const ArrayBase<T, true, 0>& vec){
        this->copyUncheckContent(*this,vec);
        return *this;
    }
    template<typename T2,bool isPtr2, size_t size2>
        ArrayBase<T,true,0>& operator= (const ArrayBase<T2, isPtr2, size2>& vec){
            this->copyContent(*this,vec);
            return *this;
        }
    ArrayBase<T,true,0>& operator= (ArrayBase<T, true, 0>&& vec){
        if (this->getSize() != vec.getSize())
            throw "Transfert impossible : taille incohérente";
        cleanArray();
        setArrayPtr(vec.getArrayPtr());
        vec.setArrayPtr(nullptr);
        vec.setSize(0);
        return *this;
    }

};


#endif

