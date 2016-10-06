package bike;

public class MountainBike extends Bicycle {
	private boolean frontSusp;
	private boolean rearSusp;

	public MountainBike(int g, int s, boolean f, boolean r) {
		super(g, s);
		frontSusp = f;
		rearSusp = r;
		// TODO Auto-generated constructor stub
	}
	
	public boolean isFull(){
		return frontSusp && rearSusp;
	}
	
	public void printMtn(){
		printInfo();
		System.out.println("Bike having full suspension is " + isFull());
	}

}
