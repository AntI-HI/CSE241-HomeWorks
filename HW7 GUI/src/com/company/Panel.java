package com.company;

import javax.swing.*;
import java.awt.*;
import java.awt.event.*;
import java.awt.image.*;

public class Panel extends JPanel {
    private Graphics graph;
    private BufferedImage image;
    private Hex game;
    private int[][] board;
    private Polygon[][] squares;

    private final Color[] colors={Color.GRAY, Color.WHITE, Color.BLACK};

    /**
     * Default constructor for the view.
     */
    public Panel() {

        game = new Hex(8, 0);

        int size = game.getSize();
        board=new int[size][size];

        squares=new Polygon[size][size];

//        String[] opts={"X", "O"};
//        colour=JOptionPane.showOptionDialog(null, "Which side would you like to play as?",
//                "Choose Side", JOptionPane.YES_NO_OPTION, JOptionPane.PLAIN_MESSAGE, null, opts, opts[0]);

        image=new BufferedImage(509, 515, BufferedImage.TYPE_INT_RGB);
        graph=image.getGraphics();
        graph.setColor(new Color(210, 180, 140));
        graph.fillRect(0, 0, 509, 515);

        drawBoard();

        addMouseListener(new Mouse());
    }

    /**
     * Redraws the board as represented internally and forces a repaint
     * 	to occur immediately.
     */
    private void drawBoard() {
        graph.setColor(new Color(210, 180, 140));
        graph.fillRect(0, 0, 509, 515);

        for (int row=0; row<game.getSize(); row++) {
            for (int col=0; col<game.getSize(); col++) {
                graph.setColor(getColor(row, col));
                squares[row][col]=drawHex(255/11.5, row * 255/11.5 + col * 510/11.5 + 255/11.5,
                        row*13.5+ 100 +(258/11.5*row));
                graph.fillPolygon(squares[row][col]);
            }
        }

        paintImmediately(getBounds());
    }

    /**
     * Paints the view.
     * @param  g  the Graphics instance to paint to.
     */
    @Override
    public void paintComponent(Graphics g) {
        g.drawImage(image, 0, 0, getWidth(), getHeight(), null);
    }

    /**
     * Creates a regular hexagon for drawing.
     *
     * @param rad The side length of the hexagon
     * @param centerX The x coordinate of the center point
     * @param centerY The y coordinate of the center point
     *
     * @return A hexagon-shaped Polygon
     */
    private Polygon drawHex(double rad, double centerX, double centerY) {
        Polygon p=new Polygon();

        double arc=(Math.PI*2)/6;

        for (int i=0; i<=6; i++) {
            p.addPoint((int)Math.round(centerX+rad*Math.sin(arc*i)), (int)Math.round(centerY+rad*Math.cos(arc*i)));
        }

        return p;
    }

    /**
     * Gets the color of the hexagon at a given point.
     *
     * @param row The x coordinate of the hexagon
     * @param col The y coordinate of the hexagon
     *
     * @return The color of the hexagon at (x, y)
     */
    private Color getColor(int row, int col) {
        return colors[board[row][col]];
    }

    /**
     * Places a piece for the current player at a given location on the board.
     *
     * @param row The x coordinate of the play location
     * @param col The y coordinate of the play location
     */
    private void playAt(int row, int col) {

        if (game.getTurn() == 0 && !isLegalPlay(row, col)) {
            JOptionPane.showMessageDialog(null, "You can't make that move!", "Invalid move!", JOptionPane.PLAIN_MESSAGE);
            return;
        }

        if (game.getTurn() == 0) {
            game.play(row, col);
            board[row][col]=2;

        }
        else if (game.getTurn() == 1) {
            FinalMove loc = game.ParseMove_AI();;
            game.play(loc.getRow(), loc.getCol());
            board[loc.getRow()][loc.getCol()]=1;

        }

        drawBoard();

        if (game.IsGameOver() && game.getTurn() == 0) {
            JOptionPane.showMessageDialog(null, "The computer won. You didn't.", "Victory!", JOptionPane.PLAIN_MESSAGE);
            game.setTurn(-1);
            return;
        } else if (game.IsGameOver() && game.getTurn() == 1) {
            JOptionPane.showMessageDialog(null, "You won.", "Victory!", JOptionPane.PLAIN_MESSAGE);
            game.setTurn(-1);
            return;
        }

        if (game.getTurn() == 0) {
            game.setTurn(1);
            drawBoard();
        }
        else if (game.getTurn() == 1) {
            game.setTurn(0);
            drawBoard();
        }
    }

    /**
     * Checks if a player can legally play at the given location.
     *
     * @param row The x coordinate of the play location
     * @param col The y coordinate of the play location
     *
     * @return true if the location is empty
     */
    private boolean isLegalPlay(int row, int col) {
        Hex.Cell[][] Cells = game.getHexCells();
        return Cells[row][col].getVal() == 0;
    }

    public static boolean onSegment(Point p, Point q, Point r)
    {
        if (q.x <= Math.max(p.x, r.x) && q.x >= Math.min(p.x, r.x)
                && q.y <= Math.max(p.y, r.y) && q.y >= Math.min(p.y, r.y))
            return true;
        return false;
    }

    public static int orientation(Point p, Point q, Point r)
    {
        int val = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);

        if (val == 0)
            return 0;
        return (val > 0) ? 1 : 2;
    }

    public static boolean doIntersect(Point p1, Point q1, Point p2, Point q2)
    {
        int o1 = orientation(p1, q1, p2);
        int o2 = orientation(p1, q1, q2);
        int o3 = orientation(p2, q2, p1);
        int o4 = orientation(p2, q2, q1);

        if (o1 != o2 && o3 != o4)
            return true;

        if (o1 == 0 && onSegment(p1, p2, q1))
            return true;

        if (o2 == 0 && onSegment(p1, q2, q1))
            return true;

        if (o3 == 0 && onSegment(p2, p1, q2))
            return true;

        if (o4 == 0 && onSegment(p2, q1, q2))
            return true;

        return false;
    }

    public static boolean isInside(Polygon polygon, Point p)
    {
        int INF = 10000;
        Point[] pol = new Point[6];
        for(int i = 0; i < 6; i++) {
            pol[i] = new Point();
            pol[i].x = polygon.xpoints[i];
            pol[i].y = polygon.ypoints[i];
        }
        Point extreme = new Point(INF, p.y);

        int count = 0, i = 0;
        do
        {
            int next = (i + 1) % 6;
            if (doIntersect(pol[i], pol[next], p, extreme))
            {
                if (orientation(pol[i], p, pol[next]) == 0)
                    return onSegment(pol[i], p, pol[next]);

                count++;
            }
            i = next;
        } while (i != 0);

        return (count & 1) == 1 ? true : false;
    }
    /**
     * Handles mouse events in the panel.
     */
    private class Mouse extends MouseAdapter {
        /**
         * Handles a left click event and makes a play if necessary.
         *
         * @param e A MouseEvent to process.
         */
        public void mousePressed(MouseEvent e) {
            int eX=e.getX();
            int eY=e.getY();
            Point p = new Point(eX, eY);
            if (game.getTurn()==-1)
                return;

            if (game.getTurn()==1)
                playAt(-1,-1);

            for (int row=0; row<squares.length; row++)
                for (int col=0; col<squares[row].length; col++)
                    if (isInside(squares[row][col], p))
                        playAt(row, col);
//                    if (squares[row][col].contains(eX, eY))   // This code does the same.
//                        playAt(row, col);
        }
    }
}
