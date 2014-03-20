
package infof202.projetJava;

import java.util.Random;


class Productor extends BoxUser {
    public Productor(MultiBox<Integer> multiBox,String id, Integer actionSequence[]){
        super(multiBox,id,actionSequence);
    }
    public void makeAction(Integer actionIndex){
        Random randomGenerator = new Random();
        Integer value = randomGenerator.nextInt();  // objet aléatoire
        // print pas synchronize par rapport au autre 
        System.out.println("Le "+getIdUser()+" essaye de placer un objet Integer valant "+value+ " en position "+actionIndex);
        getMultiBox().put(actionIndex,value,getIdUser());
        System.out.println("Le "+getIdUser()+" a reussi à placer l'objet Integer en position "+actionIndex);


    }
    
}