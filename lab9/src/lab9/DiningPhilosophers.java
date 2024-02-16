/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package lab9;

/**
 *
 * @author Hamza Iqbal
 */

public class DiningPhilosophers {
    
     public static int counter = 0;
     //Number of philosophers
    public static final int n = 5;  
    //Defined set of states of philosophers
    public enum phil_state {EATING, THINKING, HUNGRY};
    
    public static Philosopher[] philosophers;
    public static Semaphore fork; 
    
    
    public static void main(String args[]){
        
        philosophers = new Philosopher[n];
        fork = new Semaphore(n);
        
        
        //Initializing Philosophers
        for(int i = 0; i < n; i++){
            philosophers[i] = new Philosopher();
        }
        
        //Starting every Philosopher
        for(int i = 0; i < n; i++){
            philosophers[i].start();
        }
        
        while(counter >= n){
            try{
                for(int i = 0; i < n; i++){
                    philosophers[i].join();
                }
            }catch(Exception ex){
                System.out.println("Exception");
            }
            System.out.println("All Philosophers have now eaten.");
        }
        
    }

    
    public static class Philosopher extends Thread{
        
        private static int M_ID = 0;
        private int id = 0; 
        private phil_state state;
        private int left; 
        private int right;
        
        public Philosopher(){
            this.id = M_ID;
            M_ID++;
            state = phil_state.HUNGRY;
            
            switch (this.id) {
                case 0:
                    right = 1;
                    left = n-1;
                    break;
                case n-1:
                    right = 0;
                    left = n-2;
                    break;
                default:
                    right = this.id + 1;
                    left = this.id - 1;
                    break;
            }
    }
        
    @Override
    public String toString(){
        
        return "Philosopher: "+ this.id + " State: " + this.state.toString();
        
    }
    
    public synchronized void thinking(){
        
        this.state = phil_state.THINKING;
        System.out.println(this.toString());
        
        try{
            wait(5);
        }catch(Exception ex){
            System.out.println("Exception.");
        }
    }
    
    public synchronized void eating(){
        
    
        this.state = phil_state.EATING;
        System.out.println(this.toString());
        
        try{
            Thread.sleep(5);
        }catch(Exception ex){
            System.out.println("Exception.");
        }
    }
    
    public synchronized void takeForks(){
        
        System.out.println(this.toString());
        System.out.println("Retrieving Forks..\n");
 
        if(philosophers[left].getState_() != phil_state.EATING || philosophers[right].getState_() != phil_state.EATING){
            
            try{
                fork.down();
            }catch(InterruptedException ie){
                System.out.println("Exception.\n");
            }
            
            this.state = phil_state.EATING;
            System.out.println(this.id + "'s Fork is acquired.\n");
        }
        while(philosophers[left].getState_() == phil_state.EATING || philosophers[right].getState_() == phil_state.EATING){
            
            System.out.println(this.id + "'s fork is being used\n");
            thinking();
        }
    
    }
    
    
    public synchronized void putForks(){
        
        this.state = phil_state.THINKING;
        
        try{
            fork.up();
        }catch(InterruptedException ie){
            System.out.println("Error");
        }
        
        counter++;
        }
    
    public phil_state getState_(){
        return this.state;
    }
    
    @Override
    public void run(){
        thinking();
        takeForks();
        eating();
        putForks();
        System.out.println(this.toString());
    }
   
    }
}