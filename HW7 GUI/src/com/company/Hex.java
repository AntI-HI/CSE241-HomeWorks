package com.company;

import com.company.FinalMove;

import java.util.Random;
import java.util.Scanner;
import java.util.concurrent.atomic.AtomicBoolean;

// MAIN Game Class. Everything about Hex game is contained within this class.
public class Hex {
    public static final int DOT = 0;
    public static final int X = 1;
    public static final int O = 2;
    private int hexSize;
    private int opponent;
    private int turn;
    private int winSituation;
    private int userMarked;
    private int opponentMarked;
    private boolean end;
    private AI_POS_List posList;
    private Cell[][] hexCells;

    public class Cell {

        private int row;
        private int col;
        private int val;        // Keeps the corresponding value for the particular location on board.
        private boolean visited;// Indicates the node has been visited or not. This is gonna help traverse the adjacent.

        public Cell() {
            val = 0;
            visited = false;
        }
        public Cell(int Row, int Col) {
            row = Row;
            col = Col;
            val = 0;
            visited = false;
        }
        public int getRow() { return row; }
        public int getCol() { return col; }
        public int getVal() { return val; }
        public boolean getVisited() { return visited; }

        public void setVal(int newVal) { val = newVal; }
        public void setVisited(boolean newVal) { visited = newVal; }
    }
    /*
    This Struct keeps the necessary informations whenever the AI Attempts to make a move.
    */
    private class AI_POS_List
    {
        private int size;               // Keeps the AI_ROW and AI_COL's current sizes.
        private int rightColDifference;   // This attributs keeps the best position difference for right side of the board
        private int leftColDifference; // This attributs keeps the best position difference for left side of the board
        private int AI_ROW[];             // Keeps the ROWs for Moves that's been played by AI
        private int AI_COL[];             // Keeps the COLs for Moves that's been played by AI

        // Constructor that assigns necessary table informations.
        public AI_POS_List(int hexSize) {
            size = 0;
            rightColDifference = hexSize;
            leftColDifference = hexSize;
            AI_ROW = new int[hexSize*hexSize/2];
            AI_COL = new int[hexSize*hexSize/2];
        }
        public AI_POS_List() {
            AI_ROW = new int[26*26/2];
            AI_COL = new int[26*26/2];
        }

        public int getSize() { return size; }
        public int getRightColDifference() { return rightColDifference; }
        public int getLeftColDifference() { return leftColDifference; }
        public int getRow(int idx) { return AI_ROW[idx]; }
        public int getCol(int idx) { return AI_COL[idx]; }

        // Sets the positions to AI_ROW and AI_COL to save the AI progress.
        public void SetPosition(int row, int col) {
            AI_ROW[size] = row;
            AI_COL[size] = col;
            size++;
        }
        public void setSize(int newSize) { size = newSize; }
        public void setRightColDifference(int newVal) { rightColDifference = newVal;}
        public void setLeftColDifference(int newVal) { leftColDifference = newVal; }
        public void setRow(int idx, int newVal) { AI_ROW[idx] = newVal; }
        public void setCol(int idx, int newVal) { AI_COL[idx] = newVal; }
    }




    public FinalMove ParseMove_AI(){
        int row;
        int col;
        Random rand = new Random();

        if(posList.getSize() == 0){
            do {
                row = rand.nextInt(hexSize-1);
                col = rand.nextInt(hexSize-1);
            } while (hexCells[row][col].getVal() != DOT);

            posList.SetPosition(row, col);
            posList.setLeftColDifference(col);
            posList.setRightColDifference(col);
            hexCells[row][col].setVal(X);
            FinalMove finalMove = new FinalMove();
            finalMove.setRow(row);
            finalMove.setCol(col);
            return finalMove;
        }
        else {
            FinalMove finalMove = SimulateMoves();
            return finalMove;
            // hexCells[finalMove.getRow()][finalMove.getCol()].setVal(X);
        }
    }

