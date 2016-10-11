package zoo;

import java.util.ArrayList;

public class ZooCorp {
	private String zooCorpName;
	private ArrayList<Zoo> zoos;

	public void addZoo(Zoo zoo){
		zoos.add(zoo);
	}
	
	public ZooCorp(String name, Zoo zoo){
		this.zooCorpName = name;
		zoos = new ArrayList<Zoo>();
		addZoo(zoo);
	}
	
	public static void main(String[] args) {
		// TODO Auto-generated method stub
	}

}
