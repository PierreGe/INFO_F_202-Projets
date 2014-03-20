/* Pierre GERARD - 00379259 - INFO2*/
#include <iostream>
#include "ArrayBase.hpp"
#include "ArrayNumeric.hpp"


using namespace std;

 
int main()
{
    cout << "-------- Problème de base --------"<<endl;

    cout << "--> Test :construction tableau valeur / taille template" <<endl;
    const size_t sizeBase = 6;
    double doubleExample = 6.1;
    int intExample = 40;
    float floatExample = 8;
    long longExample = 9;
    ArrayBase<double,false,sizeBase> testValFixe;
    testValFixe[0] = doubleExample;
    cout << testValFixe <<endl;

    cout << "--> Test :construction tableau pointeur / taille template" <<endl;
    ArrayBase<int,true,sizeBase> testPtrFixe;
    testPtrFixe[1] = intExample;
    cout << testPtrFixe <<endl;

    cout << "--> Test :construction tableau valeur / taille construction" <<endl;
    ArrayBase<float,false> testValVar(sizeBase);
    testValVar[2] = floatExample;
    cout << testValVar <<endl;

    cout << "--> Test :construction tableau pointeur / taille construction" <<endl;
    ArrayBase<long,true> testPtrVar(sizeBase);
    testPtrVar[3] = longExample;
    cout << testPtrVar <<endl;
    cout << "--> Test :type de base est un pointeur" <<endl;
    /* types de bases sont des pointeurs, l'énoncé dit :
    "Toutefois, si le type de base est lui-même déjà un pointeur, 
    cette distinction formelle n’aura pas lieu."
    Je ne suis pas certain d'avoir bien compris cette partie :
     - J'ai considéré que si le type de base est un pointeur on 
       fait comme si le paramètre est false cad le tableau contient 
        des valeurs (qui ici sont des pointeurs)
    */
    // création de pointeur vers des valeurs
    float* fl1 = new float(4); float* fl2 = new float(5); float* fl3 = new float(6);
    int* i1 = new int(4); int* i2 = new int(5); int* i3 = new int(6); 
    // test :
    // vu mon choix d'implementation il faut ici préciser false
    ArrayBase<float*,false,sizeBase> testTypePtr;
    testTypePtr[0] = fl1; testTypePtr[1] = fl3;
    testTypePtr[2] = fl2; testTypePtr[3] = fl1;
    testTypePtr[4] = fl3; testTypePtr[5] = fl2;
    cout << "impression des pointeurs :" << endl;
    cout << testTypePtr <<endl; 
    // taille a la construction, on peut ne pas préciser true/false
    ArrayBase<int*> testTypePtrBis(sizeBase);
    testTypePtrBis[0] = i1; testTypePtrBis[1] = i1;
    testTypePtrBis[2] = i2; testTypePtrBis[3] = i2;
    testTypePtrBis[4] = i3; testTypePtrBis[5] = i3;
    cout << "impression des pointeurs :" << endl;
    cout << testTypePtrBis <<endl;
    delete fl1; delete fl2; delete fl3;
    delete i1; delete i2; delete i3;

    cout << "--> Test : Assignation" <<endl;
    testPtrVar = testValFixe;
    testValFixe = testValVar;
    testValVar = testPtrFixe;
    testPtrFixe = testPtrVar;
    cout << "Si mauvaise taille ?" <<endl;
    ArrayBase<long,true> testPtrVarBis(10);
    try {
        testPtrVar = testPtrVarBis; // exception est levé à l'exécution
    }
    catch (const char* const& e) {
        // on recoit une ref constante vers un pointeur constant après un
        // throw "message"
        cout << e << endl;
    }
    cout << "Independant ? (valeur en indice 0)" <<endl;
    testValFixe = testPtrVar;
    testValFixe[0] = 2;
    cout << testPtrVar <<" !=";
    cout << testValFixe <<endl;

    cout << "--> Test : Constructeur de copie" <<endl;
    ArrayBase<double,false,sizeBase> testValFixe2(testPtrVar);
    ArrayBase<int,true,sizeBase> testPtrFixe2(testValFixe);
    ArrayBase<float,false> testValVar2(testValVar);
    ArrayBase<int,true> testPtrVar2(testPtrFixe);
    ArrayBase<long,true> testPtrVar2bis(testPtrFixe);
    cout << "Independant ?" <<endl;
    cout << testPtrFixe <<" ==";
    cout << testPtrVar2bis <<" ==";
    testPtrVar2bis[0] = 2;
    cout << testPtrFixe <<" !=";
    cout << testPtrVar2bis <<endl;    
    cout << "Independant ?" <<endl;
    cout << testValVar2 <<" ==";
    cout << testValVar <<" ==";
    testValVar[0] = 2;
    cout << testValVar2 <<" !=";
    cout << testValVar <<endl;

    cout << "--> Test : op Transfert" <<endl;
    ArrayBase<int,false> testValVar3(testValVar); // ici copie / pas transfert
    ArrayBase<int,false> testValVar3bis(testValVar); // ici copie / pas transfert
    ArrayBase<int,true> testPtrVar3(testPtrFixe); // ici copie / pas transfert
    testValVar3 = ArrayBase<int,false>(sizeBase); // op transfert - constructeur
    testPtrVar3 = ArrayBase<int,true>(sizeBase); // op transfert - constructeur
    testValVar3 = move(testValVar3bis); // op transfert forcé
    cout << testValVar3 << endl;
    cout << testPtrVar3 << endl;

    cout << "--> Test : Constructeur de Transfert" <<endl;
    ArrayBase<int,false> testValVar4(move(testValVar3)); // constructeur de transfert
    ArrayBase<int,true> testPtrVar4(move(testPtrVar3)); // constructeur de transfert
    cout << testValVar4 << endl;
    cout << testPtrVar4 << endl;

    cout << "--> Test : Destructeur" <<endl;
    ArrayBase<double,false,sizeBase> *p_testValFixe = new ArrayBase<double,false,sizeBase>;
    ArrayBase<int,true,sizeBase> *p_testPtrFixe2 = new ArrayBase<int,true,sizeBase>;
    ArrayBase<float,false> *p_testValVar2 = new ArrayBase<float,false>(sizeBase);
    ArrayBase<int,true> *p_testPtrVar2 = new ArrayBase<int,true>(sizeBase);
    delete p_testValFixe;
    p_testValFixe = nullptr;
    delete p_testPtrFixe2;
    p_testPtrFixe2 = nullptr;
    delete p_testValVar2;
    p_testValVar2 = nullptr;
    delete p_testPtrVar2;
    p_testPtrVar2 = nullptr;
    cout << "test avec valgrind --tool=memcheck --leak-check=full ./main" <<endl;
    cout << "==37701== " <<endl;
    cout << "==37701== HEAP SUMMARY:" <<endl;
    cout << "==37701==     in use at exit: 0 bytes in 0 blocks" <<endl;
    cout << "==37701==   total heap usage: 176 allocs, 176 frees, 2,353 bytes allocated" <<endl;
    cout << "==37701== " <<endl;
    cout << "==37701== All heap blocks were freed -- no leaks are possible" <<endl;
    cout << "==37701== " <<endl;
    cout << "==37701== For counts of detected and suppressed errors, rerun with: -v" <<endl;
    cout << "==37701== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 2 from 2)" <<endl;

    cout << "--> Test : cin" <<endl;
    const size_t cinSize = 4;
    ArrayBase<int,true,cinSize> testCin;
    cout << "Entrez une array de int avec un retour de ligne \\n a la fin de taille  " << cinSize <<endl;
    try {
        cin.clear();
        cin >>testCin;
        cout << testCin << endl;
    }
    catch (const char* const& e) {
        cout << e << endl;
    }
    try {
        cin.clear();
        cin.ignore(10000, '\n'); // nettoyer le stream ?
        cin >>testCin;
        cout << testCin << endl;
    }
    catch (const char* const& e) {
        cout << e << endl;
    }

    cout << "-------- Premier problème complémentaire --------"<<endl;
    const size_t sizeNumeric = 4;
    ArrayNumeric<int,true,sizeNumeric> numTest;
    ArrayNumeric<int,false,sizeNumeric> numTest2;
    ArrayNumeric<int,true> numTest3(sizeNumeric);
    ArrayNumeric<short,false> numTest4(sizeNumeric);
    numTest[0]  = 1 ; numTest[1]  = 2;numTest[2]  = 1;numTest[3]  = 4;
    numTest2[0] = 7 ; numTest2[1] = 7;numTest2[2] = 3;numTest2[3] = 5;
    numTest3[0] = 4 ; numTest3[1] = 2;numTest3[2] = 9;numTest3[3] = 4;
    numTest4[0] = 5 ; numTest4[1] = 4;numTest4[2] = 3;numTest4[3] = 7;

    cout << "--> Test op+ " <<endl;
    ArrayNumeric<int,true,sizeNumeric> numTestBis = +numTest4;
    cout << numTestBis <<endl;

    cout << "--> Test op- " <<endl;
    cout << numTest2 <<endl;
    numTest = - numTest;

    cout << "--> Test op+= " <<endl;
    cout << numTest2 <<endl;
    cout << "+=" <<numTest <<endl;
    numTest2 += numTest;
    cout << numTest2 <<endl;

    cout << "--> Test op-= " <<endl;
    cout << numTest2 <<endl;
    cout << "-=" << numTest <<endl;
    numTest2 -= numTest;
    cout << numTest2 <<endl;

    cout << "--> Test op+ " <<endl;
    cout << numTest << endl;
    cout << "+" <<numTest2 << endl;
    cout << numTest2 << "==";
    numTest3 = numTest2 + numTest;
    cout << numTest2 << "==";
    numTest3 = numTest + numTest2;
    cout << numTest2 <<endl;
    cout << numTest3 <<endl;

    cout << "--> Test op* scalaire * array " <<endl;
    int scalaire = 8;
    cout << scalaire <<"   *" <<numTest << endl;
    cout << numTest <<endl;
    numTest2 = scalaire * numTest;
    cout << numTest2 << endl;

    cout << "--> Test op* array * scalaire " <<endl;
    int scalaire2 = 6;
    cout << numTest << "  * "<< scalaire2 <<endl;
    numTest2 = numTest * scalaire2;
    cout << numTest2 << endl;

    cout << "--> Test op- " <<endl;
    cout << numTest <<endl;
    cout << "- " << numTest2 <<endl;
    numTest3 = numTest2 - numTest;
    numTest3 = numTest - numTest2;
    cout << numTest3 <<endl;

    cout << "-------- Deuxième problème complémentaire --------"<<endl;
    const size_t sizeString = 3;
    string castedString;

    cout << "--> Test avec char" <<endl;
    ArrayBase<char,true> charArray1(sizeString);
    charArray1[0] = 'c'; charArray1[1] = '+'; charArray1[2] = '+';
    castedString = (string) charArray1; // < cast en string
    cout << charArray1 <<endl;
    cout << castedString << endl;

    cout << "--> Test avec string" <<endl;
    ArrayBase<string,true,sizeString> charArray2;
    charArray2[0] = "INFO"; charArray2[1] = "F"; charArray2[2] = "202";
    castedString = (string) charArray2; // < cast en string
    cout << charArray2 <<endl;
    cout << castedString << endl;

    cout << "--> Test avec char*" <<endl;
    ArrayBase<char*,false,sizeString> charArray3;
    char char0[] = "Langages"; 
    char char1[] = "de"; 
    char char2[] = "programmation"; 
    charArray3[0] = char0; charArray3[1] = char1; charArray3[2] = char2;
    castedString = (string) charArray3; // < cast en string
    cout << charArray3 <<endl;
    cout << castedString << endl;
    ArrayBase<char*> charArray3bis(sizeString);
    charArray3bis[0] = char0; charArray3bis[1] = char1; charArray3bis[2] = char2;
    castedString = (string) charArray3bis;
    cout << charArray3bis <<endl;
    cout << castedString << endl;

    return 0;
}




