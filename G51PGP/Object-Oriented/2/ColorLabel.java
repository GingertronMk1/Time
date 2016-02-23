import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;

import javax.swing.JLabel;

// Arrggghhh - I had to use US spelling for Color throughout to avoid confusion

public class ColorLabel extends JLabel
{
    /** Colour of main part */
    Color drawColor; 
    /** Colour of border */
    Color borderColor;
    /** Width of border in pixels */
    int borderSize; 

    /**
     * Constructor initialises the object - for a colour and a different coloured border
     * @param width Width of the label - preferred and min size
     * @param height Height of the label - preferred and min size
     * @param color Colour of the main part of the label
     * @param borderWidth Width of the border, in pixels
     * @param borderCol Colour of the border
     */
    public ColorLabel( int width, int height, Color color, int borderWidth, Color borderCol )
    {
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
    public ColorLabel( int width, int height, Color color )
    {
        // Call the other constructor with some default values
        this( width, height, color, 0, null );
    }

    /**
     * This is called by the system and your code needs to draw the component
     * @param g The graphics object that the systems gives you to draw to
     */
    protected void paintComponent(Graphics g)
    {
        //super.paintComponent(arg0);
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
}


