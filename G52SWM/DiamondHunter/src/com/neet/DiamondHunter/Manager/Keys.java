// Contains an array of current key state
// previous key state. A value of true
// means the key is pressed.

// The GamePanel KeyListener will update the array.
// All GameStates now have a handleInput() function
// in order to keep all keyboard input operations
// on the game thread rather than on the EDT to avoid
// problems.

package com.neet.DiamondHunter.Manager;

import java.awt.event.KeyEvent;

public class Keys {
	
	public static final int NUM_KEYS = 8;
	
	public static boolean keyState[] = new boolean[NUM_KEYS];
	public static boolean prevKeyState[] = new boolean[NUM_KEYS];
	
	public static int K1 = 0;
	public static int K2 = 1;
	public static int K3 = 2;
	public static int K4 = 3;
	public static int K5 = 4;
	public static int K6 = 5;
	public static int K7 = 6;
	public static int K8 = 7;
	
	public static int keySet(int i, boolean b) {
		if(i == KeyEvent.VK_UP) keyState[K1] = b;
		else if(i == KeyEvent.VK_LEFT) keyState[K2] = b;
		else if(i == KeyEvent.VK_DOWN) keyState[K3] = b;
		else if(i == KeyEvent.VK_RIGHT) keyState[K4] = b;
		else if(i == KeyEvent.VK_SPACE) keyState[K5] = b;
		else if(i == KeyEvent.VK_ENTER) keyState[K6] = b;
		else if(i == KeyEvent.VK_ESCAPE) keyState[K7] = b;
		else if(i == KeyEvent.VK_F1) keyState[K8] = b;
		return 0;
	}

	public static int update() {
		for(int i = 0; i < NUM_KEYS; i++) {
			prevKeyState[i] = keyState[i];
		}
		return 0;
	}
	
	public static boolean isPressed(int i) {
		return keyState[i] && !prevKeyState[i];
	}
	
	public static boolean isDown(int i) {
		return keyState[i];
	}
	
	public static boolean anyKeyDown() {
		for(int i = 0; i < NUM_KEYS; i++) {
			if(keyState[i]) return true;
		}
		return false;
	}
	
	public static boolean anyKeyPress() {
		for(int i = 0; i < NUM_KEYS; i++) {
			if(keyState[i] && !prevKeyState[i]) return true;
		}
		return false;
	}
	
}
