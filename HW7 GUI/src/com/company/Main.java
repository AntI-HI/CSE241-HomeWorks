package com.company;

import javax.swing.JFrame;

public class Main {

    public static void main(String[] args) {

        JFrame frame=new JFrame("Hex");
        frame.setSize(525, 550);
        frame.setLocation(100, 100);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setContentPane(new Panel());
        frame.setVisible(true);
    }
}
