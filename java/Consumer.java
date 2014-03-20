
package infof202.projetJava;

class Consumer extends BoxUser {
    public Consumer(MultiBox<Integer> multiBox,String id, Integer actionSequence[]){
        super(multiBox,id,actionSequence);
    }
    public void makeAction(Integer actionIndex){
        if (actionIndex== -1) { // -1 : valeur sentinelle pour un getAll
            // print pas synchronize par rapport au autre mais bien dans le bon ordre
            System.out.println("Le "+getIdUser()+" essaye de tout prendre");
            getMultiBox().getAll(); // on ne fait rien des objets récupéré
            System.out.println("Le "+getIdUser()+" a reussi à tout prendre");
        }
        else{
            // print pas synchronize par rapport au autre 
            System.out.println("Le "+getIdUser()+" essaye de prendre l'objet en position "+actionIndex);
            Integer value = getMultiBox().getItem(actionIndex,getIdUser());
            System.out.println("Le "+getIdUser()+" a reussi à prendre l'objet en position "+actionIndex+"de valeur "+value);
        }
    }
    
}