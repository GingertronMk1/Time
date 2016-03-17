package CW3;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.EventQueue;
import java.awt.Graphics;

import javax.swing.JFrame;

import javax.swing.JButton;


public class ColorButton extends JButton implements Runnable{
    /** Colour of main part */
    protected Color drawColor; 
    /** Colour of border */
    protected Color borderColor;
    /** Width of border in pixels */
    protected int borderSize; 

    /**
     * Constructor initialises the object - for a colour and a different coloured border
     * @param width Width of the label - preferred and min size
     * @param height Height of the label - preferred and min size
     * @param color Colour of the main part of the label
     * @param borderWidth Width of the border, in pixels
     * @param borderCol Colour of the border
     */
    public ColorButton( int width, int height, Color color, int borderWidth, Color borderCol ){
        borderSize = borderWidth;
        drawColor = color;
        borderColor = borderCol;
        setMinimumSize( new Dimension(width, height) );
        setPreferredSize( new Dimension(width, height) );
        setMaximumSize( new Dimension(width, height) );
    }

    /**
     * Constructor initialises the object - for a solid colour
     * @param width Width of the label - preferred and min size
     * @param height Height of the label - preferred and min size
     * @param color Colour of the main part of the label
     */
    public ColorButton( int width, int height, Color color ){
        // Call the other constructor with some default values
        this( width, height, color, 0, null );
    }

    /**
     * This is called by the system and your code needs to draw the component
     * @param g The graphics object that the systems gives you to draw to
     */
    protected void paintComponent(Graphics g){
        //super.paintComponent(g); // Not used
        if ( borderColor != null )
        {
            g.setColor(borderColor);
            g.fillRect(0, 0, getWidth(), getHeight());
        }
        if ( drawColor != null )
        {
            g.setColor(drawColor);
            g.fillRect(borderSize, borderSize, getWidth()-borderSize*2, getHeight()-borderSize*2);
        }
    }   

    /** Ask the even thread to redraw this button now */
    public void redrawSelf() {
        // First line was my first implementation - make event thread run this
        // EventQueue.invokeLater( new Runnable() { public void run() { repaint(); } } );
        // Then I just reused the current object and made it support the run function
        EventQueue.invokeLater(this);
    }

    /** Implemented run() in this object for passing to invokeLater() above */
    public void run() { 
        repaint(); 
    }

    /** Set the colour of the button AND ask it to redraw now */
    public void setColor(Color newColor) { drawColor = newColor; redrawSelf(); }

    /** Set the border colour of the button AND ask it to redraw now */
    public void setBorderColor(Color newColor) { borderColor = newColor; redrawSelf(); }

    /** Set the border width of the button AND ask it to redraw now */
    public void setBorderWidth(int newWidth) { borderSize = newWidth; redrawSelf(); }

    /** Added to get rid of warning, for serialisation */
    private static final long serialVersionUID = 9041257494324082543L;

    /** Main just does a test of the class */
    public static void main(String[] args){
        JFrame frame = new JFrame();
        frame.add( new ColorButton(500,500,Color.RED,10,Color.WHITE) );
        frame.pack();
        frame.setVisible(true);
    }
}
