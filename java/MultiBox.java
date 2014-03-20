/*

A quelle niveau sont géré les exceptions ?

On est sensé rendre les fichiers java hors archive, mais on doit faire des package ? wut ?

*/


package infof202.projetJava;

import java.util.List;
import java.util.Vector; // les méthodes de vector sont synchronized


public class MultiBox<Type>  {

    private List<Type> _listBox = new Vector<Type>();
    private boolean _starvationLock = false;

    public MultiBox(Integer size){
    for (Integer idx=0; idx<size; ++idx){
            _listBox.add(null); // on initialise la multibox a null pour chaque emplacement
        }
    }

    public synchronized void setStravationLock(boolean lock){
        _starvationLock = lock;
    }

    public synchronized boolean getStarvationLock(){
        return _starvationLock;
    }

    public synchronized List<Type> getBox(){
        return _listBox;
    }

    public synchronized void setBox(List<Type> box){
        _listBox = box;
    }

    public synchronized void put(Integer pos, Type value,String id){
        while (_listBox.get(pos)!=null){ 
            try{
                this.wait();
            } 
            catch ( InterruptedException e ) { 
            }
        }
        getBox().set(pos,value);
        this.notifyAll(); // car si un thread attend un get sur la case
        // mieux que notify qui se contente de prevenir un seul des threads en attente=> le thread choisi dependant de l’environnement => deconseillé
    }
    public synchronized Type getItem(Integer pos,String id){
        while (getBox().get(pos)==null || getStarvationLock() ){ 
            try{
                this.wait();
            } 
            catch ( InterruptedException e ) { 
            }
        }
        Type toReturn = _listBox.get(pos);
        getBox().set(pos,null);
        this.notifyAll(); // car si un thread attend un put sur la case
        // mieux que notify qui se contente de prevenir un seul des threads en attente=> le thread choisi dependant de l’environnement => deconseillé
        return toReturn;
    }
    public synchronized List<Type> getAll(){
        while (getStarvationLock()){  // si un autre thread a deja reserve la boite, on ne pourra plus la reserver une seconde fois.
            try{
                this.wait(); // si les conditions sont pas ok (un autre a la reservation) on attend
            } 
            catch ( InterruptedException e ) { 
            }  
        }
        // il n'y a PAS de file d'attente pour un getAll => peu importe qui l'a dès que c'est possible
        setStravationLock(true);
        while (!boxIsFull()){ 
            try{
                this.wait(); // si les conditions sont pas ok (boite pas pleine) on attend
            } 
            catch ( InterruptedException e ) { 
            }  
        }
        List<Type> toReturn = new Vector<Type>();
        toReturn = getBox();
        emptyBox();
        setStravationLock(false);
        this.notifyAll(); // car si un autre thread attend un put ou get
        // mieux que notify qui se contente de prevenir un seul des threads en attente=> le thread choisi dependant de l’environnement => deconseillé
        return toReturn;
    }

    private synchronized void emptyBox(){
        for (Integer idx=0; idx<_listBox.size();++idx) {
            _listBox.set(idx,null);
        }
    }

    private synchronized boolean boxIsFull(){
        boolean isFull = true;
        for (Integer idx=0; idx < _listBox.size() && isFull;++idx ){
            if (_listBox.get(idx) == null){
                isFull = false;
            }
        }
        return isFull;      
    }

    
}