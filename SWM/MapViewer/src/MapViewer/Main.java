package MapViewer;

 import java.io.IOException;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.image.ImageView;
import javafx.scene.image.WritableImage;
import javafx.scene.paint.Color;
import javafx.scene.Group;
import javafx.stage.Stage;
import MapViewer.TileMap;
import MapViewer.TileSet;

 
public class Main extends Application {

	public static void main(String[] args) {
        launch(args);
    }
    
    @Override
    public void start(Stage stage) throws IOException {  
		final int tileSize = 16;
		
		//Importing the map file (THE TEXT ONE)
		TileMap tilemap = new TileMap("/Maps/testmap.map");
		
		//Importing the tile set (THE GIF ONE)
		TileSet tilesetbase = new TileSet("/Tilesets/testtileset.gif", tileSize);		
		WritableImage[] subImageWritable = tilesetbase.getTileArray();

		int numCols = tilemap.tileCols();
		int numRows = tilemap.tileRows();
		int [][] map = tilemap.getMapValues();
		


    	//Initialising a window for everything to go in
        stage.setTitle("Map Viewer");
		Group root = new Group();
		Scene scene = new Scene(root);
		scene.setFill(Color.WHITE);
		
		int xcoord = 0;
		int ycoord = 0;
		
		//Creating and populating a JavaFX Window
		for (int i = 0; i < numRows; i++) {
			ycoord = 0;
			for (int j = 0; j < numCols; j++) {
				ImageView iv1 = new ImageView();
				iv1.setImage(subImageWritable[map[i][j]]);
				iv1.setX(xcoord);
				iv1.setY(ycoord);
				root.getChildren().add(iv1);
				ycoord += tileSize;
			}
			xcoord += tileSize;
		}
		int stageWidth = numCols * tileSize;
		int stageHeight = numRows * tileSize;
		stage.setTitle("ImageView");
        stage.setWidth(stageWidth);
        stage.setHeight(stageHeight);
        stage.setScene(scene); 
        stage.sizeToScene(); 
        stage.show();
    }

}