    private void ParseMove() {
        String alphabet = "abcdefghijklmnopqrstuvwxyz";
        boolean alpha = true;
        int row = 0, col = 0;
        boolean breakLoop = false;
        String move;
        AtomicBoolean isCommand = new AtomicBoolean(); //This becames true if input entered is LOAD or SAVE or MENU Command.
        int currentTurn = turn;

        do {
            alpha = true;
            isCommand.set(false);
            move = GetMove();

            if (isCommand.get()) {
                if (currentTurn != turn || end)
                    return;
                if (turn == 0)  // Player 1
                    System.out.println("Player 1! Make Your Move: ");

                else if (turn == 1)  // Player 2
                    System.out.println("Player 2! Make Your Move: ");
            }
            else {
                if(move.length() == 2)
                    for (int i=0; i < move.length(); ++i)
                        if (alpha){
                            col = alphabet.indexOf(move.charAt(i));
                            alpha = false;
                        }
                        else
                            row = move.charAt(i) - '0';
            else {
                    row = move.charAt(1) - '0';
                    col = alphabet.indexOf(move.charAt(0));
                }
                if (turn == 0 && hexCells[row-1][col].getVal() == DOT){
                    play(row-1, col);
                    breakLoop = true;
                }
                else if (turn == 1 && hexCells[row-1][col].getVal() == DOT) {
                    play(row-1, col);
                    breakLoop = true;
                }
                else { System.out.println("Make a valid Move: "); }
            }
        } while(!breakLoop);
    }
    private String GetMove(){
        String move = new String();
        boolean breakloop = false;
        Scanner input = new Scanner(System.in);

        do {

            move = input.nextLine();
            if (move.length() == 2 && move.charAt(0) >= 'a' && move.charAt(0) < 'a' + hexSize &&
                    move.charAt(1) >= '1' && move.charAt(1) < '1' + hexSize)

                breakloop = true;

            else if (hexSize > 9 && move.length() == 3 && move.charAt(0) >= 'a' && move.charAt(0) < 'a' + hexSize && move.charAt(1) >= '1' &&
                    move.charAt(1) < '1'+hexSize && move.charAt(2) >= '0' && move.charAt(2) < '0' + hexSize)

                breakloop = true;

            else System.out.println("Invalid Move! Make Your Move Again: ");

        } while (!breakloop);

        return move;
    }

