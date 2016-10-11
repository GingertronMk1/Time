package zoo;

import java.util.ArrayList;

public class Zoo {
	private String location;
	private int noLocations;
	private static int noZoos;
	private ArrayList<Enclosure> enclosures;
	private ArrayList<Animal> animals;
	
	public String getLocation(){
		return location;
	}
	
	public void setLocation(String location){
		this.location = location;
	}

	public Zoo(String location, int noLocations) {
		this.location = location;
		this.noLocations = noLocations;

		enclosures = new ArrayList<Enclosure>();
		
		this.addZoo();
		for(int i=0; i<noLocations; i++){
			addEnclosure(new Enclosure());
		}
	}
	
	private void addEnclosure(Enclosure enclosure) {
		// TODO Auto-generated method stub
		this.enclosures.add(enclosure);
	}

	public Zoo(){
		this("Unknown", 30);
		this.addZoo();
	}
	
	public void buildNewEnclosure(){
		this.noLocations++;
	}
	
	public void printInfo(){
		System.out.println("There are "+this.noLocations+" enclosures. This one's in "+this.location+".");
	}
	
	public void addZoo(){
		Zoo.noZoos++;
	}
	
	public static int totalZoos(){
		return Zoo.noZoos;
	}
	
	public void addAnimal(Animal animal){
		animals.add(animal);
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Zoo.noZoos = 0;
		System.out.println("It Lives!");
	}

}
