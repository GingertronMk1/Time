package MapViewer;

 import java.awt.image.BufferedImage;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

import javax.imageio.ImageIO;

import MapViewer.Tile;

import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.image.ImageView;
import javafx.scene.image.WritableImage;
import javafx.scene.paint.Color;
import javafx.scene.Group;
import javafx.stage.Stage;
import javafx.embed.swing.SwingFXUtils;
 
public class Main extends Application {

	public static void main(String[] args) {
        launch(args);
    }
    
    @Override
    public void start(Stage stage) throws IOException {    	
    	//Initialising a window for everything to go in
        stage.setTitle("Map Viewer");
		Group root = new Group();
		Scene scene = new Scene(root);
		scene.setFill(Color.WHITE);
		
		//Importing the map file
		InputStream in = getClass().getResourceAsStream("/Maps/testmap.map");
		BufferedReader br = new BufferedReader(
					new InputStreamReader(in)
				);
		
		//Importing the tile set
		BufferedImage tileset = ImageIO.read(
				getClass().getResourceAsStream("/Tilesets/testtileset.gif")
			);
		
		//IMAGE THINGS
		final int tileSize = 16;
		int numTilesAcross = tileset.getWidth() / tileSize;
		BufferedImage subimage = null;
		WritableImage subimageWritable[] = new WritableImage[2*numTilesAcross];
		
		Tile[][] tiles = new Tile[2][numTilesAcross];
		
		for(int col = 0; col < numTilesAcross; col++) {
			subimage = tileset.getSubimage(
						col * tileSize,
						0,
						tileSize,
						tileSize
					);
			tiles[0][col] = new Tile(subimage, Tile.NORMAL);
			subimage = tileset.getSubimage(
						col * tileSize,
						tileSize,
						tileSize,
						tileSize
					);
			tiles[1][col] = new Tile(subimage, Tile.BLOCKED);
		}

		for (int p = 0; p < 2; p++) {
			for (int q = 0; q < numTilesAcross; q++) {
				int index = (numTilesAcross*p)+q;
				subimageWritable[index] = new WritableImage(16, 16);
				subimageWritable[index] = SwingFXUtils.toFXImage(tiles[p][q].getImage(), subimageWritable[index]);
			}
		}


		
		// TEXT THINGS
		int numCols = Integer.parseInt(br.readLine());
		int numRows = Integer.parseInt(br.readLine());
		int [][] map = new int[numRows][numCols];
		String delims = "\\s+";
		for(int row = 0; row < numRows; row++) {
			String line = br.readLine();
			String[] tokens = line.split(delims);
			for(int col = 0; col < numCols; col++) {
				map[row][col] = Integer.parseInt(tokens[col]);
			}
		}
		
		int xcoord = 0;
		int ycoord = 0;
		
		//MAP THINGS
		for (int i = 0; i < numRows; i++) {
			ycoord = 0;
			for (int j = 0; j < numCols; j++) {
				System.out.format("i = %d, j = %d, map[i][j] = %d%n", i, j, map[i][j]);
				ImageView iv1 = new ImageView();
				iv1.setImage(subimageWritable[map[i][j]]);
				iv1.setX(xcoord);
				iv1.setY(ycoord);
				root.getChildren().add(iv1);
				ycoord += 16;
			}
			xcoord += 16;
		}
		
		stage.setTitle("ImageView");
        //stage.setWidth(640);
        //stage.setHeight(500);
        stage.setScene(scene); 
        stage.sizeToScene(); 
        stage.show();
    }

}