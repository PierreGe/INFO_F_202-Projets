/* Pierre GERARD - 00379259 - INFO2*/
#ifndef DEF_ARRAYNUMERIC
#define DEF_ARRAYNUMERIC


#include "AbstractArray.hpp"
#include "ArrayBase.hpp"
#include "AbstractArrayNumeric.hpp"

using namespace std;


template <typename T,bool isPtr, size_t size > 
class ArrayNumeric final: public ArrayBase<T,isPtr,size>,public AbstractArrayNumeric<T,isPtr,size>{
public:

    ArrayNumeric():AbstractArray<T>::AbstractArray(size),
                    ArrayBase<T,isPtr,size>::ArrayBase(size),
                    AbstractArrayNumeric<T,isPtr,size>::AbstractArrayNumeric(size){}
    ArrayNumeric(size_t vecSize):AbstractArray<T>::AbstractArray(vecSize),
                                ArrayBase<T,isPtr,size>::ArrayBase(vecSize),
                                AbstractArrayNumeric<T,isPtr,size>::AbstractArrayNumeric(vecSize){}
    ArrayNumeric(const ArrayNumeric<T, isPtr, size>& vec):AbstractArray<T>::AbstractArray(vec.getSize()),
                                    ArrayBase<T,isPtr,size>::ArrayBase(vec.getSize()),
                                    AbstractArrayNumeric<T,isPtr,size>::AbstractArrayNumeric(vec.getSize()){
        this->copyContent(*this,vec);
    }

    template<typename T2,bool isPtr2, size_t size2>
        ArrayNumeric(const ArrayNumeric<T2, isPtr2, size2>& vec):AbstractArray<T>::AbstractArray(vec.getSize()),
                                        ArrayBase<T,isPtr,size>::ArrayBase(vec.getSize()),
                                        AbstractArrayNumeric<T,isPtr,size>::AbstractArrayNumeric(vec.getSize()){
            this->copyContent(*this,vec);  
        }

    template<typename T2,bool isPtr2, size_t size2>
        ArrayNumeric(const AbstractArrayNumeric<T2, isPtr2, size2>& vec):AbstractArray<T>::AbstractArray(vec.getSize()),
                                                ArrayBase<T,isPtr,size>::ArrayBase(vec.getSize()),
                                                AbstractArrayNumeric<T,isPtr,size>::AbstractArrayNumeric(vec.getSize()){
            this->copyContent(*this,vec);  
          }
    using ArrayBase<T,isPtr,size>::operator=;

};




#endif