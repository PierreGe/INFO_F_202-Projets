

package infof202.projetJava;

import java.util.Random;



public class Main  {

    public static void main(String[] args) {
        System.out.println("- -  Multibox  - -");
        Integer nbrProductor = 0;
        Integer nbrConsumer = 0;
        try{
            nbrProductor = Integer.parseInt(args[0]); // cast
            nbrConsumer = Integer.parseInt(args[1]); // cast
        }catch (ArrayIndexOutOfBoundsException e) {
           System.err.println("Erreur : 2 arguments doivent être entrés");
        }catch (NumberFormatException e) {
            System.err.println("Erreur: les arguments doivent être des chiffres");
        }

        // la stratégie choisit la strategie permetant de se finir, d'éviter un deadlock, respectant l'endormissement
        // demandé dans l'énnoncé, et avec une taille de MultiBox raisonnable
        // on pourrait faire une statégie avec un grand nombre d'action mais il faudrait pour un prod/cons
        // que lorsque il ne peut pas faire l'action effectuer qu'il teste autre chose au lieu de dormir

         // on utilisera multibox avec des Int dans l'exemple
        if (nbrProductor <= 0 || nbrConsumer <= 0) {
            System.err.println("Erreur : au moins 1 producteur et 1 consommateur necessaire");
            
        }
        else{
            final Consumer consumers[] = new Consumer[nbrConsumer];
            final Productor productors[] = new Productor[nbrProductor];
            // --------- Stratégie -----------
            if (nbrProductor < nbrConsumer) {
                strategyConsGreater(nbrProductor,nbrConsumer ,productors,consumers);
            }
            else if (nbrConsumer < nbrProductor) {
                strategyProdGreater(nbrProductor,nbrConsumer ,productors,consumers);
            }
            else{ // nbrConsumer == Nbr Productor
                strategyProdEqualCons(nbrProductor,nbrConsumer ,productors,consumers);
            }
            // --------- JOIN -----------
            joinThread(nbrProductor,nbrConsumer ,productors,consumers);
            System.out.println("Message de fin de la production/consommation");
       
        }
    }
    private static void strategyProdGreater(int nbrProductor,int nbrConsumer ,Productor[] productors, Consumer[] consumers){
        final Integer differenceProdCons = nbrProductor - nbrConsumer;
        final Integer boxSize = nbrConsumer;
        final MultiBox<Integer> sharedMultiBox = new MultiBox<Integer>(boxSize);

        for (Integer prodNbr = 0;prodNbr < (nbrProductor); ++prodNbr ) {
            Integer actionSequence[];
            if (prodNbr<boxSize) {
                actionSequence = new Integer[2];
                actionSequence[0] = prodNbr;
                actionSequence[1] = prodNbr;
                
            }
            else{
                actionSequence = new Integer[1];
                actionSequence[0] = 0;

            }
            productors[prodNbr] = new Productor(sharedMultiBox,("producteur n°"+prodNbr), actionSequence); 
        }

        for (Integer consNbr = 0;consNbr < nbrConsumer; ++consNbr ) {
            Integer actionSequence[];
            if (consNbr==0) {
                actionSequence = new Integer[1+differenceProdCons+1];
                for (Integer i=0; i<differenceProdCons+1;++i ) {
                    actionSequence[i] = 0;
                }
                actionSequence[actionSequence.length-1] = -1;                   
            }
            else{
                actionSequence = new Integer[1];
                actionSequence[0] = consNbr;
            }

            consumers[consNbr] = new Consumer(sharedMultiBox,("consommateur n°"+consNbr),actionSequence); 
        }

    }
    private static void strategyProdEqualCons(int nbrProductor,int nbrConsumer ,Productor[] productors, Consumer[] consumers){
        final Integer boxSize = nbrConsumer;
        final MultiBox<Integer> sharedMultiBox = new MultiBox<Integer>(boxSize);
        for (Integer i = 0;i < (nbrProductor); ++i ) {
            Integer actionSequence[] = new Integer[2];
            actionSequence[0] = i;
            actionSequence[1] = i;
            productors[i] = new Productor(sharedMultiBox,("producteur n°"+i), actionSequence); 
        
        }
        for (Integer i = 0;i < (nbrConsumer-1); ++i ) {
            Integer actionSequence[] = new Integer[1];
            actionSequence[0] = i;
            consumers[i] = new Consumer(sharedMultiBox,("consommateur n°"+i),actionSequence);
        }
        // dernier consomateur
        Integer actionSequence[] = new Integer[2];
        actionSequence[0] = nbrConsumer-1;
        actionSequence[1] = -1;            
        consumers[consumers.length-1] = new Consumer(sharedMultiBox,("consommateur n°"+(consumers.length-1)),actionSequence);


    }
    private static void strategyConsGreater(int nbrProductor,int nbrConsumer ,Productor[] productors, Consumer[] consumers){
        final Integer differenceProdCons = nbrConsumer - nbrProductor;
        final Integer boxSize = nbrProductor;
        final MultiBox<Integer> sharedMultiBox = new MultiBox<Integer>(boxSize);

        for (Integer prodNbr = 0;prodNbr < (nbrProductor); ++prodNbr ) {
            Integer actionSequence[] = new Integer[1+differenceProdCons];
            for (Integer i = 0; i<(1+differenceProdCons); ++i ) {
                actionSequence[i] = prodNbr;
            }
            productors[prodNbr] = new Productor(sharedMultiBox,("producteur n°"+prodNbr), actionSequence); 
        }

        for (Integer consNbr = 0;consNbr < nbrProductor; ++consNbr ) {
            Integer actionSequence[] = new Integer[1];
            actionSequence[0] = consNbr;
            consumers[consNbr] = new Consumer(sharedMultiBox,("consommateur n°"+consNbr),actionSequence); 
        }
        for (Integer consNbr = nbrProductor; consNbr<nbrConsumer ;++consNbr ) {
            Integer actionSequence[] = new Integer[1];
            actionSequence[0] = -1 ;          
            consumers[consNbr] = new Consumer(sharedMultiBox,("consommateur n°"+consNbr),actionSequence);   
        }

    }
    private static void joinThread(int nbrProductor,int nbrConsumer ,Productor[] productors, Consumer[] consumers){
        for (Integer idx=0;idx<nbrProductor;++idx ) {
            try{
                productors[idx].join();
            } 
            catch ( InterruptedException e ) { 
            }
        }
        for (Integer idx=0;idx<nbrConsumer;++idx ) {
            try{
                consumers[idx].join();
            } 
            catch ( InterruptedException e ) { 
            }
        }
    }
}