    private FinalMove SimulateMoves() {
        int col;
        int row;
        int finalRowMove = 0;
        int finalColMove = 0;
        int leftCol = posList.getCol(posList.getSize() - 1);
        int rightCol = leftCol;
        boolean foundMove = false;

        FinalMove finalMove = new FinalMove();

        for(int i = posList.getSize()-1; i >= 0; --i) {
            row = posList.getRow(i);
            col = posList.getCol(i);

            if (IsValidAI(row, col-1)){
                leftCol = col-1;
                if (leftCol < posList.getLeftColDifference()) {
                    posList.setLeftColDifference(leftCol);

                    finalRowMove = row;
                    finalColMove = col-1;

                    foundMove = true;

                    break;
                }
            }
            if(IsValidAI(row+1, col-1)){

                leftCol = col-1;
                if (leftCol < posList.getLeftColDifference()) {
                    posList.setLeftColDifference(leftCol);

                    finalRowMove = row+1;
                    finalColMove = col-1;

                    foundMove = true;

                    break;
                }
            }
            if(IsValidAI(row, col+1)){
                rightCol = col+1;
                if (rightCol > posList.getRightColDifference()) {
                    posList.setRightColDifference(rightCol);

                    finalRowMove = row;
                    finalColMove = col+1;
                    foundMove = true;

                    break;
                }
            }
            if(IsValidAI(row-1, col+1)){
                rightCol = col+1;
                if (rightCol > posList.getRightColDifference()) {
                    posList.setRightColDifference(rightCol);

                    finalRowMove = row-1;
                    finalColMove = col+1;
                    foundMove = true;

                    break;
                }
            }
        }

        if (!foundMove){

            Random rand = new Random();

            do {
                row = rand.nextInt(hexSize-1);
                col = rand.nextInt(hexSize-1);
            }while (hexCells[row][col].getVal() != DOT);

            posList.setLeftColDifference(col);
            posList.setRightColDifference(getSize() - col);

            finalRowMove = row;
            finalColMove = col;
        }

        posList.SetPosition(finalRowMove, finalColMove);

        finalMove.setRow(finalRowMove);
        finalMove.setCol(finalColMove);

        System.out.println("AI made move: " + (char)('a' + finalMove.getCol()) + " " + finalMove.getRow() + 1);

        return finalMove;
    }
    private boolean IsValidAI(int row, int col) {
        if (row >= 0 && row < hexSize && col >= 0 && col < hexSize && hexCells[row][col].getVal() == DOT)
            return true;
        return false;
    }
    private boolean IsValidP1(int row, int col) {
        if (row >= 0 && row < hexSize && col >= 0 && col < hexSize &&
                hexCells[row][col].getVal() == O && !hexCells[row][col].getVisited()){

            hexCells[row][col].setVisited(true);
            return true;
        }
        else if (row >= 0 && row < hexSize && col >= 0 &&
                col < hexSize && hexCells[row][col].getVal() == DOT) {

            hexCells[row][col].setVisited(true);
        }
        return false;
    }
    private boolean IsValidP2(int row, int col) {
        if (row >= 0 && row < hexSize && col >= 0 && col < hexSize &&
                hexCells[row][col].getVal() == X && !hexCells[row][col].getVisited()){

            hexCells[row][col].setVisited(true);
            return true;
        }
        else if (row >= 0 && row < hexSize && col >= 0 &&
                col < hexSize && hexCells[row][col].getVal() == DOT) {

            hexCells[row][col].setVisited(true);
        }
        return false;
    }
    private void ResetVisiteds() {
        for (int i = 0; i < hexSize; ++i)
            for (int j = 0; j < hexSize; ++j)
                hexCells[i][j].setVisited(false);
    }
    private boolean CheckP1(int row, int col, boolean found){
        if (!IsValidP1(row, col))
            return false;

        if (row == hexSize-1 && hexCells[row][col].getVal() == O) {
            hexCells[row][col].setVisited(true);
            return true;
        }

        found = CheckP1(row-1, col, found) ||
                CheckP1(row-1, col+1, found) ||
                CheckP1(row, col+1, found) ||
                CheckP1(row+1, col, found) ||
                CheckP1(row+1, col-1, found) ||
                CheckP1(row, col-1, found);

        return found;
    }
    private boolean CheckP2(int row, int col, boolean found) {

        if (!IsValidP2(row, col))
            return false;

        if (col == hexSize-1 && hexCells[row][col].getVal() == X) {
            hexCells[row][col].setVisited(true);
            return true;
        }

        found = CheckP2(row-1, col, found) ||
                CheckP2(row-1, col+1, found) ||
                CheckP2(row, col+1, found) ||
                CheckP2(row+1, col, found) ||
                CheckP2(row+1, col-1, found) ||
                CheckP2(row, col-1, found);

        return found;
    }
    private void MakeMove_AI(){
        if (turn == 0) { // Player 1
            System.out.println("Player 1! Make Your Move: ");
            ParseMove();
        }
        else if (turn == 1) { // AI
            System.out.println("Player 2! Make Your Move: ");
            play();
        }
    }

    private void MakeMove() {
        if (turn == 0)  // Player 1
            System.out.println("Player 1! Make Your Move: ");

        else if (turn == 1)  // Player 2
            System.out.println("Player 2! Make Your Move: ");

        ParseMove();
    }

    private void createCells() {
        hexCells = new Cell[hexSize][hexSize];
        for (int i=0; i < hexSize; ++i) {
            for (int j=0; j < hexSize; ++j)
                hexCells[i][j] = new Cell(i, j);
        }
    }



    public Hex(int hexSize, int opponent){
        this.hexSize = hexSize;
        this.opponent = opponent;
        this.turn = 0;
        this.winSituation = 0;
        this.userMarked = 0;
        opponentMarked = 0;
        this.end = false;
        posList = new AI_POS_List(hexSize);
        createCells();

    }
    public Hex() {
        hexSize = 0;
        opponent = 0;
        turn = 0;
        winSituation = 0;
        userMarked = 0;
        opponentMarked = 0;
        end = false;
        playGame();
    }


    public int getSize() { return hexSize; }
    public int getOpponent() { return opponent; }
    public int getTurn() { return turn; }
    public int getWinSituation() { return winSituation; }
    public AI_POS_List getPosList() { return posList; }
    public Cell[][] getHexCells() { return hexCells; }
    public int getWidth() { return hexSize; }
    public int getHeight() { return hexSize; }
    public int getUserMarked() { return userMarked; };
    public int getOpponentMarked() { return opponentMarked; }

