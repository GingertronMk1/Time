package bike;

public class Main {
	public static void main(String[] args){
		Bicycle bike = new Bicycle(3, 5);
		bike.speedUp(5);	
		bike.switchLight();
		//bike.printInfo();
		
		MountainBike mb1 = new MountainBike(3,5,true,true);
		MountainBike mb2 = new MountainBike(3,5,true,false);
		mb1.printMtn();
		mb2.printMtn();
	}
}
