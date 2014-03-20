/* Pierre GERARD - 00379259 - INFO2*/
#ifndef DEF_ARRAYABSTRACT
#define DEF_ARRAYABSTRACT

#include <iostream>
#include <string>
#include <vector>
#include <iterator>


using namespace std;

template <typename T>
class AbstractArray {
    size_t _size;
    friend ostream& operator<< (ostream& out, const AbstractArray<T>& vec){
        for (size_t i = 0; i < vec.getSize(); ++i) 
            out << " " << vec[i];
        return out;
        }
    friend istream& operator>> (istream& input, AbstractArray<T>& array){
        // Convention de l'input, on sépare chaque élément de ' '
        // exemple 5 7 9 10 2 est un input de taille 5
        vector<int> vec((istream_iterator<int>(input)), istream_iterator<int>());
        // copy (InputIterator first, InputIterator last, OutputIterator result);
        // back_insert_iterator<Container> back_inserter (Container& x); 
        // source : http://www.cplusplus.com/reference/algorithm/copy/
        copy(istream_iterator<T>(input), istream_iterator<T>(),back_inserter(vec));
        if (vec.size() != array.getSize()){
            throw "Erreur dans l'input : taille incohérente"; 
        }
        for (int i = 0; i < vec.size(); ++i){
            array[i] = vec[i];
        }
        return input;
    }
protected:
    // on defini une méthode d'assignation pour T tel que A<T> = A<T> ici pour eviter de copier 4 fois
    void copyUncheckContent(AbstractArray<T>& array1, const AbstractArray<T>& array2){
        if (&array1 != &array2){ // verif qu'on fait pas a = a;
            if (array1.getSize() != array2.getSize())
                throw "Erreur : taille incohérente";   
            for (size_t i = 0; i < array1.getSize(); ++i) 
                array1[i] = array2[i];
        }
    }
    // on defini une méthode d'assignation pour T tel que A<T> = A<T2> ici pour eviter de copier 4 fois
    template<typename T2>
        void copyContent(AbstractArray<T>& array1, const AbstractArray<T2>& array2){
            if (array1.getSize() != array2.getSize())
                throw "Erreur : taille incohérente";   
            for (size_t i = 0; i < array1.getSize(); ++i) 
                array1[i] = static_cast<T>(array2[i]);
        }
public:
    AbstractArray(size_t size):_size(size){}

    virtual const T& operator[] (ptrdiff_t) const =0;
    virtual T& operator[] (ptrdiff_t) =0;
    size_t getSize () const{
        return _size;
    }
    void setSize (size_t size){
        _size = size;
    }
    operator string() const{ // cast  s = (string) array
        string toReturn;
        for (int i = 0; i < this->getSize(); ++i){
            toReturn += ' ';
            toReturn += ((*this)[i]);
        }
        return toReturn;
    }
};


#endif