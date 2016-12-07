package MapViewer;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;;

public class TileMap {
	private BufferedReader br;

	private int numCols;
	
	private int numRows;
	
	private int[][] map;
	
	public TileMap(String s) throws NumberFormatException, IOException {
		InputStream in = getClass().getResourceAsStream(s);
		br = new BufferedReader(
					new InputStreamReader(in)
				);
		numCols = Integer.parseInt(br.readLine());
		numRows = Integer.parseInt(br.readLine());
		map = new int[numRows][numCols];
		String delims = "\\s+";
		for(int row = 0; row < numRows; row++) {
			String line = br.readLine();
			String[] tokens = line.split(delims);
			for(int col = 0; col < numCols; col++) {
				map[row][col] = Integer.parseInt(tokens[col]);
			}
		}
	}
	
	public BufferedReader getReader() {return br;};
	
	public int tileCols() {return numCols;};
	public int tileRows() {return numRows;};
	public int[][] getMapValues() {return map;};
	
}
