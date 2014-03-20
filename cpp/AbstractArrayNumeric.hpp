/* Pierre GERARD - 00379259 - INFO2*/
#ifndef DEF_ABSTRACTARRAYNUMERIC
#define DEF_ABSTRACTARRAYNUMERIC


#include <limits>
#include <type_traits>

#include "AbstractArray.hpp"
#include "ArrayNumeric.hpp"


using namespace std;




// car inclusion circulaire
template <typename T,bool isPtr=true, size_t size = 0 > 
class ArrayNumeric;



template <typename T,bool isPtr=true, size_t size = 0 > 
class AbstractArrayNumeric: virtual public AbstractArray<T>{
public:
    AbstractArrayNumeric(size_t vecSize):AbstractArray<T>::AbstractArray(vecSize){}


    AbstractArrayNumeric& operator- (){
        for (int i = 0; i < this->getSize(); ++i)
        {
            (*this)[i] = -(*this)[i];
        }
        return *this;
    }
    template<typename T2,bool isPtr2, size_t size2>
        AbstractArrayNumeric& operator+=(const AbstractArrayNumeric<T2, isPtr2, size2>& toAdd){
            for (int i = 0; i < this->getSize(); ++i){
                (*this)[i]+=toAdd[i];
            }
            return *this;
        }
    template<typename T2,bool isPtr2, size_t size2>
        AbstractArrayNumeric& operator-=(const AbstractArrayNumeric<T2, isPtr2, size2>& toAdd) {
            for (int i = 0; i < this->getSize(); ++i){
                (*this)[i]-=toAdd[i];
            }
            return *this;
        }
    AbstractArrayNumeric& operator*= (const int number){
        for (int i = 0; i < this->getSize(); ++i)
            (*this)[i] *= number;
        return *this;
    }


    ArrayNumeric<T,isPtr,size> operator+ () const{
        // ISO/IEC 14882:2003(E) 5.3.1 Unary op   (p78)
        // 6 The operand of the unary + operator shall have arithmetic, enumeration, or pointer type and 
        // the result is the value of the argument. Integral promotion is performed on integral or enumeration operands.
        //  The type of the result is the type of the promoted operand.
        if (sizeof(T) >= sizeof(int) or (! is_integral<T>::value))
        {
            ArrayNumeric<T,isPtr,size> toReturn(*this);
            return toReturn;
        }
        else if (numeric_limits<T>::is_signed){ // T test = T(0); test-1; if (test<0) aurait aussi fonctionné
            ArrayNumeric<int,isPtr,size> toReturn(*this);
            return toReturn;
        }
        else{
            ArrayNumeric<unsigned int,isPtr,size> toReturn(*this);
            return toReturn;
        }
    }
    template<typename T2,bool isPtr2, size_t size2>
        inline ArrayNumeric<T,isPtr,size> operator+ (const AbstractArrayNumeric<T2, isPtr2, size2>& rValue) const{
            // on considère qu'on retourne un vecteur d'objet dont le nombre est en mémoire sur le plus de bit
            if (sizeof(T) >= sizeof(T2)){
                ArrayNumeric<T,isPtr,size> toReturn(*this);
                for (std::size_t i = 0; i < this->getSize(); ++i)
                    toReturn[i] += rValue[i] ;
                return toReturn;
            }
            else{
                ArrayNumeric<T2,isPtr,size> toReturn(*this);
                for (std::size_t i = 0; i < this->getSize(); ++i)
                    toReturn[i] += rValue[i] ;
                return toReturn;
            }
        }
    template<typename T2,bool isPtr2, size_t size2>
        inline ArrayNumeric<T,isPtr,size> operator- (const AbstractArrayNumeric<T2, isPtr2, size2>& rValue) const{
            if (sizeof(T) >= sizeof(T2)){
                ArrayNumeric<T,isPtr,size> toReturn(*this);
                for (std::size_t i = 0; i < this->getSize(); ++i)
                    toReturn[i] -= rValue[i] ;
                return toReturn;
            }
            else{
                ArrayNumeric<T2,isPtr,size> toReturn(*this);
                for (std::size_t i = 0; i < this->getSize(); ++i)
                    toReturn[i] -= rValue[i] ;
                return toReturn;
            }
        }
    ArrayNumeric<T,isPtr,size> operator* (const T scalar) const{
        ArrayNumeric<T,isPtr,size> toReturn(*this);
        for (int i = 0; i < this->getSize(); ++i)
            toReturn[i] *= scalar;
        return toReturn;
    }


    // je ne vois pas comment implémenter l'op de multiplication à gauche dans la classe

};





template<typename T2,bool isPtr2, size_t size2>
    inline ArrayNumeric<T2, isPtr2, size2> operator*(const T2 scalar,const AbstractArrayNumeric<T2, isPtr2, size2>& rValue)
    {
        return (rValue*scalar); //  commutative
    }



#endif