    public void setSize(int newSize) {
        if(newSize < 5){
            System.out.println("Sorry. You Entered the wrong value!! Terminating");
            System.exit(1);
        }
        hexSize = newSize;
    }
    public void setOpponent(int newOpponent) {
        if (newOpponent != 0 && newOpponent != 1) {
            System.out.println("You can only type the value opponent 0 or 1!! Terminating");
            System.exit(1);
        }
        opponent = newOpponent;
    }
    public void setTurn(int newTurn) {
        if (newTurn == -1)
            return;
        if (newTurn != 0 && newTurn != 1) {
            System.out.println("You can only type the value turn 0 or 1!! Terminating");
            System.exit(1);
        }
        turn = newTurn;
    }
    public void setWinSituation(int newVal) { winSituation = newVal; }
    public void setUserMarked() { ++userMarked; }
    public void setOpponentMarked() { ++opponentMarked; }
    public void setCell(int row, int col, int val) { hexCells[row][col].setVal(val); }

    public void DrawTable() {
        System.out.print(" ");
        for(char l = 'a'; l < 'a' + hexSize; ++l)
            System.out.print(l + " ");
        System.out.println();

        for (int i = 0; i < hexSize; ++i) {
            System.out.print(1 + i);
            if(i < 9)
                for (int k = 0; k < i; ++k)
                    System.out.print(" ");
            else
                for (int k = 1; k < i; ++k)
                    System.out.print(" ");

            for (int j = 0; j < hexSize; ++j)
                switch(hexCells[i][j].getVal()){
                    case 0:
                        System.out.print(". ");
                        break;
                    case 1:
                        if (winSituation == 1)
                            System.out.print("X ");
                        else
                            System.out.print("x ");
                        break;
                    case 2:
                        if (winSituation == 2)
                            System.out.print("O ");
                        else
                            System.out.print("o ");
                        break;
                }
            System.out.println();
        }
    }

    public void play() {
        ParseMove_AI();
        setOpponentMarked();
    }

    public void play(int row, int col){
        if (turn == 0)                      // Player 1
            hexCells[row][col].setVal(O);
        else if (turn == 1)                 // Player 2
            hexCells[row][col].setVal(X);

        setUserMarked();    // Also set the User Marked for Comparing other games.
    }

    public void playGame() {
        System.out.println("Welcome to the Game HEX.");
        System.out.print("Please Enter the Size of the Board (Minimum 5, Maximum 26): ");

        Scanner input = new Scanner(System.in);

        do {
            hexSize = input.nextInt();
            if (hexSize < 5 || hexSize > 26)
                System.out.print("Please enter the size in between limits: ");
        } while(hexSize < 5 || hexSize > 26);

        System.out.print("Who Do You Play Against (Type 0 for AI, Type 1 for Player): ");
        do {
            opponent = input.nextInt();
            if (!(opponent == 0 || opponent == 1))
                System.out.print("Please enter 0 or 1: ");
        }while(!(opponent == 0 || opponent == 1));

        posList.setSize(0);
        posList.setRightColDifference(hexSize);
        posList.setLeftColDifference(hexSize);

        createCells();

        DrawTable();
    }

    public boolean IsGameOver() {
        boolean finished = false;

        int col = 0;
        int row = 0;

        if (turn == 0) {    // Which means check if player1 finished the game
            while (col < hexSize && !finished) {
                if(hexCells[0][col].getVal() == O)
                    finished = CheckP1(0, col, false);

                if (finished) {
                    ResetVisiteds();
                    break;
                }
                else col++;

                // Everytime we check the board first reset all the visited locations.
                ResetVisiteds();
            }

            if(finished) {
                System.out.println("Player1 WIN!");
                winSituation = 2;
                DrawTable();
                end = true;
            }
            turn = 1;
        }
        else if (turn == 1) {   // Which means check if player2 or AI finished the game

            while (row < hexSize && !finished) {

                if(hexCells[row][col].getVal() == X)
                    finished = CheckP2(row, 0, false);

                if (finished) {

                    ResetVisiteds();
                    break;
                }
                else row++;
                // Everytime we check the board first reset all the visited locations.
                ResetVisiteds();
            }

            if(finished) {
                System.out.println( "Player2 WIN!");
                winSituation = 1;
                DrawTable();
                end = true;
            }
            turn = 0;
        }

        return finished;
    }

    public void Update() {
        do {
            if (opponent == 1) {
                MakeMove();
                DrawTable();
            }
            else if (opponent == 0){
                MakeMove_AI();
                DrawTable();
            }
        } while(!IsGameOver());
    }

}
