import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import javax.swing.JFrame; 
import javax.swing.JLabel;
import javax.swing.JPanel;
import java.awt.GridLayout;
import java.awt.BorderLayout;
import javax.swing.Box;

class psyje5{
    public static void main(String[] args){
        JFrame guiFrame = new JFrame();
        guiFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        guiFrame.setLocationRelativeTo(null);
        guiFrame.setLayout(new BorderLayout());

        JPanel westPanel = new JPanel(new BorderLayout());

        JPanel westWestPanel = new JPanel(new GridLayout(6,1));
        westWestPanel.add(new ColorLabel(50, 50, Color.GREEN, 1, Color.GRAY));
        westWestPanel.add(new ColorLabel(50, 50, Color.GREEN, 1, Color.GRAY));
        westWestPanel.add(new ColorLabel(50, 50, Color.GREEN, 1, Color.GRAY));
        westWestPanel.add(new ColorLabel(50, 50, Color.GREEN, 1, Color.GRAY));
        westWestPanel.add(new ColorLabel(50, 50, Color.GREEN, 1, Color.GRAY));
        westWestPanel.add(new ColorLabel(50, 50, Color.YELLOW, 1, Color.GRAY));
        westPanel.add(westWestPanel, BorderLayout.WEST);

        JPanel eastWestPanel = new JPanel(new GridLayout(6,1));
        eastWestPanel.add(new ColorLabel(50, 50, Color.YELLOW, 1, Color.GRAY));
        eastWestPanel.add(new ColorLabel(50, 50, Color.GREEN, 1, Color.GRAY));
        eastWestPanel.add(new ColorLabel(50, 50, Color.GREEN, 1, Color.GRAY));
        eastWestPanel.add(new ColorLabel(50, 50, Color.GREEN, 1, Color.GRAY));
        eastWestPanel.add(new ColorLabel(50, 50, Color.GREEN, 1, Color.GRAY));
        eastWestPanel.add(new ColorLabel(50, 50, Color.GREEN, 1, Color.GRAY));
        westPanel.add(eastWestPanel, BorderLayout.EAST);

        westPanel.add(Box.createRigidArea(new Dimension(5, 0)), BorderLayout.CENTER);
 
        guiFrame.add(westPanel, BorderLayout.WEST);

        JPanel eastPanel = new JPanel(new BorderLayout());
        
        JPanel northEastPanel = new JPanel(new GridLayout(2,3));
        northEastPanel.add(new ColorLabel(50, 50, Color.YELLOW, 1, Color.GRAY));
        northEastPanel.add(new ColorLabel(50, 50, Color.YELLOW, 1, Color.GRAY));
        northEastPanel.add(new ColorLabel(50, 50, Color.GREEN, 1, Color.GRAY));
        northEastPanel.add(new ColorLabel(50, 50, Color.GREEN, 1, Color.GRAY));
        northEastPanel.add(new ColorLabel(50, 50, Color.GREEN, 1, Color.GRAY));
        northEastPanel.add(new ColorLabel(50, 50, Color.GREEN, 1, Color.GRAY));
        eastPanel.add(northEastPanel, BorderLayout.NORTH);

        JPanel southEastPanel = new JPanel(new GridLayout(3,3));
        southEastPanel.add(new ColorLabel(50, 50, Color.GREEN, 1, Color.GRAY));
        southEastPanel.add(new ColorLabel(50, 50, Color.GREEN, 1, Color.GRAY));
        southEastPanel.add(new ColorLabel(50, 50, Color.GREEN, 1, Color.GRAY));
        southEastPanel.add(new ColorLabel(50, 50, Color.GREEN, 1, Color.GRAY));
        southEastPanel.add(new ColorLabel(50, 50, Color.GREEN, 1, Color.GRAY));
        southEastPanel.add(new ColorLabel(50, 50, Color.GREEN, 1, Color.GRAY));
        southEastPanel.add(new ColorLabel(50, 50, Color.YELLOW, 1, Color.GRAY));
        eastPanel.add(southEastPanel, BorderLayout.SOUTH);

        guiFrame.add(eastPanel, BorderLayout.EAST);
        guiFrame.add(Box.createRigidArea(new Dimension(5, 0)), BorderLayout.CENTER);

        guiFrame.pack();
        guiFrame.setVisible(true);
    }
}
