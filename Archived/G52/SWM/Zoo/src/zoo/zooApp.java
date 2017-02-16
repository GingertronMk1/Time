package zoo;

public class zooApp {
	public zooApp() {
	}

	public static void main(String[] args) {
		/*
		Zoo zoo1 = new Zoo();
		Zoo zoo2 = new Zoo("Grimsby", 12);
		zoo1.printInfo();
		zoo2.printInfo();
		*/
		Zoo zoo1 = new Zoo("Hull", 3);
		Zoo zoo2 = new Zoo("York", 4);
		Zoo zoo3 = new Zoo("Bridlington", 5);
		Zoo zoo4 = new Zoo("Driffield", 6);
		Zoo zoo5 = new Zoo("Brisbane", 19);
		ZooCorp zooCorp1 = new ZooCorp("Globex", zoo1);
		System.out.println("There are "+Zoo.totalZoos()+" zoos.");
		}

}
