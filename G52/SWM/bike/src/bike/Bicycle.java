package bike;

public class Bicycle {
    private int gear;
    private int speed;
    private boolean light;
    
   	Bicycle(int g, int s){
   		gear = g;
   		speed = s;
   	}
                        
    public void setGear(int newValue) {
        gear = newValue;
    }
        
    public void applyBrake(int decrement) {
        speed -= decrement;
    }
   public void speedUp(int increment) {
        speed += increment;
    }
  	
  	public void switchLight(){
  		light = !light;
  	}
  	
  	public void printInfo(){
  		System.out.print("Light is " + light + "\n");
  		System.out.print("Gear is " + gear + "\n");
  		System.out.print("Speed is " + speed + "\n");
  	}
}