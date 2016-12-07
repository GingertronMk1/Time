package MapViewer;

import java.awt.image.BufferedImage;
import java.io.IOException;
import javax.imageio.ImageIO;
import MapViewer.Tile;
import javafx.embed.swing.SwingFXUtils;
import javafx.scene.image.WritableImage;

public class TileSet {
	private BufferedImage tileSet, subImage;
	private int tilesAcross;
	private WritableImage[] subImageWritable;
	private Tile[][] tiles;

	
	
	public TileSet(String s, int tileSize) throws IOException {
		tileSet = ImageIO.read(
				getClass().getResourceAsStream("/Tilesets/testtileset.gif")
			);
		tilesAcross = tileSet.getWidth() / tileSize;

		subImageWritable = new WritableImage[2*tilesAcross];
		tiles = new Tile[2][tilesAcross];
		
		for(int col = 0; col < tilesAcross; col++) {
			subImage = tileSet.getSubimage(
						col * tileSize,
						0,
						tileSize,
						tileSize
					);
			tiles[0][col] = new Tile(subImage, Tile.NORMAL);
			subImage = tileSet.getSubimage(
						col * tileSize,
						tileSize,
						tileSize,
						tileSize
					);
			tiles[1][col] = new Tile(subImage, Tile.BLOCKED);
		}

		for (int p = 0; p < 2; p++) {
			for (int q = 0; q < tilesAcross; q++) {
				int index = (tilesAcross*p)+q;
				subImageWritable[index] = new WritableImage(tileSize, tileSize);
				subImageWritable[index] = SwingFXUtils.toFXImage(tiles[p][q].getImage(), subImageWritable[index]);
			}
		}
		
	}
	
	public BufferedImage getImage() {return tileSet;};
	
	public int getTilesAcross() {return tilesAcross;};
	
	public WritableImage[] getTileArray() {return subImageWritable;};
	
	
	
}
