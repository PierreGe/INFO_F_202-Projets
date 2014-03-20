
package infof202.projetJava;

import java.lang.Thread;

public abstract class BoxUser extends Thread {
    
    private MultiBox<Integer> _multiBox;
    private String _id;
    private Integer _actionSequence[];

    public BoxUser(MultiBox<Integer> multiBox,String id, Integer actionSequence[]){
        setMultiBox(multiBox);
        setId(id);
        setActionSequence(actionSequence);
        start(); // start thread
    }

    public MultiBox<Integer> getMultiBox(){
        return _multiBox;
    }
    public void setMultiBox(MultiBox<Integer> multibox) {
        _multiBox = multibox;
    }
    public String getIdUser(){ // getId() est defini dans Thread
        return _id;
    }
    public void setId(String id){
        _id = id;
    }
    public Integer[] getActionSequence(){
        return _actionSequence;
    }
    public void setActionSequence(Integer actionSequence[]){
        _actionSequence = actionSequence.clone();
    }

    abstract public void makeAction(Integer actionIndex);

    public void run(){

        for (Integer actionIndex=0; actionIndex<getActionSequence().length;++actionIndex ) {
            makeAction(getActionSequence()[actionIndex]);
        }
        System.out.println("Le "+_id+" a fini.");
    }

}