import java.awt.FlowLayout; 
import java.awt.Font; 
import javax.swing.JFrame; 
import javax.swing.JLabel;

class Psyje5{
    public static void main(String[] args){
        JFrame guiFrame = new JFrame(); // Create a new top level window
        // You can leave the following 3 lines untouched 
        guiFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE); // Close window exits 
        guiFrame.setLocationRelativeTo(null); // centre on screen 
        guiFrame.setLayout( new FlowLayout() ); // Layout : how to layout components 
        // The next line sets the caption
        guiFrame.setTitle("Hello World from Jack Ellis"); // Set a caption/title bar content

        // The following code creates a new label object and adds it to the frame 
        JLabel labelAll = new JLabel(); // Create a new label object 
        labelAll.setText("Hello World from Jack Ellis!"); // Set its message to show 
        labelAll.setFont(new Font("American Typewriter", Font.BOLD, 30)); // Set a font for the label 
        //guiFrame.add(labelAll); // Add the label to the frame, so that it will show

        JLabel labelHello = new JLabel(); // Create a new label object 
        labelHello.setText("Hello"); // Set its message to show 
        labelHello.setFont(new Font("Comic Sans MS", Font.BOLD, 50)); // Set a font for the label 
        guiFrame.add(labelHello); // Add the label to the frame, so that it will show

        JLabel labelWorld = new JLabel(); // Create a new label object 
        labelWorld.setText("World"); // Set its message to show 
        labelWorld.setFont(new Font("Comic Sans MS", Font.BOLD, 50)); // Set a font for the label 
        guiFrame.add(labelWorld); // Add the label to the frame, so that it will show

        JLabel labelFrom = new JLabel(); // Create a new label object 
        labelFrom.setText("From"); // Set its message to show 
        labelFrom.setFont(new Font("Comic Sans MS", Font.BOLD, 50)); // Set a font for the label 
        guiFrame.add(labelFrom); // Add the label to the frame, so that it will show

        JLabel labelJack = new JLabel(); // Create a new label object 
        labelJack.setText("Jack"); // Set its message to show 
        labelJack.setFont(new Font("Comic Sans MS", Font.BOLD, 50)); // Set a font for the label 
        guiFrame.add(labelJack); // Add the label to the frame, so that it will show

        JLabel labelEllis = new JLabel(); // Create a new label object 
        labelEllis.setText("Ellis"); // Set its message to show 
        labelEllis.setFont(new Font("Comic Sans MS", Font.BOLD, 50)); // Set a font for the label 
        guiFrame.add(labelEllis); // Add the label to the frame, so that it will show

        // And this code resizes the frame to be the right size for everything in it 
        guiFrame.pack(); // Resize frame to fit content
        guiFrame.setVisible(true); // Display it – until you do it will not appear
    }
}
